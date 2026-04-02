import os
import shutil
import struct

def mp4_moov_reserved(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            moov_type_pos = data.find(b'moov')
            if moov_type_pos == -1:
                if debug:
                    print("[DEBUG] moov.reserved not found")
                return

            # moov is a container box: size(4) + type(4) + child boxes.
            # data.find returns the type field pos. Body starts at type_pos+4.
            # Write into the moov body (first child box area) for violation fuzzing.
            write_offset = moov_type_pos + 4
            write_len = min(len(value), 4)
            old_value = data[write_offset:write_offset+write_len]

            if debug:
                print(f"[DEBUG] moov.reserved before: {old_value}")

            f.seek(write_offset)
            f.write(value[:write_len])

            if debug:
                print(f"[DEBUG] moov.reserved after: {value[:write_len]}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_moov_reserved(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the 'reserved' component
        test_value = b'newresvd'
        
        # Call the function with debug=True
        mp4_moov_reserved(tmp_path, test_value, debug=True)
        
        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_moov_reserved('example.mp4')