#!/usr/bin/env python3
"""
Generator script: reads 03_subcomponents.json and generates editor scripts
for all MP4 box types.

Each box type gets a folder (e.g., ftyp/) with a script (e.g., ftyp.py)
containing a function that can read/modify fields in that box.
"""

import json
import os
import textwrap

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
JSON_PATH = os.path.join(SCRIPT_DIR, '..', '..', '03_subcomponents.json')
OUTPUT_DIR = SCRIPT_DIR

# ============================================================
# Box type tag mapping (JSON key -> actual 4-byte tag in file)
# Most are identical; only list exceptions here.
# ============================================================
TAG_MAP = {
    "url":  b'url ',
    "urn":  b'urn ',
    "xml":  b'xml ',
}

# ============================================================
# Field definitions for each box type.
# Format: field_name -> (offset_from_box_start, byte_size, struct_format)
#   ">I" = uint32 BE, ">H" = uint16 BE, ">B" = uint8,
#   ">Q" = uint64 BE, ">i" = int32 BE, ">h" = int16 BE,
#   "4s" = 4-byte string, "raw" = raw bytes
#
# We define ALL field names from the JSON, mapping aliases to
# the correct offset. If two JSON fields are the same physical
# location, they both appear with the same offset.
# ============================================================

# -- Helper: common box header fields --
def _box_header():
    return {
        "size": (0, 4, ">I"),
        "type": (4, 4, "4s"),
        "box_type": (4, 4, "4s"),
    }

def _fullbox_header():
    d = _box_header()
    d.update({
        "version": (8, 1, ">B"),
        "flags":   (9, 3, "raw"),
    })
    return d

# -- Container boxes: only have size + type --
CONTAINER_FIELDS = _box_header()
CONTAINER_FIELDS["reserved"] = (8, 4, "raw")

# -- Visual sample entry base layout (avc1, avc3, hvc1, mp4v, dvav, dvh1, dvhe, dvvc, encv) --
def _visual_sample_entry():
    return {
        "size":              (0,  4, ">I"),
        "type":              (4,  4, "4s"),
        "reserved":          (8,  6, "raw"),
        "reserved1":         (8,  6, "raw"),
        "data_reference_index": (14, 2, ">H"),
        "pre_defined":       (16, 2, ">H"),
        "version":           (16, 2, ">H"),
        "reserved2":         (18, 2, ">H"),
        "revision_level":    (18, 2, ">H"),
        "pre_defined1":      (20, 12, "raw"),
        "vendor":            (20, 4, "raw"),
        "temporal_quality":  (24, 4, ">I"),
        "spatial_quality":   (28, 4, ">I"),
        "pre_defined2":      (20, 12, "raw"),
        "width":             (32, 2, ">H"),
        "height":            (34, 2, ">H"),
        "horizresolution":   (36, 4, ">I"),
        "vertresolution":    (40, 4, ">I"),
        "reserved3":         (44, 4, "raw"),
        "data_size":         (44, 4, ">I"),
        "frame_count":       (48, 2, ">H"),
        "compressorname":    (50, 32, "raw"),
        "depth":             (82, 2, ">H"),
        "pre_defined3":      (84, 2, ">H"),
    }

# -- Audio sample entry base layout (mp4a, ac-3, ec-3, dtsc, dtse, dtsh, dtsl, alaw, ulaw, enca, etc.) --
def _audio_sample_entry():
    return {
        "size":              (0,  4, ">I"),
        "type":              (4,  4, "4s"),
        "reserved":          (8,  6, "raw"),
        "reserved1":         (8,  6, "raw"),
        "data_reference_index": (14, 2, ">H"),
        "version":           (16, 2, ">H"),
        "entry_version":     (16, 2, ">H"),
        "revision":          (18, 2, ">H"),
        "revision_level":    (18, 2, ">H"),
        "vendor":            (20, 4, "raw"),
        "channelcount":      (24, 2, ">H"),
        "channelCount":      (24, 2, ">H"),
        "channel_count":     (24, 2, ">H"),
        "channels":          (24, 2, ">H"),
        "samplesize":        (26, 2, ">H"),
        "sampleSize":        (26, 2, ">H"),
        "sample_size":       (26, 2, ">H"),
        "compression_id":    (28, 2, ">H"),
        "compressionid":     (28, 2, ">H"),
        "pre_defined":       (28, 2, ">H"),
        "predefined":        (28, 2, ">H"),
        "packet_size":       (30, 2, ">H"),
        "packetsize":        (30, 2, ">H"),
        "samplerate":        (32, 4, ">I"),
        "sampleRate":        (32, 4, ">I"),
        "sample_rate":       (32, 4, ">I"),
        "reserved2":         (16, 8, "raw"),
        "reserved3":         (30, 2, "raw"),
        "pre_defined1":      (28, 2, ">H"),
    }

# ============================================================
# Per-box field definitions
# ============================================================
BOX_DEFS = {}

# --- ftyp ---
BOX_DEFS["ftyp"] = {
    "size":              (0,  4, ">I"),
    "type":              (4,  4, "4s"),
    "box_type":          (4,  4, "4s"),
    "major_brand":       (8,  4, "4s"),
    "brand":             (8,  4, "4s"),
    "minor_brand":       (8,  4, "4s"),
    "minor_version":     (12, 4, ">I"),
    "compatible_brands": (16, 4, "4s"),
    "reserved":          (12, 4, "raw"),
}

# --- styp (same as ftyp) ---
BOX_DEFS["styp"] = {
    "size":              (0,  4, ">I"),
    "type":              (4,  4, "4s"),
    "major_brand":       (8,  4, "4s"),
    "minor_version":     (12, 4, ">I"),
    "compatible_brands": (16, 4, "4s"),
}

# --- Container boxes ---
for box in ["moov", "trak", "mdia", "minf", "stbl", "dinf", "moof", "traf",
            "mfra", "sinf", "schi", "ipco", "iprp", "ipro", "pdam", "wide",
            "trak", "mdia", "minf", "stbl"]:
    BOX_DEFS[box] = dict(CONTAINER_FIELDS)

# --- Data-only boxes ---
for box in ["mdat", "free", "skip", "idat", "jp2c", "ilst", "udta", "edts"]:
    d = _box_header()
    d["data"] = (8, 4, "raw")  # just first 4 bytes of data
    BOX_DEFS[box] = d

# --- mvhd (version 0) ---
BOX_DEFS["mvhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "creation_time":     (12,  4, ">I"),
    "modification_time": (16,  4, ">I"),
    "timescale":         (20,  4, ">I"),
    "duration":          (24,  4, ">I"),
    "rate":              (28,  4, ">I"),
    "volume":            (32,  2, ">H"),
    "reserved":          (34, 10, "raw"),
    "reserved1":         (34,  2, "raw"),
    "reserved2":         (36,  8, "raw"),
    "reserved_2":        (36,  8, "raw"),
    "reserved3":         (34, 10, "raw"),
    "pad":               (34,  2, "raw"),
    "matrix":            (44, 36, "raw"),
    "matrix_structure":  (44, 36, "raw"),
    "pre_defined":       (80, 24, "raw"),
    "next_track_ID":     (104, 4, ">I"),
    "next_track_id":     (104, 4, ">I"),
}

# --- tkhd (version 0) ---
BOX_DEFS["tkhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "creation_time":     (12,  4, ">I"),
    "modification_time": (16,  4, ">I"),
    "track_ID":          (20,  4, ">I"),
    "track_id":          (20,  4, ">I"),
    "reserved":          (24,  4, "raw"),
    "reserved1":         (24,  4, "raw"),
    "duration":          (28,  4, ">I"),
    "reserved2":         (32,  8, "raw"),
    "reserved_2":        (32,  8, "raw"),
    "layer":             (40,  2, ">H"),
    "alternate_group":   (42,  2, ">H"),
    "volume":            (44,  2, ">H"),
    "reserved3":         (46,  2, "raw"),
    "reserved_3":        (46,  2, "raw"),
    "reserved4":         (46,  2, "raw"),
    "pad":               (46,  2, "raw"),
    "matrix":            (48, 36, "raw"),
    "matrix_structure":  (48, 36, "raw"),
    "width":             (84,  4, ">I"),
    "height":            (88,  4, ">I"),
}

