import struct
import os


def hvcC(fp, values, fields, debug=False):
    """Edit hvcC box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "avgFrameRate": (27, 2, ">H"),
        "bitDepthChromaMinus8": (26, 1, ">B"),
        "bitDepthLumaMinus8": (25, 1, ">B"),
        "chromaFormat": (24, 1, ">B"),
        "configurationVersion": (8, 1, ">B"),
        "constantFrameRate": (29, 1, ">B"),
        "general_constraint_indicator_flags": (14, 6, "raw"),
        "general_level_idc": (20, 1, ">B"),
        "general_profile_compatibility_flags": (10, 4, ">I"),
        "general_profile_idc": (9, 1, ">B"),
        "general_profile_space": (9, 1, ">B"),
        "general_tier_flag": (9, 1, ">B"),
        "lengthSizeMinusOne": (30, 1, ">B"),
        "min_spatial_segmentation_idc": (21, 2, ">H"),
        "numOfArrays": (31, 1, ">B"),
        "numTemporalLayers": (29, 1, ">B"),
        "parallelismType": (23, 1, ">B"),
        "reserved": (21, 2, "raw"),
        "size": (0, 4, ">I"),
        "temporalIdNested": (29, 1, ">B"),
        "type": (4, 4, "4s"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'hvcC'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] hvcC box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] hvcC.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] hvcC.{field} before: {old_val}")

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
                    print(f"[DEBUG] hvcC.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
