import os
import struct
import shutil

def mp4_mvhd_timescale(fp, value, debug=False):
    # Open the file in binary read and write mode
    with open(fp, 'r+b') as f:
        # Read the entire file content
        file_content = f.read()

    # Define the box header structure: size (4 bytes) and type (4 bytes)
    box_header_fmt = '>I4s'
    box_header_size = struct.calcsize(box_header_fmt)

    offset = 0
    mvhd_found = False

    # Iterate through the file to find the 'mvhd' box
    while offset < len(file_content):
        # Read the box header
        box_size, box_type = struct.unpack_from(box_header_fmt, file_content, offset)

        # If 'mvhd' is found, process it
        if box_type == b'mvhd':
            # Found the mvhd box
            mvhd_found = True

            # Skip the full box header (version and flags)
            full_box_header_size = 4

            # Define timescale offset within mvhd box
            timescale_offset_relative = 12  # Relative to the start of mvhd box
            timescale_offset = offset + box_header_size + full_box_header_size + timescale_offset_relative

            # Read the current timescale
            current_timescale = struct.unpack_from('>I', file_content, timescale_offset)[0]

            if debug:
                print(f"[DEBUG] mvhd.timescale before: {current_timescale}")

            # Write the new timescale
            f.seek(timescale_offset)
            f.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] mvhd.timescale after: {value}")

            break

        # Move to the next box
        offset += box_size

    if not mvhd_found and debug:
        print("[DEBUG] mvhd.timescale not found")

def test_mp4_mvhd_timescale(input_file):
    # Make a temporary copy of the input file
    tmp_path = 'temp_test_file.mp4'
    shutil.copy(input_file, tmp_path)

    try:
        # Call the mp4_mvhd_timescale function with a test value
        test_value = 1000  # Example test value in the valid range
        mp4_mvhd_timescale(tmp_path, test_value, debug=True)

        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)