import os
import shutil
import struct

def mp4_mvhd_type(fp, value, debug=False):
    with open(fp, 'r+b') as file:
        # MP4 files start with a 'ftyp' box identifying the file type.
        # Seek to the beginning of the file.
        file.seek(0)

        while True:
            # Read the size (4 bytes) and type (4 bytes) of the box.
            header = file.read(8)
            if len(header) < 8:
                break  # Reached end of file without finding 'mvhd' box.

            box_size, box_type = struct.unpack('>I4s', header)
            box_type = box_type.decode('utf-8')

            # Check if this is the 'moov' box which might contain 'mvhd'
            if box_type == "moov":
                # We've found the 'moov' box; now we need to search within it.
                end_of_moov = file.tell() + box_size - 8
                while file.tell() < end_of_moov:
                    mvhd_header = file.read(8)
                    if len(mvhd_header) < 8:
                        break

                    mvhd_size, mvhd_type = struct.unpack('>I4s', mvhd_header)
                    mvhd_type = mvhd_type.decode('utf-8')

                    if mvhd_type == "mvhd":
                        # Found the mvhd box; find its 'type' component
                        current_position = file.tell()
                        mvhd_end = current_position + mvhd_size - 8

                        # Read 'mvhd.type'
                        current_type = file.read(4)

                        if debug:
                            print(f"[DEBUG] mvhd.type before: {current_type.decode('utf-8')}")

                        file.seek(current_position)
                        file.write(value.encode('utf-8'))

                        if debug:
                            print(f"[DEBUG] mvhd.type after: {value}")

                        return  # Successfully found and replaced the value.

                    file.seek(mvhd_size - 8, os.SEEK_CUR)
            
            else:
                # Skip the entire box if it's not 'moov'.
                file.seek(box_size - 8, os.SEEK_CUR)

    if debug:
        print(f"[DEBUG] mvhd.type not found")

def test_mp4_mvhd_type(input_file):
    # Create a temporary copy of the input file
    temp_file = 'temp_test.mp4'
    shutil.copy(input_file, temp_file)

    try:
        # Use a representative test value
        mp4_mvhd_type(temp_file, 'mvhd', debug=True)
        print("Function executed successfully")
    finally:
        # Clean up the temporary file
        os.remove(temp_file)