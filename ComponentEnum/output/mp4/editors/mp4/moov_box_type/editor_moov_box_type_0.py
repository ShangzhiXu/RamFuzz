import os
import shutil
import struct

def mp4_moov_box_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Find the 'moov' box
            offset = 0
            while offset < len(data):
                # Read the size and type of the box
                if offset + 8 > len(data):
                    break
                size, box_type = struct.unpack('>I4s', data[offset:offset+8])
                box_type = box_type.decode('utf-8')

                if box_type == 'moov':
                    # Found the 'moov' box, read its box_type
                    moov_box_type_offset = offset + 4
                    old_value = box_type

                    if debug:
                        print(f"[DEBUG] moov.box_type before: {old_value}")

                    # Replace the box_type with the new value
                    new_value_bytes = value.encode('utf-8').ljust(4, b'\x00')
                    f.seek(moov_box_type_offset)
                    f.write(new_value_bytes)

                    if debug:
                        print(f"[DEBUG] moov.box_type after: {value}")

                    return

                # Move to the next box
                offset += size

            if debug:
                print("[DEBUG] moov.box_type not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_moov_box_type(input_file):
    import tempfile

    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".mp4")
    os.close(tmp_fd)

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Test value to replace 'moov.box_type'
        test_value = "moov"

        # Call the function with debug=True
        mp4_moov_box_type(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_moov_box_type('path_to_your_test_file.mp4')