import struct
import os


def enca(fp, values, fields, debug=False):
    """Edit enca box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "audio_compression_id": (28, 2, ">H"),
        "audio_encoding_revision_level": (18, 2, ">H"),
        "audio_encoding_vendor": (20, 4, "raw"),
        "audio_encoding_version": (16, 2, ">H"),
        "audio_number_of_channels": (24, 2, ">H"),
        "audio_packet_size": (30, 2, ">H"),
        "audio_sample_rate": (32, 4, ">I"),
        "audio_sample_size": (26, 2, ">H"),
        "channelCount": (24, 2, ">H"),
        "channel_count": (24, 2, ">H"),
        "channelcount": (24, 2, ">H"),
        "channels": (24, 2, ">H"),
        "compression_id": (28, 2, ">H"),
        "compressionid": (28, 2, ">H"),
        "dataReferenceIndex": (14, 2, ">H"),
        "data_reference_index": (14, 2, ">H"),
        "dataformat": (4, 4, "4s"),
        "entry_version": (16, 2, ">H"),
        "flags": (9, 3, "raw"),
        "packet_size": (30, 2, ">H"),
        "packetsize": (30, 2, ">H"),
        "pre_defined": (28, 2, ">H"),
        "pre_defined1": (28, 2, ">H"),
        "predefined": (28, 2, ">H"),
        "reserved": (8, 6, "raw"),
        "reserved1": (8, 6, "raw"),
        "reserved2": (16, 8, "raw"),
        "reserved3": (30, 2, "raw"),
        "revision": (18, 2, ">H"),
        "revision_level": (18, 2, ">H"),
        "sampleRate": (32, 4, ">I"),
        "sampleSize": (26, 2, ">H"),
        "sample_rate": (32, 4, ">I"),
        "sample_size": (26, 2, ">H"),
        "samplerate": (32, 4, ">I"),
        "samplesize": (26, 2, ">H"),
        "scheme_type": (36, 4, "4s"),
        "scheme_uri": (44, 4, "4s"),
        "scheme_version": (40, 4, ">I"),
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "vendor": (20, 4, "raw"),
        "version": (16, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'enca'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] enca box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] enca.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] enca.{field} before: {old_val}")

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
                    print(f"[DEBUG] enca.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
