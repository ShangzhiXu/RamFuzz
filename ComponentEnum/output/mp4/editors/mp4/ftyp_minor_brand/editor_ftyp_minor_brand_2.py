import os
import shutil

def mp4_ftyp_minor_brand(fp, value, debug=False):
    if not isinstance(value, str) or not (0 < len(value) <= 4):
        raise ValueError("The value must be a non-empty string of at most 4 characters.")

    try:
        with open(fp, 'r+b') as file:
            while True:
                header = file.read(8)
                if len(header) < 8:
                    if debug:
                        print("[DEBUG] Reached end of file without finding ftyp box")
                    break

                size, box_type = int.from_bytes(header[0:4], 'big'), header[4:8]

                if box_type == b'ftyp':
                    major_brand = file.read(4)
                    minor_brand = file.read(4)
                    
                    if debug:
                        print(f"[DEBUG] ftyp.minor_brand before: {minor_brand.decode('ascii', 'replace')}")
                    
                    # Seek back to the start of the minor_brand and write the new value
                    file.seek(file.tell() - 4)
                    file.write(value.encode('ascii').ljust(4, b'\x00'))
                    
                    if debug:
                        # Verify that the write was successful
                        file.seek(file.tell() - 4)
                        new_minor_brand = file.read(4).decode('ascii', 'replace')
                        print(f"[DEBUG] ftyp.minor_brand after: {new_minor_brand}")
                    
                    return
                else:
                    file.seek(size - 8, os.SEEK_CUR)
        
        if debug:
            print("[DEBUG] ftyp.box not found")
    except Exception as e:
        if debug:
            print(f"An error occurred: {e}")
        raise e  # Re-raise the exception for test harness to capture

def test_mp4_ftyp_minor_brand(input_file):
    test_value = "test"
    tmp_path = "temp_test_file.mp4"
    shutil.copy(input_file, tmp_path)
    
    try:
        mp4_ftyp_minor_brand(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    except Exception as e:
        print(f"Test failed with exception: {e}")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)