import os
import shutil
import struct

def find_ftyp(fp):
    """Locate the position of the 'ftyp' box in the MP4 file."""
    with open(fp, 'rb') as f:
        while True:
            # Read size (4 bytes) and type (4 bytes)
            header = f.read(8)
            if len(header) < 8:
                break
            size, box_type = struct.unpack('>I4s', header)
            if box_type == b'ftyp':
                return f.tell() - 8  # Return position of 'ftyp' box
            f.seek(size - 8, os.SEEK_CUR)
    return None

def mp4_ftyp_type(fp, value, debug=False):
    """Parse and rewrite the 'ftyp.type' component in an MP4 file."""
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4")
    
    pos = find_ftyp(fp)
    
    if pos is None:
        if debug:
            print("[DEBUG] ftyp.type not found")
        return
    
    with open(fp, 'r+b') as f:
        f.seek(pos + 4)  # Move to the box type field (offset +4, after size)
        old_value = f.read(4).decode('utf-8', errors='replace')

        if debug:
            print(f"[DEBUG] ftyp.type before: {old_value}")

        # Move back to write the new value
        f.seek(pos + 4)
        f.write(value.encode('utf-8').ljust(4, b'\0')[:4])

        if debug:
            f.seek(pos + 4)
            new_value = f.read(4).decode('utf-8', errors='replace')
            print(f"[DEBUG] ftyp.type after: {new_value}")

def test_mp4_ftyp_type(input_file):
    """Test harness for mp4_ftyp_type function."""
    tmp_path = input_file + '.test'
    shutil.copy(input_file, tmp_path)
    
    try:
        mp4_ftyp_type(tmp_path, 'test', debug=True)
        print("Function executed successfully.")
    except Exception as e:
        print(f"Function raised an exception: {e}")
    finally:
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_type('example.mp4')