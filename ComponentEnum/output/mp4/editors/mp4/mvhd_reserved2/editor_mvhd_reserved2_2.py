import os
import shutil
import struct

def mp4_mvhd_reserved2(fp, value, debug=False):
    def find_mvhd_reserved2_position(file_data):
        offset = 4  # Skip the size of the container
        while offset < len(file_data) - 4:  # Reserve space for 'mvhd' scan
            size, typ = struct.unpack('>I4s', file_data[offset:offset + 8])
            if typ == b'mvhd':
                # mvhd box found, read until reserved2 which is at bytes 20-23
                if offset + 20 < len(file_data):
                    return offset + 20
            offset += size
        return None

    # Read the whole file into memory
    with open(fp, 'rb+') as f:
        file_data = f.read()
        
        position = find_mvhd_reserved2_position(file_data)
        
        if position is None:
            if debug:
                print("[DEBUG] mvhd.reserved2 not found")
            return
        
        old_value = file_data[position:position + 4]
        
        if debug:
            print(f"[DEBUG] mvhd.reserved2 before: {list(old_value)}")
        
        # Seek to the position and overwrite
        f.seek(position)
        f.write(value[:4])  # Ensure only 4 bytes written
        
        if debug:
            print(f"[DEBUG] mvhd.reserved2 after: {list(value[:4])}")

def test_mp4_mvhd_reserved2(input_file):
    import tempfile
    
    # Creating a temporary file
    tmp_dir = tempfile.gettempdir()
    tmp_file = os.path.join(tmp_dir, 'test_mvhd_reserved2.mp4')
    
    shutil.copy(input_file, tmp_file)
    test_value = bytes([0, 0, 0, 0])  # A representative test value
    
    try:
        mp4_mvhd_reserved2(tmp_file, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        os.remove(tmp_file)