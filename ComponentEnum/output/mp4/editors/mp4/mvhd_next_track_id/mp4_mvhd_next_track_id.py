import os
import shutil
import struct

def mp4_mvhd_next_track_id(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.next_track_id not found")
                return

            # next_track_ID: 4 bytes at mvhd_pos+100
            offset = mvhd_pos + 100
            current_value = struct.unpack('>I', data[offset:offset+4])[0]

            if debug:
                print(f"[DEBUG] mvhd.next_track_id before: {current_value}")

            f.seek(offset)
            f.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] mvhd.next_track_id after: {value}")

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