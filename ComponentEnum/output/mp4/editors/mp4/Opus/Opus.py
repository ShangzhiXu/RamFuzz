import struct
import os


def Opus(fp, values, fields, debug=False):
    """Edit Opus box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {
        "channelCount": (24, 2, ">H"),
        "channelMappingFamily": (44, 1, ">B"),
        "channel_count": (24, 2, ">H"),
        "channel_map": (46, 4, "raw"),
        "channelcount": (24, 2, ">H"),
        "channels": (24, 2, ">H"),
        "compression_id": (28, 2, ">H"),
        "compressionid": (28, 2, ">H"),
        "data_reference_index": (14, 2, ">H"),
        "entry_version": (16, 2, ">H"),
        "flags": (9, 3, "raw"),
        "inputSampleRate": (38, 4, ">I"),
        "input_sample_rate": (38, 4, ">I"),
        "numOutputs": (45, 1, ">B"),
        "outputChannelCount": (45, 1, ">B"),
        "outputGain": (42, 2, ">H"),
        "output_gain": (42, 2, ">H"),
        "packet_size": (30, 2, ">H"),
        "packetsize": (30, 2, ">H"),
        "preSkip": (36, 2, ">H"),
        "pre_defined": (28, 2, ">H"),
        "pre_defined1": (28, 2, ">H"),
        "pre_skip": (36, 2, ">H"),
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
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "vendor": (20, 4, "raw"),
        "version": (16, 2, ">H"),
    }

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = b'Opus'
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] Opus box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] Opus.{field}: unknown field, skipping")
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
                    print(f"[DEBUG] Opus.{field} before: {old_val}")

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
                    print(f"[DEBUG] Opus.{field} after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")
