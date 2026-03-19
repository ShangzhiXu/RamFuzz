import os
import shutil
import struct

def mp4_ftyp_major_brand(fp, value, debug=False):
    # Ensure the value is a string of exactly 4 characters
    if not isinstance(value, str) or len(value) != 4:
        raise ValueError("The 'value' must be a string of exactly 4 characters.")

    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes to check the 'ftyp' box
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            # Unpack the header to get size and type
            size, box_type = struct.unpack('>I4s', header)
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            # Read the major brand (next 4 bytes)
            major_brand_bytes = file.read(4)
            if len(major_brand_bytes) < 4:
                if debug:
                    print("[DEBUG] ftyp.major_brand not found")
                return

            # Decode the current major brand
            old_value = major_brand_bytes.decode('utf-8')
            if debug:
                print(f"[DEBUG] ftyp.major_brand before: {old_value}")

            # Move the file pointer back to overwrite the major brand
            file.seek(8)
            file.write(value.encode('utf-8'))
            if debug:
                print(f"[DEBUG] ftyp.major_brand after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_ftyp_major_brand(input_file):
    import tempfile

    # Create a temporary file to work with
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, "test.mp4")

    try:
        # Copy the input file to the temporary path
        shutil.copy2(input_file, tmp_path)

        # Define a test value, ensuring it matches the component's constraints
        test_value = "isom"  # Example value from common values

        # Call the function with debug=True to print output
        mp4_ftyp_major_brand(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# This code is designed to be run as a script or imported as a module.
# To execute the test, call test_mp4_ftyp_major_brand with a valid MP4 file path.