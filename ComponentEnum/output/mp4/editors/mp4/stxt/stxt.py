import struct
import os


def stxt(fp, values, fields, debug=False):
    """Edit stxt box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "alternate_group": (18, 2, ">H"),
        "bitmap": (36, 4, "raw"),
        "cue_text": (12, 4, "4s"),
        "flags": (9, 3, "raw"),
        "height": (28, 4, ">I"),
        "layer": (16, 2, ">H"),
        "private_data": (40, 4, "raw"),
        "reserved": (22, 2, "raw"),
        "samplerate": (32, 4, ">I"),
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "volume": (20, 2, ">H"),
        "width": (24, 4, ">I"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'stxt'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] stxt box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] stxt.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] stxt.{field} before: {old_val}")

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
                    print(f"[DEBUG] stxt.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
