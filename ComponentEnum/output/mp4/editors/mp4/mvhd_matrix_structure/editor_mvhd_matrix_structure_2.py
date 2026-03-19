import os
import shutil
import struct

def mp4_mvhd_matrix_structure(fp, value, debug=False):
    # Ensure that value is a byte array of the correct length
    if not isinstance(value, (bytes, bytearray)) or len(value) != 36:
        raise ValueError("Value must be a byte array of length 36.")

    try:
        with open(fp, 'r+b') as file:
            file_content = file.read()

            mvhd_pos = file_content.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd box not found.")
                return

            # Determine if it's version 0 or version 1
            version_offset = mvhd_pos + 8
            if version_offset >= len(file_content):
                if debug:
                    print("[DEBUG] Insufficient data for version check.")
                return

            version = file_content[version_offset]
            header_len = 12 if version == 0 else 32
            creation_mod_size = 8 if version == 0 else 16
            
            matrix_offset = mvhd_pos + header_len + creation_mod_size + 12

            if matrix_offset + 36 > len(file_content):
                if debug:
                    print("[DEBUG] mvhd.matrix_structure incomplete or not found.")
                return

            old_value = file_content[matrix_offset: matrix_offset + 36]

            if debug:
                print(f"[DEBUG] mvhd.matrix_structure before: {old_value}")

            file.seek(matrix_offset)
            file.write(value)

            if debug:
                print(f"[DEBUG] mvhd.matrix_structure after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error encountered: {e}")

def test_mp4_mvhd_matrix_structure(input_file):
    # Make a temporary copy of the input file
    tmp_path = 'temp_' + os.path.basename(input_file)
    shutil.copy(input_file, tmp_path)
    
    try:
        # Define a test value for replacement
        test_value = b'\x00' * 36  # Dummy placeholder example, 36 zero bytes

        # Attempt to modify the mvhd.matrix_structure
        mp4_mvhd_matrix_structure(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)