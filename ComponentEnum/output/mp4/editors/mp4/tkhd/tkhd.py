import struct
import os


def tkhd(fp, values, fields, debug=False):
    """Edit tkhd box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "alternate_group": (42, 2, ">H"),
        "creation_time": (12, 4, ">I"),
        "duration": (28, 4, ">I"),
        "flags": (9, 3, "raw"),
        "height": (88, 4, ">I"),
        "layer": (40, 2, ">H"),
        "matrix": (48, 36, "raw"),
        "matrix_structure": (48, 36, "raw"),
        "modification_time": (16, 4, ">I"),
        "pad": (46, 2, "raw"),
        "reserved": (24, 4, "raw"),
        "reserved1": (24, 4, "raw"),
        "reserved2": (32, 8, "raw"),
        "reserved3": (46, 2, "raw"),
        "reserved4": (46, 2, "raw"),
        "reserved_2": (32, 8, "raw"),
        "reserved_3": (46, 2, "raw"),
        "size": (0, 4, ">I"),
        "track_ID": (20, 4, ">I"),
        "track_id": (20, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "volume": (44, 2, ">H"),
        "width": (84, 4, ">I"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'tkhd'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] tkhd box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] tkhd.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] tkhd.{field} before: {old_val}")

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
                    print(f"[DEBUG] tkhd.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
