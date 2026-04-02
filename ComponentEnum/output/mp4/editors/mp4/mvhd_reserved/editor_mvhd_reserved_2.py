import os
import shutil
import struct

def mp4_mvhd_reserved(fp, value, debug=False):
    try:
        # Ensure that the provided value is a bytes object and has the correct length
        if not isinstance(value, bytes) or len(value) != 12:
            raise ValueError("The provided value must be a bytes object of length 12.")
        
        with open(fp, 'r+b') as file:
            content = file.read()
            # Find the 'mvhd' atom
            mvhd_pos = content.find(b'mvhd')
            
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd atom not found")
                return
            
            # The position of 'mvhd' atom indicates the start of the atom
            atom_size_pos = mvhd_pos - 4
            if atom_size_pos < 0 or atom_size_pos + 4 > len(content):
                if debug:
                    print("[DEBUG] Unable to read atom size")
                return
            
            atom_size, = struct.unpack('>I', content[atom_size_pos:mvhd_pos])
            
            # Calculate position to skip version (1 byte), flags (3 bytes), and two timestamps (8 bytes each)
            reserved_pos = mvhd_pos + 1 + 3 + 8 + 8
            
            if reserved_pos + 12 > len(content):
                if debug:
                    print("[DEBUG] File seems corrupt or mvhd is incomplete")
                return
            
            # Read current reserved value (12 bytes)
            current_reserved_value = content[reserved_pos:reserved_pos + 12]
            if debug:
                print(f"[DEBUG] mvhd.reserved before: {current_reserved_value}")
            
            # Modify the reserved part
            file.seek(reserved_pos)
            file.write(value)
            if debug:
                print(f"[DEBUG] mvhd.reserved after: {value}")
    
    except ValueError as e:
        if debug:
            print(f"[DEBUG] ValueError: {e}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_reserved(input_file):
    temp_file = 'temp_mp4_file.mp4'
    shutil.copy(input_file, temp_file)
    
    try:
        # A representative test value (must be 12 bytes long)
        test_value = b'\x00' * 12
        
        mp4_mvhd_reserved(temp_file, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        # Clean up temporary file
        os.remove(temp_file)

# Example usage (assuming 'example.mp4' is your input test file):
# test_mp4_mvhd_reserved('example.mp4')