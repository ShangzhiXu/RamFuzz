import os
import shutil
import struct

def mp4_mvhd_size(fp, value, debug=False):
    # Ensure the value is within the specified uint32 range
    if not (8 <= value <= 4294967295):
        raise ValueError("Value must be within the range [8, 4294967295]")

    mvhd_atom_identifier = b'mvhd'
    try:
        with open(fp, 'r+b') as f:
            while True:
                # Read the size and type of the next atom
                header = f.read(8)
                if len(header) < 8:
                    break
                atom_size, atom_type = struct.unpack('>I4s', header)

                # Check if this is the 'mvhd' atom
                if atom_type == mvhd_atom_identifier:
                    # Read the version and flags (4 bytes)
                    version_and_flags = f.read(4)
                    
                    # Read the current size value (4 bytes)
                    old_size_bytes = f.read(4)
                    old_size = struct.unpack('>I', old_size_bytes)[0]
                    
                    # Debug print the old size
                    if debug:
                        print(f"[DEBUG] mvhd.size before: {old_size}")
                    
                    # Move back 4 bytes to overwrite the old size
                    f.seek(-4, os.SEEK_CUR)
                    
                    # Write the new size value
                    f.write(struct.pack('>I', value))
                    
                    # Debug print the new size
                    if debug:
                        print(f"[DEBUG] mvhd.size after: {value}")
                    
                    # Exit after modifying the first found mvhd atom
                    return

                # Move to the next atom
                f.seek(atom_size - 8, os.SEEK_CUR)

        # If we finish the loop without finding mvhd, print debug message
        if debug:
            print("[DEBUG] mvhd.size not found")
    
    except Exception as e:
        raise RuntimeError(f"An error occurred while processing the file: {e}")

def test_mp4_mvhd_size(input_file):
    # Create a temporary copy of the file to modify
    tmp_path = input_file + ".tmp"
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for mvhd.size
        test_value = 1024

        # Call the function with debug mode on
        mp4_mvhd_size(tmp_path, test_value, debug=True)

        print("Function executed successfully.")
    except Exception as e:
        print(f"Test failed: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(tmp_path):
            os.remove(tmp_path)