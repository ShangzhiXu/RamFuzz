import os
import shutil
from struct import unpack, pack

def mp4_mvhd_reserved2(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the file header to locate the 'mvhd' box
            while True:
                # Read the box header (4 bytes size and 4 bytes type)
                box_header = f.read(8)
                if len(box_header) < 8:
                    break

                box_size, box_type = unpack('>I4s', box_header)

                # Check if we are at the 'mvhd' box
                if box_type == b'mvhd':
                    # Skip version and flags (1 byte + 3 bytes)
                    f.seek(4, os.SEEK_CUR)

                    # Read the creation and modification times (8 bytes)
                    f.seek(8, os.SEEK_CUR)

                    # Read time_scale and duration (8 bytes)
                    f.seek(8, os.SEEK_CUR)

                    # Read preferred rate and volume (6 bytes)
                    f.seek(6, os.SEEK_CUR)

                    # Read reserved2 (10 bytes)
                    current_reserved2 = f.read(10)

                    if debug:
                        print(f"[DEBUG] mvhd.reserved2 before: {current_reserved2}")

                    # Replace the reserved2 with the new value
                    f.seek(-10, os.SEEK_CUR)
                    f.write(value)

                    if debug:
                        print(f"[DEBUG] mvhd.reserved2 after: {value}")

                    return
            
                # Move to the next box
                f.seek(box_size - 8, os.SEEK_CUR)

        if debug:
            print("[DEBUG] mvhd.reserved2 not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_reserved2(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Call the function with a test value (10 zero bytes)
        test_value = b'\x00' * 10
        mp4_mvhd_reserved2(tmp_path, test_value, debug=True)

        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example test run
# test_mp4_mvhd_reserved2('path_to_input_file.mp4')