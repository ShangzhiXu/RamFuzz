import os
import shutil
import struct

def mp4_mvhd_pre_defined(fp, value, debug=False):
    try:
        with open(fp, 'r+b') as f:
            # Read the entire file into memory
            data = f.read()
            
            # Find the 'mvhd' box
            mvhd_pos = data.find(b'mvhd')
            if mvhd_pos == -1:
                if debug:
                    print("[DEBUG] mvhd box not found")
                return

            # Locate the start of the 'mvhd' box
            mvhd_start = mvhd_pos - 4
            
            # Read the size of the 'mvhd' box
            mvhd_size = struct.unpack('>I', data[mvhd_start:mvhd_start+4])[0]
            
            # Calculate the end of the 'mvhd' box
            mvhd_end = mvhd_start + mvhd_size

            # Version (1 byte) and flags (3 bytes) are 4 bytes, 
            # creation (4 bytes), modification (4 bytes), timescale (4 bytes), duration (4 bytes) are 16 bytes
            # Rate (4 bytes), volume (2 bytes), reserved (10 bytes)
            # So, pre_defined starts at offset 32 bytes from the start of the 'mvhd' box
            pre_defined_offset = mvhd_pos + 20

            # Verify if pre_defined_offset is within mvhd box size
            if pre_defined_offset + 24 > mvhd_end:
                if debug:
                    print("[DEBUG] Calculated pre_defined_offset exceeds mvhd box size")
                return

            # Read the current pre_defined value
            current_value = data[pre_defined_offset:pre_defined_offset + 24]
            if debug:
                print(f"[DEBUG] mvhd.pre_defined before: {current_value}")

            # Replace the pre_defined value with the new value
            if not isinstance(value, bytes) or len(value) != 24:
                raise ValueError("The 'value' must be a 24-byte long bytes object.")
            
            # Construct new data with the replaced value
            new_data = data[:pre_defined_offset] + value + data[pre_defined_offset + 24:]

            # Write the modified data back to the file
            f.seek(0)
            f.write(new_data)
            f.truncate()
            
            if debug:
                print(f"[DEBUG] mvhd.pre_defined after: {value}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {str(e)}")

def test_mp4_mvhd_pre_defined(input_file):
    import tempfile
    
    # Create a temporary file path
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".mp4")
    os.close(tmp_fd)
    
    # Copy the input file to the temporary path
    shutil.copy(input_file, tmp_path)
    
    try:
        # Define a test value for pre_defined (24 bytes long)
        test_value = bytes(range(24))  # Example value
        mp4_mvhd_pre_defined(tmp_path, test_value, debug=True)
        
        print("Function executed successfully")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_mvhd_pre_defined('example.mp4')