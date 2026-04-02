import os
import shutil

def mp4_ftyp_reserved(fp, value, debug=False):
    if not isinstance(value, bytes):
        raise ValueError("Value must be of type bytes")

    try:
        with open(fp, 'rb') as f:
            data = f.read()
        
        # Find 'ftyp' box
        pos = 0
        ftyp_found = False
        while pos < len(data):
            box_size = int.from_bytes(data[pos:pos+4], 'big')
            box_type = data[pos+4:pos+8].decode('utf-8')
            
            if box_type == 'ftyp':
                ftyp_found = True
                # Compatible brands area: after size(4)+type(4)+major_brand(4)+minor_version(4)
                reserved_start = pos + 16
                reserved_end = pos + box_size

                old_value = data[reserved_start:reserved_end]
                if debug:
                    print(f"[DEBUG] ftyp.reserved before: {old_value}")

                # Overwrite in-place: write value bytes, padded/truncated to fit
                write_len = reserved_end - reserved_start
                new_value = value[:write_len].ljust(write_len, b'\x00')

                with open(fp, 'r+b') as f:
                    f.seek(reserved_start)
                    f.write(new_value)

                if debug:
                    print(f"[DEBUG] ftyp.reserved after: {new_value}")
                break
            else:
                pos += box_size

        if not ftyp_found and debug:
            print("[DEBUG] ftyp.reserved not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error processing the file: {e}")

def test_mp4_ftyp_reserved(input_file):
    temp_file = f"{input_file}_temp.mp4"
    shutil.copy(input_file, temp_file)
    
    try:
        mp4_ftyp_reserved(temp_file, b'test', debug=True)
        print("[INFO] Function executed successfully.")
    finally:
        if os.path.exists(temp_file):
            os.remove(temp_file)

# Example usage:
# test_mp4_ftyp_reserved('sample.mp4')