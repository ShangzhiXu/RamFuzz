import os
import shutil
import struct

def mp4_mvhd_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Look for the 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.type not found")
                return

            # The 'mvhd' box type is located 4 bytes after the 'mvhd' string
            type_pos = mvhd_pos + 4

            # Read the current value
            old_value = data[type_pos:type_pos + 4].decode('utf-8', errors='ignore')

            if debug:
                print(f"[DEBUG] mvhd.type before: {old_value}")

            # Replace with the new value, ensuring it is exactly 4 bytes
            new_value = value.ljust(4, '\0').encode('utf-8')
            data = data[:type_pos] + new_value + data[type_pos + 4:]

            # Write the modified data back to the file
            f.seek(0)
            f.write(data)

            if debug:
                print(f"[DEBUG] mvhd.type after: {value}")

    except Exception as e:
        print(f"An error occurred: {e}")

def test_mp4_mvhd_type(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the mvhd.type component
        test_value = "mvhd"

        # Call the function with debug enabled
        mp4_mvhd_type(tmp_path, test_value, debug=True)

        # If no exception was raised, the function executed successfully
        print("Function executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)