import os
import struct
import shutil

def mp4_mvhd_size(fp, value, debug=False):
    def find_mvhd_offset(file):
        """
        Locate the 'mvhd' atom and return its offset in the file.
        """
        file.seek(0)
        while True:
            box_header = file.read(8)
            if len(box_header) < 8:
                break  # End of file reached
            box_size, box_type = struct.unpack(">I4s", box_header)

            # Check if we've found the 'mvhd' box
            if box_type == b'moov':
                # Traverse the 'moov' atom
                moov_size = box_size
                moov_data = file.tell()
                while moov_data < moov_size - 8:
                    sub_header = file.read(8)
                    if len(sub_header) < 8:
                        break
                    sub_size, sub_type = struct.unpack(">I4s", sub_header)

                    if sub_type == b'mvhd':
                        return file.tell() - 8  # Return the offset of 'mvhd'

                    # Move to the next sub box
                    file.seek(sub_size - 8, os.SEEK_CUR)
                break

            # Move to the next main atom
            file.seek(box_size - 8, os.SEEK_CUR)
        
        return None  # 'mvhd' is not found

    if not (8 <= value <= 4294967295):
        raise ValueError(f"Value must be between 8 and 4294967295, got {value}")

    with open(fp, 'r+b') as file:
        mvhd_offset = find_mvhd_offset(file)
        if mvhd_offset is None:
            if debug:
                print("[DEBUG] mvhd.size not found")
            return

        file.seek(mvhd_offset + 8)  # Move to the size field after 'mvhd' header
        old_value_bytes = file.read(4)

        old_value = struct.unpack(">I", old_value_bytes)[0]
        if debug:
            print(f"[DEBUG] mvhd.size before: {old_value}")

        file.seek(mvhd_offset + 8)
        file.write(struct.pack(">I", value))

        if debug:
            print(f"[DEBUG] mvhd.size after: {value}")


def test_mp4_mvhd_size(input_file):
    import tempfile
    
    # Create a temporary copy of the input file
    tmp_dir = tempfile.gettempdir()
    tmp_path = os.path.join(tmp_dir, os.path.basename(input_file))
    shutil.copy(input_file, tmp_path)
    
    try:
        # Define a test value
        test_value = 1000
        
        # Call the function
        mp4_mvhd_size(tmp_path, test_value, debug=True)
        print("Function executed successfully with test value.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)