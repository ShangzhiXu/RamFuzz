import struct
import shutil
import os

def mp4_mvhd_next_track_ID(fp, value, debug=False):
    # Define constants for 'mvhd' box lookup
    MVHD_BOX_TYPE = b'mvhd'
    HEADER_SIZE = 8  # 4 bytes for size, 4 bytes for type

    with open(fp, 'r+b') as file:
        # Function to read uint32
        def read_uint32(file_obj):
            return struct.unpack('>I', file_obj.read(4))[0]

        # Seek to the beginning and start reading the file
        file.seek(0, os.SEEK_END)
        file_size = file.tell()
        file.seek(0)

        while file.tell() < file_size:
            box_start = file.tell()
            # Read box header
            box_header = file.read(HEADER_SIZE)
            if len(box_header) < HEADER_SIZE:
                break
            box_size, box_type = struct.unpack('>I4s', box_header)

            # Verify it is a valid box size
            if box_size < HEADER_SIZE:
                break

            if box_type == MVHD_BOX_TYPE:
                # Skip version & flags (4 bytes), creation & modification time (8 bytes each for v1 or 4 each for v0)
                file.read(16)
                # Skip time scale and duration (4 bytes each)
                file.read(8)
                # Read preferred rate (4 bytes) and preferred volume with RESERVED (4 bytes)
                file.read(8)
                # Skip reserved (10 bytes)
                file.read(10)
                # Skip matrix (36 bytes)
                file.read(36)
                # Skip pre_defined (24 bytes)
                file.read(24)
                # Finally, read the current next_track_ID (4 bytes)
                current_value = read_uint32(file)

                # Output current value if debug is True
                if debug:
                    print(f"[DEBUG] mvhd.next_track_ID before: {current_value}")
                
                # Move file pointer back to the location of next_track_ID to write the new value
                file.seek(-4, os.SEEK_CUR)
                file.write(struct.pack('>I', value))

                # Output new value if debug is True
                if debug:
                    print(f"[DEBUG] mvhd.next_track_ID after: {value}")
                
                return
            else:
                # Skip remaining part of this box since it's not 'mvhd'
                file.seek(box_start + box_size, os.SEEK_SET)
    
    if debug:
        print("[DEBUG] mvhd.next_track_ID not found")

def test_mp4_mvhd_next_track_ID(input_file):
    import tempfile

    # Create a temporary copy of the input file
    with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
        shutil.copyfile(input_file, tmp_file.name)

        try:
            # Define a representative test value
            test_value = 1234567890

            # Attempt to modify the mvhd.next_track_ID and print the result
            mp4_mvhd_next_track_ID(tmp_file.name, test_value, debug=True)
            print("Test completed successfully.")

        finally:
            # Clean up temporary file
            if os.path.exists(tmp_file.name):
                os.remove(tmp_file.name)

# Example usage:
# test_mp4_mvhd_next_track_ID("path_to_some_mp4_file.mp4")