# RamFuzz

Format-aware fuzzing with LLM-synthesized binary templates and violation-guided mutations. Built on top of [FormatFuzzer](https://github.com/uds-se/FormatFuzzer).

RamFuzz automatically synthesizes format components and their default value sets using LLMs, then implements a custom mutator for AFL++ that systematically violates these default values to trigger edge cases and expose spatial memory corruptions.

## Overview

RamFuzz has two core components:

1. **Component Synthesis** -- LLM-driven enumeration of format components, fields, types, and valid value sets, stored as JSON specifications. LLM-generated binary templates (.bt) enable structure-aware parsing and mutation.

2. **Violation-Guided Mutation** -- A custom AFL++ mutator that parses seed files using the generated binary templates, identifies field positions via the parse tree, and assigns non-default values guided by an epsilon-greedy coverage feedback scheduler.

### Three .so Variants

For each format, `build.sh` produces three shared libraries:

| Variant | Description |
|---------|-------------|
| `{fmt}_enhanced.so` | Pure FormatFuzzer with enhanced .bt (no violation) |
| `{fmt}_enhanced_violation.so` | + violation with random field selection |
| `{fmt}_enhanced_violation_cov.so` | + violation with coverage-guided scheduling |

## Supported Formats

MP4, MP3, TIFF, JPEG, PNG, GIF, BMP, AVI, WAV, PCAP, ELF, PDF, FLV

## Project Structure

```
.
├── templates/                      # .bt binary template source files
│   └── *_enhanced.bt               # LLM-generated enhanced templates
├── build/                          # Compiled artifacts (.so, .cpp)
├── ComponentEnum/output/<format>/  # Per-format JSON specifications
│   ├── 01_initial_components.json
│   ├── 02_components_after_consistency.json
│   ├── 03_subcomponents.json
│   └── 04_type_values.json         # Field types + valid value sets
├── build.sh                        # Build script (.bt -> .so variants)
├── ffcompile                       # .bt -> .cpp compiler
├── bt.h                            # FormatFuzzer core (with field collection hook)
├── fuzzer.cpp                      # AFL++ custom mutator (with violation calls)
├── fuzzer_orig.cpp                 # Original mutator (no violation)
├── field_collector.h               # Field collection interface
├── field_collector_stub.c          # Stub for origin builds
├── violation_postproc.h            # Violation API
├── violation_postproc.c            # Violation (random selection)
├── violation_postproc_cov.c        # Violation (coverage-guided scheduling)
├── json_reader.h                   # JSON parser interface
├── json_reader.c                   # Minimal JSON parser for 04_type_values.json
└── AFLplusplus                     # AFL++ (submodule)
```

## Quick Start

### Prerequisites

- GCC 12+ (with C++17 support)
- Boost (for `boost/crc.hpp`)
- zlib (`-lz`)
- AFL++ (included as submodule)

On HPC systems:
```bash
module load gcc/12.2.0 boost/1.80.0
```

### Step 1: Build the .so Libraries

Build all three variants for a single format:
```bash
./build.sh mp3_enhanced
```

Build all formats:
```bash
for fmt in mp3 mp4 jpeg png gif bmp avi wav pcap elf pdf flv tiff; do
    ./build.sh ${fmt}_enhanced
done
```

Output files are placed in `build/`:
```
build/mp3_enhanced.so
build/mp3_enhanced_violation.so
build/mp3_enhanced_violation_cov.so
```

### Step 2: Build the Target Program with AFL++

Compile the target with AFL++ instrumentation (and optionally ASAN):
```bash
export CC=/path/to/AFLplusplus/afl-gcc
export CXX=/path/to/AFLplusplus/afl-g++

# With ASAN (recommended for bug finding):
export AFL_USE_ASAN=1
export CFLAGS="-fsanitize=address -g"
export LDFLAGS="-fsanitize=address"

cd /path/to/target && ./configure && make
```

### Step 3: Run AFL++ with RamFuzz

**Pure enhanced template (no violation):**
```bash
AFL_CUSTOM_MUTATOR_LIBRARY=/path/to/build/mp3_enhanced.so \
afl-fuzz -d -i seeds/ -o output/ -t 5000 -m none \
  -- /path/to/target @@
```

**With violation (random selection):**
```bash
AFL_CUSTOM_MUTATOR_LIBRARY=/path/to/build/mp3_enhanced_violation.so \
VIOLATION_JSON=/path/to/ComponentEnum/output/mp3/04_type_values.json \
afl-fuzz -d -i seeds/ -o output/ -t 5000 -m none \
  -- /path/to/target @@
```

**With violation + coverage scheduling:**
```bash
AFL_CUSTOM_MUTATOR_LIBRARY=/path/to/build/mp3_enhanced_violation_cov.so \
VIOLATION_JSON=/path/to/ComponentEnum/output/mp3/04_type_values.json \
afl-fuzz -d -i seeds/ -o output/ -t 5000 -m none \
  -- /path/to/target @@
```

### Step 4: Analyze Crashes

Count unique bugs by ASAN stack trace:
```bash
for crash in output/crashes/id:*; do
    timeout 5 /path/to/target "$crash" 2>&1 | \
        grep -E 'ERROR|#[0-9]' | \
        sed 's/==[0-9]*==//g; s/0x[0-9a-f]*//g' | \
        md5sum
done | sort -u | wc -l
```

## Environment Variables

| Variable | Description |
|----------|-------------|
| `AFL_CUSTOM_MUTATOR_LIBRARY` | Path to the `.so` custom mutator |
| `VIOLATION_JSON` | Path to `04_type_values.json` (required for violation variants) |
| `VIOLATION_VERBOSE` | Set to `1` for verbose violation logging |
| `VIOLATION_LOG` | Path to log file (defaults to stderr) |

## JSON Specification Format

`04_type_values.json` defines fields, their types, and valid value sets:

```json
{
  "parent.field_name": {
    "type": "uint16",
    "values": {
      "discrete": [1, 2, 3]
    }
  },
  "header.compression": {
    "type": "uint32",
    "values": {
      "discrete": [1, 5, 7, 8, 32773]
    }
  },
  "box.type": {
    "type": "string",
    "values": {
      "enum": ["moov", "trak", "mdia", "minf"]
    }
  }
}
```

Value types:
- `discrete` -- list of exact valid values (integers)
- `range` -- two-element `[min, max]` interval
- `enum` -- list of valid string values (for FourCC fields)

Fields covering the full type range (e.g., uint32 with range [0, 4294967295]) are automatically filtered out as they cannot be meaningfully violated.

## Algorithm Parameters

| Parameter | Value | Description |
|-----------|-------|-------------|
| Violation probability | 0.5 | Chance of applying violation per mutation round |
| Geometric base (b) | 5/3 | Controls mutation cardinality distribution (b > 1) |
| Epsilon | 0.1 | Exploration rate for field selection |
| Alpha | 0.5 | Coverage vs frequency weight in scoring |
| Lambda | 1.0 | Coverage normalization sensitivity |
| Coverage window | 100 | Rounds for coverage score computation |
| Frequency window | 200 | Rounds for frequency bonus computation |
| Cold start | 50 | Random selection rounds before score-based ranking |

## References

- [FormatFuzzer](https://github.com/uds-se/FormatFuzzer) -- upstream framework
- [FormatFuzzer paper](https://arxiv.org/abs/2109.11277)
- [010 Editor binary templates](https://www.sweetscape.com/010editor/templates.html)
