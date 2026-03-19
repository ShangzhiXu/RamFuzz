import struct
import os


def ihdr(fp, values, fields, debug=False):
    """Edit ihdr box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "bitDepth": (20, 1, ">B"),
        "colorspace": (22, 1, ">B"),
        "colorspaceUnknown": (23, 1, ">B"),
        "colorspaceUnknownFlag": (23, 1, ">B"),
        "colortable_id": (69, 2, ">H"),
        "compressionType": (21, 1, ">B"),
        "compressorname": (35, 32, "raw"),
        "depth": (67, 2, ">H"),
        "flags": (9, 3, "raw"),
        "frame_count": (33, 2, ">H"),
        "height": (16, 4, ">I"),
        "horizresolution": (25, 4, ">I"),
        "intellectualProperty": (24, 1, ">B"),
        "intellectualPropertyFlag": (24, 1, ">B"),
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "vertresolution": (29, 4, ">I"),
        "width": (12, 4, ">I"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'ihdr'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] ihdr box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] ihdr.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] ihdr.{field} before: {old_val}")

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
                    print(f"[DEBUG] ihdr.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
