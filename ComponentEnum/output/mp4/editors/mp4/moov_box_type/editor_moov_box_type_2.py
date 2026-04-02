import os
import shutil
import struct

def mp4_moov_box_type(fp, value, debug=False):
    def find_moov_offset(file_data):
        offset = 0
        while offset < len(file_data) - 8:
            box_size, box_type = struct.unpack('>I4s', file_data[offset:offset+8])
            if box_type == b'moov':
                return offset + 4  # Return the start of the 'moov' box type
            offset += box_size
        return None

    if not isinstance(value, str) or len(value) > 4:
        raise ValueError("Value must be a string with a maximum length of 4 characters.")

    with open(fp, 'rb') as f:
        file_data = f.read()

    moov_offset = find_moov_offset(file_data)
    if moov_offset is None:
        if debug:
            print("[DEBUG] moov.box_type not found")
        return
    
    current_value = file_data[moov_offset:moov_offset+4].decode('utf-8')

    if debug:
        print(f"[DEBUG] moov.box_type before: {current_value}")

    new_value_bytes = value.encode('utf-8').ljust(4, b'\0')
    updated_file_data = (file_data[:moov_offset] +
                         new_value_bytes +
                         file_data[moov_offset+4:])
    
    with open(fp, 'wb') as f:
        f.write(updated_file_data)

    if debug:
        print(f"[DEBUG] moov.box_type after: {value}")

def test_mp4_moov_box_type(input_file):
    import tempfile

    # Create a temporary file path
    temp_dir = tempfile.mkdtemp()
    temp_path = os.path.join(temp_dir, 'test.mp4')

    try:
        # Copy the input file to the temporary location
        shutil.copy(input_file, temp_path)

        # Test value to replace the moov box type
        test_value = 'mova'
        
        # Run the function with debug enabled
        mp4_moov_box_type(temp_path, test_value, debug=True)

        # If we reach here, the function executed without errors
        print("Function executed successfully.")
    finally:
        # Clean up the temporary file
        shutil.rmtree(temp_dir)

# Example usage (assuming 'example.mp4' exists in the working directory)
# test_mp4_moov_box_type('example.mp4')