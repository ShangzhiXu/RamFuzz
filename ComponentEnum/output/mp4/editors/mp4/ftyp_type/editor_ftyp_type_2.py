import os
import shutil

def mp4_ftyp_type(fp, value, debug=False):
    """
    Parse and rewrite the 'ftyp.type' component of an MP4 file.

    Args:
    - fp (str): path to the input MP4 file.
    - value (str): the new 'ftyp.type' to set in the file.
    - debug (bool): if True, print debug information.
    """
    try:
        with open(fp, 'rb+') as f:
            # Read the first 8 bytes to get the size and type of the "ftyp" box
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.type not found")
                return

            # Interpret size and type
            box_size = int.from_bytes(header[0:4], byteorder='big')
            box_type = header[4:8].decode('utf-8')

            # Validate we are looking at an "ftyp" box
            if box_type != "ftyp":
                if debug:
                    print("[DEBUG] ftyp.type not found")
                return

            # The next bytes are the major_brand field we want to rewrite
            f.seek(8)  # Move to "major brand" position in ftyp box
            old_value = f.read(4).decode('utf-8')

            if debug:
                print(f"[DEBUG] ftyp.type before: {old_value}")

            # Replace with new value
            f.seek(8)  # Re-position in case read moved it
            f.write(value.encode('utf-8'))

            if debug:
                print(f"[DEBUG] ftyp.type after: {value}")

    except IOError as e:
        if debug:
            print(f"[DEBUG] IOError: {e}")

def test_mp4_ftyp_type(input_file):
    """
    Test harness for mp4_ftyp_type function.
    
    Args:
    - input_file (str): Path to an input MP4 file for testing.
    """
    import tempfile

    # Create a temporary copy of the input file for testing
    tmp_path = tempfile.mktemp(suffix=".mp4")

    # Copy the original file to a temp location
    shutil.copy(input_file, tmp_path)

    try:
        # Call function with the temp file and a test new value
        value = "test"
        mp4_ftyp_type(tmp_path, value, debug=True)
        print("Test executed successfully")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)