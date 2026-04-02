import os
import shutil
import struct

def mp4_ftyp_brand(fp, value, debug=False):
    if len(value) > 4:
        raise ValueError("The 'value' must be a string with a maximum length of 4.")

    if not value in ["mp41", "mp42", "isom"]:
        raise ValueError("The 'value' must be one of the following: 'mp41', 'mp42', 'isom'.")

    try:
        with open(fp, 'rb+') as file:
            # Read the first 8 bytes to locate the ftyp box
            file.seek(0)
            header = file.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            # Unpack the size and type
            size, box_type = struct.unpack(">I4s", header)
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            # Read the major brand value
            major_brand = file.read(4).decode('utf-8')

            if debug:
                print(f"[DEBUG] ftyp.brand before: {major_brand}")

            # Replace the brand value with the new value
            file.seek(8)
            file.write(value.encode('utf-8'))

            if debug:
                print(f"[DEBUG] ftyp.brand after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error encountered: {e}")

def test_mp4_ftyp_brand(input_file):
    tmp_path = "temporary_test_file.mp4"
    try:
        shutil.copy(input_file, tmp_path)
        mp4_ftyp_brand(tmp_path, "mp42", debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage
# test_mp4_ftyp_brand("path_to_your_mp4_file.mp4")