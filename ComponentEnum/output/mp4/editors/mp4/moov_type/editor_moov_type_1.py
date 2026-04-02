import os
import shutil
import struct

def mp4_moov_type(fp, value, debug=False):
    # Check that the value is valid
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The 'value' must be a string with a maximum length of 4.")

    try:
        with open(fp, 'r+b') as f:
            found_moov = False
            while True:
                # Read the size and type of the next box
                header = f.read(8)
                if len(header) < 8:
                    if debug:
                        print("[DEBUG] End of file reached without finding 'moov' box.")
                    break  # End of file reached
                
                size, box_type = struct.unpack('>I4s', header)
                box_type = box_type.decode('utf-8', errors='ignore')

                if box_type == 'moov':
                    # We found the 'moov' box
                    found_moov = True
                    if size < 8:
                        if debug:
                            print("[DEBUG] Invalid 'moov' box size, cannot proceed.")
                        break

                    # Read the current 'moov' type
                    pos = f.tell() - 4
                    f.seek(pos)
                    current_type = f.read(4).decode('utf-8', errors='ignore')
                    
                    if debug:
                        print(f"[DEBUG] moov.type before: {current_type}")

                    # Write new 'moov' type value
                    f.seek(pos)
                    f.write(value.encode('utf-8'))

                    if debug:
                        print(f"[DEBUG] moov.type after: {value}")
                    break
                else:
                    # Skip the current box, move forward
                    if size < 8:
                        if debug:
                            print("[DEBUG] Invalid box size encountered, skipping.")
                        break
                    f.seek(size - 8, os.SEEK_CUR)

            if not found_moov and debug:
                print("[DEBUG] moov.type not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_moov_type(input_file):
    tmp_path = input_file + '.tmp'
    try:
        shutil.copy(input_file, tmp_path)
        mp4_moov_type(tmp_path, 'mov', debug=True)
        print("Test executed successfully.")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage:
# test_mp4_moov_type('example.mp4')