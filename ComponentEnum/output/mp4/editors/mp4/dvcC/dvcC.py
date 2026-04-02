import struct
import os


def dvcC(fp, values, fields, debug=False):
    """Edit dvcC box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "aviVersion": (12, 1, ">B"),
        "bitDepth": (17, 1, ">B"),
        "blPresentFlag": (15, 1, ">B"),
        "chromaSubsampling": (18, 1, ">B"),
        "codecConfigurationVersion": (12, 1, ">B"),
        "codecLevel": (14, 1, ">B"),
        "codecProfile": (13, 1, ">B"),
        "colorPrimaries": (19, 1, ">B"),
        "colorTableID": (97, 2, ">H"),
        "compressorName": (63, 32, "raw"),
        "depth": (95, 2, ">H"),
        "dvBlSignalCompatibilityId": (16, 1, ">B"),
        "dvLevel": (14, 1, ">B"),
        "dvProfile": (13, 1, ">B"),
        "dvVersion": (12, 1, ">B"),
        "elPresentFlag": (15, 1, ">B"),
        "flags": (9, 3, "raw"),
        "height": (53, 2, ">H"),
        "horizontalResolution": (55, 4, ">I"),
        "level": (14, 1, ">B"),
        "manufacturerCode": (39, 4, "raw"),
        "matrixCoefficients": (21, 1, ">B"),
        "preferredUUID": (23, 16, "raw"),
        "profile": (13, 1, ">B"),
        "rpuPresentFlag": (15, 1, ">B"),
        "size": (0, 4, ">I"),
        "spatialQuality": (47, 4, ">I"),
        "temporalQuality": (43, 4, ">I"),
        "transferCharacteristics": (20, 1, ">B"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "verticalResolution": (59, 4, ">I"),
        "videoFullRangeFlag": (22, 1, ">B"),
        "width": (51, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'dvcC'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] dvcC box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] dvcC.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] dvcC.{field} before: {old_val}")

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
                    print(f"[DEBUG] dvcC.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
