import os
import shutil
import struct

def mp4_mvhd_next_track_id(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the file header to find the 'mvhd' atom
            while True:
                atom_header = f.read(8)
                if len(atom_header) < 8:
                    if debug:
                        print("[DEBUG] mvhd.next_track_id not found")
                    return
                
                atom_size, atom_type = struct.unpack('>I4s', atom_header)
                if atom_type == b'mvhd':
                    # Skip version and flags (4 bytes) and other fields to reach next_track_id
                    f.seek(96, os.SEEK_CUR)
                    
                    # Read the current next_track_id
                    current_value_bytes = f.read(4)
                    if len(current_value_bytes) < 4:
                        if debug:
                            print("[DEBUG] mvhd.next_track_id not found")
                        return
                    
                    current_value = struct.unpack('>I', current_value_bytes)[0]
                    
                    if debug:
                        print(f"[DEBUG] mvhd.next_track_id before: {current_value}")
                    
                    # Write the new value
                    f.seek(-4, os.SEEK_CUR)
                    f.write(struct.pack('>I', value))
                    
                    if debug:
                        print(f"[DEBUG] mvhd.next_track_id after: {value}")
                    
                    return
                else:
                    # Skip to the next atom
                    f.seek(atom_size - 8, os.SEEK_CUR)
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_next_track_id(input_file):
    import tempfile
    
    # Create a temporary file path
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, 'test.mp4')
    
    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)
        
        # Define a test value for next_track_id
        test_value = 123456789
        
        # Call the function with debug enabled
        mp4_mvhd_next_track_id(tmp_path, test_value, debug=True)
        
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# Example usage:
# test_mp4_mvhd_next_track_id('path_to_your_input_file.mp4')