# --- mdhd (version 0) ---
BOX_DEFS["mdhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "creation_time":     (12,  4, ">I"),
    "modification_time": (16,  4, ">I"),
    "timescale":         (20,  4, ">I"),
    "duration":          (24,  4, ">I"),
    "language":          (28,  2, ">H"),
    "pad":               (28,  2, ">H"),
    "pre_defined":       (30,  2, ">H"),
    "reserved1":         (30,  2, "raw"),
}

# --- hdlr ---
BOX_DEFS["hdlr"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "pre_defined":       (12,  4, ">I"),
    "handler_type":      (16,  4, "4s"),
    "reserved":          (20, 12, "raw"),
    "reserved1":         (20,  4, "raw"),
    "reserved2":         (24,  4, "raw"),
    "pad":               (20, 12, "raw"),
    "name":              (32,  4, "4s"),
}

# --- smhd ---
BOX_DEFS["smhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "balance":           (12,  2, ">H"),
    "reserved":          (14,  2, "raw"),
    "reserved1":         (14,  2, "raw"),
    "pad":               (14,  2, "raw"),
}

# --- vmhd ---
BOX_DEFS["vmhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "graphicsmode":      (12,  2, ">H"),
    "graphics_mode":     (12,  2, ">H"),
    "opcolor":           (14,  6, "raw"),
    "pad":               (12,  2, "raw"),
    "reserved2":         (14,  6, "raw"),
}

# --- nmhd ---
BOX_DEFS["nmhd"] = _fullbox_header()

# --- dref ---
BOX_DEFS["dref"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "pad":               (12,  4, "raw"),
}

# --- stsd ---
BOX_DEFS["stsd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "pad":               (12,  4, "raw"),
    "reserved1":         (9,   3, "raw"),
}

# --- stts ---
BOX_DEFS["stts"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "pad":               (12,  4, "raw"),
}

# --- stsc ---
BOX_DEFS["stsc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "first_chunk":       (16,  4, ">I"),
    "samples_per_chunk": (20,  4, ">I"),
    "sample_description_index": (24, 4, ">I"),
}

# --- stsz ---
BOX_DEFS["stsz"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sample_size":       (12,  4, ">I"),
    "sample_count":      (16,  4, ">I"),
    "entry_size":        (20,  4, ">I"),
}

# --- stz2 ---
BOX_DEFS["stz2"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "reserved":          (12,  3, "raw"),
    "field_size":        (15,  1, ">B"),
    "sample_count":      (16,  4, ">I"),
    "entry_size":        (20,  4, ">I"),
}

# --- stco ---
BOX_DEFS["stco"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "chunk_offset":      (16,  4, ">I"),
}

# --- co64 ---
BOX_DEFS["co64"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "chunk_offset":      (16,  8, ">Q"),
}

# --- ctts ---
BOX_DEFS["ctts"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "sample_count":      (16,  4, ">I"),
    "sample_offset":     (20,  4, ">I"),
}

# --- stss ---
BOX_DEFS["stss"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "pad":               (12,  4, "raw"),
}

# --- stsh ---
BOX_DEFS["stsh"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "shadowed_sample_number":  (16, 4, ">I"),
    "shadowed_sample_numbers": (16, 4, ">I"),
    "shadowed_sample_count":   (16, 4, ">I"),
    "sync_sample_number":      (20, 4, ">I"),
}

# --- sdtp ---
BOX_DEFS["sdtp"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sample_dependency_table": (12, 4, "raw"),
}

# --- sbgp ---
BOX_DEFS["sbgp"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "grouping_type":     (12,  4, ">I"),
    "entry_count":       (16,  4, ">I"),
    "sample_count":      (20,  4, ">I"),
    "group_description_index": (24, 4, ">I"),
}

# --- sgpd ---
BOX_DEFS["sgpd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "grouping_type":     (12,  4, ">I"),
    "default_length":    (16,  4, ">I"),
    "entry_count":       (20,  4, ">I"),
    "description_length": (24, 4, ">I"),
    "description":       (28,  4, "raw"),
    "group_description": (28,  4, "raw"),
    "description_count": (20,  4, ">I"),
    "default_sample_description_index": (16, 4, ">I"),
    "default_group_description_index":  (16, 4, ">I"),
}

# --- elst (version 0) ---
BOX_DEFS["elst"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "segment_duration":  (16,  4, ">I"),
    "media_time":        (20,  4, ">i"),
    "media_rate_integer":   (24, 2, ">H"),
    "media_rate_fraction":  (26, 2, ">H"),
}

# --- mehd ---
BOX_DEFS["mehd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "fragment_duration": (12,  4, ">I"),
}

# --- trex ---
BOX_DEFS["trex"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "track_ID":          (12,  4, ">I"),
    "default_sample_description_index": (16, 4, ">I"),
    "default_sample_duration":          (20, 4, ">I"),
    "default_sample_size":              (24, 4, ">I"),
    "default_sample_flags":             (28, 4, ">I"),
}

# --- mfhd ---
BOX_DEFS["mfhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sequence_number":   (12,  4, ">I"),
}

# --- tfhd ---
BOX_DEFS["tfhd"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "track_ID":          (12,  4, ">I"),
    "base_data_offset":         (16, 8, ">Q"),
    "sample_description_index": (24, 4, ">I"),
    "default_sample_duration":  (28, 4, ">I"),
    "default_sample_size":      (32, 4, ">I"),
    "default_sample_flags":     (36, 4, ">I"),
}

# --- trun ---
BOX_DEFS["trun"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sample_count":      (12,  4, ">I"),
    "data_offset":       (16,  4, ">i"),
    "first_sample_flags": (20, 4, ">I"),
    "sample_duration":   (24,  4, ">I"),
    "sample_size":       (28,  4, ">I"),
    "sample_flags":      (32,  4, ">I"),
    "sample_composition_time_offset": (36, 4, ">I"),
}

# --- tfdt ---
BOX_DEFS["tfdt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "base_media_decode_time": (12, 4, ">I"),
}

# --- sidx ---
BOX_DEFS["sidx"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "reference_ID":      (12,  4, ">I"),
    "timescale":         (16,  4, ">I"),
    "earliest_presentation_time": (20, 4, ">I"),
    "first_offset":      (24,  4, ">I"),
    "reserved":          (28,  2, ">H"),
    "reference_count":   (30,  2, ">H"),
    "reference_type":    (32,  4, ">I"),
    "referenced_size":   (32,  4, ">I"),
    "subsegment_duration": (36, 4, ">I"),
    "starts_with_SAP":   (40,  1, ">B"),
    "SAP_type":          (40,  1, ">B"),
    "SAP_delta_time":    (41,  3, "raw"),
}

# --- saiz ---
BOX_DEFS["saiz"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "default_sample_info_size": (12, 1, ">B"),
    "default_sample_size":      (12, 1, ">B"),
    "sample_count":      (13,  4, ">I"),
    "sample_info_size":  (17,  1, ">B"),
    "sample_size":       (17,  1, ">B"),
    "entry_size":        (17,  1, ">B"),
    "aux_info_type":     (12,  4, ">I"),
    "aux_info_type_parameter": (16, 4, ">I"),
}

# --- saio ---
BOX_DEFS["saio"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "offset":            (16,  4, ">I"),
}

