import struct
import shutil
import os
import tempfile

def mp4_mvhd_creation_time(fp, value, debug=False):
    try:
        with open(fp, 'rb+') as f:
            content = f.read()
            mvhd_index = content.find(b'mvhd')
            
            if mvhd_index == -1:
                if debug:
                    print("[DEBUG] mvhd.creation_time not found")
                return
            
            version = struct.unpack('B', content[mvhd_index + 4:mvhd_index + 5])[0]
            creation_time_index = mvhd_index + 8 if version == 0 else mvhd_index + 12

            old_value = struct.unpack('>I', content[creation_time_index:creation_time_index + 4])[0]
            
            if debug:
                print(f"[DEBUG] mvhd.creation_time before: {old_value}")

            # Set file position for writing
            f.seek(creation_time_index)
            
            f.write(struct.pack('>I', value))
            
            if debug:
                print(f"[DEBUG] mvhd.creation_time after: {value}")

    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {str(e)}")

def test_mp4_mvhd_creation_time(input_file):
    try:
        with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
            tmp_path = tmp_file.name
        shutil.copy(input_file, tmp_path)
        
        test_value = 2100000000  # Example representative test value within the uint32 range.
        mp4_mvhd_creation_time(tmp_path, test_value, debug=True)
        
        print("Test executed successfully")
        
    except Exception as e:
        print(f"Test failed: {e}")
    
    finally:
        os.remove(tmp_path)

# Example test execution
# Make sure you have a valid MP4 file path to pass for testing.
# test_mp4_mvhd_creation_time('input.mp4')