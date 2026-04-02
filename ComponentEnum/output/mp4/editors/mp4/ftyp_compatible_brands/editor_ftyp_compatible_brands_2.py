import os
import shutil
import tempfile

def mp4_ftyp_compatible_brands(fp, value, debug=False):
    # Check that value is a bytes array of length multiples of 4
    if not isinstance(value, (bytes, bytearray)) or len(value) % 4 != 0:
        raise ValueError("Value must be a byte sequence with a length multiple of 4.")

    with open(fp, 'r+b') as file:
        data = file.read()
        
        # Search for 'ftyp' box
        pos = data.find(b'ftyp')
        if pos == -1:
            if debug:
                print("[DEBUG] ftyp.compatible_brands not found")
            return
        
        # 'ftyp' found, seek to its position
        file.seek(pos)
        
        # Read box header size (first 4 bytes) and move to the end of 'major_brand' and 'minor_version'
        size = int.from_bytes(data[pos:pos+4], byteorder='big')
        file.seek(pos + 8)
        
        # Calculate existing compatible brands length
        existing_brands_length = size - 16  # Total box size - header and fixed fields
        
        # Ensure we do not read past the file
        compatible_brands = data[pos+16:pos+16+existing_brands_length]

        if debug:
            print(f"[DEBUG] ftyp.compatible_brands before: {compatible_brands}")

        # Replacing with the new value
        new_value_length = len(value)
        file.seek(pos + 16)
        file.write(value)
        
        # Adjust the file size if different
        if new_value_length != existing_brands_length:
            remaining_data = data[pos + 16 + existing_brands_length:]
            file.write(remaining_data)
            new_size = pos + 16 + new_value_length + len(remaining_data)
            
            # Update the initial size field if needed
            file.seek(pos)
            file.write((16 + new_value_length).to_bytes(4, byteorder='big'))

            file.truncate(new_size)

        if debug:
            print(f"[DEBUG] ftyp.compatible_brands after: {value}")

def test_mp4_ftyp_compatible_brands(input_file):
    # Create a temporary copy of the file
    tmp_file = tempfile.mktemp(suffix='.mp4')
    shutil.copy(input_file, tmp_file)

    try:
        # Corrected test value (should be bytes and a multiple length of 4)
        test_value = b'isomiso2'
        mp4_ftyp_compatible_brands(tmp_file, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        # Clean up
        if os.path.exists(tmp_file):
            os.remove(tmp_file)