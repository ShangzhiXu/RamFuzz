import os
import shutil
import struct

def mp4_ftyp_major_brand(fp, value, debug=False):
    # Ensure the new value is a string of max 4 characters
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("value must be a string with a maximum length of 4")

    try:
        with open(fp, 'r+b') as f:
            found = False
            offset = 0

            # Read through the file in chunks
            while True:
                header = f.read(8)
                if len(header) < 8:
                    break

                size, box_type = struct.unpack(">I4s", header)
                box_type = box_type.decode('utf-8', 'ignore')

                if size < 8:
                    break  # Corrupted box, exit

                if box_type == 'ftyp':
                    # Read the major_brand directly after the ftyp's box type
                    major_brand = f.read(4).decode('utf-8', 'ignore')
                    if debug:
                        print(f"[DEBUG] ftyp.major_brand before: {major_brand}")

                    # Modify major_brand
                    f.seek(offset + 8, 0)  # Move to the start of the major_brand
                    f.write(value.ljust(4, '\x00').encode('utf-8', 'ignore'))  # Pad with null bytes if necessary

                    if debug:
                        print(f"[DEBUG] ftyp.major_brand after: {value}")

                    found = True
                    break
                else:
                    f.seek(size - 8, 1)

                offset += size

            if not found and debug:
                print("[DEBUG] ftyp.major_brand not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")


def test_mp4_ftyp_major_brand(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".mp4")
    os.close(tmp_fd)
    shutil.copy2(input_file, tmp_path)

    try:
        # Call the function with a representative test value and debug=True
        mp4_ftyp_major_brand(tmp_path, 'isom', debug=True)
        print("Test executed successfully")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)