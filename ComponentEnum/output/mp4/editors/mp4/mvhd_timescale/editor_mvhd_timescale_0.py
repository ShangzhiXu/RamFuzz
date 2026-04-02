import os
import struct
import shutil
import tempfile

def mp4_mvhd_timescale(fp, value, debug=False):
    def find_mvhd_offset(data):
        offset = 0
        while offset < len(data):
            size = struct.unpack(">I", data[offset:offset+4])[0]
            box_type = data[offset+4:offset+8].decode("utf-8", errors="ignore")
            if box_type == "mvhd":
                return offset + 12  # Skip size (4 bytes), type (4 bytes), version/flags (4 bytes)
            offset += size
        return None

    try:
        with open(fp, "r+b") as f:
            data = f.read()
            mvhd_offset = find_mvhd_offset(data)
            if mvhd_offset is None:
                if debug:
                    print("[DEBUG] mvhd.timescale not found")
                return

            timescale_offset = mvhd_offset + 4  # Skip creation_time (4 bytes)
            old_value = struct.unpack(">I", data[timescale_offset:timescale_offset+4])[0]

            if debug:
                print(f"[DEBUG] mvhd.timescale before: {old_value}")

            f.seek(timescale_offset)
            f.write(struct.pack(">I", value))

            if debug:
                print(f"[DEBUG] mvhd.timescale after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_timescale(input_file):
    test_value = 1000  # A representative test value within the common range
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, os.path.basename(input_file))

    try:
        shutil.copy(input_file, tmp_path)
        mp4_mvhd_timescale(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed with error: {e}")
    finally:
        shutil.rmtree(tmp_dir)

# Example usage
# test_mp4_mvhd_timescale("path_to_your_test_file.mp4")