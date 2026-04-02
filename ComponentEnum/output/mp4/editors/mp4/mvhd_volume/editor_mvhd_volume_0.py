import os
import struct
import shutil

def mp4_mvhd_volume(fp, value, debug=False):
    def find_mvhd(fp):
        with open(fp, 'rb') as f:
            while True:
                header = f.read(8)
                if len(header) < 8:
                    return None
                size, box_type = struct.unpack('>I4s', header)
                if box_type == b'mvhd':
                    return f.tell() - 8
                f.seek(size - 8, os.SEEK_CUR)

    def read_fixed_point(f):
        data = f.read(2)
        if len(data) < 2:
            return None
        return struct.unpack('>H', data)[0] / 256.0

    def write_fixed_point(f, value):
        fixed_point_value = int(value * 256)
        f.write(struct.pack('>H', fixed_point_value))

    mvhd_offset = find_mvhd(fp)
    if mvhd_offset is None:
        if debug:
            print("[DEBUG] mvhd.volume not found")
        return

    with open(fp, 'r+b') as f:
        f.seek(mvhd_offset + 16)  # Skip to the volume field
        old_value = read_fixed_point(f)
        if debug:
            print(f"[DEBUG] mvhd.volume before: {old_value}")

        f.seek(mvhd_offset + 16)
        write_fixed_point(f, value)

        if debug:
            f.seek(mvhd_offset + 16)
            new_value = read_fixed_point(f)
            print(f"[DEBUG] mvhd.volume after: {new_value}")

def test_mp4_mvhd_volume(input_file):
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)
    try:
        mp4_mvhd_volume(tmp_path, 1.0, debug=True)
        print("Test executed successfully.")
    finally:
        os.remove(tmp_path)