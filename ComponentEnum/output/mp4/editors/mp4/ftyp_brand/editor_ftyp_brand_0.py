import os
import shutil
import struct

def mp4_ftyp_brand(fp, value, debug=False):
    if not isinstance(value, str) or len(value) != 4:
        raise ValueError("The value must be a string of exactly 4 characters.")

    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes to get the size and type of the first box
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            size, box_type = struct.unpack('>I4s', header)

            # Check if the first box is 'ftyp'
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            # Read the major_brand (4 bytes) after the header
            major_brand = file.read(4)
            if len(major_brand) < 4:
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            old_value = major_brand.decode('utf-8')

            if debug:
                print(f"[DEBUG] ftyp.brand before: {old_value}")

            # Move the file cursor back to the start of the major_brand
            file.seek(8)
            # Write the new value
            file.write(value.encode('utf-8'))

            if debug:
                print(f"[DEBUG] ftyp.brand after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_ftyp_brand(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + ".tmp"
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the ftyp.brand
        test_value = "mp42"
        mp4_ftyp_brand(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed with exception: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)