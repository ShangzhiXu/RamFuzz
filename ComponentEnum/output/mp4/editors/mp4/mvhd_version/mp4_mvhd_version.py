import struct
import os
import shutil

def mp4_mvhd_version(fp, value, debug=False):
    if not (0 <= value <= 255):
        raise ValueError("Value must be an uint8 (0-255).")

    try:
        with open(fp, 'r+b') as file:
            content = file.read()
            
            # Find 'mvhd' box
            mvhd_pos = content.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.version not found")
                return
            
            # The 'mvhd' version is 4 bytes after the start of the 'mvhd' box
            version_pos = mvhd_pos + 4
            
            # Read current version
            old_value = struct.unpack_from('>B', content, version_pos)[0]
            if debug:
                print(f"[DEBUG] mvhd.version before: {old_value}")
            
            # Rewrite version
            file.seek(version_pos)
            file.write(struct.pack('>B', value))
            
            if debug:
                print(f"[DEBUG] mvhd.version after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_version(input_file):
    import tempfile
    
    # Create a temporary file path
    with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
        tmp_path = tmp_file.name
    
    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)
        
        # Call the function with a test value (e.g., 1)
        mp4_mvhd_version(tmp_path, 1, debug=True)
        
        print("Function executed successfully.")
        
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)