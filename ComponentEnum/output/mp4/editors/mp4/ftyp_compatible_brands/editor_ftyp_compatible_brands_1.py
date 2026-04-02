import os
import shutil
import struct

def mp4_ftyp_compatible_brands(fp, value, debug=False):
    # Ensure the new value is a list of strings, each exactly 4 characters long
    if not isinstance(value, list) or not all(isinstance(v, str) and len(v) == 4 for v in value):
        raise ValueError("Each brand must be a 4-character string.")

    with open(fp, 'rb+') as f:
        # Read the file signature to ensure it's an MP4 file
        f.seek(0)
        file_signature = f.read(8)  # typically 'ftyp' starts after first 8 bytes
        if len(file_signature) < 8:
            if debug:
                print("[DEBUG] File too small to be a valid MP4.")
            return
        
        # Search for ftyp box
        f.seek(0)
        while True:
            box_header = f.read(8)
            if len(box_header) < 8:
                if debug:
                    print("[DEBUG] Reached end of file without finding 'ftyp'.")
                return

            box_size, box_type = struct.unpack('>I4s', box_header)
            box_type = box_type.decode('utf-8')

            if box_type == 'ftyp':
                major_brand = f.read(4)
                minor_version = f.read(4)
                
                compatible_brands_size = box_size - 16  # 8 for the header, 8 for major_brand and minor_version
                if compatible_brands_size < 0 or compatible_brands_size % 4 != 0:
                    if debug:
                        print("[DEBUG] Invalid ftyp compatible brands length.")
                    return

                # Read the current compatible brands
                compatible_brands = []
                for _ in range(compatible_brands_size // 4):
                    brand = f.read(4).decode('utf-8')
                    compatible_brands.append(brand)
                
                if debug:
                    print(f"[DEBUG] ftyp.compatible_brands before: {compatible_brands}")

                # Update compatible brands
                new_compatible_brands_bytes = b''.join(b.encode('utf-8') for b in value)
                new_box_size = 16 + len(new_compatible_brands_bytes)
                
                # Seek back to the start of ftyp box to overwrite
                f.seek(-box_size, os.SEEK_CUR)
                f.write(struct.pack('>I4s', new_box_size, b'ftyp'))
                f.write(major_brand)
                f.write(minor_version)
                f.write(new_compatible_brands_bytes)

                if debug:
                    print(f"[DEBUG] ftyp.compatible_brands after: {value}")
                return

            else:
                # Skip to the next box
                if box_size < 8:
                    if debug:
                        print("[DEBUG] Invalid box size encountered.")
                    return
                f.seek(box_size - 8, os.SEEK_CUR)

def test_mp4_ftyp_compatible_brands(input_file):
    temp_file = input_file + '.tmp'
    shutil.copy(input_file, temp_file)

    try:
        test_value = ['isom', 'iso2', 'avc1', 'mp41']
        mp4_ftyp_compatible_brands(temp_file, test_value, debug=True)
        print("Function executed successfully.")
    finally:
        if os.path.exists(temp_file):
            os.remove(temp_file)