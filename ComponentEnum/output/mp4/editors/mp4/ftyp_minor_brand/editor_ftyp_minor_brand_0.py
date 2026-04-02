import os
import shutil
import struct

def mp4_ftyp_minor_brand(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The 'value' must be a string with a maximum length of 4.")

    with open(fp, 'r+b') as f:
        # Read the first 8 bytes to get the size and type of the box
        header = f.read(8)
        if len(header) < 8:
            if debug:
                print("[DEBUG] ftyp box not found or file too short")
            return

        size, box_type = struct.unpack('>I4s', header)
        if box_type != b'ftyp':
            if debug:
                print("[DEBUG] ftyp box not found")
            return

        # Read the major brand and minor version (4 bytes each)
        major_brand = f.read(4)
        if len(major_brand) < 4:
            if debug:
                print("[DEBUG] Major brand not found")
            return

        minor_brand = f.read(4)
        if len(minor_brand) < 4:
            if debug:
                print("[DEBUG] Minor brand not found")
            return

        old_value = minor_brand.decode('utf-8', errors='ignore')
        if debug:
            print(f"[DEBUG] ftyp.minor_brand before: {old_value}")

        # Replace the minor brand with the new value
        f.seek(-4, os.SEEK_CUR)
        f.write(value.encode('utf-8').ljust(4, b'\x00'))

        if debug:
            print(f"[DEBUG] ftyp.minor_brand after: {value}")

def test_mp4_ftyp_minor_brand(input_file):
    import tempfile

    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".mp4")
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Test value for the minor brand
        test_value = "test"

        # Call the function with debug=True
        mp4_ftyp_minor_brand(tmp_path, test_value, debug=True)

        print("Function executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_minor_brand('example.mp4')