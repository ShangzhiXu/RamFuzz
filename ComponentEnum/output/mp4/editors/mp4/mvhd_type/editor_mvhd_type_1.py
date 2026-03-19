import os
import shutil

def mp4_mvhd_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The value must be a string with a maximum length of 4.")

    with open(fp, 'r+b') as file:
        data = file.read()
        
        # The 'mvhd' box is usually found within the 'moov' box, starting with 'mvhd' as type
        # Find the 'mvhd' box by searching for its type
        mvhd_start = data.find(b'mvhd')
        if mvhd_start == -1:
            if debug:
                print("[DEBUG] mvhd.type not found")
            return
        
        # The mvhd type itself is 'mvhd' (4 bytes), we assume it's at the start of the box
        current_value = data[mvhd_start:mvhd_start + 4].decode('utf-8')
        
        if debug:
            print(f"[DEBUG] mvhd.type before: {current_value}")
        
        # Write the new value, ensuring it's 4 bytes long by padding or truncating
        new_value = value.ljust(4)[:4].encode('utf-8')
        file.seek(mvhd_start)
        file.write(new_value)

        if debug:
            print(f"[DEBUG] mvhd.type after: {value}")

def test_mp4_mvhd_type(input_file):
    # Create a temporary copy of the input file
    tmp_path = f"{input_file}.tmp"
    shutil.copyfile(input_file, tmp_path)
    
    try:
        # Call the function with a test value
        mp4_mvhd_type(tmp_path, "mvhd", debug=True)
        print("Function executed successfully")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_type('example.mp4')