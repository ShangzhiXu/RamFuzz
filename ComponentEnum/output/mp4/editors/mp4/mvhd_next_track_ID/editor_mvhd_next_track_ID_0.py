import os
import struct
import shutil

def mp4_mvhd_next_track_ID(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()
            
            # Find the 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.next_track_ID not found")
                return
            
            # 'mvhd' box is found, locate the next_track_ID
            # Skip the 'mvhd' header (4 bytes for size, 4 bytes for 'mvhd')
            mvhd_header_size = 8
            mvhd_start = mvhd_pos + mvhd_header_size
            
            # Determine version to find the correct offset
            version = data[mvhd_start]
            if version == 0:
                # Version 0: skip 96 bytes to reach next_track_ID
                next_track_id_offset = mvhd_start + 96
            elif version == 1:
                # Version 1: skip 104 bytes to reach next_track_ID
                next_track_id_offset = mvhd_start + 104
            else:
                if debug:
                    print("[DEBUG] mvhd.next_track_ID not found")
                return
            
            # Read the current next_track_ID value
            old_value = struct.unpack('>I', data[next_track_id_offset:next_track_id_offset + 4])[0]
            
            if debug:
                print(f"[DEBUG] mvhd.next_track_ID before: {old_value}")
            
            # Write the new value
            new_value_bytes = struct.pack('>I', value)
            f.seek(next_track_id_offset)
            f.write(new_value_bytes)
            
            if debug:
                print(f"[DEBUG] mvhd.next_track_ID after: {value}")
                
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_next_track_ID(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + ".tmp"
    shutil.copy(input_file, tmp_path)
    
    try:
        # Call the function with a test value
        test_value = 123456789  # Example test value within uint32 range
        mp4_mvhd_next_track_ID(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)