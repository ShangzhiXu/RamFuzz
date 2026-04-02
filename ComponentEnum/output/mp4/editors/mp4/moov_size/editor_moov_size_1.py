import os
import shutil
import struct

def mp4_moov_size(fp, value, debug=False):
    """
    Modifies the 'moov.size' component in an MP4 file to a new uint32 value.
    
    Arguments:
    - fp (str): Path to the input MP4 file.
    - value (int): New value for 'moov.size', must be within uint32 range.
    - debug (bool): If True, prints debug information.
    """
    try:
        with open(fp, 'r+b') as file:
            while True:
                # Read the size (4 bytes) and type (4 bytes) of the box
                header = file.read(8)
                if len(header) < 8:
                    break  # EOF

                box_size, box_type = struct.unpack('>I4s', header)

                if box_type == b'moov':
                    if debug:
                        print(f"[DEBUG] moov.size before: {box_size}")

                    # Check the validity of the new value
                    if not (8 <= value <= 4294967295):
                        raise ValueError("Invalid value for moov.size. Must be in the range [8, 4294967295].")

                    # Seek back to the start of the box to overwrite the size
                    file.seek(-8, os.SEEK_CUR)
                    # Write the new size
                    file.write(struct.pack('>I', value))

                    if debug:
                        print(f"[DEBUG] moov.size after: {value}")
                    return

                # Skip to the next box
                file.seek(box_size - 8, os.SEEK_CUR)

        # If we exit the loop without finding 'moov'
        if debug:
            print("[DEBUG] moov.size not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error occurred: {e}")

def test_mp4_moov_size(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_path = tempfile.mktemp(suffix=".mp4")
    shutil.copy(input_file, tmp_path)

    try:
        # Use a representative test value for 'moov.size'
        test_value = 1024
        mp4_moov_size(tmp_path, test_value, debug=True)
        print("Function executed successfully")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_moov_size('example.mp4')