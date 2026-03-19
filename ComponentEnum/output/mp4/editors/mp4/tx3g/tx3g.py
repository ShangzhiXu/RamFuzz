import struct
import os


def tx3g(fp, values, fields, debug=False):
    """Edit tx3g box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "background_color": (20, 4, "raw"),
        "background_color_rgba": (20, 4, "raw"),
        "box_record": (24, 8, "raw"),
        "data": (12, 4, "raw"),
        "data_reference_index": (12, 2, ">H"),
        "default_text_box": (24, 8, "raw"),
        "display_flags": (14, 4, ">I"),
        "flags": (9, 3, "raw"),
        "font_table": (44, 4, "raw"),
        "horizontal_justification": (18, 1, ">B"),
        "line_placement_flags": (14, 4, ">I"),
        "navbar_center_x": (18, 2, ">H"),
        "size": (0, 4, ">I"),
        "style_record": (32, 12, "raw"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "vertical_justification": (19, 1, ">B"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'tx3g'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] tx3g box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] tx3g.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] tx3g.{field} before: {old_val}")

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
                    print(f"[DEBUG] tx3g.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
