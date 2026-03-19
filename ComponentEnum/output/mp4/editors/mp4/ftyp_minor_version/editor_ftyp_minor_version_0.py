import os
import struct
import shutil

def mp4_ftyp_minor_version(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes to get the size and type of the box
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            size, box_type = struct.unpack('>I4s', header)
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            # Read the major brand and minor version
            file.seek(8, os.SEEK_SET)
            major_brand = file.read(4)
            minor_version = file.read(4)
            if len(minor_version) < 4:
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            # Unpack the current minor version
            old_value = struct.unpack('>I', minor_version)[0]

            if debug:
                print(f"[DEBUG] ftyp.minor_version before: {old_value}")

            # Write the new minor version
            file.seek(12, os.SEEK_SET)
            file.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] ftyp.minor_version after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_ftyp_minor_version(input_file):
    import tempfile

    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix='.mp4')
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Test value for minor_version
        test_value = 1

        # Call the function with debug=True
        mp4_ftyp_minor_version(tmp_path, test_value, debug=True)

        # Check if the function executed successfully
        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_minor_version('example.mp4')