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
                reserved_start = pos + 8 + 4 + 4  # Skip size, type, major_brand, minor_version
                reserved_end = box_size + pos

                # current reserved value present
                old_value = data[reserved_start:reserved_end]
                if debug:
                    print(f"[DEBUG] ftyp.reserved before: {old_value}")

                # Replace reserved value with new value
                new_data = data[:reserved_start] + value + data[reserved_end:]
                
                with open(fp, 'wb') as f:
                    f.write(new_data)
                
                if debug:
                    print(f"[DEBUG] ftyp.reserved after: {value}")
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