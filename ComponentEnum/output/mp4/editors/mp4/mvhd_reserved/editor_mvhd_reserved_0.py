import os
import shutil
import struct

def mp4_mvhd_reserved(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the file header to locate the 'mvhd' atom
            f.seek(0)
            while True:
                # Read the size and type of the atom
                atom_header = f.read(8)
                if len(atom_header) < 8:
                    break  # End of file reached without finding 'mvhd'

                atom_size, atom_type = struct.unpack('>I4s', atom_header)
                if atom_type == b'mvhd':
                    # Skip version and flags (4 bytes)
                    f.seek(4, os.SEEK_CUR)

                    # Read creation time, modification time, timescale, duration (16 bytes)
                    f.seek(16, os.SEEK_CUR)

                    # Read reserved field (4 bytes)
                    reserved = f.read(4)
                    if debug:
                        print(f"[DEBUG] mvhd.reserved before: {reserved}")

                    # Replace with new value
                    f.seek(-4, os.SEEK_CUR)
                    f.write(value)

                    if debug:
                        print(f"[DEBUG] mvhd.reserved after: {value}")
                    return

                # Move to the next atom
                f.seek(atom_size - 8, os.SEEK_CUR)

        if debug:
            print("[DEBUG] mvhd.reserved not found")
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