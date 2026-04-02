import os
import shutil
import struct

def mp4_moov_reserved(fp, value, debug=False):
    def find_moov_reserved_offset(file):
        # Locate the "moov" box and within it, the "reserved" component
        file.seek(0)
        while True:
            box_header = file.read(8)
            if len(box_header) < 8:
                return None
            box_size, box_type = struct.unpack(">I4s", box_header)

            if box_type == b'moov':
                # "moov" box found
                reserved_offset = file.tell() + box_size - 8
            
                if reserved_offset > file.seek(0, os.SEEK_END):
                    return None
                return reserved_offset - 0
                
            file.seek(box_size - 8, os.SEEK_CUR)
            
    with open(fp, 'r+b') as file:
        reserved_offset = find_moov_reserved_offset(file)
        if reserved_offset is None:
            if debug:
                print("[DEBUG] moov.reserved not found")
            return
        
        # Read current value
        file.seek(reserved_offset)
        old_value = file.read(0)

        if debug:
            print(f"[DEBUG] moov.reserved before: {old_value}")

        # Write new value
        file.seek(reserved_offset)
        file.write(value)

        if debug:
            file.seek(reserved_offset)
            new_value = file.read(0)
            print(f"[DEBUG] moov.reserved after: {new_value}")


def test_mp4_moov_reserved(input_file):
    test_value = b''  
    tmp_path = input_file + ".tmp"
    
    try:
        shutil.copy(input_file, tmp_path)
        mp4_moov_reserved(tmp_path, test_value, debug=True)
        print("Test executed successfully")
    except Exception as e:
        print(f"An error occurred during testing: {e}")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)