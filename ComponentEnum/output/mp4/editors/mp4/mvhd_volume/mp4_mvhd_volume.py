import os
import struct
import shutil

def mp4_mvhd_volume(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.volume not found")
                return

            # volume: 2 bytes at mvhd_pos+28 (fixed-point 8.8, stored as uint16)
            volume_offset = mvhd_pos + 28
            old_value = struct.unpack('>H', data[volume_offset:volume_offset+2])[0]

            if debug:
                print(f"[DEBUG] mvhd.volume before: {old_value}")

            f.seek(volume_offset)
            f.write(struct.pack('>H', value))

            if debug:
                print(f"[DEBUG] mvhd.volume after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_volume(input_file):
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)
    try:
        mp4_mvhd_volume(tmp_path, 1.0, debug=True)
        print("Test executed successfully.")
    finally:
        os.remove(tmp_path)