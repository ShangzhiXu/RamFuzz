import os
import struct
import shutil

def mp4_ftyp_minor_version(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the length and type of the box
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            box_size, box_type = struct.unpack('>I4s', header)

            # Check if the box is 'ftyp'
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            # Skip the major_brand (4 bytes) to reach minor_version
            f.seek(4, os.SEEK_CUR)

            # Read the current minor_version
            current_minor_version_bytes = f.read(4)
            if len(current_minor_version_bytes) < 4:
                if debug:
                    print("[DEBUG] ftyp.minor_version not found")
                return

            current_minor_version = struct.unpack('>I', current_minor_version_bytes)[0]

            if debug:
                print(f"[DEBUG] ftyp.minor_version before: {current_minor_version}")

            # Write the new minor_version
            f.seek(-4, os.SEEK_CUR)
            f.write(struct.pack('>I', value))

            if debug:
                print(f"[DEBUG] ftyp.minor_version after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_ftyp_minor_version(input_file):
    test_value = 0  # A representative test value for minor_version
    tmp_path = input_file + ".tmp"

    try:
        shutil.copy2(input_file, tmp_path)
        mp4_ftyp_minor_version(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    except Exception as e:
        print(f"Error during test execution: {e}")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage
# test_mp4_ftyp_minor_version('example.mp4')