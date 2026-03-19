import os
import shutil
import struct

def mp4_ftyp_size(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as file:
            # Read the first 8 bytes which usually is size and 'ftyp' type
            file.seek(0)
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.size not found")
                return
            
            # Check if this is an 'ftyp' box
            current_size, box_type = struct.unpack('>I4s', header)
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.size not found")
                return
            
            if debug:
                print(f"[DEBUG] ftyp.size before: {current_size}")
            
            # Overwrite the size with the new value
            file.seek(0)
            file.write(struct.pack('>I', value))
            
            if debug:
                print(f"[DEBUG] ftyp.size after: {value}")
    except Exception as e:
        print(f"[ERROR] An error occurred: {e}")

def test_mp4_ftyp_size(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.temp'
    shutil.copy(input_file, tmp_path)
    
    try:
        test_value = 1024  # A representative test value for 'ftyp.size'
        mp4_ftyp_size(tmp_path, test_value, debug=True)

        # Optionally, verify that the value was updated
        with open(tmp_path, 'rb') as file:
            file.seek(0)
            after_size = struct.unpack('>I', file.read(4))[0]
            success = after_size == test_value
            print("Test executed successfully") if success else print("Test failed")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_size('path_to_your_input_mp4_file.mp4')