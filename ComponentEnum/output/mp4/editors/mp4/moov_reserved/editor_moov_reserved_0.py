import os
import shutil
import struct

def mp4_moov_reserved(fp, value, debug=False):
    def find_moov_reserved(fp):
        with open(fp, 'rb') as f:
            while True:
                # Read the size and type of the next box
                header = f.read(8)
                if len(header) < 8:
                    break
                size, box_type = struct.unpack('>I4s', header)
                
                if box_type == b'moov':
                    # Read the entire 'moov' box
                    moov_data = f.read(size - 8)
                    # Look for 'reserved' within 'moov'
                    reserved_index = moov_data.find(b'reserved')
                    if reserved_index != -1:
                        return f.tell() - len(moov_data) + reserved_index, len('reserved')
                else:
                    # Skip to the next box
                    f.seek(size - 8, os.SEEK_CUR)
        return None, None

    reserved_pos, reserved_len = find_moov_reserved(fp)
    
    if reserved_pos is None:
        if debug:
            print("[DEBUG] moov.reserved not found")
        return

    with open(fp, 'r+b') as f:
        f.seek(reserved_pos)
        old_value = f.read(reserved_len)
        
        if debug:
            print(f"[DEBUG] moov.reserved before: {old_value}")
        
        # Write the new value
        f.seek(reserved_pos)
        f.write(value)
        
        if debug:
            print(f"[DEBUG] moov.reserved after: {value}")

def test_mp4_moov_reserved(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the 'reserved' component
        test_value = b'newresvd'
        
        # Call the function with debug=True
        mp4_moov_reserved(tmp_path, test_value, debug=True)
        
        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_moov_reserved('example.mp4')