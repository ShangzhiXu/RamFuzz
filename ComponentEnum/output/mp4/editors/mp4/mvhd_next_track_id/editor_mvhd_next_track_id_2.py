import struct
import os
import shutil

def mp4_mvhd_next_track_id(fp, value, debug=False):
    def find_mvhd_box(f):
        f.seek(0, os.SEEK_SET)
        while True:
            box_header = f.read(8)
            if len(box_header) < 8:
                break
            
            box_size, box_type = struct.unpack(">I4s", box_header)
            if box_type == b'mvhd':
                return f.tell() - 8, box_size
            
            # Seek to the next box
            f.seek(box_size - 8, os.SEEK_CUR)
        return None, None

    def read_uint32(f, offset):
        f.seek(offset)
        return struct.unpack(">I", f.read(4))[0]

    def write_uint32(f, offset, value):
        f.seek(offset)
        f.write(struct.pack(">I", value))

    if not (0 <= value <= 4294967295):
        raise ValueError("The value must be a uint32 (0 to 4294967295).")

    with open(fp, 'r+b') as f:
        mvhd_offset, mvhd_size = find_mvhd_box(f)
        if mvhd_offset is None:
            if debug:
                print("[DEBUG] mvhd.next_track_id not found")
            return
        
        # Version and flags are 4 bytes at the start of mvhd box
        # Need to skip them to get to the component
        version_and_flags_offset = 4
        component_offset = mvhd_offset + version_and_flags_offset + (96 if mvhd_size > 100 else 84)
        
        try:
            old_value = read_uint32(f, component_offset)
            if debug:
                print(f"[DEBUG] mvhd.next_track_id before: {old_value}")
            write_uint32(f, component_offset, value)
            if debug:
                print(f"[DEBUG] mvhd.next_track_id after: {value}")
        except Exception as e:
            if debug:
                print("[DEBUG] mvhd.next_track_id not found")
            return

def test_mp4_mvhd_next_track_id(input_file):
    import tempfile

    test_value = 12345
    tmp_path = tempfile.mktemp(suffix=".mp4")

    try:
        shutil.copy2(input_file, tmp_path)
        mp4_mvhd_next_track_id(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# To use the test function, simply call it with the path to an input MP4 file:
# test_mp4_mvhd_next_track_id("some_input_file.mp4")