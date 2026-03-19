import os
import shutil
import struct

def mp4_moov_type(fp, value, debug=False):
    # The moov.type component is a 4 character string.
    assert isinstance(value, str) and len(value) <= 4, "Value must be a string with max length of 4."

    try:
        with open(fp, 'r+b') as f:
            # Scan through the file to locate the 'moov' box
            while True:
                # Read the box header (4 bytes for size, 4 bytes for type)
                header = f.read(8)
                if len(header) < 8:
                    if debug:
                        print("[DEBUG] moov.type not found")
                    return  # End of file reached; component not found
                
                size, box_type = struct.unpack('>I4s', header)
                
                # Convert box type from bytes to string
                box_type = box_type.decode('utf-8')
                
                if box_type == 'moov':
                    # Found 'moov' box; read type value
                    old_value = box_type

                    if debug:
                        print(f"[DEBUG] moov.type before: {old_value}")
                    
                    # Move the file pointer to the 'type' start and replace with new value
                    f.seek(-4, os.SEEK_CUR)  # Move back 4 bytes to overwrite
                    f.write(value.ljust(4).encode('utf-8'))  # Ensure 4 bytes used

                    if debug:
                        print(f"[DEBUG] moov.type after: {value}")
                    
                    return  # Successfully modified
                else:
                    # Move to the next box, subtract header length
                    f.seek(size - 8, os.SEEK_CUR)
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {str(e)}")

def test_mp4_moov_type(input_file):
    # Use a representative value for testing
    test_value = "moov"
    
    # Create a temporary copy of the input file
    temp_file = input_file + ".tmp"
    shutil.copy(input_file, temp_file)

    try:
        # Call the function with debugging enabled
        mp4_moov_type(temp_file, test_value, debug=True)
        print("[TEST] Function executed successfully")
    finally:
        # Clean up the temporary file
        if os.path.exists(temp_file):
            os.remove(temp_file)