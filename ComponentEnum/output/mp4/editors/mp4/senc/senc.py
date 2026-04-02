import struct
import os


def senc(fp, values, fields, debug=False):
    """Edit senc box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "IV": (16, 16, "raw"),
        "IV_size": (16, 1, ">B"),
        "KID": (16, 16, "raw"),
        "bytes_of_clear_data": (34, 2, ">H"),
        "bytes_of_encrypted_data": (36, 4, ">I"),
        "cipher_bytes": (36, 4, ">I"),
        "clear_bytes": (34, 2, ">H"),
        "crypt_byte_block": (12, 1, ">B"),
        "encrypted_bytes": (36, 4, ">I"),
        "flags": (9, 3, "raw"),
        "is_encrypted": (12, 1, ">B"),
        "sample_count": (12, 4, ">I"),
        "sample_encryption_entries": (16, 4, "raw"),
        "size": (0, 4, ">I"),
        "skip_byte_block": (13, 1, ">B"),
        "subsample_count": (32, 2, ">H"),
        "type": (4, 4, "4s"),
        "version": (8, 1, ">B"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'senc'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] senc box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] senc.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] senc.{field} before: {old_val}")

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
                    print(f"[DEBUG] senc.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
