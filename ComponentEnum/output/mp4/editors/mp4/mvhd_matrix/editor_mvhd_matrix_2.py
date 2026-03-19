import os
import struct
import shutil

def mp4_mvhd_matrix(fp, value, debug=False):
    # Ensure the replacement value is the correct length
    if not isinstance(value, (bytes, bytearray)) or len(value) != 36:
        raise ValueError("Value must be a bytes or bytearray of length 36.")

    try:
        with open(fp, 'r+b') as file:
            # Read the entire file to find the mvhd atom 
            file_data = file.read()
            
            # Find the beginning of the 'mvhd' box
            mvhd_start = file_data.find(b'mvhd')
            if mvhd_start == -1:
                if debug:
                    print("[DEBUG] 'mvhd' box not found in the file")
                return

            # Move to the start of the 'mvhd' box
            offset = mvhd_start + 4  # Skip the 'mvhd' string itself

            # Read version and flags (version is 1 byte, flags are 3 bytes)
            version_flags = struct.unpack_from('>I', file_data, offset)[0]
            offset += 4

            # Determine matrix offset based on version
            if (version_flags >> 24) == 1:
                # If version 1, skip creation and modification times (8 bytes each)
                # Skip time scale (4 bytes) and duration (8 bytes)
                offset += 28
            else:
                # Version 0; skip creation and modification times (4 bytes each)
                # Skip time scale (4 bytes) and duration (4 bytes)
                offset += 16
            
            # Now skip the rate (4 bytes), volume (2 bytes), and reserved (10 bytes)
            offset += 16
            
            # Verify if the file has enough data to contain the matrix
            if offset + 36 > len(file_data):
                if debug:
                    print("[DEBUG] Insufficient data in file to contain a complete matrix.")
                return
            
            # Debug output before replacement
            matrix_before = file_data[offset:offset+36]
            if debug:
                print(f"[DEBUG] mvhd.matrix before: {matrix_before}")
            
            # Overwrite the matrix with the new value
            file.seek(offset)
            file.write(value)
        
            if debug:
                print(f"[DEBUG] mvhd.matrix after: {value}")
        
    except Exception as e:
        print(f"Error manipulating the file: {e}")

def test_mp4_mvhd_matrix(input_file):
    # Setup a temporary path
    tmp_path = 'temp_test_file.mp4'
    shutil.copy(input_file, tmp_path)

    # Define a test matrix value (36 bytes)
    test_value = bytes(range(1, 37))  # Ensure this is correctly formatted

    # Invoke the function
    try:
        mp4_mvhd_matrix(tmp_path, test_value, debug=True)
        print("Function executed successfully")
    except Exception as e:
        print(f"Function failed with error: {e}")
    finally:
        # Clean up temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)