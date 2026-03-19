import os
import shutil
import struct

def mp4_mvhd_version(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the file in binary mode
            data = f.read()
            
            # Look for the 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.version not found")
                return
            
            # The 'mvhd' box starts with a 4-byte size and 'mvhd' type
            # The version is the first byte after the 'mvhd' type
            version_pos = mvhd_pos + 8  # 4 bytes for size + 4 bytes for 'mvhd'
            
            # Read the current version
            old_version = data[version_pos]
            
            if debug:
                print(f"[DEBUG] mvhd.version before: {old_version}")
            
            # Replace with the new version
            f.seek(version_pos)
            f.write(struct.pack('B', value))
            
            if debug:
                print(f"[DEBUG] mvhd.version after: {value}")
    
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_version(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)
    
    try:
        # Call the function with a test value
        mp4_mvhd_version(tmp_path, 1, debug=True)
        print("Function executed successfully.")
    except Exception as e:
        print(f"Function execution failed: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_version('example.mp4')