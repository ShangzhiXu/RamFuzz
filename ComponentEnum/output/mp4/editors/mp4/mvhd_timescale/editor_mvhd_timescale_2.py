import os
import struct
import tempfile
import shutil

def mp4_mvhd_timescale(fp, value, debug=False):
    # Define constants
    MVHD_HEADER_SIZE = 8  # 'mvhd' atom type
    FULL_BOX_HEADER_SIZE = 12  # size + type + version + flags
    TIMESCALE_OFFSET_V0 = 12  # offset from start of version 0 full box
    TIMESCALE_OFFSET_V1 = 20  # offset from start of version 1 full box

    try:
        # Open the file in read & write binary mode
        with open(fp, 'r+b') as f:
            data = f.read()

            # Find the 'moov' atom
            moov_pos = data.find(b'moov')
            if moov_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.timescale not found")
                return

            # Find the 'mvhd' atom within 'moov'
            mvhd_pos = data.find(b'mvhd', moov_pos)
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.timescale not found")
                return

            # Read the box size and version from 'mvhd' header
            mvhd_box_size, = struct.unpack(">I", data[mvhd_pos - 4:mvhd_pos])
            version_flags = data[mvhd_pos + 4]

            if version_flags == 0:
                timescale_offset = TIMESCALE_OFFSET_V0
            else:
                timescale_offset = TIMESCALE_OFFSET_V1

            # Calculate timescale position
            timescale_pos = mvhd_pos + FULL_BOX_HEADER_SIZE + timescale_offset

            # Check if the position is valid
            if timescale_pos + 4 <= mvhd_pos + mvhd_box_size:
                old_timescale, = struct.unpack(">I", data[timescale_pos:timescale_pos + 4])

                if debug:
                    print(f"[DEBUG] mvhd.timescale before: {old_timescale}")

                # Write the new timescale
                f.seek(timescale_pos)
                f.write(struct.pack(">I", value))

                if debug:
                    print(f"[DEBUG] mvhd.timescale after: {value}")
            else:
                if debug:
                    print("[DEBUG] mvhd.timescale not found")
    
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {str(e)}")


def test_mp4_mvhd_timescale(input_file):
    # Create a temporary file for testing
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, 'test_file.mp4')

    try:
        # Copy the input file to the temporary location
        shutil.copy(input_file, tmp_path)

        # Representative test value for timescale
        test_value = 90000

        # Invoke the function with debug set to True
        mp4_mvhd_timescale(tmp_path, test_value, debug=True)

        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed with error: {str(e)}")
    finally:
        # Clean up the temporary file
        try:
            shutil.rmtree(tmp_dir)
        except OSError as e:
            print(f"Error cleaning up temporary files: {str(e)}")

# You can test the function using:
# test_mp4_mvhd_timescale('path_to_your_test_file.mp4')