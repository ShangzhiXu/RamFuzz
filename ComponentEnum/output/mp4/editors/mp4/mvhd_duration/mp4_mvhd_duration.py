import os
import shutil
import struct

def mp4_mvhd_duration(fp, value, debug=False):
    if not (0 <= value <= 4294967295):
        raise ValueError("Value must be a uint32 within the range [0, 4294967295].")

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Find the 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.duration not found")
                return

            # From 'mvhd' string: +4=version/flags(4), +8=creation_time(4),
            # +12=modification_time(4), +16=timescale(4), +20=duration(4)
            duration_offset = mvhd_pos + 20

            # Read the current duration value
            old_duration = struct.unpack_from('>I', data, duration_offset)[0]

            if debug:
                print(f"[DEBUG] mvhd.duration before: {old_duration}")

            # Write the new duration value
            new_data = struct.pack('>I', value)
            f.seek(duration_offset)
            f.write(new_data)

            if debug:
                print(f"[DEBUG] mvhd.duration after: {value}")

    except Exception as e:
        print(f"An error occurred: {e}")

def test_mp4_mvhd_duration(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the duration
        test_value = 3600  # 1 hour in seconds

        # Call the function with debug enabled
        mp4_mvhd_duration(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_duration('example.mp4')