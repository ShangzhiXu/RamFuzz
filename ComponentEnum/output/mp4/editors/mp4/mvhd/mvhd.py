import struct
import os


def mvhd(fp, values, fields, debug=False):
    """Edit mvhd box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "creation_time": (12, 4, ">I"),
        "duration": (24, 4, ">I"),
        "flags": (9, 3, "raw"),
        "matrix": (44, 36, "raw"),
        "matrix_structure": (44, 36, "raw"),
        "modification_time": (16, 4, ">I"),
        "next_track_ID": (104, 4, ">I"),
        "next_track_id": (104, 4, ">I"),
        "pad": (34, 2, "raw"),
        "pre_defined": (80, 24, "raw"),
        "rate": (28, 4, ">I"),
        "reserved": (34, 10, "raw"),
        "reserved1": (34, 2, "raw"),
        "reserved2": (36, 8, "raw"),
        "reserved3": (34, 10, "raw"),
        "reserved_2": (36, 8, "raw"),
        "size": (0, 4, ">I"),
        "timescale": (20, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "volume": (32, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'mvhd'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] mvhd box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] mvhd.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] mvhd.{field} before: {old_val}")

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
                    print(f"[DEBUG] mvhd.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
