import os
import struct
import shutil

def mp4_mvhd_modification_time(fp, value, debug=False):
    """
    Parses and modifies the 'mvhd.modification_time' component of an MP4 file.

    :param fp: Path to the input file. The function modifies the file in-place.
    :param value: The new value to write for this component (uint32).
    :param debug: If True, print debug information.
    """
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Find 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.modification_time not found")
                return

            # The 'mvhd' box starts with a 4-byte size and the 'mvhd' type
            # The modification_time is located at offset 16 from the start of 'mvhd'
            modification_time_offset = mvhd_pos + 16

            # Read the current modification_time
            old_value = struct.unpack('>I', data[modification_time_offset:modification_time_offset + 4])[0]

            if debug:
                print(f"[DEBUG] mvhd.modification_time before: {old_value}")

            # Write the new modification_time
            new_value_bytes = struct.pack('>I', value)
            f.seek(modification_time_offset)
            f.write(new_value_bytes)

            if debug:
                print(f"[DEBUG] mvhd.modification_time after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_modification_time(input_file):
    """
    Test harness for the mp4_mvhd_modification_time function.

    :param input_file: Path to the input MP4 file.
    """
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for modification_time
        test_value = 2100000000

        # Call the function with debug enabled
        mp4_mvhd_modification_time(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_modification_time('example.mp4')