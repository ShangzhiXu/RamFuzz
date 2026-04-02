import os
import shutil
import struct


def mp4_ftyp_brand(fp, value, debug=False):
    if not isinstance(value, str) or len(value) != 4:
        raise ValueError("value must be a 4-character string")

    try:
        with open(fp, 'r+b') as f:
            # Read the initial 8 bytes
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return
            
            # Unpack the size and type (4 bytes each)
            size, box_type = struct.unpack(">I4s", header)
            box_type = box_type.decode('ascii')

            if box_type != 'ftyp':
                if debug:
                    print("[DEBUG] ftyp.brand not found")
                return

            # Read the major_brand after the size and box_type
            major_brand = f.read(4).decode('ascii')

            if debug:
                print(f"[DEBUG] ftyp.brand before: {major_brand}")

            # Move to the position of the brand
            f.seek(8, os.SEEK_SET)

            # Write the new major brand
            f.write(value.encode('ascii'))

            if debug:
                print(f"[DEBUG] ftyp.brand after: {value}")

    except FileNotFoundError:
        print(f"[DEBUG] File {fp} not found")
    except Exception as e:
        print(f"[DEBUG] Error: {str(e)}")


def test_mp4_ftyp_brand(input_file):
    tmp_file = '/tmp/test_mp4_file.mp4'
    try:
        shutil.copy(input_file, tmp_file)
        mp4_ftyp_brand(tmp_file, 'isom', debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed: {str(e)}")
    finally:
        try:
            os.remove(tmp_file)
        except Exception as e:
            print(f"Error cleaning up: {str(e)}")


# Example usage:
# test_mp4_ftyp_brand('path/to/input/file.mp4')