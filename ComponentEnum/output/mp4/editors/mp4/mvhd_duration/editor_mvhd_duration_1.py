import struct
import os
import shutil

def mp4_mvhd_duration(fp, value, debug=False):
    if not (0 <= value <= 4294967295):
        raise ValueError("value must be a uint32 between 0 and 4294967295")

    mvhd_found = False
    with open(fp, 'r+b') as f:
        while True:
            atom_header = f.read(8)
            if len(atom_header) < 8:
                break
            
            atom_size, atom_type = struct.unpack('>I4s', atom_header)
            if atom_type == b'mvhd':
                mvhd_found = True
                version_flags = f.read(4)
                duration_offset = 16 if version_flags[0] == 0 else 24
                f.seek(duration_offset, os.SEEK_CUR)
                
                current_duration_data = f.read(4)
                current_duration = struct.unpack('>I', current_duration_data)[0]
                
                if debug:
                    print(f"[DEBUG] mvhd.duration before: {current_duration}")
                
                f.seek(-4, os.SEEK_CUR)
                f.write(struct.pack('>I', value))
                
                if debug:
                    print(f"[DEBUG] mvhd.duration after: {value}")
                
                break
            else:
                f.seek(atom_size - 8, os.SEEK_CUR)

    if not mvhd_found:
        if debug:
            print("[DEBUG] mvhd.duration not found")

def test_mp4_mvhd_duration(input_file):
    import tempfile
    
    test_value = 123456  # A representative test value for the mvhd.duration field
    tmp_path = tempfile.mktemp(suffix=".mp4")
    shutil.copy(input_file, tmp_path)
    
    try:
        mp4_mvhd_duration(tmp_path, test_value, debug=True)
        print("Function executed successfully")
    except Exception as e:
        print(f"Function execution failed: {e}")
    finally:
        os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_duration('example.mp4')