import os
import shutil
import struct

def mp4_moov_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()

            # Find the 'moov' box
            moov_pos = data.find(b'moov')
            if moov_pos == -1:
                if debug:
                    print("[DEBUG] moov.type not found")
                return

            # Read the size of the moov box
            moov_size = struct.unpack('>I', data[moov_pos-4:moov_pos])[0]

            # Read the current type value
            current_value = data[moov_pos:moov_pos+4].decode('utf-8')

            if debug:
                print(f"[DEBUG] moov.type before: {current_value}")

            # Replace the type value with the new value
            new_value_bytes = value.encode('utf-8').ljust(4, b'\x00')
            data = data[:moov_pos] + new_value_bytes + data[moov_pos+4:]

            # Write the modified data back to the file
            f.seek(0)
            f.write(data)

            if debug:
                print(f"[DEBUG] moov.type after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_moov_type(input_file):
    # Create a temporary copy of the input file
    tmp_path = input_file + '.tmp'
    shutil.copy(input_file, tmp_path)

    try:
        # Call the function with a test value
        test_value = "moov"
        mp4_moov_type(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed with exception: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)