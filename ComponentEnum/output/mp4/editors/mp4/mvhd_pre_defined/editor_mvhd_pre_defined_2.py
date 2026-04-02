import os
import shutil
import struct

def mp4_mvhd_pre_defined(fp, value, debug=False):
    def find_mvhd_box(file_content):
        file_size = len(file_content)
        offset = 0

        while offset < file_size:
            box_size = struct.unpack('>I', file_content[offset:offset+4])[0]
            box_type = file_content[offset+4:offset+8]

            if box_type == b'mvhd':
                return offset, box_size

            # Move to the next box
            offset += box_size
        
        return None, None

    # Load the file content
    with open(fp, 'rb') as f:
        content = f.read()

    # Find the mvhd box
    mvhd_offset, mvhd_size = find_mvhd_box(content)
    if mvhd_offset is None:
        if debug:
            print("[DEBUG] mvhd.pre_defined not found")
        return

    # Set the start position for pre_defined
    # `mvhd` box standard specifies:
    # - 1 byte version and 3 bytes flags: total 4 bytes
    # - 8 or 16 bytes datetime depending on version
    # - 4 bytes for timescale
    # - 4 or 8 bytes for duration
    # - Several other fields (including rate and volume) totaling more
    # The `pre_defined` (4 bytes) typically come after the volume (fixed 2 bytes) and reserved (2 bytes).

    version = content[mvhd_offset + 8]  # After 'mvhd' and box header (8 bytes)
    base_offset = mvhd_offset + 12

    if version == 1:
        # version 1 offsets
        pre_defined_offset = base_offset + 64  # Adjust this value as necessary
    else:
        # version 0 offsets
        pre_defined_offset = base_offset + 48  # Adjust this value as necessary

    old_value = content[pre_defined_offset:pre_defined_offset + 4]

    if debug:
        print(f"[DEBUG] mvhd.pre_defined before: {old_value}")

    # Modify the content
    content = content[:pre_defined_offset] + value + content[pre_defined_offset + 4:]

    # Write back the modified content
    with open(fp, 'wb') as f:
        f.write(content)

    if debug:
        print(f"[DEBUG] mvhd.pre_defined after: {value}")

def test_mp4_mvhd_pre_defined(input_file):
    test_value = b'\x00\x00\x00\x01'  # Example test value
    tmp_path = 'temp_test.mp4'

    # Create a copy of the file
    shutil.copy(input_file, tmp_path)

    try:
        mp4_mvhd_pre_defined(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        os.remove(tmp_path)