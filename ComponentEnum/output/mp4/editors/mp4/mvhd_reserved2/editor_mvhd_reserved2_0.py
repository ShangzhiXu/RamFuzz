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
        with open(fp, 'r+b') as file:
            # Read the entire file into memory
            data = file.read()

            # Locate the 'mvhd' box
            pos = 0
            mvhd_found = False
            while pos < len(data):
                # Read box size and type
                if pos + 8 > len(data):
                    break
                size, box_type = struct.unpack('>I4s', data[pos:pos+8])
                if box_type == b'mvhd':
                    mvhd_found = True
                    break
                pos += size

            if not mvhd_found:
                if debug:
                    print("[DEBUG] mvhd.reserved2 not found")
                return

            # Move to the reserved2 field within the mvhd box
            # mvhd box structure: version(1) + flags(3) + creation_time(4) + modification_time(4) +
            # timescale(4) + duration(4) + rate(4) + volume(2) + reserved(10) + reserved2(4)
            reserved2_offset = pos + 20 + 20 + 4 + 2 + 10

            if reserved2_offset + 4 > len(data):
                if debug:
                    print("[DEBUG] mvhd.reserved2 not found")
                return

            # Read the current reserved2 value
            old_value = data[reserved2_offset:reserved2_offset+4]

            if debug:
                print(f"[DEBUG] mvhd.reserved2 before: {old_value}")

            # Replace with the new value
            data = data[:reserved2_offset] + value + data[reserved2_offset+4:]

            # Write the modified data back to the file
            file.seek(0)
            file.write(data)

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