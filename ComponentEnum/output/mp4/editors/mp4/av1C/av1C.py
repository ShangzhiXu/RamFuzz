import struct
import os


def av1C(fp, values, fields, debug=False):
    """Edit av1C box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "chromaSamplePosition": (13, 1, ">B"),
        "chromaSubsamplingX": (12, 1, ">B"),
        "chromaSubsamplingY": (12, 1, ">B"),
        "chroma_sample_position": (13, 1, ">B"),
        "chroma_subsampling_x": (12, 1, ">B"),
        "chroma_subsampling_y": (12, 1, ">B"),
        "highBitdepth": (11, 1, ">B"),
        "high_bitdepth": (11, 1, ">B"),
        "initialPresentationDelayMinusOne": (14, 1, ">B"),
        "initialPresentationDelayPresent": (13, 1, ">B"),
        "initial_presentation_delay_minus_one": (14, 1, ">B"),
        "initial_presentation_delay_present": (13, 1, ">B"),
        "marker": (8, 1, ">B"),
        "marker_bit": (8, 1, ">B"),
        "monochrome": (12, 1, ">B"),
        "reserved": (14, 1, "raw"),
        "seqLevelIdx0": (10, 1, ">B"),
        "seqProfile": (9, 1, ">B"),
        "seqTier0": (11, 1, ">B"),
        "seq_level_idx_0": (10, 1, ">B"),
        "seq_profile": (9, 1, ">B"),
        "seq_tier_0": (11, 1, ">B"),
        "size": (0, 4, ">I"),
        "twelveBit": (11, 1, ">B"),
        "twelve_bit": (11, 1, ">B"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'av1C'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] av1C box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] av1C.{field}: unknown field, skipping")
                    continue

                offset, size, fmt = FIELD_MAP[field]
                abs_pos = box_start + offset
                value = values[i] if i < len(values) else None
                if value is None:
                    continue

                # Read old value
                try:
                    if fmt in ("4s", "str"):
                        old_val = data[abs_pos:abs_pos+size]
                        old_val = old_val.decode('utf-8', errors='replace')
                    elif fmt == "raw":
                        old_val = data[abs_pos:abs_pos+size].hex()
                    else:
                        old_val = struct.unpack_from(fmt, data, abs_pos)[0]
                except Exception:
                    old_val = "N/A"

                if debug:
                    print(f"[DEBUG] av1C.{field} before: {old_val}")

                # Write new value
                f.seek(abs_pos)
                if fmt in ("4s", "str"):
                    if isinstance(value, str):
                        encoded = value.encode('utf-8')
                    else:
                        encoded = bytes(value)
                    f.write(encoded[:size].ljust(size, b'\x00'))
                elif fmt == "raw":
                    if isinstance(value, bytes):
                        f.write(value[:size].ljust(size, b'\x00'))
                    elif isinstance(value, int):
                        f.write(value.to_bytes(size, 'big'))
                    else:
                        f.write(bytes(value)[:size].ljust(size, b'\x00'))
                else:
                    f.write(struct.pack(fmt, value))

                if debug:
                    print(f"[DEBUG] av1C.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
