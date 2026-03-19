import os
import shutil
import struct

def mp4_mvhd_matrix_structure(fp, value, debug=False):
    # The matrix structure is 36 bytes long
    MATRIX_STRUCTURE_SIZE = 36
    MVHD_BOX_TYPE = b'mvhd'
    
    try:
        with open(fp, 'r+b') as f:
            # Read the file to find the mvhd box
            while True:
                # Read the box header (8 bytes: 4 bytes size, 4 bytes type)
                header = f.read(8)
                if len(header) < 8:
                    break  # End of file reached
                
                box_size, box_type = struct.unpack('>I4s', header)
                
                if box_type == MVHD_BOX_TYPE:
                    # Found the mvhd box, read its content
                    version_flags = f.read(4)  # 4 bytes for version and flags
                    creation_time = f.read(4)  # 4 bytes for creation time
                    modification_time = f.read(4)  # 4 bytes for modification time
                    timescale = f.read(4)  # 4 bytes for timescale
                    duration = f.read(4)  # 4 bytes for duration
                    rate = f.read(4)  # 4 bytes for rate
                    volume = f.read(2)  # 2 bytes for volume
                    reserved = f.read(10)  # 10 bytes reserved
                    
                    # Read the current matrix structure
                    current_matrix = f.read(MATRIX_STRUCTURE_SIZE)
                    
                    if len(current_matrix) != MATRIX_STRUCTURE_SIZE:
                        print("[DEBUG] mvhd.matrix_structure not found")
                        return
                    
                    if debug:
                        print(f"[DEBUG] mvhd.matrix_structure before: {current_matrix}")
                    
                    # Ensure the new value is the correct length
                    if len(value) != MATRIX_STRUCTURE_SIZE:
                        raise ValueError(f"Value must be {MATRIX_STRUCTURE_SIZE} bytes long")
                    
                    # Write the new matrix structure
                    f.seek(-MATRIX_STRUCTURE_SIZE, os.SEEK_CUR)
                    f.write(value)
                    
                    if debug:
                        print(f"[DEBUG] mvhd.matrix_structure after: {value}")
                    
                    return  # Successfully modified the file
                
                else:
                    # Skip to the next box
                    f.seek(box_size - 8, os.SEEK_CUR)
        
        print("[DEBUG] mvhd.matrix_structure not found")
    
    except Exception as e:
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