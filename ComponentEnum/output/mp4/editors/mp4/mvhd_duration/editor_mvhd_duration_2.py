import struct
import os
import shutil

def mp4_mvhd_duration(fp, value, debug=False):
    def read_uint32(file):
        return struct.unpack('>I', file.read(4))[0]

    def write_uint32(file, val):
        file.write(struct.pack('>I', val))

    try:
        with open(fp, 'r+b') as file:
            file.seek(0, os.SEEK_END)
            file_size = file.tell()
            file.seek(0)

            while file.tell() < file_size:
                box_header = file.read(8)
                if len(box_header) < 8:
                    break
                box_size, box_type = struct.unpack('>I4s', box_header)

                if box_type == b'moov':
                    moov_end = file.tell() + box_size - 8

                    while file.tell() < moov_end:
                        atom_header = file.read(8)
                        if len(atom_header) < 8:
                            break
                        atom_size, atom_type = struct.unpack('>I4s', atom_header)

                        if atom_type == b'mvhd':
                            # Move to the duration position (always at offset 20 for version 0 boxes)
                            file.seek(12, os.SEEK_CUR)  # Skip version and creation/modification times

                            # Read current duration for debug
                            current_duration = read_uint32(file)
                            if debug:
                                print(f"[DEBUG] mvhd.duration before: {current_duration}")

                            # Seek back and write the new duration
                            file.seek(-4, os.SEEK_CUR)
                            write_uint32(file, value)

                            # Verify and print debug information after modification
                            file.seek(-4, os.SEEK_CUR)
                            new_duration = read_uint32(file)
                            if debug:
                                print(f"[DEBUG] mvhd.duration after: {new_duration}")

                            return

                        # Move to the next atom within moov
                        file.seek(atom_size - 8, os.SEEK_CUR)

                # Move to the next top-level box
                file.seek(box_size - 8, os.SEEK_CUR)

            if debug:
                print("[DEBUG] mvhd.duration not found")

    except Exception as e:
        if debug:
            print("[DEBUG] Error occurred: ", e)

def test_mp4_mvhd_duration(input_file):
    tmp_path = 'tmp_test_file.mp4'
    shutil.copy2(input_file, tmp_path)

    try:
        mp4_mvhd_duration(tmp_path, 3600, debug=True)  # Use a test duration value e.g., 3600
        print("Function executed successfully.")
    except Exception as e:
        print("Function failed: ", e)
    finally:
        os.remove(tmp_path)

# Example usage for the test function
# test_mp4_mvhd_duration('your_input_file.mp4')