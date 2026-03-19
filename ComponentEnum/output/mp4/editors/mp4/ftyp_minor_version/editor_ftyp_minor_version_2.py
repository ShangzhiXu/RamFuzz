import os
import struct
import shutil

def mp4_ftyp_minor_version(fp, value, debug=False):
    # Ensure `value` is within the uint32 range
    if not (0 <= value <= 0xFFFFFFFF):
        raise ValueError("Value must be a uint32.")

    try:
        with open(fp, 'r+b') as file:
            while True:
                # Read the box size and type
                header = file.read(8)
                if len(header) < 8:
                    break

                size, box_type = struct.unpack('>I4s', header)

                if box_type == b'ftyp':
                    # Found the 'ftyp' box, read the brand and skip 4 bytes
                    brand_data = file.read(4)
                    minor_version_data = file.read(4)
                    
                    # Read and print the current minor version
                    old_value = struct.unpack('>I', minor_version_data)[0]
                    if debug:
                        print(f"[DEBUG] ftyp.minor_version before: {old_value}")
                    
                    # Modify the minor version to the new value
                    file.seek(file.tell() - 4)  # Move back 4 bytes to overwrite
                    file.write(struct.pack('>I', value))
                    
                    # Debug the new value
                    if debug:
                        print(f"[DEBUG] ftyp.minor_version after: {value}")
                    return

                # Move to the next box
                file.seek(size - 8, os.SEEK_CUR)
                
        # If we went through the file and didn't find an 'ftyp' box
        if debug:
            print("[DEBUG] ftyp.minor_version not found")

    except (OSError, struct.error) as e:
        if debug:
            print(f"[DEBUG] Encountered an error: {e}")

def test_mp4_ftyp_minor_version(input_file):
    import tempfile
    import shutil
    
    # Create a temporary file for testing
    temp_file = tempfile.mkstemp()[1]
    try:
        # Copy the contents of `input_file` to `temp_file`
        shutil.copy(input_file, temp_file)
        
        # Define a test value
        test_value = 1234567890  # A representative uint32 test value
        
        # Call the function with debug True
        mp4_ftyp_minor_version(temp_file, test_value, debug=True)
        
        print("Function executed successfully")

    finally:
        # Clean up the temporary file
        os.remove(temp_file)