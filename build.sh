#!/bin/bash
set -e

# Usage:
#   ./build.sh mp4              # build all 3 variants for mp4
#   ./build.sh mp3              # build all 3 variants for mp3
#   ./build.sh mp4 origin       # build only origin variant
#   ./build.sh mp4 violation    # build only violation variant
#   ./build.sh mp4 violation_cov # build only violation_cov variant

FMT="${1:?Usage: $0 <format> [origin|violation|violation_cov]}"
VARIANT="$2"

module load boost/1.80.0 2>/dev/null || true

CXXFLAGS="-I . -std=c++17 -O2 -fPIC -Wall"

# Step 1: Compile .bt -> .cpp (skip if .cpp already exists and is newer)
if [ ! -f "${FMT}.cpp" ] || [ "templates/${FMT}.bt" -nt "${FMT}.cpp" ]; then
    echo "==> Compiling templates/${FMT}.bt -> ${FMT}.cpp"
    ./ffcompile "templates/${FMT}.bt" "${FMT}.cpp"
else
    echo "==> ${FMT}.cpp is up to date"
fi

build_origin() {
    echo "==> Building ${FMT}.so (pure FormatFuzzer, no violation)"
    g++ -shared $CXXFLAGS "${FMT}.cpp" fuzzer_orig.cpp field_collector_stub.c -o "${FMT}.so" -lz
    echo "    -> ${FMT}.so"
}

build_violation() {
    echo "==> Building ${FMT}_violation.so (+ violation, no coverage)"
    g++ -shared $CXXFLAGS "${FMT}.cpp" fuzzer.cpp violation_postproc.c json_reader.c -o "${FMT}_violation.so" -lz -lm
    echo "    -> ${FMT}_violation.so"
}

build_violation_cov() {
    echo "==> Building ${FMT}_violation_cov.so (+ violation + coverage feedback)"
    g++ -shared $CXXFLAGS "${FMT}.cpp" fuzzer.cpp violation_postproc_cov.c json_reader.c -o "${FMT}_violation_cov.so" -lz -lm
    echo "    -> ${FMT}_violation_cov.so"
}

if [ -z "$VARIANT" ]; then
    build_origin
    build_violation
    build_violation_cov
else
    case "$VARIANT" in
        origin)        build_origin ;;
        violation)     build_violation ;;
        violation_cov) build_violation_cov ;;
        *) echo "Unknown variant: $VARIANT (use origin|violation|violation_cov)"; exit 1 ;;
    esac
fi

echo "==> Done"
