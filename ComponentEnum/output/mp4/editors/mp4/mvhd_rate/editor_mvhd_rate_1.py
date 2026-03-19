import os
import struct
import shutil
import tempfile

def mp4_mvhd_rate(fp, value, debug=False):
    try:
        # Open the file in read and write binary mode
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            file_data = f.read()

        # Locate 'mvhd' atom
        mvhd_pos = file_data.find(b'mvhd')
        if mvhd_pos == -1:
            if debug:
                print("[DEBUG] mvhd.rate not found")
            return

        # 'mvhd' atom is found, locate the rate which comes after version(1 byte) + flags(3 bytes) + creation time(4 bytes) + modification time(4 bytes) + time scale(4 bytes) + duration(4 bytes)
        rate_pos = mvhd_pos + 20
        
        # Ensure there is enough data for the rate
        if rate_pos + 4 > len(file_data):
            if debug:
                print("[DEBUG] mvhd atom is incomplete, cannot read rate")
            return

        # Read the current rate value
        old_rate = struct.unpack(">I", file_data[rate_pos:rate_pos+4])[0]

        if debug:
            print(f"[DEBUG] mvhd.rate before: {old_rate / 65536}")

        # Convert new value to fixed-point and pack it
        new_rate = int(value * 65536)
        
        # Check if the value is within the valid range for fixed-point representation
        if not (0 <= new_rate < 2**32):
            if debug:
                print(f"[DEBUG] Error: provided value results in out-of-bounds rate")
            return

        new_rate_bytes = struct.pack(">I", new_rate)

        # Replace the old rate with the new rate in the file data
        new_file_data = file_data[:rate_pos] + new_rate_bytes + file_data[rate_pos+4:]

        # Write the modified data back to the file
        with open(fp, 'r+b') as f:
            f.write(new_file_data)

        if debug:
            print(f"[DEBUG] mvhd.rate after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_rate(input_file):
    # Create a temporary file path
    tmp_dir = tempfile.mkdtemp()
    tmp_path = os.path.join(tmp_dir, os.path.basename(input_file))
    
    try:
        # Copy the input file to the temporary file
        shutil.copy(input_file, tmp_path)

        # Define a test value for the 'rate' component
        test_value = 1.5  # Example representative test value

        # Call the function with the temporary path and test value
        mp4_mvhd_rate(tmp_path, test_value, debug=True)

        print("Test executed successfully")

    except Exception as e:
        print(f"Test failed: {e}")

    finally:
        # Clean up the temporary file
        shutil.rmtree(tmp_dir)

# Example usage:
# test_mp4_mvhd_rate('path_to_your_test_mp4_file.mp4')