import os
import shutil
import struct

def mp4_mvhd_version(fp, value, debug=False):
    def find_mvhd(fp):
        with open(fp, 'rb') as f:
            content = f.read()
            offset = content.find(b'mvhd')
            if offset == -1:
                return None
            return offset + 4  # skip 'mvhd'

    mvhd_offset = find_mvhd(fp)
    if mvhd_offset is None:
        if debug:
            print("[DEBUG] mvhd.version not found")
        return

    with open(fp, 'r+b') as f:
        f.seek(mvhd_offset)
        current_version = f.read(1)
        if debug:
            old_value = struct.unpack('B', current_version)[0]
            print(f"[DEBUG] mvhd.version before: {old_value}")
        
        f.seek(mvhd_offset)
        f.write(struct.pack('B', value))
        
        if debug:
            f.seek(mvhd_offset)
            new_version = struct.unpack('B', f.read(1))[0]
            print(f"[DEBUG] mvhd.version after: {new_version}")

def test_mp4_mvhd_version(input_file):
    # Temporary path for testing
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Use a representative test value for mvhd.version, e.g., 1
        mp4_mvhd_version(tmp_path, 1, debug=True)
        print("Test executed successfully.")
    finally:
        # Clean up temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_version('example.mp4')