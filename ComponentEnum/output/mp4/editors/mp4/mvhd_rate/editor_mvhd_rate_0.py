import os
import struct
import shutil

def mp4_mvhd_rate(fp, value, debug=False):
    def find_mvhd_offset(file_data):
        offset = 0
        while offset < len(file_data):
            size = struct.unpack(">I", file_data[offset:offset+4])[0]
            box_type = file_data[offset+4:offset+8]
            if box_type == b'mvhd':
                return offset
            offset += size
        return None

    def read_fixed_point(data, offset):
        integer_part = struct.unpack(">H", data[offset:offset+2])[0]
        fractional_part = struct.unpack(">H", data[offset+2:offset+4])[0]
        return integer_part + fractional_part / 65536.0

    def write_fixed_point(value):
        integer_part = int(value)
        fractional_part = int((value - integer_part) * 65536)
        return struct.pack(">HH", integer_part, fractional_part)

    with open(fp, 'rb+') as f:
        file_data = f.read()
        mvhd_offset = find_mvhd_offset(file_data)

        if mvhd_offset is None:
            if debug:
                print("[DEBUG] mvhd.rate not found")
            return

        rate_offset = mvhd_offset + 16  # mvhd box starts with version(1) + flags(3) + creation_time(4) + modification_time(4) + timescale(4)
        old_rate = read_fixed_point(file_data, rate_offset)

        if debug:
            print(f"[DEBUG] mvhd.rate before: {old_rate}")

        f.seek(rate_offset)
        f.write(write_fixed_point(value))

        if debug:
            print(f"[DEBUG] mvhd.rate after: {value}")

def test_mp4_mvhd_rate(input_file):
    import tempfile

    # Create a temporary file path
    tmp_path = tempfile.mktemp(suffix=".mp4")
    shutil.copy(input_file, tmp_path)

    try:
        # Test with a representative value
        test_value = 1.0
        mp4_mvhd_rate(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_rate('example.mp4')