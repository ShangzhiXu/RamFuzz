import os
import shutil
import struct

def mp4_moov_size(fp, value, debug=False):
    def find_moov(fp):
        with open(fp, 'rb') as f:
            while True:
                header = f.read(8)
                if len(header) < 8:
                    break
                size, box_type = struct.unpack('>I4s', header)
                if box_type == b'moov':
                    return f.tell() - 8, size
                f.seek(size - 8, os.SEEK_CUR)
        return None, None

    moov_offset, moov_size = find_moov(fp)
    if moov_offset is None:
        if debug:
            print("[DEBUG] moov.size not found")
        return

    if debug:
        print(f"[DEBUG] moov.size before: {moov_size}")

    with open(fp, 'r+b') as f:
        f.seek(moov_offset)
        f.write(struct.pack('>I', value))

    if debug:
        print(f"[DEBUG] moov.size after: {value}")

def test_mp4_moov_size(input_file):
    import tempfile

    test_value = 1024  # Example test value for moov.size
    tmp_path = tempfile.mktemp(suffix=".mp4")

    try:
        shutil.copy(input_file, tmp_path)
        mp4_moov_size(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)