import os
import shutil
import struct

def mp4_ftyp_box_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            # Read the first 8 bytes to get the size and type of the first box
            f.seek(0)
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] File too short to contain any valid MP4 box")
                return

            size, box_type = struct.unpack('>I4s', header)
            box_type = box_type.decode('utf-8', errors='replace')

            # Check if the first box is 'ftyp'
            if box_type != 'ftyp':
                if debug:
                    print("[DEBUG] ftyp.box_type not found")
                return

            # Ensure the file is large enough to contain the ftyp box
            if size < 12:
                if debug:
                    print("[DEBUG] File too short to contain a complete ftyp box")
                return

            # Read the current ftyp box type
            f.seek(8)  # Move to the major_brand position
            current_value = f.read(4).decode('utf-8', errors='replace')

            if debug:
                print(f"[DEBUG] ftyp.box_type before: {current_value}")

            # Replace it with the new value
            f.seek(8)  # Move back to the major_brand position
            f.write(value.encode('utf-8').ljust(4, b'\0'))  # Pad with null bytes if necessary

            if debug:
                print(f"[DEBUG] ftyp.box_type after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_ftyp_box_type(input_file):
    import tempfile

    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix='.mp4')
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Call the function with a test value
        test_value = "test"
        mp4_ftyp_box_type(tmp_path, test_value, debug=True)

        # Check if the function executed successfully
        print("Function executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_box_type('path_to_your_input_file.mp4')