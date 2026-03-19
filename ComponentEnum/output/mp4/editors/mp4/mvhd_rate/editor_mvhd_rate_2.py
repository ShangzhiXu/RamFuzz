import os
import struct
import shutil

def mp4_mvhd_rate(fp, value, debug=False):
    # Structures for identifying and reading components
    BOX_HEADER_SIZE = 8
    MVHD_HEADER_SIZE = 8  # size of version and flags in the mvhd box
    RATE_OFFSET = 16

    try:
        with open(fp, 'r+b') as f:
            while True:
                box_start = f.tell()

                box_header = f.read(BOX_HEADER_SIZE)
                if len(box_header) < BOX_HEADER_SIZE:
                    break

                size, box_type = struct.unpack('>I4s', box_header)
                if box_type == b'mvhd':
                    f.seek(MVHD_HEADER_SIZE, os.SEEK_CUR)  # Skip mvhd header
                    rate_position = f.tell() + RATE_OFFSET

                    f.seek(rate_position)
                    old_rate = struct.unpack('>I', f.read(4))[0]

                    if debug:
                        print(f"[DEBUG] mvhd.rate before: {old_rate}")

                    new_rate_fixed = int(value * 65536)
                    f.seek(rate_position)
                    f.write(struct.pack('>I', new_rate_fixed))

                    if debug:
                        print(f"[DEBUG] mvhd.rate after: {new_rate_fixed}")
                    return

                else:
                    f.seek(size - BOX_HEADER_SIZE, os.SEEK_CUR)

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {str(e)}")

    if debug:
        print("[DEBUG] mvhd.rate not found")

import tempfile

def test_mp4_mvhd_rate(input_file):
    # Create a temporary copy of the input file
    tmp_file = tempfile.mktemp(suffix=".mp4")
    shutil.copy(input_file, tmp_file)
    
    test_value = 1.0  # Representative test value for mvhd.rate (discrete 1.0)
    
    try:
        mp4_mvhd_rate(tmp_file, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_file)

# Example usage:
# test_mp4_mvhd_rate('example.mp4')