import os
import shutil
import struct

def mp4_ftyp_major_brand(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The 'value' must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            # Read the first 8 bytes to get the size and type of the first box
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            size, box_type = struct.unpack('>I4s', header)
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            # Read the major brand (4 bytes)
            major_brand = f.read(4)
            if len(major_brand) < 4:
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            old_value = major_brand.decode('utf-8')

            if debug:
                print(f"[DEBUG] ftyp.major_brand before: {old_value}")

            # Move back to the position of the major brand and write the new value
            f.seek(8)
            f.write(value.encode('utf-8').ljust(4, b'\0'))

            if debug:
                print(f"[DEBUG] ftyp.major_brand after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_ftyp_major_brand(input_file):
    import tempfile

    # Create a temporary file to work with
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Call the function with a test value
        test_value = "mp42"
        mp4_ftyp_major_brand(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_major_brand('path_to_your_test_file.mp4')