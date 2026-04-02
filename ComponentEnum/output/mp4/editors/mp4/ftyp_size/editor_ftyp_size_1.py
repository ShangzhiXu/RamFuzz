import struct
import shutil
import os

def mp4_ftyp_size(fp, value, debug=False):
    # Validate value range for uint32
    if not (8 <= value <= 4294967295):
        raise ValueError("Value must be within the range [8, 4294967295].")

    try:
        with open(fp, 'r+b') as file:
            # Read the initial 8 bytes to check for the 'ftyp' box
            box_header = file.read(8)
            if len(box_header) < 8:
                print("[DEBUG] ftyp.size not found")
                return

            # Unpack the size and type
            size, box_type = struct.unpack('>I4s', box_header)

            if box_type != b'ftyp':
                print("[DEBUG] ftyp.size not found")
                return

            # Debug print the current ftyp size
            if debug:
                print(f"[DEBUG] ftyp.size before: {size}")

            # Move file pointer back to the start
            file.seek(0)

            # Write the new size
            file.write(struct.pack('>I', value))

            # Debug print the new ftyp size
            if debug:
                print(f"[DEBUG] ftyp.size after: {value}")

    except Exception as e:
        print(f"[ERROR] An error occurred: {e}")

def test_mp4_ftyp_size(input_file):
    tmp_path = input_file + ".tmp"
    
    try:
        # Copy the input file to a temporary path
        shutil.copy(input_file, tmp_path)
        
        # Call the mp4_ftyp_size function with a test value
        test_value = 20  # Example test value, must be in the valid range
        mp4_ftyp_size(tmp_path, test_value, debug=True)
        
        # If no exceptions, print success
        print("Function executed successfully")
    
    except Exception as e:
        print(f"[ERROR] Test failed: {e}")
    
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

# Example usage
# test_mp4_ftyp_size('example.mp4')