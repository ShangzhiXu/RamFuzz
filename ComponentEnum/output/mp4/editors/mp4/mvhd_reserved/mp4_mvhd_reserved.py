import os
import shutil
import struct

def mp4_mvhd_reserved(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.reserved not found")
                return

            # reserved: 10 bytes at mvhd_pos+30
            reserved_offset = mvhd_pos + 30
            old_value = data[reserved_offset:reserved_offset+10]

            if debug:
                print(f"[DEBUG] mvhd.reserved before: {old_value}")

            f.seek(reserved_offset)
            f.write(value[:10].ljust(10, b'\x00'))

            if debug:
                print(f"[DEBUG] mvhd.reserved after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_reserved(input_file):
    import tempfile

    # Create a temporary file path
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, 'test.mp4')

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Define a test value for the reserved field
        test_value = b'\x00\x00\x00\x00'

        # Call the function with debug enabled
        mp4_mvhd_reserved(tmp_path, test_value, debug=True)

        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# Example usage:
# test_mp4_mvhd_reserved('path_to_your_test_file.mp4')