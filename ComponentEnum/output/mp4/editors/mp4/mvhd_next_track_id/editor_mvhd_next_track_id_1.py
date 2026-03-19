import os
import struct
import shutil

def mp4_mvhd_next_track_id(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            file_content = f.read()
            
            # Search for 'mvhd' box
            mvhd_pos = file_content.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.next_track_id not found")
                return
            
            # Determine version to find the 'next_track_id'
            version = file_content[mvhd_pos + 8]
            if version == 0:
                next_track_id_pos = mvhd_pos + 96
            elif version == 1:
                next_track_id_pos = mvhd_pos + 108
            else:
                if debug:
                    print("[DEBUG] mvhd.next_track_id not found")
                return
            
            # Ensure we don't read or write out of bounds
            if next_track_id_pos + 4 > len(file_content):
                if debug:
                    print("[DEBUG] mvhd.next_track_id not found")
                return

            # Read current next_track_id
            old_value = struct.unpack('>I', file_content[next_track_id_pos:next_track_id_pos + 4])[0]
            
            if debug:
                print(f"[DEBUG] mvhd.next_track_id before: {old_value}")
            
            # Write new next_track_id
            new_value_bytes = struct.pack('>I', value)
            f.seek(next_track_id_pos)
            f.write(new_value_bytes)
            
            if debug:
                print(f"[DEBUG] mvhd.next_track_id after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_mvhd_next_track_id(input_file):
    import tempfile
    
    # Create a temporary copy of the input file
    temp_dir = tempfile.mkdtemp()
    temp_file = os.path.join(temp_dir, os.path.basename(input_file))
    shutil.copy(input_file, temp_file)

    try:
        test_value = 12345  # Representative test value for next_track_id
        mp4_mvhd_next_track_id(temp_file, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        if os.path.exists(temp_file):
            os.remove(temp_file)
        if os.path.exists(temp_dir):
            os.rmdir(temp_dir)