import os
import struct
import shutil

def mp4_mvhd_rate(fp, value, debug=False):
    try:
        with open(fp, 'rb+') as f:
            file_data = f.read()
            mvhd_pos = file_data.find(b'mvhd')

            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.rate not found")
                return

            # rate: 4 bytes at mvhd_pos+24 (fixed-point 16.16, stored as uint32)
            rate_offset = mvhd_pos + 24
            old_rate = struct.unpack('>I', file_data[rate_offset:rate_offset+4])[0]

            if debug:
                print(f"[DEBUG] mvhd.rate before: {old_rate}")

            f.seek(rate_offset)
            f.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] mvhd.rate after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

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