import struct
import os
import shutil
import tempfile

def mp4_mvhd_next_track_ID(fp, value, debug=False):
    def find_mvhd_box(file):
        file.seek(0, os.SEEK_SET)
        while True:
            header = file.read(8)
            if len(header) < 8:
                return None
            size, box_type = struct.unpack(">I4s", header)
            if box_type == b'mvhd':
                return file.tell() - 8
            file.seek(size - 8, os.SEEK_CUR)
    
    def read_uint32(file):
        return struct.unpack(">I", file.read(4))[0]
    
    def write_uint32(file, value):
        file.write(struct.pack(">I", value))
    
    with open(fp, 'r+b') as file:
        mvhd_position = find_mvhd_box(file)
        
        if mvhd_position is None:
            if debug:
                print("[DEBUG] mvhd.next_track_ID not found")
            return
        
        file.seek(mvhd_position + 12)  # Skip mvhd header and version/flags
        version_flags = file.read(4)
        version = struct.unpack(">B", version_flags[0:1])[0]
        
        if version == 1:
            file.seek(96, os.SEEK_CUR)  # Skip to next_track_ID for version 1
        else:
            file.seek(84, os.SEEK_CUR)  # Skip to next_track_ID for version 0
        
        old_value = read_uint32(file)
        
        if debug:
            print(f"[DEBUG] mvhd.next_track_ID before: {old_value}")
        
        file.seek(-4, os.SEEK_CUR)
        write_uint32(file, value)
        
        if debug:
            print(f"[DEBUG] mvhd.next_track_ID after: {value}")

def test_mp4_mvhd_next_track_ID(input_file):
    test_value = 123456789  # A representative test value for next_track_ID
    
    with tempfile.NamedTemporaryFile(delete=False) as temp_file:
        tmp_path = temp_file.name
    
    try:
        shutil.copy(input_file, tmp_path)
        mp4_mvhd_next_track_ID(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        os.remove(tmp_path)

# You can test the function using the following line (assuming 'input.mp4' is your test file):
# test_mp4_mvhd_next_track_ID('input.mp4')