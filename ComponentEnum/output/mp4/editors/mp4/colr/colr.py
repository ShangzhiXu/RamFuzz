import struct
import os


def colr(fp, values, fields, debug=False):
    """Edit colr box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "colourPrimaries": (12, 2, ">H"),
        "colourType": (8, 4, "4s"),
        "colour_primaries": (12, 2, ">H"),
        "colour_type": (8, 4, "4s"),
        "fullRangeFlag": (18, 1, ">B"),
        "full_range_flag": (18, 1, ">B"),
        "matrixCoefficients": (16, 2, ">H"),
        "matrix_coefficients": (16, 2, ">H"),
        "matrix_index": (16, 2, ">H"),
        "primaries_index": (12, 2, ">H"),
        "size": (0, 4, ">I"),
        "transferCharacteristics": (14, 2, ">H"),
        "transfer_characteristics": (14, 2, ">H"),
        "transfer_function_index": (14, 2, ">H"),
        "type": (4, 4, "4s"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'colr'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] colr box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] colr.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] colr.{field} before: {old_val}")

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
                    print(f"[DEBUG] colr.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
