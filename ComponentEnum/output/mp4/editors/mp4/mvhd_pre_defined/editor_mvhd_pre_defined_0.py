import os
import shutil

def mp4_mvhd_pre_defined(fp, value, debug=False):
    """
    Parses the 'mvhd.pre_defined' component from an input MP4 file and rewrites it with the specified value.

    :param fp: Path to the input file. The function modifies the file in-place.
    :param value: The new value to write for this component. Its Python type should match the component's data type (bytes).
    :param debug: If True, print the component value BEFORE and AFTER rewriting.
    """
    # Constants for locating the 'mvhd' atom and 'pre_defined' field
    MVHD_ATOM = b'mvhd'
    PRE_DEFINED_OFFSET = 20  # Offset from the start of 'mvhd' to 'pre_defined'
    PRE_DEFINED_SIZE = 12  # Size of 'pre_defined' field in bytes

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            file_data = f.read()

            # Locate the 'mvhd' atom
            mvhd_pos = file_data.find(MVHD_ATOM)
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.pre_defined not found")
                return

            # Calculate the position of the 'pre_defined' field
            pre_defined_pos = mvhd_pos + PRE_DEFINED_OFFSET

            # Ensure the file has enough data for the 'pre_defined' field
            if pre_defined_pos + PRE_DEFINED_SIZE > len(file_data):
                if debug:
                    print("[DEBUG] mvhd.pre_defined field is out of file bounds")
                return

            # Read the current 'pre_defined' value
            old_value = file_data[pre_defined_pos:pre_defined_pos + PRE_DEFINED_SIZE]

            if debug:
                print(f"[DEBUG] mvhd.pre_defined before: {old_value}")

            # Validate the new value length
            if not isinstance(value, bytes) or len(value) != PRE_DEFINED_SIZE:
                if debug:
                    print(f"[DEBUG] Error: new value must be bytes of length {PRE_DEFINED_SIZE}")
                return

            # Replace the 'pre_defined' value with the new value
            new_file_data = (
                file_data[:pre_defined_pos] +
                value +
                file_data[pre_defined_pos + PRE_DEFINED_SIZE:]
            )

            # Write the modified data back to the file
            f.seek(0)
            f.write(new_file_data)

            if debug:
                print(f"[DEBUG] mvhd.pre_defined after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error processing file: {e}")

def test_mp4_mvhd_pre_defined(input_file):
    """
    Test harness for the mp4_mvhd_pre_defined function.

    :param input_file: Path to the input MP4 file to test.
    """
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Define a test value for 'pre_defined'
        test_value = b'\x00' * 12  # Example test value

        # Call the function with debug enabled
        mp4_mvhd_pre_defined(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)