import os
import shutil
import struct

def mp4_mvhd_matrix(fp, value, debug=False):
    def find_mvhd_matrix_offset(data):
        # Locate the 'mvhd' box and then the matrix within it
        offset = 0
        while offset < len(data):
            size, box_type = struct.unpack('>I4s', data[offset:offset+8])
            if box_type == b'mvhd':
                # Skip to the matrix part within the 'mvhd' box
                version_flags = 4
                creation_modification_time = 8
                timescale_duration = 8
                rate_volume_reserved = 8
                matrix_offset = offset + 8 + version_flags + creation_modification_time + timescale_duration + rate_volume_reserved
                return matrix_offset
            offset += size
        return None

    # Read the file content
    with open(fp, 'rb') as f:
        data = f.read()

    # Find the mvhd matrix offset
    matrix_offset = find_mvhd_matrix_offset(data)
    if matrix_offset is None:
        if debug:
            print("[DEBUG] mvhd.matrix not found")
        return

    # Read the current matrix value
    old_value = data[matrix_offset:matrix_offset+36]

    if debug:
        print(f"[DEBUG] mvhd.matrix before: {list(old_value)}")

    # Prepare the new matrix value
    new_value = struct.pack('>9I', *value)

    # Replace the old matrix with the new one
    new_data = data[:matrix_offset] + new_value + data[matrix_offset+36:]

    # Write the modified content back to the file
    with open(fp, 'wb') as f:
        f.write(new_data)

    if debug:
        print(f"[DEBUG] mvhd.matrix after: {list(new_value)}")

def test_mp4_mvhd_matrix(input_file):
    # Create a temporary file path
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Define a test value for the matrix (9 integers)
        test_value = [0x00010000, 0, 0, 0, 0x00010000, 0, 0, 0, 0x40000000]

        # Call the function with debug enabled
        mp4_mvhd_matrix(tmp_path, test_value, debug=True)

        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)