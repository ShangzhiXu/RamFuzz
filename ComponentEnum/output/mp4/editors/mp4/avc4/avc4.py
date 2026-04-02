import struct
import os


def avc4(fp, values, fields, debug=False):
    """Edit avc4 box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "AVCLevelIndication": (11, 1, ">B"),
        "AVCProfileIndication": (9, 1, ">B"),
        "arrayCompleteness": (14, 1, ">B"),
        "chromaFormat": (12, 1, ">B"),
        "configVersion": (8, 1, ">B"),
        "configurationVersion": (8, 1, ">B"),
        "depthFlags": (12, 1, ">B"),
        "flags": (9, 3, "raw"),
        "lengthSizeMinusOne": (12, 1, ">B"),
        "levelIndication": (11, 1, ">B"),
        "nalUnitType": (15, 1, ">B"),
        "naluLengthSize": (12, 1, ">B"),
        "numOfArrays": (13, 1, ">B"),
        "numOfPictureParameterSets": (20, 1, ">B"),
        "numOfSequenceParameterSets": (13, 1, ">B"),
        "numberOfPictureParameterSets": (20, 1, ">B"),
        "numberOfSequenceParameterSets": (13, 1, ">B"),
        "pictureParameterSetLength": (21, 2, ">H"),
        "pictureParameterSetNALUnit": (23, 4, "raw"),
        "pictureParameterSetNALUnits": (23, 4, "raw"),
        "pictureParameterSets": (23, 4, "raw"),
        "profileCompatibility": (10, 1, ">B"),
        "profileIndication": (9, 1, ">B"),
        "profile_compatibility": (10, 1, ">B"),
        "reserved": (12, 1, "raw"),
        "reserved1": (12, 1, "raw"),
        "reserved2": (12, 1, "raw"),
        "sequenceParameterSetLength": (14, 2, ">H"),
        "sequenceParameterSetNALUnit": (16, 4, "raw"),
        "sequenceParameterSetNALUnits": (16, 4, "raw"),
        "sequenceParameterSets": (16, 4, "raw"),
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'avc4'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] avc4 box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] avc4.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] avc4.{field} before: {old_val}")

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
                    print(f"[DEBUG] avc4.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
