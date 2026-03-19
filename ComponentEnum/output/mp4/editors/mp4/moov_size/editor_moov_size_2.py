import os
import struct
import shutil
import tempfile

def mp4_moov_size(fp, value, debug=False):
    def find_moov(fp):
        with open(fp, 'rb') as f:
            while True:
                header = f.read(8)
                if len(header) < 8:
                    break
                size, box_type = struct.unpack('>I4s', header)
                if box_type == b'moov':
                    return f.tell() - 8
                f.seek(size - 8, os.SEEK_CUR)
        return None

    if not (8 <= value <= 4294967295):
        raise ValueError("Value should be within the range [8, 4294967295]")

    moov_offset = find_moov(fp)
    if moov_offset is None:
        if debug:
            print("[DEBUG] moov.size not found")
        return

    with open(fp, 'r+b') as f:
        # Read the current moov size
        f.seek(moov_offset)
        current_raw_size = f.read(4)
        current_size, = struct.unpack('>I', current_raw_size)

        if debug:
            print(f"[DEBUG] moov.size before: {current_size}")

        # Write the new moov size
        f.seek(moov_offset)
        f.write(struct.pack('>I', value))

        if debug:
            print(f"[DEBUG] moov.size after: {value}")


def test_mp4_moov_size(input_file):
    # Create a temporary directory
    with tempfile.TemporaryDirectory() as tmpdirname:
        # Make a copy of the input file
        tmp_path = os.path.join(tmpdirname, os.path.basename(input_file))
        shutil.copy(input_file, tmp_path)

        try:
            # Test value within permissible range
            test_value = 1024
            mp4_moov_size(tmp_path, test_value, debug=True)
            print(f"Test executed successfully for {tmp_path}.")
        except Exception as e:
            print(f"Test failed due to exception: {e}")

# Example usage:
# test_mp4_moov_size('example.mp4')