# --- pssh ---
BOX_DEFS["pssh"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "system_ID":         (12, 16, "raw"),
    "KID_count":         (28,  4, ">I"),
    "key_ID_count":      (28,  4, ">I"),
    "kid_count":         (28,  4, ">I"),
    "KID":               (32, 16, "raw"),
    "key_IDs":           (32, 16, "raw"),
    "data_size":         (48,  4, ">I"),
    "data_length":       (48,  4, ">I"),
    "data":              (52,  4, "raw"),
}

# --- tenc ---
BOX_DEFS["tenc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "reserved":          (12,  1, "raw"),
    "default_isProtected":       (12, 1, ">B"),
    "default_is_protected":      (12, 1, ">B"),
    "is_encrypted":              (12, 1, ">B"),
    "default_Per_Sample_IV_Size": (13, 1, ">B"),
    "default_per_sample_iv_size": (13, 1, ">B"),
    "iv_size":                    (13, 1, ">B"),
    "default_KID":               (14, 16, "raw"),
    "default_kid":               (14, 16, "raw"),
    "key_id":                    (14, 16, "raw"),
}

# --- senc ---
BOX_DEFS["senc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sample_count":      (12,  4, ">I"),
    "IV_size":           (16,  1, ">B"),
    "IV":                (16, 16, "raw"),
    "subsample_count":   (32,  2, ">H"),
    "clear_bytes":       (34,  2, ">H"),
    "cipher_bytes":      (36,  4, ">I"),
    "encrypted_bytes":   (36,  4, ">I"),
    "bytes_of_clear_data":     (34, 2, ">H"),
    "bytes_of_encrypted_data": (36, 4, ">I"),
    "sample_encryption_entries": (16, 4, "raw"),
    "KID":               (16, 16, "raw"),
    "crypt_byte_block":  (12,  1, ">B"),
    "skip_byte_block":   (13,  1, ">B"),
    "is_encrypted":      (12,  1, ">B"),
}

# --- meta ---
BOX_DEFS["meta"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "handler_type":      (16,  4, "4s"),
    "data":              (12,  4, "raw"),
}

# --- pitm ---
BOX_DEFS["pitm"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "item_ID":           (12,  2, ">H"),
    "item_id":           (12,  2, ">H"),
}

# --- iloc ---
BOX_DEFS["iloc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "offset_size":       (12,  1, ">B"),
    "offsetSize":        (12,  1, ">B"),
    "length_size":       (12,  1, ">B"),
    "lengthSize":        (12,  1, ">B"),
    "base_offset_size":  (13,  1, ">B"),
    "baseOffsetSize":    (13,  1, ">B"),
    "index_size":        (13,  1, ">B"),
    "indexSize":         (13,  1, ">B"),
    "item_count":        (14,  2, ">H"),
    "itemCount":         (14,  2, ">H"),
    "itemSize":          (14,  2, ">H"),
    "itemStartOffset":   (14,  2, ">H"),
    "itemExtent":        (14,  2, ">H"),
}

# --- iinf ---
BOX_DEFS["iinf"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  2, ">H"),
}

# --- infe ---
BOX_DEFS["infe"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "item_ID":           (12,  2, ">H"),
    "item_id":           (12,  2, ">H"),
    "item_protection_index": (14, 2, ">H"),
    "item_name_length":  (16,  1, ">B"),
    "item_name":         (17,  4, "4s"),
    "content_type_length": (21, 1, ">B"),
    "content_type":      (22,  4, "4s"),
    "content_encoding_length": (26, 1, ">B"),
    "content_encoding":  (27,  4, "4s"),
}

# --- iref ---
BOX_DEFS["iref"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
}

# --- ipma ---
BOX_DEFS["ipma"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "item_id":           (16,  2, ">H"),
    "association_count": (18,  1, ">B"),
    "property_index":    (19,  2, ">H"),
}

# --- ipmc ---
BOX_DEFS["ipmc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "creation_time":     (16,  4, ">I"),
    "modification_time": (20,  4, ">I"),
    "item_ID":           (24,  2, ">H"),
    "reserved":          (26,  2, "raw"),
    "ipma_version_compatible_flags": (28, 4, ">I"),
}

# --- iods ---
BOX_DEFS["iods"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "OD_profile_level_indication":      (12, 1, ">B"),
    "OD_profile_level":                 (12, 1, ">B"),
    "scene_profile_level_indication":   (13, 1, ">B"),
    "scene_profile_level":              (13, 1, ">B"),
    "audio_profile_level_indication":   (14, 1, ">B"),
    "audio_profile_level":              (14, 1, ">B"),
    "visual_profile_level_indication":  (15, 1, ">B"),
    "visual_profile_level":             (15, 1, ">B"),
    "graphics_profile_level_indication": (16, 1, ">B"),
    "graphics_profile_level":            (16, 1, ">B"),
    "graphical_profile_level_indication": (16, 1, ">B"),
}

# --- cprt ---
BOX_DEFS["cprt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "language":          (12,  2, ">H"),
    "notice":            (14,  4, "4s"),
    "notice_length":     (14,  1, ">B"),
}

# --- emsg ---
BOX_DEFS["emsg"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "scheme_id_uri":     (12,  4, "4s"),
    "value":             (16,  4, "4s"),
    "timescale":         (20,  4, ">I"),
    "presentation_time_delta": (24, 4, ">I"),
    "presentation_time": (24,  4, ">I"),
    "event_duration":    (28,  4, ">I"),
    "id":                (32,  4, ">I"),
    "message_data":      (36,  4, "raw"),
}

# --- cslg ---
BOX_DEFS["cslg"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "compositionToDTSShift":             (12, 4, ">i"),
    "composition_to_dts_shift":          (12, 4, ">i"),
    "leastDecodeToDisplayDelta":         (16, 4, ">i"),
    "least_decode_to_display_delta":     (16, 4, ">i"),
    "least_decode_to_presentation_delta": (16, 4, ">i"),
    "greatestDecodeToDisplayDelta":      (20, 4, ">i"),
    "greatest_decode_to_display_delta":  (20, 4, ">i"),
    "greatest_decode_to_presentation_delta": (20, 4, ">i"),
    "compositionStartTime":             (24, 4, ">i"),
    "composition_start_time":           (24, 4, ">i"),
    "compositionEndTime":               (28, 4, ">i"),
    "composition_end_time":             (28, 4, ">i"),
}

# --- elng ---
BOX_DEFS["elng"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "extended_language":  (12,  4, "4s"),
    "extendedLanguage":   (12,  4, "4s"),
    "language":           (12,  4, "4s"),
}

# --- kind ---
BOX_DEFS["kind"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "schemeURI":         (12,  4, "4s"),
    "value":             (16,  4, "4s"),
}

# --- pdin ---
BOX_DEFS["pdin"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "rate":              (12,  4, ">I"),
    "initial_delay":     (16,  4, ">I"),
}

# --- prft ---
BOX_DEFS["prft"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "reference_track_ID":  (12, 4, ">I"),
    "reference_track_id":  (12, 4, ">I"),
    "reference_track_id_present": (12, 4, ">I"),
    "ntp_timestamp":       (16, 8, ">Q"),
    "media_time":          (24, 4, ">I"),
}

# --- mfro ---
BOX_DEFS["mfro"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "mfra_size":         (12,  4, ">I"),
    "offset_size":       (12,  4, ">I"),
}

# --- tfra ---
BOX_DEFS["tfra"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "track_ID":          (12,  4, ">I"),
    "reserved":          (16,  4, "raw"),
    "length_size_of_traf_num":   (20, 1, ">B"),
    "length_size_of_Traf_num":   (20, 1, ">B"),
    "length_size_of_trun_num":   (20, 1, ">B"),
    "length_size_of_sample_num": (21, 1, ">B"),
    "number_of_entry":           (22, 4, ">I"),
    "number_of_entries":         (22, 4, ">I"),
    "entry_count":               (22, 4, ">I"),
}

