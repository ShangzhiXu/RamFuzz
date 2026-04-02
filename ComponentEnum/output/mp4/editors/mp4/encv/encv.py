import struct
import os


def encv(fp, values, fields, debug=False):
    """Edit encv box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "compressorname": (50, 32, "raw"),
        "dataReferenceIndex": (14, 2, ">H"),
        "data_reference_index": (14, 2, ">H"),
        "data_size": (44, 4, ">I"),
        "dataformat": (4, 4, "4s"),
        "depth": (82, 2, ">H"),
        "flags": (9, 3, "raw"),
        "frameCount": (48, 2, ">H"),
        "frame_count": (48, 2, ">H"),
        "height": (34, 2, ">H"),
        "horizresolution": (36, 4, ">I"),
        "pre_defined": (16, 2, ">H"),
        "pre_defined1": (20, 12, "raw"),
        "pre_defined2": (20, 12, "raw"),
        "pre_defined3": (84, 2, ">H"),
        "reserved": (8, 6, "raw"),
        "reserved1": (8, 6, "raw"),
        "reserved2": (18, 2, ">H"),
        "reserved3": (44, 4, "raw"),
        "revision_level": (18, 2, ">H"),
        "scheme_type": (86, 4, "4s"),
        "scheme_uri": (94, 4, "4s"),
        "scheme_version": (90, 4, ">I"),
        "size": (0, 4, ">I"),
        "spatial_quality": (28, 4, ">I"),
        "temporal_quality": (24, 4, ">I"),
        "type": (4, 4, "4s"),
        "vendor": (20, 4, "raw"),
        "version": (16, 2, ">H"),
        "vertresolution": (40, 4, ">I"),
        "video_color_table_id": (84, 2, ">H"),
        "video_compressor_name": (50, 32, "raw"),
        "video_data_size": (44, 4, ">I"),
        "video_depth": (82, 2, ">H"),
        "video_encoding_revision_level": (18, 2, ">H"),
        "video_encoding_vendor": (20, 4, "raw"),
        "video_encoding_version": (16, 2, ">H"),
        "video_frame_count": (48, 2, ">H"),
        "video_height": (34, 2, ">H"),
        "video_horizontal_resolution": (36, 4, ">I"),
        "video_spatial_quality": (28, 4, ">I"),
        "video_temporal_quality": (24, 4, ">I"),
        "video_vertical_resolution": (40, 4, ">I"),
        "video_width": (32, 2, ">H"),
        "width": (32, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'encv'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] encv box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] encv.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] encv.{field} before: {old_val}")

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
                    print(f"[DEBUG] encv.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
