import os
import struct
import shutil

def mp4_mvhd_size(fp, value, debug=False):
    def find_mvhd(fp):
        with open(fp, 'rb') as f:
            while True:
                header = f.read(8)
                if len(header) < 8:
                    break
                box_size, box_type = struct.unpack('>I4s', header)
                if box_type == b'mvhd':
                    return f.tell() - 8
                f.seek(box_size - 8, os.SEEK_CUR)
        return None

    mvhd_offset = find_mvhd(fp)
    if mvhd_offset is None:
        if debug:
            print("[DEBUG] mvhd.size not found")
        return

    with open(fp, 'r+b') as f:
        f.seek(mvhd_offset)
        header = f.read(8)
        box_size, box_type = struct.unpack('>I4s', header)
        if box_type != b'mvhd':
            if debug:
                print("[DEBUG] mvhd.size not found")
            return

        if debug:
            print(f"[DEBUG] mvhd.size before: {box_size}")

        f.seek(mvhd_offset)
        f.write(struct.pack('>I', value))

        if debug:
            print(f"[DEBUG] mvhd.size after: {value}")

def test_mp4_mvhd_size(input_file):
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        test_value = 1024  # Example test value within the valid range
        mp4_mvhd_size(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)