# --- ssix ---
BOX_DEFS["ssix"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "subsegment_count":  (12,  4, ">I"),
    "subsegmentCount":   (12,  4, ">I"),
    "numSegments":       (12,  4, ">I"),
    "numSubSegments":    (12,  4, ">I"),
    "ranges":            (16,  4, "raw"),
    "reserved":          (16,  4, "raw"),
    "substreamCount":    (16,  4, ">I"),
    "substreamInfo":     (20,  4, "raw"),
    "scCount":           (16,  4, ">I"),
    "scMode":            (20,  1, ">B"),
    "higherScPhysical":  (21,  1, ">B"),
}

# --- schm ---
BOX_DEFS["schm"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "scheme_type":       (12,  4, "4s"),
    "scheme_version":    (16,  4, ">I"),
    "scheme_uri":        (20,  4, "4s"),
}

# --- frma ---
BOX_DEFS["frma"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "data_format":       (8,   4, "4s"),
    "format":            (8,   4, "4s"),
}

# --- colr ---
BOX_DEFS["colr"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "colourType":        (8,   4, "4s"),
    "colour_type":       (8,   4, "4s"),
    "colourPrimaries":   (12,  2, ">H"),
    "colour_primaries":  (12,  2, ">H"),
    "primaries_index":   (12,  2, ">H"),
    "transferCharacteristics":  (14, 2, ">H"),
    "transfer_characteristics": (14, 2, ">H"),
    "transfer_function_index":  (14, 2, ">H"),
    "matrixCoefficients":       (16, 2, ">H"),
    "matrix_coefficients":      (16, 2, ">H"),
    "matrix_index":             (16, 2, ">H"),
    "fullRangeFlag":            (18, 1, ">B"),
    "full_range_flag":          (18, 1, ">B"),
}

# --- pasp ---
BOX_DEFS["pasp"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "hSpacing":          (8,   4, ">I"),
    "vSpacing":          (12,  4, ">I"),
}

# --- clap ---
BOX_DEFS["clap"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "cleanApertureWidthN":  (8,  4, ">I"),
    "cleanApertureWidthD":  (12, 4, ">I"),
    "cleanApertureHeightN": (16, 4, ">I"),
    "cleanApertureHeightD": (20, 4, ">I"),
    "horizOffN":            (24, 4, ">I"),
    "horizOffD":            (28, 4, ">I"),
    "vertOffN":             (32, 4, ">I"),
    "vertOffD":             (36, 4, ">I"),
}

# --- btrt ---
BOX_DEFS["btrt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "bufferSizeDB":      (8,   4, ">I"),
    "maxBitrate":        (12,  4, ">I"),
    "avgBitrate":        (16,  4, ">I"),
}

# --- Visual sample entries ---
for box in ["mp4v", "avc1", "avc3", "hvc1", "dvav", "dvh1", "dvhe", "dvvc"]:
    BOX_DEFS[box] = _visual_sample_entry()

# --- encv (encrypted visual) ---
d = _visual_sample_entry()
d.update({
    "dataReferenceIndex":  (14, 2, ">H"),
    "frameCount":          (48, 2, ">H"),
    "dataformat":          (4,  4, "4s"),
    "scheme_type":         (86, 4, "4s"),
    "scheme_version":      (90, 4, ">I"),
    "scheme_uri":          (94, 4, "4s"),
    "video_encoding_version":        (16, 2, ">H"),
    "video_encoding_revision_level": (18, 2, ">H"),
    "video_encoding_vendor":         (20, 4, "raw"),
    "video_temporal_quality":        (24, 4, ">I"),
    "video_spatial_quality":         (28, 4, ">I"),
    "video_width":                   (32, 2, ">H"),
    "video_height":                  (34, 2, ">H"),
    "video_horizontal_resolution":   (36, 4, ">I"),
    "video_vertical_resolution":     (40, 4, ">I"),
    "video_data_size":               (44, 4, ">I"),
    "video_frame_count":             (48, 2, ">H"),
    "video_compressor_name":         (50, 32, "raw"),
    "video_depth":                   (82, 2, ">H"),
    "video_color_table_id":          (84, 2, ">H"),
    "flags":                         (9,  3, "raw"),
})
BOX_DEFS["encv"] = d

# --- Audio sample entries ---
for box in ["mp4a", "dtsc", "dtse", "dtsh", "dtsl"]:
    BOX_DEFS[box] = _audio_sample_entry()

# --- ac-3 ---
d = _audio_sample_entry()
d.update({
    "fscod":          (36, 1, ">B"),
    "bsid":           (37, 1, ">B"),
    "bsmod":          (38, 1, ">B"),
    "acmod":          (39, 1, ">B"),
    "lfeon":          (40, 1, ">B"),
    "bit_rate_code":  (41, 1, ">B"),
    "bitrate":        (41, 1, ">B"),
})
BOX_DEFS["ac-3"] = d

# --- ec-3 ---
d = _audio_sample_entry()
d.update({
    "fscod":          (36, 1, ">B"),
    "bsid":           (37, 1, ">B"),
    "bsmod":          (38, 1, ">B"),
    "acmod":          (39, 1, ">B"),
    "lfeon":          (40, 1, ">B"),
    "num_dep_sub":    (41, 1, ">B"),
    "chan_loc":        (42, 2, ">H"),
    "bitrate":        (44, 4, ">I"),
})
BOX_DEFS["ec-3"] = d

# --- alaw / ulaw ---
for box in ["alaw", "ulaw"]:
    d = _audio_sample_entry()
    d.update({
        "dataReferenceIndex": (14, 2, ">H"),
        "endianness":         (36, 2, ">H"),
    })
    BOX_DEFS[box] = d

# --- enca (encrypted audio) ---
d = _audio_sample_entry()
d.update({
    "dataReferenceIndex":  (14, 2, ">H"),
    "dataformat":          (4,  4, "4s"),
    "flags":               (9,  3, "raw"),
    "scheme_type":         (36, 4, "4s"),
    "scheme_version":      (40, 4, ">I"),
    "scheme_uri":          (44, 4, "4s"),
    "audio_encoding_version":        (16, 2, ">H"),
    "audio_encoding_revision_level": (18, 2, ">H"),
    "audio_encoding_vendor":         (20, 4, "raw"),
    "audio_number_of_channels":      (24, 2, ">H"),
    "audio_sample_size":             (26, 2, ">H"),
    "audio_compression_id":          (28, 2, ">H"),
    "audio_packet_size":             (30, 2, ">H"),
    "audio_sample_rate":             (32, 4, ">I"),
})
BOX_DEFS["enca"] = d

# --- Opus ---
d = _audio_sample_entry()
d.update({
    "preSkip":              (36, 2, ">H"),
    "pre_skip":             (36, 2, ">H"),
    "inputSampleRate":      (38, 4, ">I"),
    "input_sample_rate":    (38, 4, ">I"),
    "outputGain":           (42, 2, ">H"),
    "output_gain":          (42, 2, ">H"),
    "channelMappingFamily": (44, 1, ">B"),
    "outputChannelCount":   (45, 1, ">B"),
    "numOutputs":           (45, 1, ">B"),
    "channel_map":          (46, 4, "raw"),
    "flags":                (9,  3, "raw"),
})
BOX_DEFS["Opus"] = d

