import os
import shutil
import struct

def mp4_ftyp_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes to find the 'ftyp' box
            while True:
                header = file.read(8)
                if len(header) < 8:
                    if debug:
                        print("[DEBUG] ftyp.type not found")
                    return

                box_size, box_type = struct.unpack('>I4s', header)
                box_type = box_type.decode('utf-8')

                if box_type == 'ftyp':
                    # Read the major brand (4 bytes)
                    major_brand = file.read(4).decode('utf-8')

                    if debug:
                        print(f"[DEBUG] ftyp.type before: {major_brand}")

                    # Move back 4 bytes to overwrite the major brand
                    file.seek(-4, os.SEEK_CUR)
                    # Write the new value
                    file.write(value.encode('utf-8').ljust(4, b'\x00'))

                    if debug:
                        print(f"[DEBUG] ftyp.type after: {value}")

                    return
                else:
                    # Skip to the next box
                    file.seek(box_size - 8, os.SEEK_CUR)

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_ftyp_type(input_file):
    import tempfile

    # Create a temporary file
    temp_dir = tempfile.mkdtemp()
    temp_file = os.path.join(temp_dir, os.path.basename(input_file))

    try:
        # Copy the input file to the temporary file
        shutil.copy(input_file, temp_file)

        # Test value for ftyp.type
        test_value = "test"

        # Call the function with debug=True
        mp4_ftyp_type(temp_file, test_value, debug=True)

        print("Function executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(temp_file):
            os.remove(temp_file)
        if os.path.exists(temp_dir):
            os.rmdir(temp_dir)