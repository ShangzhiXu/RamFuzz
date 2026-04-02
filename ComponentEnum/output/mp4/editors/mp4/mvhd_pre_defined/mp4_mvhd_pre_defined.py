import os
import shutil
import struct

def mp4_mvhd_pre_defined(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            content = f.read()
            mvhd_pos = content.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.pre_defined not found")
                return

            # pre_defined: 24 bytes at mvhd_pos+76
            pre_defined_offset = mvhd_pos + 76
            old_value = content[pre_defined_offset:pre_defined_offset+24]

            if debug:
                print(f"[DEBUG] mvhd.pre_defined before: {old_value}")

            f.seek(pre_defined_offset)
            f.write(value[:24].ljust(24, b'\x00'))

            if debug:
                print(f"[DEBUG] mvhd.pre_defined after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_pre_defined(input_file):
    test_value = b'\x00\x00\x00\x01'  # Example test value
    tmp_path = 'temp_test.mp4'

    # Create a copy of the file
    shutil.copy(input_file, tmp_path)

    try:
        mp4_mvhd_pre_defined(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        os.remove(tmp_path)