import os
import shutil

def mp4_ftyp_reserved(fp, value, debug=False):
    def find_ftyp_reserved(data):
        # MP4 files start with a box header, which is 8 bytes long
        # The first 4 bytes are the size of the box, the next 4 are the type
        offset = 0
        while offset < len(data):
            if len(data) - offset < 8:
                break
            box_size = int.from_bytes(data[offset:offset+4], byteorder='big')
            box_type = data[offset+4:offset+8]
            if box_type == b'ftyp':
                # The reserved section starts immediately after the major_brand and minor_version
                # major_brand is 4 bytes, minor_version is 4 bytes
                reserved_start = offset + 16
                reserved_end = box_size
                return reserved_start, reserved_end
            offset += box_size
        return None, None

    with open(fp, 'rb') as f:
        data = f.read()

    reserved_start, reserved_end = find_ftyp_reserved(data)
    if reserved_start is None:
        if debug:
            print("[DEBUG] ftyp.reserved not found")
        return

    old_value = data[reserved_start:reserved_end]
    if debug:
        print(f"[DEBUG] ftyp.reserved before: {old_value}")

    # Create new data with the updated reserved value
    new_data = data[:reserved_start] + value + data[reserved_end:]

    with open(fp, 'wb') as f:
        f.write(new_data)

    if debug:
        print(f"[DEBUG] ftyp.reserved after: {value}")

def test_mp4_ftyp_reserved(input_file):
    import tempfile

    # Create a temporary file to work with
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    shutil.copy(input_file, tmp_path)

    try:
        # Representative test value for ftyp.reserved
        test_value = b'\x00\x00\x00\x00'
        mp4_ftyp_reserved(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)