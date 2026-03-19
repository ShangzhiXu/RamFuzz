import os
import shutil
import struct

def mp4_mvhd_matrix_structure(fp, value, debug=False):
    # Constants and assumptions
    MVHD_ATOM = b'mvhd'
    MATRIX_STRUCTURE_SIZE = 36  # bytes

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            file_content = f.read()
            
            # Locate the 'mvhd' atom
            mvhd_pos = file_content.find(MVHD_ATOM)
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.atom not found")
                return
            
            # 'mvhd' atom is found, parse the size and version/flags
            mvhd_start = mvhd_pos - 4
            mvhd_size = struct.unpack('>I', file_content[mvhd_start:mvhd_start + 4])[0]

            # Calculate the position of the matrix structure
            # Position logic: size(4 bytes) + type(4 bytes) + version/flags(4 bytes) + other fields
            # Skip: creation_time(4), modification_time(4), timescale(4), duration(4), rate(4), volume(2), reserved(10)
            matrix_structure_pos = mvhd_start + 32 + 4 + 4 + 4 + 4 + 4 + 2 + 10

            if matrix_structure_pos + MATRIX_STRUCTURE_SIZE > mvhd_start + mvhd_size:
                if debug:
                    print("[DEBUG] mvhd.matrix_structure not found within valid range")
                return

            # Extract the current matrix structure
            old_value = file_content[matrix_structure_pos:matrix_structure_pos + MATRIX_STRUCTURE_SIZE]
            
            # Debug output before modification
            if debug:
                print(f"[DEBUG] mvhd.matrix_structure before: {list(old_value)}")

            # Validate and prepare new value (ensure it's the correct size)
            if not isinstance(value, (bytes, bytearray)) or len(value) != MATRIX_STRUCTURE_SIZE:
                raise ValueError(f"The provided value must be a byte array of size {MATRIX_STRUCTURE_SIZE}.")

            # Update the matrix structure
            f.seek(matrix_structure_pos)
            f.write(value)

            # Debug output after modification
            if debug:
                print(f"[DEBUG] mvhd.matrix_structure after: {list(value)}")

    except Exception as e:
        print(f"An error occurred: {e}")

def test_mp4_mvhd_matrix_structure(input_file):
    import tempfile

    # Create a temporary copy of the input file
    with tempfile.NamedTemporaryFile(delete=False) as temp_file:
        tmp_path = temp_file.name
        shutil.copy(input_file, tmp_path)
    
    try:
        # A representative test value for the matrix structure component
        MATRIX_STRUCTURE_SIZE = 36  # Ensure the size constant is available here
        test_value = bytearray([0] * MATRIX_STRUCTURE_SIZE)  # Create a valid test value of the correct size
        mp4_mvhd_matrix_structure(tmp_path, test_value, debug=True)

        print("Function executed successfully")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)