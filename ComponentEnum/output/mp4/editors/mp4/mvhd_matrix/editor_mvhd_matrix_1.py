import os
import struct
import shutil
import tempfile

def mp4_mvhd_matrix(fp, value, debug=False):
    # Check if the input value is a list of length 9 (9 floats)
    if not isinstance(value, list) or len(value) != 9 or not all(isinstance(v, (int, float)) for v in value):
        raise ValueError("Value must be a list of 9 floats.")

    # Calculate the byte length of the matrix (9 floats, 4 bytes each)
    matrix_byte_length = 9 * 4  # 36 bytes

    def find_mvhd_matrix(data):
        # Locate the start of the 'mvhd' box and read its matrix component
        offset = 0
        while offset < len(data):
            if offset + 8 > len(data):
                break
            size, box_type = struct.unpack(">I4s", data[offset:offset+8])
            if box_type == b'mvhd':
                # Skip the full box header (version and flags) and other fields up to the matrix
                version_and_flags = 4
                skip_fields = 8 + 8 + 4 + 4 + 4 + 4  # creation, modification, timescale, duration
                matrix_start = offset + 8 + version_and_flags + skip_fields
                if matrix_start + matrix_byte_length <= len(data):
                    return matrix_start
            if size == 0:
                break  # Prevent infinite loop if size is zero
            offset += size
        return None

    # Ensure the file is opened in read-write binary mode
    with open(fp, 'rb+') as f:
        data = f.read()
        
        # Find the start of the mvhd matrix
        matrix_start = find_mvhd_matrix(data)

        if matrix_start is None:
            if debug:
                print("[DEBUG] mvhd.matrix not found")
            return

        # Unpack the existing matrix for debugging purposes
        old_matrix = struct.unpack(">9f", data[matrix_start:matrix_start + matrix_byte_length])
        if debug:
            print(f"[DEBUG] mvhd.matrix before: {old_matrix}")

        # Write the new matrix
        f.seek(matrix_start)
        f.write(struct.pack(">9f", *value))

        if debug:
            print(f"[DEBUG] mvhd.matrix after: {value}")

def test_mp4_mvhd_matrix(input_file):
    # Create a temporary file path
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, os.path.basename(input_file))

    try:
        # Copy the original file to the temporary path
        shutil.copy2(input_file, tmp_path)

        # Define a test value for the matrix (9 floats)
        test_value = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]

        # Call the function with debug enabled
        mp4_mvhd_matrix(tmp_path, test_value, debug=True)

        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# Example usage
# test_mp4_mvhd_matrix('path/to/input_file.mp4')