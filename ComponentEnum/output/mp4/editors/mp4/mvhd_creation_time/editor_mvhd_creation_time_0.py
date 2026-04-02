import os
import struct
import shutil

def mp4_mvhd_creation_time(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Find the 'mvhd' atom
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.creation_time not found")
                return

            # The 'mvhd' atom is preceded by a 4-byte size field
            mvhd_start = mvhd_pos - 4
            mvhd_size = struct.unpack('>I', data[mvhd_start:mvhd_pos])[0]

            # Check if the atom size is reasonable
            if mvhd_size < 32:
                if debug:
                    print("[DEBUG] mvhd.creation_time not found")
                return

            # The creation_time is located 4 bytes after the version and flags (8 bytes from 'mvhd' start)
            creation_time_offset = mvhd_pos + 4

            # Read the current creation_time
            old_creation_time = struct.unpack('>I', data[creation_time_offset:creation_time_offset + 4])[0]

            if debug:
                print(f"[DEBUG] mvhd.creation_time before: {old_creation_time}")

            # Replace with the new value
            new_creation_time_bytes = struct.pack('>I', value)
            data = data[:creation_time_offset] + new_creation_time_bytes + data[creation_time_offset + 4:]

            # Write the modified data back to the file
            f.seek(0)
            f.write(data)

            if debug:
                print(f"[DEBUG] mvhd.creation_time after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_creation_time(input_file):
    import tempfile

    # Create a temporary file path
    tmp_path = tempfile.mktemp(suffix=".mp4")

    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Define a test value for the creation_time
        test_value = 2082844800  # Example value within the common range

        # Call the function with debug enabled
        mp4_mvhd_creation_time(tmp_path, test_value, debug=True)

        print("Test executed successfully.")

    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_creation_time('example.mp4')