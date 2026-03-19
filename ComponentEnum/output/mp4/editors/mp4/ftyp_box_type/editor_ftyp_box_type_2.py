import os
import shutil

def mp4_ftyp_box_type(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string of max length 4")
    
    try:
        with open(fp, 'r+b') as file:
            # Read the file's total size
            file.seek(0, os.SEEK_END)
            file_size = file.tell()
            file.seek(0)

            if file_size < 16:  # Minimum valid size for an `ftyp` box is 16 bytes
                if debug:
                    print("[DEBUG] File seems to be too short.")
                return

            # Read the size of the first box, which should be an `ftyp` box
            size_data = file.read(4)
            if len(size_data) < 4:
                if debug:
                    print("[DEBUG] Failed to read box size.")
                return

            box_size = int.from_bytes(size_data, byteorder='big')
            if box_size < 8 or box_size > file_size:
                if debug:
                    print("[DEBUG] Corrupted or too small ftyp box size.")
                return

            box_type_data = file.read(4)
            if len(box_type_data) < 4:
                if debug:
                    print("[DEBUG] Box type data incomplete.")
                return

            box_type = box_type_data.decode('utf-8', errors='ignore')
            
            if box_type != 'ftyp':
                if debug:
                    print("[DEBUG] ftyp box not found at the start of the file. Found:", box_type)
                return

            # Read the major_brand, this is the current ftyp.box_type
            old_value_data = file.read(4)
            if len(old_value_data) < 4:
                if debug:
                    print("[DEBUG] Incomplete ftyp.box_type.")
                return

            old_value = old_value_data.decode('utf-8', errors='ignore')
            if debug:
                print(f"[DEBUG] ftyp.box_type before: {old_value}")

            # Validate input and prepare new value
            value_data = value.encode('utf-8')
            value_data = value_data[:4] + b'\x20' * (4 - len(value_data))

            # Write new value
            file.seek(8)  # Go back to the position of `ftyp.box_type` in the file
            file.write(value_data)

            if debug:
                print(f"[DEBUG] ftyp.box_type after: {value}")

    except (IOError, OSError) as e:
        if debug:
            print(f"[DEBUG] I/O Error occurred: {e}")
        return
    except Exception as e:
        if debug:
            print(f"[DEBUG] An unexpected error occurred: {e}")
        return

def test_mp4_ftyp_box_type(input_file):
    test_value = "ftyp"  # Representative test value
    tmp_path = f"temp_{os.path.basename(input_file)}"

    try:
        shutil.copy(input_file, tmp_path)
        mp4_ftyp_box_type(tmp_path, test_value, debug=True)
        print("[TEST] Function executed successfully.")
    except Exception as e:
        print(f"[TEST] Function failed with error: {e}")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage of the test harness
# test_mp4_ftyp_box_type("path_to_your_sample_mp4_file.mp4")