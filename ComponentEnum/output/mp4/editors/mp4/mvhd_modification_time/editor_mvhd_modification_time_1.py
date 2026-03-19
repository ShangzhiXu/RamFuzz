import struct
import os
import shutil
import tempfile

def mp4_mvhd_modification_time(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the whole file into memory
            data = f.read()
            
            # Look for the 'mvhd' box
            mvhd_start = data.find(b'mvhd')
            if mvhd_start == -1:
                if debug:
                    print("[DEBUG] mvhd.modification_time not found")
                return

            # The 'mvhd' box header is 8 bytes: 4 bytes for size and 4 bytes for 'mvhd'
            mvhd_header_size = 8
            mvhd_full_pos = mvhd_start + mvhd_header_size
            
            # The 'mvhd' box starts with a version and flags (4 bytes total)
            # Followed by creation_time (4 bytes), then modification_time (4 bytes)
            version_and_flags_size = 4
            time_fields_size = 8  # creation_time (4) + modification_time (4)
            
            modification_time_pos = mvhd_full_pos + version_and_flags_size + 4

            # Read the current modification_time
            current_modification_time = struct.unpack_from('>I', data, modification_time_pos)[0]
            
            if debug:
                print(f"[DEBUG] mvhd.modification_time before: {current_modification_time}")
            
            # Write the new modification_time
            new_data = struct.pack('>I', value)
            f.seek(modification_time_pos)
            f.write(new_data)
            
            if debug:
                print(f"[DEBUG] mvhd.modification_time after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error processing file {fp}: {e}")

def test_mp4_mvhd_modification_time(input_file):
    # Create a temporary file path
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, os.path.basename(input_file))
    
    try:
        # Copy input file to the temporary path
        shutil.copy(input_file, tmp_path)
        
        # Test value for modification_time
        test_value = 3000000000  # Example value within the common range
        
        # Call the function
        mp4_mvhd_modification_time(tmp_path, test_value, debug=True)
        
        print("Test execution completed successfully.")
        
    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# Example usage:
# test_mp4_mvhd_modification_time('path_to_your_input_file.mp4')