import os
import shutil
import struct

def mp4_mvhd_flags(fp, value, debug=False):
    def read_uint24(file):
        """Reads a 24-bit unsigned integer from the file."""
        data = file.read(3)
        if len(data) != 3:
            return None
        return struct.unpack('>I', b'\x00' + data)[0]

    def write_uint24(file, value):
        """Writes a 24-bit unsigned integer to the file."""
        data = struct.pack('>I', value)[1:]  # Skip the first byte
        file.write(data)

    try:
        with open(fp, 'r+b') as f:
            # Search for the 'mvhd' box
            while True:
                # Read box header: size (4 bytes) and type (4 bytes)
                header = f.read(8)
                if len(header) < 8:
                    break

                size, box_type = struct.unpack('>I4s', header)
                if box_type == b'mvhd':
                    # Skip version (1 byte) and read flags (3 bytes)
                    f.seek(1, os.SEEK_CUR)
                    current_flags = read_uint24(f)
                    if current_flags is None:
                        break

                    if debug:
                        print(f"[DEBUG] mvhd.flags before: {current_flags}")

                    # Move back 3 bytes to overwrite the flags
                    f.seek(-3, os.SEEK_CUR)
                    write_uint24(f, value)

                    if debug:
                        print(f"[DEBUG] mvhd.flags after: {value}")

                    return

                # Move to the next box
                f.seek(size - 8, os.SEEK_CUR)

        if debug:
            print("[DEBUG] mvhd.flags not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_flags(input_file):
    import tempfile

    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix='.mp4')
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Test value for mvhd.flags
        test_value = 0  # Common value for mvhd.flags

        # Call the function with debug=True
        mp4_mvhd_flags(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_flags('example.mp4')