# --- alac ---
BOX_DEFS["alac"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "maxSamplePerFrame": (12,  4, ">I"),
    "frameLength":       (12,  4, ">I"),
    "sampleSize":        (16,  1, ">B"),
    "bitDepth":          (16,  1, ">B"),
    "historyMult":       (17,  1, ">B"),
    "initialHistory":    (18,  1, ">B"),
    "kModifier":         (19,  1, ">B"),
    "channels":          (20,  1, ">B"),
    "maxCodedFrameSize": (21,  4, ">I"),
    "bitRate":           (25,  4, ">I"),
    "sampleRate":        (29,  4, ">I"),
    "alacSpecificInfo":  (12, 24, "raw"),
    "config":            (12, 24, "raw"),
}

# --- flac / dfLa ---
for box in ["flac", "dfLa"]:
    d = _audio_sample_entry()
    d.update({
        "dataReferenceIndex": (14, 2, ">H"),
        "bitsPerSample":      (36, 1, ">B"),
        "samplesPerPacket":   (37, 4, ">I"),
        "samples":            (37, 4, ">I"),
        "nativeLength":       (41, 4, ">I"),
        "nativeSpeakerAlwaysCentralized": (45, 1, ">B"),
        "nativeMajorMinor":   (46, 2, ">H"),
        "unknown_fields":     (36, 4, "raw"),
        "flags":              (9,  3, "raw"),
    })
    BOX_DEFS[box] = d

# --- ac-4 ---
d = _audio_sample_entry()
d.update({
    "flags":                  (9,  3, "raw"),
    "dataReferenceIndex":     (14, 2, ">H"),
    "preDefined":             (28, 2, ">H"),
    "streamType":             (36, 1, ">B"),
    "bufferSizeDB":           (37, 4, ">I"),
    "maxBitrate":             (41, 4, ">I"),
    "avgBitrate":             (45, 4, ">I"),
    "ac4_dsi_version":        (49, 1, ">B"),
    "ac4_bitrate_indicator":  (50, 1, ">B"),
    "ac4_bitstream_version":  (51, 1, ">B"),
    "streamId":               (52, 2, ">H"),
    "grade":                  (54, 1, ">B"),
    "frameRate":              (55, 1, ">B"),
    "objectCount":            (56, 1, ">B"),
})
BOX_DEFS["ac-4"] = d

# --- avcC ---
BOX_DEFS["avcC"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "configurationVersion":      (8,  1, ">B"),
    "AVCProfileIndication":      (9,  1, ">B"),
    "profile_compatibility":     (10, 1, ">B"),
    "AVCLevelIndication":        (11, 1, ">B"),
    "lengthSizeMinusOne":        (12, 1, ">B"),
    "numOfSequenceParameterSets": (13, 1, ">B"),
    "sequenceParameterSetLength": (14, 2, ">H"),
    "sequenceParameterSetNALUnit": (16, 4, "raw"),
    "sequenceParameterSets":      (16, 4, "raw"),
    "sequenceParameterSetNALUnits": (16, 4, "raw"),
    "numOfPictureParameterSets":  (20, 1, ">B"),
    "pictureParameterSetLength":  (21, 2, ">H"),
    "pictureParameterSetNALUnit": (23, 4, "raw"),
    "pictureParameterSets":       (23, 4, "raw"),
    "pictureParameterSetNALUnits": (23, 4, "raw"),
}

# --- avc4 (similar to avcC but as full box variant) ---
d = dict(BOX_DEFS["avcC"])
d.update({
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "configVersion":     (8,   1, ">B"),
    "profileIndication": (9,   1, ">B"),
    "profileCompatibility": (10, 1, ">B"),
    "levelIndication":   (11,  1, ">B"),
    "reserved":          (12,  1, "raw"),
    "reserved1":         (12,  1, "raw"),
    "reserved2":         (12,  1, "raw"),
    "naluLengthSize":    (12,  1, ">B"),
    "numOfArrays":       (13,  1, ">B"),
    "arrayCompleteness": (14,  1, ">B"),
    "nalUnitType":       (15,  1, ">B"),
    "numberOfSequenceParameterSets": (13, 1, ">B"),
    "numberOfPictureParameterSets":  (20, 1, ">B"),
    "depthFlags":        (12,  1, ">B"),
    "chromaFormat":      (12,  1, ">B"),
})
BOX_DEFS["avc4"] = d

# --- hvcC ---
BOX_DEFS["hvcC"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "configurationVersion":  (8,  1, ">B"),
    "general_profile_space":  (9, 1, ">B"),
    "general_tier_flag":      (9, 1, ">B"),
    "general_profile_idc":    (9, 1, ">B"),
    "general_profile_compatibility_flags": (10, 4, ">I"),
    "general_constraint_indicator_flags":  (14, 6, "raw"),
    "general_level_idc":      (20, 1, ">B"),
    "min_spatial_segmentation_idc": (21, 2, ">H"),
    "parallelismType":        (23, 1, ">B"),
    "chromaFormat":           (24, 1, ">B"),
    "bitDepthLumaMinus8":     (25, 1, ">B"),
    "bitDepthChromaMinus8":   (26, 1, ">B"),
    "avgFrameRate":           (27, 2, ">H"),
    "constantFrameRate":      (29, 1, ">B"),
    "numTemporalLayers":      (29, 1, ">B"),
    "temporalIdNested":       (29, 1, ">B"),
    "lengthSizeMinusOne":     (30, 1, ">B"),
    "numOfArrays":            (31, 1, ">B"),
    "reserved":               (21, 2, "raw"),
}

# --- hev1 (same layout issues as hvcC config) ---
BOX_DEFS["hev1"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "configurationVersion":               (12, 1, ">B"),
    "general_profile_space":              (13, 1, ">B"),
    "general_tier_flag":                  (13, 1, ">B"),
    "general_profile_idc":                (13, 1, ">B"),
    "general_profile_compatibility_flags": (14, 4, ">I"),
    "general_constraint_indicator_flags":  (18, 6, "raw"),
    "general_level_idc":                  (24, 1, ">B"),
}

# --- av1C ---
BOX_DEFS["av1C"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "marker":            (8,   1, ">B"),
    "marker_bit":        (8,   1, ">B"),
    "version":           (8,   1, ">B"),
    "seq_profile":       (9,   1, ">B"),
    "seqProfile":        (9,   1, ">B"),
    "seq_level_idx_0":   (10,  1, ">B"),
    "seqLevelIdx0":      (10,  1, ">B"),
    "seq_tier_0":        (11,  1, ">B"),
    "seqTier0":          (11,  1, ">B"),
    "high_bitdepth":     (11,  1, ">B"),
    "highBitdepth":      (11,  1, ">B"),
    "twelve_bit":        (11,  1, ">B"),
    "twelveBit":         (11,  1, ">B"),
    "monochrome":        (12,  1, ">B"),
    "chroma_subsampling_x": (12, 1, ">B"),
    "chromaSubsamplingX":   (12, 1, ">B"),
    "chroma_subsampling_y": (12, 1, ">B"),
    "chromaSubsamplingY":   (12, 1, ">B"),
    "chroma_sample_position": (13, 1, ">B"),
    "chromaSamplePosition":   (13, 1, ">B"),
    "initial_presentation_delay_present": (13, 1, ">B"),
    "initialPresentationDelayPresent":    (13, 1, ">B"),
    "initial_presentation_delay_minus_one": (14, 1, ">B"),
    "initialPresentationDelayMinusOne":     (14, 1, ">B"),
    "reserved":          (14, 1, "raw"),
}

# --- esds ---
BOX_DEFS["esds"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "ES_Descriptor":     (12,  4, "raw"),
    "ESDescriptor":      (12,  4, "raw"),
    "ES_ID":             (15,  2, ">H"),
    "streamDependenceFlag": (17, 1, ">B"),
    "URL_Flag":          (17,  1, ">B"),
    "OCRstreamFlag":     (17,  1, ">B"),
    "streamPriority":    (17,  1, ">B"),
}

