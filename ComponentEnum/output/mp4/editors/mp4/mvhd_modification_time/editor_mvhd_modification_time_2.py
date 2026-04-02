import os
import struct
import shutil

def mp4_mvhd_modification_time(fp, value, debug=False):
    if not (2082844800 <= value <= 4294967295):
        raise ValueError("Value must be a valid uint32 in the specified range.")
    
    try:
        with open(fp, 'r+b') as f:
            file_data = f.read()

            mvhd_pos = file_data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.modification_time not found")
                return

            # The mvhd box starts at mvhd_pos, and the modification_time is the (4+4+4)*2 = 16th byte offset within the box
            mod_time_pos = mvhd_pos + 16 
            current_value = struct.unpack('>I', file_data[mod_time_pos:mod_time_pos+4])[0]

            if debug:
                print(f"[DEBUG] mvhd.modification_time before: {current_value}")

            # Writing the new value
            new_bytes = struct.pack('>I', value)
            f.seek(mod_time_pos)
            f.write(new_bytes)

            if debug:
                print(f"[DEBUG] mvhd.modification_time after: {value}")
                
    except Exception as e:
        print(f"An error occurred: {e}")

def test_mp4_mvhd_modification_time(input_file):
    try:
        tmp_path = input_file + ".temp"
        shutil.copy(input_file, tmp_path)

        # Let's assume a test value within the valid range
        test_value = 2082844801
        mp4_mvhd_modification_time(tmp_path, test_value, debug=True)

        print("Test completed successfully")
    except Exception as e:
        print(f"Test failed with error: {e}")
    finally:
        try:
            os.remove(tmp_path)
        except OSError:
            pass

# Example usage:
# test_mp4_mvhd_modification_time("path/to/your/input.mp4")