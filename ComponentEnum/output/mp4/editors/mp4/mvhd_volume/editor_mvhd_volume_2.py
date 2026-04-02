import os
import struct
import shutil

def mp4_mvhd_volume(fp, value, debug=False):
    def read_uint32(f):
        return struct.unpack(">I", f.read(4))[0]
    
    def read_fixed_point(f):
        # Read 16.16 fixed-point number
        raw = struct.unpack(">H", f.read(2))[0]
        fractional = struct.unpack(">H", f.read(2))[0] / 65536.0
        return raw + fractional

    def write_fixed_point(f, value):
        # Write 16.16 fixed-point number
        integer_part = int(value)
        fractional_part = int((value - integer_part) * 65536)
        f.write(struct.pack(">H", integer_part))
        f.write(struct.pack(">H", fractional_part))

    try:
        with open(fp, 'r+b') as f:
            while True:
                offset = f.tell()
                header = f.read(8)
                if len(header) < 8:
                    break
                
                size, box_type = struct.unpack(">I4s", header)
                
                if box_type == b'mvhd':
                    # Skip version (1 byte) and flags (3 bytes)
                    f.seek(offset + 8 + 4, os.SEEK_SET)
                    
                    # Read creation and modification times (8 bytes each) and timescale (4 bytes), altogether 20 bytes
                    f.seek(20, os.SEEK_CUR)
                    
                    # Skip duration (4 bytes)
                    f.seek(4, os.SEEK_CUR)
                    
                    # Read current volume
                    initial_volume = read_fixed_point(f)
                    
                    if debug:
                        print(f"[DEBUG] mvhd.volume before: {initial_volume}")
                    
                    # Go back 4 bytes to rewrite the fixed point number
                    f.seek(-4, os.SEEK_CUR)
                    write_fixed_point(f, value)
                    
                    if debug:
                        print(f"[DEBUG] mvhd.volume after: {value}")
                    
                    return  # Exit after modifying

                else:
                    # Move to the next box
                    f.seek(offset + size, os.SEEK_SET)
            
            if debug:
                print("[DEBUG] mvhd.volume not found")
                
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_volume(input_file):
    import tempfile
    test_value = 1.0  # Representative value for testing
    
    tmp_dir = tempfile.mkdtemp()
    try:
        tmp_file = os.path.join(tmp_dir, "temp.mp4")
        shutil.copy(input_file, tmp_file)
        
        mp4_mvhd_volume(tmp_file, test_value, debug=True)
        print("Function executed successfully")
    finally:
        shutil.rmtree(tmp_dir)

# Sample usage
# test_mp4_mvhd_volume("example.mp4")