# --- dvcC ---
BOX_DEFS["dvcC"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "codecConfigurationVersion": (12, 1, ">B"),
    "dvVersion":         (12,  1, ">B"),
    "codecProfile":      (13,  1, ">B"),
    "dvProfile":         (13,  1, ">B"),
    "profile":           (13,  1, ">B"),
    "codecLevel":        (14,  1, ">B"),
    "dvLevel":           (14,  1, ">B"),
    "level":             (14,  1, ">B"),
    "rpuPresentFlag":    (15,  1, ">B"),
    "elPresentFlag":     (15,  1, ">B"),
    "blPresentFlag":     (15,  1, ">B"),
    "dvBlSignalCompatibilityId": (16, 1, ">B"),
    "bitDepth":          (17,  1, ">B"),
    "chromaSubsampling": (18,  1, ">B"),
    "colorPrimaries":    (19,  1, ">B"),
    "transferCharacteristics": (20, 1, ">B"),
    "matrixCoefficients": (21, 1, ">B"),
    "videoFullRangeFlag": (22, 1, ">B"),
    "aviVersion":        (12,  1, ">B"),
    "preferredUUID":     (23, 16, "raw"),
    "manufacturerCode":  (39,  4, "raw"),
    "temporalQuality":   (43,  4, ">I"),
    "spatialQuality":    (47,  4, ">I"),
    "width":             (51,  2, ">H"),
    "height":            (53,  2, ">H"),
    "horizontalResolution": (55, 4, ">I"),
    "verticalResolution":   (59, 4, ">I"),
    "compressorName":    (63, 32, "raw"),
    "depth":             (95,  2, ">H"),
    "colorTableID":      (97,  2, ">H"),
}

# --- avcn ---
BOX_DEFS["avcn"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "parameterSets":     (12,  4, "raw"),
}

# --- avss ---
BOX_DEFS["avss"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "subSampleInformation": (12, 4, "raw"),
}

# --- box ---
BOX_DEFS["box"] = _box_header()

# --- bxml / xml ---
for box in ["bxml", "xml"]:
    BOX_DEFS[box] = {
        "size":              (0,   4, ">I"),
        "type":              (4,   4, "4s"),
        "box_type":          (4,   4, "4s"),
        "version":           (8,   1, ">B"),
        "flags":             (9,   3, "raw"),
        "namespace":         (12,  4, "4s"),
        "default_namespace": (12,  4, "4s"),
        "schema_location":   (16,  4, "4s"),
        "data":              (20,  4, "raw"),
        "binary_xml_data":   (20,  4, "raw"),
        "xml_data":          (20,  4, "raw"),
        "entry_count":       (12,  4, ">I"),
        "content_offset":    (16,  4, ">I"),
    }

# --- ttml ---
BOX_DEFS["ttml"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "namespace":         (12,  4, "4s"),
    "default_namespace": (12,  4, "4s"),
    "namespace_length":  (12,  2, ">H"),
    "schema_location":   (16,  4, "4s"),
    "schema_location_length": (16, 2, ">H"),
    "ttml_data":         (20,  4, "raw"),
    "data":              (20,  4, "raw"),
}

# --- cdsc ---
BOX_DEFS["cdsc"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "entry_version":     (16,  1, ">B"),
    "entry_flags":       (17,  3, "raw"),
    "creationTime":      (20,  4, ">I"),
    "modificationTime":  (24,  4, ">I"),
    "trackID":           (28,  4, ">I"),
    "sizeID":            (32,  4, ">I"),
}

# --- trep ---
BOX_DEFS["trep"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "trackID":           (12,  4, ">I"),
    "track_ID":          (12,  4, ">I"),
    "playbackRateNumerator":   (16, 2, ">H"),
    "playbackRateDenominator": (18, 2, ">H"),
}

# --- tref ---
BOX_DEFS["tref"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "reference_type":    (8,   4, "4s"),
    "track_id":          (12,  4, ">I"),
    "entry_count":       (12,  4, ">I"),
}

# --- url ---
BOX_DEFS["url"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "location":          (12,  4, "4s"),
    "name":              (12,  4, "4s"),
    "location_length":   (12,  2, ">H"),
}

# --- urn ---
BOX_DEFS["urn"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "name":              (12,  4, "4s"),
    "location":          (16,  4, "4s"),
    "location_length":   (16,  2, ">H"),
}

# --- uuid ---
BOX_DEFS["uuid"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "user_type":         (8,  16, "raw"),
    "usertype":          (8,  16, "raw"),
    "data":              (24,  4, "raw"),
}

# --- tx3g ---
BOX_DEFS["tx3g"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "data_reference_index": (12, 2, ">H"),
    "display_flags":     (14,  4, ">I"),
    "horizontal_justification": (18, 1, ">B"),
    "vertical_justification":   (19, 1, ">B"),
    "background_color_rgba":    (20, 4, "raw"),
    "background_color":         (20, 4, "raw"),
    "default_text_box":         (24, 8, "raw"),
    "box_record":               (24, 8, "raw"),
    "style_record":             (32, 12, "raw"),
    "font_table":               (44, 4, "raw"),
    "data":                     (12, 4, "raw"),
    "line_placement_flags":     (14, 4, ">I"),
    "navbar_center_x":          (18, 2, ">H"),
}

# --- stpp ---
BOX_DEFS["stpp"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "namespace":         (8,   4, "4s"),
    "schema_location":   (12,  4, "4s"),
    "auxiliary_mime_types": (16, 4, "4s"),
    "auxiliary_mime_type":  (16, 4, "4s"),
}

# --- sbtl ---
BOX_DEFS["sbtl"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "cue_text":          (12,  4, "4s"),
    "layer":             (16,  2, ">H"),
    "alternate_group":   (18,  2, ">H"),
    "volume":            (20,  2, ">H"),
    "reserved":          (22,  2, "raw"),
    "width":             (24,  4, ">I"),
    "height":            (28,  4, ">I"),
    "timescale":         (32,  4, ">I"),
    "language_code":     (36,  2, ">H"),
}

# --- stxt ---
BOX_DEFS["stxt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "cue_text":          (12,  4, "4s"),
    "layer":             (16,  2, ">H"),
    "alternate_group":   (18,  2, ">H"),
    "volume":            (20,  2, ">H"),
    "reserved":          (22,  2, "raw"),
    "width":             (24,  4, ">I"),
    "height":            (28,  4, ">I"),
    "samplerate":        (32,  4, ">I"),
    "bitmap":            (36,  4, "raw"),
    "private_data":      (40,  4, "raw"),
}

# --- wvtt ---
BOX_DEFS["wvtt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "cue_text":          (12,  4, "4s"),
    "layer":             (16,  2, ">H"),
    "alternate_group":   (18,  2, ">H"),
    "volume":            (20,  2, ">H"),
    "reserved":          (22,  2, "raw"),
    "width":             (24,  4, ">I"),
    "height":            (28,  4, ">I"),
    "cueSourceID":       (32,  4, ">I"),
    "timescale":         (36,  4, ">I"),
    "maximumTextCompositionTime": (40, 4, ">I"),
}

# --- wave ---
BOX_DEFS["wave"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "soundFormat":       (12,  4, "4s"),
}

# --- drms ---
BOX_DEFS["drms"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "dataformat":        (12,  4, "4s"),
    "data_format":       (12,  4, "4s"),
    "reserved":          (16,  6, "raw"),
    "data_reference_index": (22, 2, ">H"),
    "encryption_version":   (24, 2, ">H"),
    "encryption_flags":     (26, 2, ">H"),
    "encryption_key_id":    (28, 4, "raw"),
    "key_indication":       (28, 4, "raw"),
    "iv_size":              (32, 1, ">B"),
}

# --- mp4s ---
BOX_DEFS["mp4s"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "reserved":          (8,   6, "raw"),
    "reserved1":         (8,   6, "raw"),
    "data_reference_index": (14, 2, ">H"),
    "vendor":            (16,  4, "raw"),
    "level":             (20,  1, ">B"),
    "profile":           (21,  1, ">B"),
}

