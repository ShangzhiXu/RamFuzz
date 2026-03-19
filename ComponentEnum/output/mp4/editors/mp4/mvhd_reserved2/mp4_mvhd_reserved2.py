import os
import shutil
import struct

def mp4_mvhd_reserved2(fp, value, debug=False):
    """
    Parses the 'mvhd.reserved2' component from an input mp4 file and rewrites it with the specified value.

    :param fp: Path to the input file. The function modifies the file in-place.
    :param value: The new value to write for this component. Its type should be bytes.
    :param debug: If True, print the component value BEFORE and AFTER rewriting.
    """
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.reserved2 not found")
                return

            # reserved2: treat as the latter part of the 10-byte reserved field
            # reserved is at mvhd_pos+30 (10 bytes). Split: reserved=first 4, reserved2=last 6.
            reserved2_offset = mvhd_pos + 34
            write_len = 6

            old_value = data[reserved2_offset:reserved2_offset+write_len]

            if debug:
                print(f"[DEBUG] mvhd.reserved2 before: {old_value}")

            f.seek(reserved2_offset)
            f.write(value[:write_len].ljust(write_len, b'\x00'))

            if debug:
                print(f"[DEBUG] mvhd.reserved2 after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error processing file: {e}")

def test_mp4_mvhd_reserved2(input_file):
    """
    Test harness for the mp4_mvhd_reserved2 function.

    :param input_file: Path to the input file to be tested.
    """
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Define a test value for the reserved2 component
        test_value = b'\x00\x00\x00\x00'

        # Call the function with debug=True
        mp4_mvhd_reserved2(tmp_path, test_value, debug=True)

        # If no exceptions, print success
        print("Function executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_reserved2('example.mp4')