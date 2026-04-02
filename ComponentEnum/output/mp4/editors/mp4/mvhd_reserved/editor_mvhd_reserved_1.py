import os
import shutil
import struct

def mp4_mvhd_reserved(fp, value, debug=False):
    try:
        with open(fp, 'rb+') as f:
            # Read the entire file into memory
            data = f.read()

            # Locate the 'mvhd' atom
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd.reserved not found")
                return

            # Parse the 'mvhd' atom header
            # 'mvhd' atom starts immediately after the 'mvhd' string
            # We assume the version is either 0 or 1, both are common
            version = struct.unpack('>B', data[mvhd_pos + 4:mvhd_pos + 5])[0]

            # Determine the offset of 'reserved' based on version
            # Version 0: creation_time, modification_time, timescale, duration (4 bytes each), rate (4 bytes), volume (2 bytes), reserved (10 bytes)
            # Version 1: creation_time, modification_time, timescale, duration (8 bytes each), rate (4 bytes), volume (2 bytes), reserved (10 bytes)
            if version == 0:
                reserved_offset = mvhd_pos + 4 + 4 + 4 + 4 + 4 + 4 + 2
            elif version == 1:
                reserved_offset = mvhd_pos + 4 + 8 + 8 + 4 + 8 + 4 + 2
            else:
                if debug:
                    print("[DEBUG] Unsupported version")
                return

            # Ensure the value is the correct length
            if not isinstance(value, (bytes, bytearray)) or len(value) != 10:
                if debug:
                    print("[DEBUG] Provided value is not 10 bytes long or not of type bytes/bytearray")
                return

            # Read the current 'reserved' value
            old_reserved = data[reserved_offset:reserved_offset + 10]

            if debug:
                print(f"[DEBUG] mvhd.reserved before: {old_reserved}")

            # Write the new 'reserved' value
            f.seek(reserved_offset)
            f.write(value)

            if debug:
                print(f"[DEBUG] mvhd.reserved after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Exception occurred: {e}")

def test_mp4_mvhd_reserved(input_file):
    import tempfile
    
    # Create a temporary copy of the input file
    tmp_file = tempfile.NamedTemporaryFile(delete=False)
    tmp_file.close()
    shutil.copy(input_file, tmp_file.name)

    try:
        # Test value to use for the reserved component
        test_value = b'\x00' * 10  # Commonly the reserved bytes are zeroed

        # Call the function with the test value
        mp4_mvhd_reserved(tmp_file.name, test_value, debug=True)
        
        print("Test executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_file.name)