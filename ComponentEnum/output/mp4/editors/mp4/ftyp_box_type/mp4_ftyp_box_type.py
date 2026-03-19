import os
import shutil
import struct

def mp4_ftyp_box_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            f.seek(0)
            while True:
                # Read box header: size (4 bytes) and type (4 bytes)
                header = f.read(8)
                if len(header) < 8:
                    if debug:
                        print("[DEBUG] ftyp.box_type not found")
                    return
                
                size, box_type = struct.unpack('>I4s', header)
                box_type = box_type.decode('utf-8', errors='ignore')
                
                if box_type == 'ftyp':
                    # Found the 'ftyp' box — box_type is the 4 bytes at offset +4
                    # Seek back to the type field (we already read past it)
                    f.seek(-4, os.SEEK_CUR)
                    old_box_type = f.read(4).decode('utf-8', errors='ignore')
                    if debug:
                        print(f"[DEBUG] ftyp.box_type before: {old_box_type}")

                    # Seek back to overwrite the type field
                    f.seek(-4, os.SEEK_CUR)
                    f.write(value.encode('utf-8').ljust(4, b'\0')[:4])
                    
                    if debug:
                        print(f"[DEBUG] ftyp.box_type after: {value}")
                    return
                
                # Move to the next box
                f.seek(size - 8, os.SEEK_CUR)
    except Exception as e:
        if debug:
            print(f"[DEBUG] An error occurred: {e}")

def test_mp4_ftyp_box_type(input_file):
    test_value = "test"
    tmp_path = input_file + ".tmp"
    shutil.copy(input_file, tmp_path)
    
    try:
        mp4_ftyp_box_type(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        os.remove(tmp_path)