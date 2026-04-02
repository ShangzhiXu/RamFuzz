import os
import struct
import shutil

def mp4_mvhd_size(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1 or mvhd_pos < 4:
                if debug:
                    print("[DEBUG] mvhd.size not found")
                return

            # size: 4 bytes at mvhd_pos-4 (the box size field before the type)
            size_offset = mvhd_pos - 4
            box_size = struct.unpack('>I', data[size_offset:size_offset+4])[0]

            if debug:
                print(f"[DEBUG] mvhd.size before: {box_size}")

            f.seek(size_offset)
            f.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] mvhd.size after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

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