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
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.flags not found")
                return

            # flags: 3 bytes at mvhd_pos+5 (after version byte at +4)
            flags_offset = mvhd_pos + 5
            current_flags = struct.unpack('>I', b'\x00' + data[flags_offset:flags_offset+3])[0]

            if debug:
                print(f"[DEBUG] mvhd.flags before: {current_flags}")

            f.seek(flags_offset)
            f.write(struct.pack('>I', value)[1:])  # write 3 bytes

            if debug:
                print(f"[DEBUG] mvhd.flags after: {value}")

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