import os
import struct
import shutil

def mp4_mvhd_creation_time(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            file_data = f.read()
            
            # The mvhd box type is 'mvhd', and it starts with a header
            # We need to find the 'mvhd' box in the file
            mvhd_index = file_data.find(b'mvhd')
            if mvhd_index == -1:
                if debug:
                    print("[DEBUG] mvhd.creation_time not found")
                return
            
            # The 'mvhd' box has a version, flags, and then the creation time
            # The structure is: version (1 byte), flags (3 bytes), creation time (4 bytes)
            # Offset from 'mvhd' to creation time: 4 bytes (version + flags)
            creation_time_offset = mvhd_index + 4
            
            # Read the current creation time
            old_value = struct.unpack('>I', file_data[creation_time_offset:creation_time_offset + 4])[0]
            if debug:
                print(f"[DEBUG] mvhd.creation_time before: {old_value}")
            
            # Write the new value
            new_value_bytes = struct.pack('>I', value)
            file_data = file_data[:creation_time_offset] + new_value_bytes + file_data[creation_time_offset + 4:]
            
            # Move the file pointer to the beginning of the file and write the modified data
            f.seek(0)
            f.write(file_data)
            
            if debug:
                print(f"[DEBUG] mvhd.creation_time after: {value}")

    except IOError as e:
        print(f"An error occurred while processing the file: {e}")

def test_mp4_mvhd_creation_time(input_file):
    # Create a temporary path for the test
    tmp_path = input_file + '.tmp'
    
    # Copy the input file to the temporary path
    shutil.copy(input_file, tmp_path)
    
    try:
        # Representative test value for the creation time
        test_value = 2082844800  # Example value within the common range
        
        # Call the function with debug set to True
        mp4_mvhd_creation_time(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
        
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_creation_time('path_to_your_test_file.mp4')