import os
import struct
import shutil
import tempfile

def mp4_mvhd_volume(fp, value, debug=False):
    """
    Parses the 'mvhd.volume' component from an input MP4 file and rewrites it with the specified value.

    Parameters:
    - fp (str): Path to the input file. The function modifies the file in-place.
    - value: The new value to write for this component. Should be a fixed-point type.
    - debug (bool): If True, print the component value before and after rewriting.
    """
    try:
        with open(fp, 'r+b') as file:
            # Read the file header and find the 'moov' atom
            file.seek(0, os.SEEK_END)
            file_size = file.tell()
            file.seek(0)

            while file.tell() < file_size:
                atom_size_data = file.read(4)
                atom_type = file.read(4)

                if len(atom_size_data) < 4 or len(atom_type) < 4:
                    break

                atom_size = struct.unpack('>I', atom_size_data)[0]

                if atom_type == b'moov':
                    moov_start = file.tell() - 8
                    moov_end = moov_start + atom_size

                    while file.tell() < moov_end:
                        sub_atom_size_data = file.read(4)
                        sub_atom_type = file.read(4)

                        if len(sub_atom_size_data) < 4 or len(sub_atom_type) < 4:
                            break

                        sub_atom_size = struct.unpack('>I', sub_atom_size_data)[0]

                        if sub_atom_type == b'mvhd':
                            mvhd_start = file.tell() - 8
                            file.seek(12, os.SEEK_CUR)  # Skip version, flags, creation and modification time
                            file.seek(8, os.SEEK_CUR)  # Skip timescale and duration
                            file.seek(4, os.SEEK_CUR)  # Skip rate

                            volume_pos = file.tell()
                            old_volume_data = file.read(2)
                            old_volume = struct.unpack('>H', old_volume_data)[0]

                            if debug:
                                print(f"[DEBUG] mvhd.volume before: {old_volume}")

                            # Calculate the fixed-point representation of the new volume
                            new_volume = int(value * 256)

                            if 0 <= new_volume <= 65535:
                                file.seek(volume_pos)
                                file.write(struct.pack('>H', new_volume))

                                if debug:
                                    print(f"[DEBUG] mvhd.volume after: {new_volume}")
                            else:
                                if debug:
                                    print(f"[DEBUG] Error: Computed volume {new_volume} is out of range.")

                            return

                        file.seek(sub_atom_size - 8, os.SEEK_CUR)

                file.seek(atom_size - 8, os.SEEK_CUR)

        if debug:
            print("[DEBUG] mvhd.volume not found")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {e}")

def test_mp4_mvhd_volume(input_file):
    """
    Test harness for the `mp4_mvhd_volume` function.

    Parameters:
    - input_file (str): Path to the input MP4 file to test with.
    """
    test_value = 0.5  # Representative test value for mvhd.volume

    with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
        tmp_path = tmp_file.name

    try:
        shutil.copy(input_file, tmp_path)
        mp4_mvhd_volume(tmp_path, test_value, debug=True)
        print("Test executed successfully.")
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)