# --- dac3 / dec3 ---
for box in ["dac3", "dec3"]:
    BOX_DEFS[box] = {
        "size":    (0, 4, ">I"),
        "type":    (4, 4, "4s"),
        "version": (8, 1, ">B"),
        "flags":   (9, 3, "raw"),
        "data":    (12, 4, "raw"),
    }

# --- dOps ---
BOX_DEFS["dOps"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "decoderVersion":    (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "vendor":            (9,   4, "raw"),
    "decoderVersionMinor": (13, 1, ">B"),
    "decoderSpecificInfo": (14, 4, "raw"),
    "numOperationalPoints": (14, 1, ">B"),
    "outputChannelCount":   (15, 1, ">B"),
}

# --- fiin ---
BOX_DEFS["fiin"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  4, ">I"),
    "info_entry_count":  (12,  4, ">I"),
    "item_id":           (16,  2, ">H"),
    "itemID":            (16,  2, ">H"),
    "item_protection_index": (18, 2, ">H"),
    "item_type":         (20,  4, "4s"),
    "item_name":         (24,  4, "4s"),
    "edataDesignator":   (28,  4, "raw"),
}

# --- fire ---
BOX_DEFS["fire"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "file_id":           (12,  4, ">I"),
    "itemID":            (12,  4, ">I"),
    "media_data_size":   (16,  4, ">I"),
}

# --- alis ---
BOX_DEFS["alis"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "aliasInfo":         (12,  4, "raw"),
}

# --- alst ---
BOX_DEFS["alst"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "fragment_count":    (12,  4, ">I"),
    "fragmentCount":     (12,  4, ">I"),
    "fragment_duration": (16,  4, ">I"),
    "fragmentInfo":      (16,  4, "raw"),
    "fragment_start_time": (20, 4, ">I"),
    "default_roll_distance": (24, 2, ">H"),
    "first_output_sample":   (26, 4, ">I"),
    "group_ID":              (30, 4, ">I"),
    "num_switches":          (34, 2, ">H"),
    "firstLiveIndex":        (36, 4, ">I"),
    "reserved":              (40, 4, "raw"),
}

# --- afra ---
BOX_DEFS["afra"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "timeScale":         (12,  4, ">I"),
    "time_scale":        (12,  4, ">I"),
    "entryCount":        (16,  4, ">I"),
    "globalEntryFlag":   (20,  1, ">B"),
    "localEntryFlag":    (21,  1, ">B"),
    "long_IDs":          (22,  1, ">B"),
    "use_offset":        (23,  1, ">B"),
    "time":              (24,  4, ">I"),
    "segment":           (28,  4, ">I"),
    "fragment":          (32,  4, ">I"),
    "first_fragment":    (32,  4, ">I"),
    "afraOffset":        (36,  4, ">I"),
    "entries":           (24,  4, "raw"),
    "fragments":         (32,  4, "raw"),
    "numTimingEntries":  (16,  4, ">I"),
    "numOffsetEntries":  (20,  4, ">I"),
    "reserved":          (24,  4, "raw"),
}

# --- pvc1 ---
BOX_DEFS["pvc1"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "profile_level_indication": (12, 1, ">B"),
    "profile":           (12,  1, ">B"),
    "compatibility_flags": (13, 4, ">I"),
    "compatibility":     (13,  4, ">I"),
    "level":             (17,  1, ">B"),
    "bit_depth_luma":    (18,  1, ">B"),
    "bit_depth_chroma":  (19,  1, ">B"),
    "flatbins":          (20,  1, ">B"),
    "options":           (21,  1, ">B"),
}

# --- dnld ---
BOX_DEFS["dnld"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "download_id":       (12,  4, ">I"),
    "data_reference_index": (12, 2, ">H"),
    "priority":          (16,  2, ">H"),
    "url":               (18,  4, "4s"),
    "url_length":        (18,  2, ">H"),
    "scheme_length":     (22,  2, ">H"),
    "scheme_data":       (24,  4, "raw"),
}

# --- eqiv ---
BOX_DEFS["eqiv"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "equivalenceObject": (12,  4, "raw"),
    "equivalenceCount":  (12,  4, ">I"),
    "equivalences":      (16,  4, "raw"),
    "track_ID":          (12,  4, ">I"),
    "equivalent_url":    (16,  4, "4s"),
    "segmentDuration":   (20,  4, ">I"),
    "mediaTimeScale":    (24,  4, ">I"),
}

# --- fpar ---
BOX_DEFS["fpar"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "fieldCount":        (8,   2, ">H"),
    "field1":            (10,  4, "raw"),
    "field2":            (14,  4, "raw"),
}

# --- fpat ---
BOX_DEFS["fpat"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "pattern_count":     (12,  4, ">I"),
    "entry_count":       (12,  4, ">I"),
    "patterns":          (16,  4, "raw"),
    "pattern_entries":   (16,  4, "raw"),
    "base_track_index":  (20,  4, ">I"),
    "sample_table_box_index": (24, 4, ">I"),
}

# --- fprt ---
BOX_DEFS["fprt"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "priority_count":    (12,  4, ">I"),
    "entry_count":       (12,  4, ">I"),
    "pattern_count":     (12,  4, ">I"),
    "priorities":        (16,  4, "raw"),
    "pattern_entries":   (16,  4, "raw"),
    "base_track_index":  (20,  4, ">I"),
    "reference_track_index": (24, 4, ">I"),
    "track_group_id":    (28,  4, ">I"),
    "function_type":     (32,  1, ">B"),
    "interpolation_flags": (33, 1, ">B"),
}

# --- ftab ---
BOX_DEFS["ftab"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "entry_count":       (12,  2, ">H"),
    "num_fonts":         (12,  2, ">H"),
    "font_entries":      (14,  4, "raw"),
    "base_track_index":  (14,  4, ">I"),
    "sample_table_box_count": (18, 4, ">I"),
    "function_class":    (22,  1, ">B"),
    "version_field":     (23,  1, ">B"),
    "nb_of_points":      (24,  2, ">H"),
}

# --- ftap ---
BOX_DEFS["ftap"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "tap_count":         (12,  4, ">I"),
    "entry_count":       (12,  4, ">I"),
    "taps":              (16,  4, "raw"),
    "tap_entries":       (16,  4, "raw"),
    "base_track_index":  (20,  4, ">I"),
    "attribute":         (24,  4, ">I"),
    "factors":           (28,  4, "raw"),
    "nb_vectors":        (32,  2, ">H"),
    "default_delta":     (34,  4, ">I"),
}

# --- mvex ---
BOX_DEFS["mvex"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "data":              (12,  4, "raw"),
}

# --- mere ---
BOX_DEFS["mere"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "group_id":          (12,  4, ">I"),
    "num_references":    (16,  4, ">I"),
    "data":              (20,  4, "raw"),
}

# --- meco ---
BOX_DEFS["meco"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
}

# --- ihdr ---
BOX_DEFS["ihdr"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "width":             (12,  4, ">I"),
    "height":            (16,  4, ">I"),
    "bitDepth":          (20,  1, ">B"),
    "compressionType":   (21,  1, ">B"),
    "colorspace":        (22,  1, ">B"),
    "colorspaceUnknown": (23,  1, ">B"),
    "colorspaceUnknownFlag": (23, 1, ">B"),
    "intellectualProperty":     (24, 1, ">B"),
    "intellectualPropertyFlag": (24, 1, ">B"),
    "horizresolution":   (25,  4, ">I"),
    "vertresolution":    (29,  4, ">I"),
    "frame_count":       (33,  2, ">H"),
    "compressorname":    (35, 32, "raw"),
    "depth":             (67,  2, ">H"),
    "colortable_id":     (69,  2, ">H"),
}

