import os
import shutil
import struct

def mp4_ftyp_minor_brand(fp, value, debug=False):
    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("The 'value' must be a string with a maximum length of 4")

    try:
        with open(fp, 'rb+') as f:
            # Read the first 8 bytes to check the size and type
            header = f.read(8)
            if len(header) < 8:
                if debug:
                    print("[DEBUG] File too small to contain a valid 'ftyp' box")
                return
                
            size, box_type = struct.unpack('>I4s', header)
            
            # Check if it's an 'ftyp' box
            if box_type != b'ftyp':
                if debug:
                    print("[DEBUG] No 'ftyp' box found at the start of the file")
                return
            
            # Read the major brand (4 bytes) and minor version (4 bytes)
            major_brand = f.read(4)
            minor_brand = f.read(4)

            if len(minor_brand) < 4:
                if debug:
                    print("[DEBUG] Incomplete 'ftyp' structure, minor brand not found")
                return

            old_value = minor_brand.decode('utf-8', errors='replace')
            if debug:
                print(f"[DEBUG] ftyp.minor_brand before: {old_value}")

            # Seek back to the start of the minor brand and write new value
            f.seek(12)  # 8 (header) + 4 (major_brand)
            f.write(value.encode('utf-8').ljust(4, b'\0'))

            if debug:
                print(f"[DEBUG] ftyp.minor_brand after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_ftyp_minor_brand(input_file):
    import tempfile

    # Create a temporary file
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    
    try:
        # Copy the input file to the temporary path
        shutil.copy(input_file, tmp_path)

        # Use a valid length test value
        test_value = "tes"  # Ensure the test value is within the length limit
        mp4_ftyp_minor_brand(tmp_path, test_value, debug=True)
        
        print("Test executed successfully.")
    
    except Exception as e:
        print(f"Test failed with error: {e}")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)