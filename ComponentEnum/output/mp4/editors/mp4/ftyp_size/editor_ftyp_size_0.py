import os
import struct
import shutil
import tempfile

def mp4_ftyp_size(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes to check the size and type
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.size not found")
                return

            # Unpack the size and type
            size, box_type = struct.unpack('>I4s', header)

            # Check if this is the 'ftyp' box
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.size not found")
                return

            # Debug output before modification
            if debug:
                print(f"[DEBUG] ftyp.size before: {size}")

            # Seek back to the start of the file to overwrite the size
            file.seek(0)
            # Pack the new size and write it
            file.write(struct.pack('>I', value))

            # Debug output after modification
            if debug:
                print(f"[DEBUG] ftyp.size after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_ftyp_size(input_file):
    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    
    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Define a test value within the valid range
        test_value = 24  # Example value, can be any valid uint32

        # Call the function with debug enabled
        mp4_ftyp_size(tmp_path, test_value, debug=True)

        # Check if the function executed successfully
        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_size('path_to_your_mp4_file.mp4')