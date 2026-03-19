import os
import shutil
import struct

def mp4_moov_reserved(fp, value, debug=False):
    def find_moov_reserved(data):
        offset = 0
        while offset < len(data):
            size, box_type = struct.unpack(">I4s", data[offset:offset+8])
            if box_type == b'moov':
                moov_data = data[offset+8:offset+size]
                reserved_offset = moov_data.find(b'reserved')
                if reserved_offset != -1:
                    return offset + 8 + reserved_offset, len(b'reserved')
            offset += size
        return None, None

    if not isinstance(value, bytes):
        raise ValueError("Value must be of type bytes")

    with open(fp, 'rb') as file:
        data = file.read()

    reserved_offset, reserved_length = find_moov_reserved(data)
    if reserved_offset is None:
        if debug:
            print("[DEBUG] moov.reserved not found")
        return

    old_value = data[reserved_offset:reserved_offset+reserved_length]
    new_data = data[:reserved_offset] + value + data[reserved_offset+reserved_length:]

    if debug:
        print(f"[DEBUG] moov.reserved before: {old_value}")
        print(f"[DEBUG] moov.reserved after: {value}")

    with open(fp, 'wb') as file:
        file.write(new_data)


def test_mp4_moov_reserved(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_fd, tmp_path = tempfile.mkstemp()
    os.close(tmp_fd)
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for the moov.reserved component
        test_value = b'newvalue'  # This should be the same length as the original reserved length

        # Call the function with debug=True to see the output
        mp4_moov_reserved(tmp_path, test_value, debug=True)

        print("Function executed successfully")

    finally:
        # Clean up the temporary file
        os.remove(tmp_path)