# --- ihra ---
BOX_DEFS["ihra"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "width":             (12,  4, ">I"),
    "height":            (16,  4, ">I"),
    "bitDepth":          (20,  1, ">B"),
    "compressionType":   (21,  1, ">B"),
    "colorspace":        (22,  1, ">B"),
    "reference_flags":   (23,  2, ">H"),
    "reference_id":      (25,  4, ">I"),
    "layer_priority":    (29,  1, ">B"),
    "discard_priority":  (30,  1, ">B"),
    "reserved":          (31,  4, "raw"),
    "attribute":         (35,  4, ">I"),
}

# --- lhdr ---
BOX_DEFS["lhdr"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "timescale":         (12,  4, ">I"),
    "duration":          (16,  4, ">I"),
    "width":             (20,  2, ">H"),
    "height":            (22,  2, ">H"),
    "layer_width":       (24,  2, ">H"),
    "layer_height":      (26,  2, ">H"),
    "horiz_resolution":  (28,  4, ">I"),
    "vert_resolution":   (32,  4, ">I"),
    "layer_id":          (36,  2, ">H"),
    "alternativeRowCount": (38, 2, ">H"),
    "firstCodingPasses": (40,  2, ">H"),
    "exampleTransitionPoint": (42, 4, ">I"),
    "compliantTransitionType": (46, 1, ">B"),
}

# --- paen ---
BOX_DEFS["paen"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "partition_entry_count": (12, 4, ">I"),
    "span_count":        (16,  4, ">I"),
    "partitioningScheme": (20, 4, "4s"),
}

# --- mmpu ---
BOX_DEFS["mmpu"] = {
    "size":              (0,   4, ">I"),
    "type":              (4,   4, "4s"),
    "version":           (8,   1, ">B"),
    "flags":             (9,   3, "raw"),
    "sequence_number":   (12,  4, ">I"),
    "sequenceNumber":    (12,  4, ">I"),
    "time_scale":        (16,  4, ">I"),
    "duration":          (20,  4, ">I"),
    "baseProfile":       (24,  1, ">B"),
    "profileCompatibility": (25, 4, ">I"),
    "levelIndication":   (29,  1, ">B"),
    "layerID":           (30,  1, ">B"),
    "fragmentAbsoluteDecodeTime": (31, 8, ">Q"),
    "media_data_size":   (39,  4, ">I"),
    "mediaDataLength":   (39,  4, ">I"),
    "media_data_hash":   (43,  4, "raw"),
    "packetIdentifier":  (47,  4, ">I"),
}


# ============================================================
# Script template
# ============================================================
SCRIPT_TEMPLATE = '''\
import struct
import os


def {func_name}(fp, values, fields, debug=False):
    """Edit {box_name} box fields in an MP4 file.

    Args:
        fp: Path to the MP4 file
        values: List of values to set, corresponding to fields
        fields: List of field names to modify
        debug: If True, print debug information
    """
    FIELD_MAP = {field_map_str}

    try:
        with open(fp, 'r+b') as f:
            data = f.read()
            tag = {tag_repr}
            pos = data.find(tag)
            if pos == -1:
                if debug:
                    print("[DEBUG] {box_name} box not found")
                return
            box_start = pos - 4

            for i, field in enumerate(fields):
                if field not in FIELD_MAP:
                    if debug:
                        print(f"[DEBUG] {box_name}.{{field}}: unknown field, skipping")
                    continue

                offset, size, fmt = FIELD_MAP[field]
                abs_pos = box_start + offset
                value = values[i] if i < len(values) else None
                if value is None:
                    continue

                # Read old value
                try:
                    if fmt in ("4s", "str"):
                        old_val = data[abs_pos:abs_pos+size]
                        old_val = old_val.decode('utf-8', errors='replace')
                    elif fmt == "raw":
                        old_val = data[abs_pos:abs_pos+size].hex()
                    else:
                        old_val = struct.unpack_from(fmt, data, abs_pos)[0]
                except Exception:
                    old_val = "N/A"

                if debug:
                    print(f"[DEBUG] {box_name}.{{field}} before: {{old_val}}")

                # Write new value
                f.seek(abs_pos)
                if fmt in ("4s", "str"):
                    if isinstance(value, str):
                        encoded = value.encode('utf-8')
                    else:
                        encoded = bytes(value)
                    f.write(encoded[:size].ljust(size, b'\\\\x00'))
                elif fmt == "raw":
                    if isinstance(value, bytes):
                        f.write(value[:size].ljust(size, b'\\\\x00'))
                    elif isinstance(value, int):
                        f.write(value.to_bytes(size, 'big'))
                    else:
                        f.write(bytes(value)[:size].ljust(size, b'\\\\x00'))
                else:
                    f.write(struct.pack(fmt, value))

                if debug:
                    print(f"[DEBUG] {box_name}.{{field}} after: {{value}}")
    except Exception as e:
        if debug:
            print(f"[DEBUG] Error: {{e}}")
'''


def sanitize_func_name(name):
    """Convert box name to valid Python function name."""
    return name.replace('-', '_').replace('.', '_')


def format_field_map(field_map):
    """Format field map dict as a Python dict literal string."""
    lines = []
    lines.append("{")
    for name, (offset, size, fmt) in sorted(field_map.items()):
        lines.append(f'        "{name}": ({offset}, {size}, "{fmt}"),')
    lines.append("    }")
    return "\n".join(lines)


def get_tag(box_name):
    """Get the 4-byte tag for a box type."""
    if box_name in TAG_MAP:
        return TAG_MAP[box_name]
    tag = box_name.encode('utf-8')
    if len(tag) < 4:
        tag = tag + b'\x00' * (4 - len(tag))
    return tag[:4]


def generate_editor(box_name, json_fields, output_dir):
    """Generate an editor script for a box type."""
    # Get field definitions
    if box_name in BOX_DEFS:
        field_map = dict(BOX_DEFS[box_name])
    else:
        # Fallback: generate a basic field map with header fields
        field_map = dict(_box_header())

    # Ensure all JSON fields are covered (add missing ones with best-guess offsets)
    base_offset = 8  # after size + type
    if "version" in field_map or "version" in json_fields:
        base_offset = 12  # after full box header

    for field_name in json_fields:
        if field_name not in field_map:
            # Unknown field: map to a reasonable position
            field_map[field_name] = (base_offset, 4, "raw")

    func_name = sanitize_func_name(box_name)
    tag = get_tag(box_name)

    script_content = SCRIPT_TEMPLATE.format(
        func_name=func_name,
        box_name=box_name,
        field_map_str=format_field_map(field_map),
        tag_repr=repr(tag),
    )

    # Fix double-escaped backslashes in the template
    script_content = script_content.replace('\\\\x00', '\\x00')

    # Create directory
    box_dir = os.path.join(output_dir, box_name)
    os.makedirs(box_dir, exist_ok=True)

    # Write script
    # Use sanitized name for the .py file if box name has special chars
    py_filename = f"{func_name}.py"
    script_path = os.path.join(box_dir, py_filename)
    with open(script_path, 'w') as f:
        f.write(script_content)

    return script_path


def main():
    # Load JSON
    with open(JSON_PATH) as f:
        data = json.load(f)

    generated = 0
    skipped = 0

    for box_name, fields_dict in sorted(data.items()):
        if not fields_dict:
            skipped += 1
            continue

        json_fields = list(fields_dict.keys())
        path = generate_editor(box_name, json_fields, OUTPUT_DIR)
        generated += 1

    print(f"Generated: {generated} editors")
    print(f"Skipped (empty): {skipped}")
    print(f"Output directory: {OUTPUT_DIR}")


if __name__ == "__main__":
    main()
