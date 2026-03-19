import os
import struct
import shutil

def mp4_mvhd_flags(fp, value, debug=False):
    # Define the constants
    MVHD_ATOM = b'mvhd'
    HEADER_SIZE = 8  # size of atom header (4 bytes for size, 4 bytes for type)

    # Ensure value fits within 24 bits
    if not (0 <= value < 2**24):
        raise ValueError("Value must be a uint24 (0 <= value < 2^24).")

    def read_uint24(file):
        data = file.read(3)
        if len(data) != 3:
            raise ValueError("Failed to read 3 bytes for uint24.")
        return struct.unpack('>I', b'\x00' + data)[0]

    def write_uint24(file, value):
        data = struct.pack('>I', value)
        file.write(data[1:])

    try:
        with open(fp, 'r+b') as f:
            # Read through the file to find the mvhd atom
            while True:
                atom_header = f.read(HEADER_SIZE)
                if len(atom_header) < HEADER_SIZE:
                    break

                size, atom_type = struct.unpack('>I4s', atom_header)
                if atom_type == MVHD_ATOM:
                    # Skip version and flags (1 + 3 bytes)
                    f.seek(4, os.SEEK_CUR)
                    flags_offset = f.tell() - 3

                    # Read the current mvhd.flags value
                    old_value = read_uint24(f)
                    if debug:
                        print(f"[DEBUG] mvhd.flags before: {old_value}")

                    # Write the new mvhd.flags value
                    f.seek(flags_offset)
                    write_uint24(f, value)

                    if debug:
                        print(f"[DEBUG] mvhd.flags after: {value}")
                    return

                # Skip to the next atom
                f.seek(size - HEADER_SIZE, os.SEEK_CUR)

        if debug:
            print("[DEBUG] mvhd.flags not found")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_mvhd_flags(input_file):
    import tempfile

    # Create a temporary copy of the input file
    with tempfile.NamedTemporaryFile(delete=False) as temp_file:
        tmp_path = temp_file.name
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for mvhd.flags (a representative uint24 value)
        test_value = 0x123456
        mp4_mvhd_flags(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)