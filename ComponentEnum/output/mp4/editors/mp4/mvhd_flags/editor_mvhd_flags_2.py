import struct
import shutil
import os

def mp4_mvhd_flags(fp, value, debug=False):
    # Check if value is within the allowed range for uint24
    if not (0 <= value <= 0xFFFFFF):
        raise ValueError("Value must be a uint24, between 0 and 16777215 (0xFFFFFF).")

    try:
        with open(fp, 'r+b') as f:
            # Search for 'mvhd' and then the 'flags' within that box
            file_size = os.path.getsize(fp)
            found_mvhd = False
            while f.tell() < file_size:
                # Read the box header (size and type)
                box_header = f.read(8)
                if len(box_header) < 8:
                    break

                box_size, box_type = struct.unpack('>I4s', box_header)
                box_type = box_type.decode('utf-8')

                if box_type == 'mvhd':
                    found_mvhd = True
                    # Skip version byte
                    f.read(1)
                    # Read current flags
                    current_flags = f.read(3)
                    if len(current_flags) < 3:
                        break

                    old_value = struct.unpack('>I', b'\x00' + current_flags)[0]

                    if debug:
                        print(f"[DEBUG] mvhd.flags before: {old_value}")

                    # Write the new flags
                    new_flags = struct.pack('>I', value)[1:]
                    f.seek(-3, os.SEEK_CUR)
                    f.write(new_flags)

                    if debug:
                        print(f"[DEBUG] mvhd.flags after: {value}")

                    return

                else:
                    # Move to the next box
                    f.seek(box_size - 8, os.SEEK_CUR)

            if not found_mvhd:
                if debug:
                    print("[DEBUG] mvhd.flags not found")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_mvhd_flags(input_file):
    # Create a temporary copy of the file
    tmp_path = 'temp_test_file.mp4'
    shutil.copy(input_file, tmp_path)

    # Test a representative value, e.g., 1 for the flags
    test_value = 1
    try:
        mp4_mvhd_flags(tmp_path, test_value, debug=True)
        print("Function executed successfully.")
    except Exception as e:
        print(f"Function failed with an error: {e}")

    # Clean up temporary file
    os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_flags('example.mp4')