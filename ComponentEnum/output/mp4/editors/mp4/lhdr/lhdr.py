import struct
import os


def lhdr(fp, values, fields, debug=False):
    """Edit lhdr box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "alternativeRowCount": (38, 2, ">H"),
        "compliantTransitionType": (46, 1, ">B"),
        "duration": (16, 4, ">I"),
        "exampleTransitionPoint": (42, 4, ">I"),
        "firstCodingPasses": (40, 2, ">H"),
        "flags": (9, 3, "raw"),
        "height": (22, 2, ">H"),
        "horiz_resolution": (28, 4, ">I"),
        "layer_height": (26, 2, ">H"),
        "layer_id": (36, 2, ">H"),
        "layer_width": (24, 2, ">H"),
        "size": (0, 4, ">I"),
        "timescale": (12, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "vert_resolution": (32, 4, ">I"),
        "width": (20, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'lhdr'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] lhdr box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] lhdr.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] lhdr.{field} before: {old_val}")

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
                    print(f"[DEBUG] lhdr.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
