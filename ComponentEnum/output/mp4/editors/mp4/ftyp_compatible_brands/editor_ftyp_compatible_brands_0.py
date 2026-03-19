import os
import shutil
import struct

def mp4_ftyp_compatible_brands(fp, value, debug=False):
    def read_box_header(file):
        header = file.read(8)
        if len(header) < 8:
            return None, None
        size, box_type = struct.unpack('>I4s', header)
        return size, box_type

    def find_ftyp(file):
        file.seek(0)
        while True:
            pos = file.tell()
            size, box_type = read_box_header(file)
            if not size or not box_type:
                return None, None
            if box_type == b'ftyp':
                return pos, size
            file.seek(size - 8, os.SEEK_CUR)

    # Ensure the value is a list of bytes-like objects
    if not isinstance(value, list) or not all(isinstance(brand, (bytes, bytearray)) and len(brand) == 4 for brand in value):
        raise ValueError("value must be a list of 4-byte bytes-like objects")

    with open(fp, 'r+b') as file:
        ftyp_pos, ftyp_size = find_ftyp(file)
        if ftyp_pos is None:
            if debug:
                print("[DEBUG] ftyp.compatible_brands not found")
            return

        file.seek(ftyp_pos + 8)  # Skip 'ftyp' header
        major_brand = file.read(4)
        minor_version = file.read(4)
        compatible_brands = []

        remaining_size = ftyp_size - 16  # Exclude header, major_brand, and minor_version
        while remaining_size >= 4:
            brand = file.read(4)
            compatible_brands.append(brand)
            remaining_size -= 4

        if debug:
            print(f"[DEBUG] ftyp.compatible_brands before: {compatible_brands}")

        # Write new compatible brands
        file.seek(ftyp_pos + 16)  # Position after major_brand and minor_version
        for brand in value:
            file.write(brand)

        # Truncate if new value is shorter
        file.truncate(ftyp_pos + 16 + len(value) * 4)

        if debug:
            print(f"[DEBUG] ftyp.compatible_brands after: {value}")

def test_mp4_ftyp_compatible_brands(input_file):
    import tempfile

    # Create a temporary copy of the input file
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".mp4")
    os.close(tmp_fd)
    shutil.copy(input_file, tmp_path)

    try:
        # Test value for compatible brands
        test_value = [b'isom', b'iso2', b'avc1', b'mp41']
        mp4_ftyp_compatible_brands(tmp_path, test_value, debug=True)
        print("Function executed successfully")
    finally:
        # Clean up the temporary file
        os.remove(tmp_path)

# Example usage:
# test_mp4_ftyp_compatible_brands('example.mp4')