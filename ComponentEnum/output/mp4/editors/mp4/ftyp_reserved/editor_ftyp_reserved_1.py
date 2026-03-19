import os
import shutil
import struct

def mp4_ftyp_reserved(fp, value, debug=False):
    """
    Parses and rewrites the 'ftyp.reserved' component in an MP4 file.

    Parameters:
    - fp: str, path to the input file. The function modifies the file in-place.
    - value: bytes, the new value to write for this component.
    - debug: bool, if True, print debug information.
    """
    if not isinstance(value, bytes):
        raise ValueError("Value must be of type bytes.")

    # Helper function to find 'ftyp' box and read 'reserved' component
    def find_ftyp_reserved(data):
        offset = 0
        while offset < len(data):
            size = struct.unpack(">I", data[offset:offset + 4])[0]
            box_type = data[offset + 4:offset + 8]

            if box_type == b'ftyp':
                # ftyp box found, read its contents
                major_brand = data[offset + 8:offset + 12]
                minor_version = data[offset + 12:offset + 16]
                reserved = data[offset + 16:size]  # reserved box content
                return offset, size, reserved

            offset += size

        return None, None, None

    # Open the file in binary mode and read its contents
    with open(fp, 'rb') as f:
        file_data = f.read()

    offset, box_size, old_reserved = find_ftyp_reserved(file_data)
    
    if old_reserved is None:
        if debug:
            print("[DEBUG] ftyp.reserved not found")
        return

    if debug:
        print(f"[DEBUG] ftyp.reserved before: {old_reserved}")

    # Construct new ftyp box with the new reserved value
    new_ftyp = (file_data[:offset + 16] + value + 
                file_data[offset + 16 + len(old_reserved):offset + box_size] +
                file_data[offset + box_size:])

    # Write the new data back to the file
    with open(fp, 'wb') as f:
        f.write(new_ftyp)

    if debug:
        print(f"[DEBUG] ftyp.reserved after: {value}")

def test_mp4_ftyp_reserved(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + ".tmp"
    shutil.copy(input_file, tmp_path)

    try:
        # Define a test value for 'ftyp.reserved'
        test_value = b'\x00\x00\x00\x00'  # Example: empty reserved bytes

        # Call the function with debug=True
        mp4_ftyp_reserved(tmp_path, test_value, debug=True)

        # Print success message
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)