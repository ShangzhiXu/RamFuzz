# RamFuzz

Format-aware fuzzing with enhanced binary templates and violation-aware mutations. Built on top of [FormatFuzzer](https://github.com/uds-se/FormatFuzzer).

## Project Structure

```
.
├── templates/                  # .bt binary template source files
│   └── *_enhanced.bt           # Enhanced templates
├── build/                      # Compiled artifacts (.so, .cpp, -fuzzer)
├── ComponentEnum/
│   └── output/<format>/        # Per-format JSON specifications
│       ├── 01_initial_components.json
│       ├── 02_components_after_consistency.json
│       ├── 03_subcomponents.json
│       └── 04_type_values.json
├── build.sh                    # Build script (.bt -> .so variants)
├── ffcompile                   # .bt -> .cpp compiler
├── fuzzer.cpp                  # Fuzzer driver (with violation support)
├── fuzzer_orig.cpp             # Fuzzer driver (original)
└── violation_postproc*.c       # Violation post-processing
```

## Building

### Build all variants for a format

```bash
./build.sh <format>_enhanced
```

Produces three `.so` files: `*_enhanced.so`, `*_enhanced_violation.so`, `*_enhanced_violation_cov.so`.

### Build a standalone fuzzer binary

```bash
g++ -I . -std=c++17 -O2 -fPIC -Wall \
    <format>_enhanced.cpp fuzzer_orig.cpp field_collector_stub.c \
    -o <format>_enhanced-fuzzer -lz
```

On HPC systems you may need `module load boost` first.

### Build all formats

```bash
for fmt in mp3 mp4 jpeg png gif bmp avi wav pdf pcap elf flv tiff; do
    ./build.sh ${fmt}_enhanced
done
```

## JSON Specification

Each format has 4 JSON files in `ComponentEnum/output/<format>/`:

| File | Purpose |
|------|---------|
| `01_initial_components.json` | All identified components (flat list) |
| `02_components_after_consistency.json` | Pruned after consistency check |
| `03_subcomponents.json` | Each component with its subfields |
| `04_type_values.json` | Type, valid values, ranges, and constraints for every field |

`04_type_values.json` entry example:

```json
{
  "IHDR.color_type": {
    "type": "uint8",
    "values": {
      "enum": [0, 2, 3, 4, 6],
      "labels": {
        "0": "Grayscale",
        "2": "Truecolor (RGB)",
        "3": "Indexed-color (palette)",
        "4": "Grayscale with alpha",
        "6": "Truecolor with alpha (RGBA)"
      }
    }
  }
}
```

## References

- [FormatFuzzer](https://github.com/uds-se/FormatFuzzer) — upstream framework
- [FormatFuzzer paper](https://arxiv.org/abs/2109.11277)
- [010 Editor binary templates](https://www.sweetscape.com/010editor/templates.html)
