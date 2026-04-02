import os
import shutil
import struct

def mp4_mvhd_matrix_structure(fp, value, debug=False):
    # The matrix structure is 36 bytes long
    MATRIX_STRUCTURE_SIZE = 36
    MVHD_BOX_TYPE = b'mvhd'
    
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.matrix_structure not found")
                return

            # matrix: 36 bytes at mvhd_pos+40
            matrix_offset = mvhd_pos + 40
            current_matrix = data[matrix_offset:matrix_offset+MATRIX_STRUCTURE_SIZE]

            if len(current_matrix) != MATRIX_STRUCTURE_SIZE:
                if debug:
                    print("[DEBUG] mvhd.matrix_structure not found")
                return

            if debug:
                print(f"[DEBUG] mvhd.matrix_structure before: {current_matrix}")

            # Accept bytes or list of 9 ints
            if isinstance(value, (list, tuple)):
                write_val = struct.pack('>9I', *[v & 0xFFFFFFFF for v in value])
            else:
                write_val = value[:MATRIX_STRUCTURE_SIZE].ljust(MATRIX_STRUCTURE_SIZE, b'\x00')

            f.seek(matrix_offset)
            f.write(write_val)

            if debug:
                print(f"[DEBUG] mvhd.matrix_structure after: {write_val}")

    except Exception as e:
        if debug:
            print(f"An error occurred: {e}")

def test_mp4_mvhd_matrix_structure(input_file):
    import tempfile
    
    # Create a temporary file path
    tmp_path = tempfile.mktemp(suffix=".mp4")
    
    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)
        
        # Define a test value for the matrix structure (36 bytes)
        test_value = b'\x00\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00' \
                     b'\x00\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00' \
                     b'\x40\x00\x00\x00'
        
        # Call the function with debug=True
        mp4_mvhd_matrix_structure(tmp_path, test_value, debug=True)
        
        print("Function executed successfully")
    
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_matrix_structure('path_to_your_input_file.mp4')