import os
import shutil
import struct

def mp4_moov_box_type(fp, value, debug=False):
    def read_uint32(f):
        return struct.unpack(">I", f.read(4))[0]

    def read_str(f, length):
        return f.read(length).decode('utf-8')

    if not (isinstance(value, str) and len(value) <= 4):
        raise ValueError("The value must be a string with a maximum length of 4 characters.")

    value = value.ljust(4, ' ')  # Ensure the value is exactly 4 bytes long

    with open(fp, 'r+b') as f:
        while True:
            try:
                start_pos = f.tell()
                box_size = read_uint32(f)
                box_type = read_str(f, 4)

                if box_type == "moov":
                    if debug:
                        print(f"[DEBUG] moov.box_type before: {box_type}")
                    
                    # Move to the start of box_type field and write the new value
                    f.seek(start_pos + 4)
                    f.write(value.encode('utf-8'))

                    if debug:
                        print(f"[DEBUG] moov.box_type after: {value}")

                    break

                # Skip to the next box
                f.seek(start_pos + box_size, os.SEEK_SET)

            except struct.error:
                # struct.error will be raised if we try to unpack beyond the file
                if debug:
                    print("[DEBUG] moov.box_type not found")
                break

def test_mp4_moov_box_type(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_file = tempfile.mktemp()
    shutil.copy(input_file, tmp_file)

    try:
        # Call the function with a test value
        mp4_moov_box_type(tmp_file, "moov", debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        # Clean up the temporary file
        os.remove(tmp_file)

# Example usage:
# test_mp4_moov_box_type('path_to_your_test_file.mp4')