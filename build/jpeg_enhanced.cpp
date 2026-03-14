#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"


class ubyte_class {
	int small;
	std::vector<ubyte> known_values;
	ubyte value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(ubyte);
	ubyte operator () () { return value; }
	ubyte_class(int small, std::vector<ubyte> known_values = {}) : small(small), known_values(known_values) {}

	ubyte generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(ubyte), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(ubyte), 0, known_values);
		}
		return value;
	}

	ubyte generate(std::vector<ubyte> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(ubyte), 0, possible_values);
		return value;
	}
};



class JPEG_SOI {
	std::vector<JPEG_SOI*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_SOI& operator () () { return *instances.back(); }
	JPEG_SOI& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_SOI(std::vector<JPEG_SOI*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_SOI() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_SOI* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_SOI* generate();
};

int JPEG_SOI::_parent_id = 0;
int JPEG_SOI::_index_start = 0;



class uint16_class {
	int small;
	std::vector<uint16> known_values;
	uint16 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(uint16);
	uint16 operator () () { return value; }
	uint16_class(int small, std::vector<uint16> known_values = {}) : small(small), known_values(known_values) {}

	uint16 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(uint16), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(uint16), 0, known_values);
		}
		return value;
	}

	uint16 generate(std::vector<uint16> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(uint16), 0, possible_values);
		return value;
	}
};



class char_class {
	int small;
	std::vector<char> known_values;
	char value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(char);
	char operator () () { return value; }
	char_class(int small, std::vector<char> known_values = {}) : small(small), known_values(known_values) {}

	char generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(char), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(char), 0, known_values);
		}
		return value;
	}

	char generate(std::vector<char> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(char), 0, possible_values);
		return value;
	}
};



class char_array_class {
	char_class& element;
	std::vector<std::string> known_values;
	std::unordered_map<int, std::vector<char>> element_known_values;
	std::string value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::string& operator () () { return value; }
	char operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	char_array_class(char_class& element, std::unordered_map<int, std::vector<char>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}
	char_array_class(char_class& element, std::vector<std::string> known_values)
		: element(element), known_values(known_values) {}

	std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
		check_array_length(size);
		_startof = FTell();
		value = "";
		if (possible_values.size()) {
			value = file_acc.file_string(possible_values);
			assert(value.length() == size);
			_sizeof = size;
			return value;
		}
		if (known_values.size()) {
			value = file_acc.file_string(known_values);
			assert(value.length() == size);
			_sizeof = size;
			return value;
		}
		if (!element_known_values.size()) {
			if (size == 0)
				 return "";
			value = file_acc.file_string(size);
			_sizeof = size;
			return value;
		}
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(char), 0, known->second));
				_sizeof += sizeof(char);
			}
		}
		return value;
	}
};



class JPEG_APP0_JFIF {
	std::vector<JPEG_APP0_JFIF*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string identifier_var;
	ubyte version_major_var;
	ubyte version_minor_var;
	ubyte density_units_var;
	uint16 x_density_var;
	uint16 y_density_var;
	ubyte x_thumbnail_var;
	ubyte y_thumbnail_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool identifier_exists = false;
	bool version_major_exists = false;
	bool version_minor_exists = false;
	bool density_units_exists = false;
	bool x_density_exists = false;
	bool y_density_exists = false;
	bool x_thumbnail_exists = false;
	bool y_thumbnail_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& identifier() {
		assert_cond(identifier_exists, "struct field identifier does not exist");
		return identifier_var;
	}
	ubyte& version_major() {
		assert_cond(version_major_exists, "struct field version_major does not exist");
		return version_major_var;
	}
	ubyte& version_minor() {
		assert_cond(version_minor_exists, "struct field version_minor does not exist");
		return version_minor_var;
	}
	ubyte& density_units() {
		assert_cond(density_units_exists, "struct field density_units does not exist");
		return density_units_var;
	}
	uint16& x_density() {
		assert_cond(x_density_exists, "struct field x_density does not exist");
		return x_density_var;
	}
	uint16& y_density() {
		assert_cond(y_density_exists, "struct field y_density does not exist");
		return y_density_var;
	}
	ubyte& x_thumbnail() {
		assert_cond(x_thumbnail_exists, "struct field x_thumbnail does not exist");
		return x_thumbnail_var;
	}
	ubyte& y_thumbnail() {
		assert_cond(y_thumbnail_exists, "struct field y_thumbnail does not exist");
		return y_thumbnail_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_APP0_JFIF& operator () () { return *instances.back(); }
	JPEG_APP0_JFIF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_APP0_JFIF(std::vector<JPEG_APP0_JFIF*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_APP0_JFIF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_APP0_JFIF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_APP0_JFIF* generate();
};

int JPEG_APP0_JFIF::_parent_id = 0;
int JPEG_APP0_JFIF::_index_start = 0;



class uint32_class {
	int small;
	std::vector<uint32> known_values;
	uint32 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(uint32);
	uint32 operator () () { return value; }
	uint32_class(int small, std::vector<uint32> known_values = {}) : small(small), known_values(known_values) {}

	uint32 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(uint32), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(uint32), 0, known_values);
		}
		return value;
	}

	uint32 generate(std::vector<uint32> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(uint32), 0, possible_values);
		return value;
	}
};



class TIFF_IFD_ENTRY {
	std::vector<TIFF_IFD_ENTRY*>& instances;

	uint16 tag_id_var;
	uint16 data_format_var;
	uint32 num_components_var;
	uint32 data_value_var;

public:
	bool tag_id_exists = false;
	bool data_format_exists = false;
	bool num_components_exists = false;
	bool data_value_exists = false;

	uint16& tag_id() {
		assert_cond(tag_id_exists, "struct field tag_id does not exist");
		return tag_id_var;
	}
	uint16& data_format() {
		assert_cond(data_format_exists, "struct field data_format does not exist");
		return data_format_var;
	}
	uint32& num_components() {
		assert_cond(num_components_exists, "struct field num_components does not exist");
		return num_components_var;
	}
	uint32& data_value() {
		assert_cond(data_value_exists, "struct field data_value does not exist");
		return data_value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	TIFF_IFD_ENTRY& operator () () { return *instances.back(); }
	TIFF_IFD_ENTRY& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	TIFF_IFD_ENTRY(std::vector<TIFF_IFD_ENTRY*>& instances) : instances(instances) { instances.push_back(this); }
	~TIFF_IFD_ENTRY() {
		if (generated == 2)
			return;
		while (instances.size()) {
			TIFF_IFD_ENTRY* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	TIFF_IFD_ENTRY* generate();
};

int TIFF_IFD_ENTRY::_parent_id = 0;
int TIFF_IFD_ENTRY::_index_start = 0;



class EXIF_IFD {
	std::vector<EXIF_IFD*>& instances;

	uint16 entry_count_var;
	TIFF_IFD_ENTRY* entry_var;
	uint32 next_ifd_offset_var;

public:
	bool entry_count_exists = false;
	bool entry_exists = false;
	bool next_ifd_offset_exists = false;

	uint16& entry_count() {
		assert_cond(entry_count_exists, "struct field entry_count does not exist");
		return entry_count_var;
	}
	TIFF_IFD_ENTRY& entry() {
		assert_cond(entry_exists, "struct field entry does not exist");
		return *entry_var;
	}
	uint32& next_ifd_offset() {
		assert_cond(next_ifd_offset_exists, "struct field next_ifd_offset does not exist");
		return next_ifd_offset_var;
	}

	/* locals */
	int i;
	int real_count;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EXIF_IFD& operator () () { return *instances.back(); }
	EXIF_IFD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EXIF_IFD(std::vector<EXIF_IFD*>& instances) : instances(instances) { instances.push_back(this); }
	~EXIF_IFD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EXIF_IFD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EXIF_IFD* generate();
};

int EXIF_IFD::_parent_id = 0;
int EXIF_IFD::_index_start = 0;



class JPEG_APP1_EXIF {
	std::vector<JPEG_APP1_EXIF*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string identifier_var;
	std::string byte_order_var;
	uint16 magic_var;
	uint32 ifd0_offset_var;
	EXIF_IFD* ifd0_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool identifier_exists = false;
	bool byte_order_exists = false;
	bool magic_exists = false;
	bool ifd0_offset_exists = false;
	bool ifd0_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& identifier() {
		assert_cond(identifier_exists, "struct field identifier does not exist");
		return identifier_var;
	}
	std::string& byte_order() {
		assert_cond(byte_order_exists, "struct field byte_order does not exist");
		return byte_order_var;
	}
	uint16& magic() {
		assert_cond(magic_exists, "struct field magic does not exist");
		return magic_var;
	}
	uint32& ifd0_offset() {
		assert_cond(ifd0_offset_exists, "struct field ifd0_offset does not exist");
		return ifd0_offset_var;
	}
	EXIF_IFD& ifd0() {
		assert_cond(ifd0_exists, "struct field ifd0 does not exist");
		return *ifd0_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_APP1_EXIF& operator () () { return *instances.back(); }
	JPEG_APP1_EXIF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_APP1_EXIF(std::vector<JPEG_APP1_EXIF*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_APP1_EXIF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_APP1_EXIF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_APP1_EXIF* generate();
};

int JPEG_APP1_EXIF::_parent_id = 0;
int JPEG_APP1_EXIF::_index_start = 0;



class ubyte_array_class {
	ubyte_class& element;
	std::unordered_map<int, std::vector<ubyte>> element_known_values;
	std::vector<ubyte> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<ubyte>& operator () () { return value; }
	ubyte operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	ubyte_array_class(ubyte_class& element, std::unordered_map<int, std::vector<ubyte>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<ubyte> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(ubyte), 0, known->second));
				_sizeof += sizeof(ubyte);
			}
		}
		return value;
	}
};



class JPEG_APP2_ICC {
	std::vector<JPEG_APP2_ICC*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string identifier_var;
	ubyte chunk_number_var;
	ubyte total_chunks_var;
	uint32 profile_size_var;
	std::string preferred_cmm_var;
	uint32 profile_version_var;
	std::string device_class_var;
	std::string color_space_var;
	std::string pcs_var;
	std::vector<ubyte> creation_date_var;
	std::string icc_signature_var;
	std::string primary_platform_var;
	uint32 profile_flags_var;
	std::string device_manufacturer_var;
	std::string device_model_var;
	std::vector<ubyte> device_attributes_var;
	uint32 rendering_intent_var;
	std::vector<ubyte> pcs_illuminant_var;
	std::string profile_creator_var;
	std::vector<ubyte> profile_id_var;
	std::vector<ubyte> icc_reserved_var;
	std::vector<ubyte> icc_tag_data_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool identifier_exists = false;
	bool chunk_number_exists = false;
	bool total_chunks_exists = false;
	bool profile_size_exists = false;
	bool preferred_cmm_exists = false;
	bool profile_version_exists = false;
	bool device_class_exists = false;
	bool color_space_exists = false;
	bool pcs_exists = false;
	bool creation_date_exists = false;
	bool icc_signature_exists = false;
	bool primary_platform_exists = false;
	bool profile_flags_exists = false;
	bool device_manufacturer_exists = false;
	bool device_model_exists = false;
	bool device_attributes_exists = false;
	bool rendering_intent_exists = false;
	bool pcs_illuminant_exists = false;
	bool profile_creator_exists = false;
	bool profile_id_exists = false;
	bool icc_reserved_exists = false;
	bool icc_tag_data_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& identifier() {
		assert_cond(identifier_exists, "struct field identifier does not exist");
		return identifier_var;
	}
	ubyte& chunk_number() {
		assert_cond(chunk_number_exists, "struct field chunk_number does not exist");
		return chunk_number_var;
	}
	ubyte& total_chunks() {
		assert_cond(total_chunks_exists, "struct field total_chunks does not exist");
		return total_chunks_var;
	}
	uint32& profile_size() {
		assert_cond(profile_size_exists, "struct field profile_size does not exist");
		return profile_size_var;
	}
	std::string& preferred_cmm() {
		assert_cond(preferred_cmm_exists, "struct field preferred_cmm does not exist");
		return preferred_cmm_var;
	}
	uint32& profile_version() {
		assert_cond(profile_version_exists, "struct field profile_version does not exist");
		return profile_version_var;
	}
	std::string& device_class() {
		assert_cond(device_class_exists, "struct field device_class does not exist");
		return device_class_var;
	}
	std::string& color_space() {
		assert_cond(color_space_exists, "struct field color_space does not exist");
		return color_space_var;
	}
	std::string& pcs() {
		assert_cond(pcs_exists, "struct field pcs does not exist");
		return pcs_var;
	}
	std::vector<ubyte>& creation_date() {
		assert_cond(creation_date_exists, "struct field creation_date does not exist");
		return creation_date_var;
	}
	std::string& icc_signature() {
		assert_cond(icc_signature_exists, "struct field icc_signature does not exist");
		return icc_signature_var;
	}
	std::string& primary_platform() {
		assert_cond(primary_platform_exists, "struct field primary_platform does not exist");
		return primary_platform_var;
	}
	uint32& profile_flags() {
		assert_cond(profile_flags_exists, "struct field profile_flags does not exist");
		return profile_flags_var;
	}
	std::string& device_manufacturer() {
		assert_cond(device_manufacturer_exists, "struct field device_manufacturer does not exist");
		return device_manufacturer_var;
	}
	std::string& device_model() {
		assert_cond(device_model_exists, "struct field device_model does not exist");
		return device_model_var;
	}
	std::vector<ubyte>& device_attributes() {
		assert_cond(device_attributes_exists, "struct field device_attributes does not exist");
		return device_attributes_var;
	}
	uint32& rendering_intent() {
		assert_cond(rendering_intent_exists, "struct field rendering_intent does not exist");
		return rendering_intent_var;
	}
	std::vector<ubyte>& pcs_illuminant() {
		assert_cond(pcs_illuminant_exists, "struct field pcs_illuminant does not exist");
		return pcs_illuminant_var;
	}
	std::string& profile_creator() {
		assert_cond(profile_creator_exists, "struct field profile_creator does not exist");
		return profile_creator_var;
	}
	std::vector<ubyte>& profile_id() {
		assert_cond(profile_id_exists, "struct field profile_id does not exist");
		return profile_id_var;
	}
	std::vector<ubyte>& icc_reserved() {
		assert_cond(icc_reserved_exists, "struct field icc_reserved does not exist");
		return icc_reserved_var;
	}
	std::vector<ubyte>& icc_tag_data() {
		assert_cond(icc_tag_data_exists, "struct field icc_tag_data does not exist");
		return icc_tag_data_var;
	}

	/* locals */
	uint32 icc_data_size;
	int remaining;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_APP2_ICC& operator () () { return *instances.back(); }
	JPEG_APP2_ICC& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_APP2_ICC(std::vector<JPEG_APP2_ICC*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_APP2_ICC() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_APP2_ICC* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_APP2_ICC* generate();
};

int JPEG_APP2_ICC::_parent_id = 0;
int JPEG_APP2_ICC::_index_start = 0;



class IPTC_DATASET {
	std::vector<IPTC_DATASET*>& instances;

	ubyte tag_marker_var;
	ubyte record_number_var;
	ubyte dataset_number_var;
	uint16 data_size_var;
	std::vector<ubyte> data_var;

public:
	bool tag_marker_exists = false;
	bool record_number_exists = false;
	bool dataset_number_exists = false;
	bool data_size_exists = false;
	bool data_exists = false;

	ubyte& tag_marker() {
		assert_cond(tag_marker_exists, "struct field tag_marker does not exist");
		return tag_marker_var;
	}
	ubyte& record_number() {
		assert_cond(record_number_exists, "struct field record_number does not exist");
		return record_number_var;
	}
	ubyte& dataset_number() {
		assert_cond(dataset_number_exists, "struct field dataset_number does not exist");
		return dataset_number_var;
	}
	uint16& data_size() {
		assert_cond(data_size_exists, "struct field data_size does not exist");
		return data_size_var;
	}
	std::vector<ubyte>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IPTC_DATASET& operator () () { return *instances.back(); }
	IPTC_DATASET& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IPTC_DATASET(std::vector<IPTC_DATASET*>& instances) : instances(instances) { instances.push_back(this); }
	~IPTC_DATASET() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IPTC_DATASET* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IPTC_DATASET* generate();
};

int IPTC_DATASET::_parent_id = 0;
int IPTC_DATASET::_index_start = 0;



class JPEG_APP13 {
	std::vector<JPEG_APP13*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string identifier_var;
	std::string resource_type_var;
	uint16 resource_id_var;
	ubyte name_length_var;
	ubyte name_pad_var;
	uint32 iptc_data_size_var;
	IPTC_DATASET* iptc1_var;
	IPTC_DATASET* iptc2_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool identifier_exists = false;
	bool resource_type_exists = false;
	bool resource_id_exists = false;
	bool name_length_exists = false;
	bool name_pad_exists = false;
	bool iptc_data_size_exists = false;
	bool iptc1_exists = false;
	bool iptc2_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& identifier() {
		assert_cond(identifier_exists, "struct field identifier does not exist");
		return identifier_var;
	}
	std::string& resource_type() {
		assert_cond(resource_type_exists, "struct field resource_type does not exist");
		return resource_type_var;
	}
	uint16& resource_id() {
		assert_cond(resource_id_exists, "struct field resource_id does not exist");
		return resource_id_var;
	}
	ubyte& name_length() {
		assert_cond(name_length_exists, "struct field name_length does not exist");
		return name_length_var;
	}
	ubyte& name_pad() {
		assert_cond(name_pad_exists, "struct field name_pad does not exist");
		return name_pad_var;
	}
	uint32& iptc_data_size() {
		assert_cond(iptc_data_size_exists, "struct field iptc_data_size does not exist");
		return iptc_data_size_var;
	}
	IPTC_DATASET& iptc1() {
		assert_cond(iptc1_exists, "struct field iptc1 does not exist");
		return *iptc1_var;
	}
	IPTC_DATASET& iptc2() {
		assert_cond(iptc2_exists, "struct field iptc2 does not exist");
		return *iptc2_var;
	}

	/* locals */
	uint32 iptc_block_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_APP13& operator () () { return *instances.back(); }
	JPEG_APP13& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_APP13(std::vector<JPEG_APP13*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_APP13() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_APP13* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_APP13* generate();
};

int JPEG_APP13::_parent_id = 0;
int JPEG_APP13::_index_start = 0;



class JPEG_APP14_ADOBE {
	std::vector<JPEG_APP14_ADOBE*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string identifier_var;
	uint16 version_var;
	uint16 flags0_var;
	uint16 flags1_var;
	ubyte color_transform_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool identifier_exists = false;
	bool version_exists = false;
	bool flags0_exists = false;
	bool flags1_exists = false;
	bool color_transform_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& identifier() {
		assert_cond(identifier_exists, "struct field identifier does not exist");
		return identifier_var;
	}
	uint16& version() {
		assert_cond(version_exists, "struct field version does not exist");
		return version_var;
	}
	uint16& flags0() {
		assert_cond(flags0_exists, "struct field flags0 does not exist");
		return flags0_var;
	}
	uint16& flags1() {
		assert_cond(flags1_exists, "struct field flags1 does not exist");
		return flags1_var;
	}
	ubyte& color_transform() {
		assert_cond(color_transform_exists, "struct field color_transform does not exist");
		return color_transform_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_APP14_ADOBE& operator () () { return *instances.back(); }
	JPEG_APP14_ADOBE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_APP14_ADOBE(std::vector<JPEG_APP14_ADOBE*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_APP14_ADOBE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_APP14_ADOBE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_APP14_ADOBE* generate();
};

int JPEG_APP14_ADOBE::_parent_id = 0;
int JPEG_APP14_ADOBE::_index_start = 0;



class JPEG_DQT {
	std::vector<JPEG_DQT*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	ubyte prec_and_id_var;
	std::vector<ubyte> qt_values_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool prec_and_id_exists = false;
	bool qt_values_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	ubyte& prec_and_id() {
		assert_cond(prec_and_id_exists, "struct field prec_and_id does not exist");
		return prec_and_id_var;
	}
	std::vector<ubyte>& qt_values() {
		assert_cond(qt_values_exists, "struct field qt_values does not exist");
		return qt_values_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_DQT& operator () () { return *instances.back(); }
	JPEG_DQT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_DQT(std::vector<JPEG_DQT*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_DQT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_DQT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_DQT* generate();
};

int JPEG_DQT::_parent_id = 0;
int JPEG_DQT::_index_start = 0;



class JPEG_DHT {
	std::vector<JPEG_DHT*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	ubyte class_and_id_var;
	std::vector<ubyte> num_codes_var;
	std::vector<ubyte> huff_values_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool class_and_id_exists = false;
	bool num_codes_exists = false;
	bool huff_values_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	ubyte& class_and_id() {
		assert_cond(class_and_id_exists, "struct field class_and_id does not exist");
		return class_and_id_var;
	}
	std::vector<ubyte>& num_codes() {
		assert_cond(num_codes_exists, "struct field num_codes does not exist");
		return num_codes_var;
	}
	std::vector<ubyte>& huff_values() {
		assert_cond(huff_values_exists, "struct field huff_values does not exist");
		return huff_values_var;
	}

	/* locals */
	uint32 total_codes;
	int ci;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_DHT& operator () () { return *instances.back(); }
	JPEG_DHT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_DHT(std::vector<JPEG_DHT*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_DHT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_DHT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_DHT* generate();
};

int JPEG_DHT::_parent_id = 0;
int JPEG_DHT::_index_start = 0;



class SOF_COMPONENT {
	std::vector<SOF_COMPONENT*>& instances;

	ubyte component_id_var;
	ubyte sampling_factors_var;
	ubyte quant_table_id_var;

public:
	bool component_id_exists = false;
	bool sampling_factors_exists = false;
	bool quant_table_id_exists = false;

	ubyte& component_id() {
		assert_cond(component_id_exists, "struct field component_id does not exist");
		return component_id_var;
	}
	ubyte& sampling_factors() {
		assert_cond(sampling_factors_exists, "struct field sampling_factors does not exist");
		return sampling_factors_var;
	}
	ubyte& quant_table_id() {
		assert_cond(quant_table_id_exists, "struct field quant_table_id does not exist");
		return quant_table_id_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SOF_COMPONENT& operator () () { return *instances.back(); }
	SOF_COMPONENT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SOF_COMPONENT(std::vector<SOF_COMPONENT*>& instances) : instances(instances) { instances.push_back(this); }
	~SOF_COMPONENT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SOF_COMPONENT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SOF_COMPONENT* generate();
};

int SOF_COMPONENT::_parent_id = 0;
int SOF_COMPONENT::_index_start = 0;



class JPEG_SOF0 {
	std::vector<JPEG_SOF0*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	ubyte precision_var;
	uint16 image_height_var;
	uint16 image_width_var;
	ubyte num_components_var;
	SOF_COMPONENT* comp_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool precision_exists = false;
	bool image_height_exists = false;
	bool image_width_exists = false;
	bool num_components_exists = false;
	bool comp_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	ubyte& precision() {
		assert_cond(precision_exists, "struct field precision does not exist");
		return precision_var;
	}
	uint16& image_height() {
		assert_cond(image_height_exists, "struct field image_height does not exist");
		return image_height_var;
	}
	uint16& image_width() {
		assert_cond(image_width_exists, "struct field image_width does not exist");
		return image_width_var;
	}
	ubyte& num_components() {
		assert_cond(num_components_exists, "struct field num_components does not exist");
		return num_components_var;
	}
	SOF_COMPONENT& comp() {
		assert_cond(comp_exists, "struct field comp does not exist");
		return *comp_var;
	}

	/* locals */
	int i;
	int nc;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_SOF0& operator () () { return *instances.back(); }
	JPEG_SOF0& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_SOF0(std::vector<JPEG_SOF0*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_SOF0() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_SOF0* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_SOF0* generate();
};

int JPEG_SOF0::_parent_id = 0;
int JPEG_SOF0::_index_start = 0;



class JPEG_DRI {
	std::vector<JPEG_DRI*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	uint16 restart_interval_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool restart_interval_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	uint16& restart_interval() {
		assert_cond(restart_interval_exists, "struct field restart_interval does not exist");
		return restart_interval_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_DRI& operator () () { return *instances.back(); }
	JPEG_DRI& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_DRI(std::vector<JPEG_DRI*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_DRI() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_DRI* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_DRI* generate();
};

int JPEG_DRI::_parent_id = 0;
int JPEG_DRI::_index_start = 0;



class JPEG_COM {
	std::vector<JPEG_COM*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	std::string comment_data_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool comment_data_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& comment_data() {
		assert_cond(comment_data_exists, "struct field comment_data does not exist");
		return comment_data_var;
	}

	/* locals */
	uint32 comment_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_COM& operator () () { return *instances.back(); }
	JPEG_COM& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_COM(std::vector<JPEG_COM*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_COM() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_COM* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_COM* generate();
};

int JPEG_COM::_parent_id = 0;
int JPEG_COM::_index_start = 0;



class SOS_COMPONENT {
	std::vector<SOS_COMPONENT*>& instances;

	ubyte component_selector_var;
	ubyte table_selectors_var;

public:
	bool component_selector_exists = false;
	bool table_selectors_exists = false;

	ubyte& component_selector() {
		assert_cond(component_selector_exists, "struct field component_selector does not exist");
		return component_selector_var;
	}
	ubyte& table_selectors() {
		assert_cond(table_selectors_exists, "struct field table_selectors does not exist");
		return table_selectors_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SOS_COMPONENT& operator () () { return *instances.back(); }
	SOS_COMPONENT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SOS_COMPONENT(std::vector<SOS_COMPONENT*>& instances) : instances(instances) { instances.push_back(this); }
	~SOS_COMPONENT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SOS_COMPONENT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SOS_COMPONENT* generate();
};

int SOS_COMPONENT::_parent_id = 0;
int SOS_COMPONENT::_index_start = 0;



class JPEG_SOS {
	std::vector<JPEG_SOS*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;
	uint16 length_var;
	ubyte num_components_var;
	SOS_COMPONENT* comp_var;
	ubyte start_spectral_var;
	ubyte end_spectral_var;
	ubyte approx_bits_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;
	bool length_exists = false;
	bool num_components_exists = false;
	bool comp_exists = false;
	bool start_spectral_exists = false;
	bool end_spectral_exists = false;
	bool approx_bits_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}
	uint16& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	ubyte& num_components() {
		assert_cond(num_components_exists, "struct field num_components does not exist");
		return num_components_var;
	}
	SOS_COMPONENT& comp() {
		assert_cond(comp_exists, "struct field comp does not exist");
		return *comp_var;
	}
	ubyte& start_spectral() {
		assert_cond(start_spectral_exists, "struct field start_spectral does not exist");
		return start_spectral_var;
	}
	ubyte& end_spectral() {
		assert_cond(end_spectral_exists, "struct field end_spectral does not exist");
		return end_spectral_var;
	}
	ubyte& approx_bits() {
		assert_cond(approx_bits_exists, "struct field approx_bits does not exist");
		return approx_bits_var;
	}

	/* locals */
	int i;
	int nc;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_SOS& operator () () { return *instances.back(); }
	JPEG_SOS& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_SOS(std::vector<JPEG_SOS*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_SOS() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_SOS* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_SOS* generate();
};

int JPEG_SOS::_parent_id = 0;
int JPEG_SOS::_index_start = 0;



class JPEG_SCAN_DATA {
	std::vector<JPEG_SCAN_DATA*>& instances;

	std::vector<ubyte> scan_data_var;

public:
	bool scan_data_exists = false;

	std::vector<ubyte>& scan_data() {
		assert_cond(scan_data_exists, "struct field scan_data does not exist");
		return scan_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_SCAN_DATA& operator () () { return *instances.back(); }
	JPEG_SCAN_DATA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_SCAN_DATA(std::vector<JPEG_SCAN_DATA*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_SCAN_DATA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_SCAN_DATA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_SCAN_DATA* generate();
};

int JPEG_SCAN_DATA::_parent_id = 0;
int JPEG_SCAN_DATA::_index_start = 0;



class JPEG_EOI {
	std::vector<JPEG_EOI*>& instances;

	ubyte marker1_var;
	ubyte marker2_var;

public:
	bool marker1_exists = false;
	bool marker2_exists = false;

	ubyte& marker1() {
		assert_cond(marker1_exists, "struct field marker1 does not exist");
		return marker1_var;
	}
	ubyte& marker2() {
		assert_cond(marker2_exists, "struct field marker2 does not exist");
		return marker2_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	JPEG_EOI& operator () () { return *instances.back(); }
	JPEG_EOI& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JPEG_EOI(std::vector<JPEG_EOI*>& instances) : instances(instances) { instances.push_back(this); }
	~JPEG_EOI() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JPEG_EOI* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JPEG_EOI* generate();
};

int JPEG_EOI::_parent_id = 0;
int JPEG_EOI::_index_start = 0;



class jpeg_file {
	std::vector<jpeg_file*>& instances;

	JPEG_SOI* soi_var;
	JPEG_APP0_JFIF* app0_var;
	JPEG_APP1_EXIF* app1_exif_var;
	JPEG_APP2_ICC* app2_icc_var;
	JPEG_APP13* app13_var;
	JPEG_APP14_ADOBE* app14_var;
	JPEG_DQT* dqt_var;
	JPEG_DHT* dht_var;
	JPEG_SOF0* sof0_var;
	JPEG_DRI* dri_var;
	JPEG_COM* com_var;
	JPEG_SOS* sos_var;
	JPEG_SCAN_DATA* scan_var;
	JPEG_EOI* eoi_var;

public:
	bool soi_exists = false;
	bool app0_exists = false;
	bool app1_exif_exists = false;
	bool app2_icc_exists = false;
	bool app13_exists = false;
	bool app14_exists = false;
	bool dqt_exists = false;
	bool dht_exists = false;
	bool sof0_exists = false;
	bool dri_exists = false;
	bool com_exists = false;
	bool sos_exists = false;
	bool scan_exists = false;
	bool eoi_exists = false;

	JPEG_SOI& soi() {
		assert_cond(soi_exists, "struct field soi does not exist");
		return *soi_var;
	}
	JPEG_APP0_JFIF& app0() {
		assert_cond(app0_exists, "struct field app0 does not exist");
		return *app0_var;
	}
	JPEG_APP1_EXIF& app1_exif() {
		assert_cond(app1_exif_exists, "struct field app1_exif does not exist");
		return *app1_exif_var;
	}
	JPEG_APP2_ICC& app2_icc() {
		assert_cond(app2_icc_exists, "struct field app2_icc does not exist");
		return *app2_icc_var;
	}
	JPEG_APP13& app13() {
		assert_cond(app13_exists, "struct field app13 does not exist");
		return *app13_var;
	}
	JPEG_APP14_ADOBE& app14() {
		assert_cond(app14_exists, "struct field app14 does not exist");
		return *app14_var;
	}
	JPEG_DQT& dqt() {
		assert_cond(dqt_exists, "struct field dqt does not exist");
		return *dqt_var;
	}
	JPEG_DHT& dht() {
		assert_cond(dht_exists, "struct field dht does not exist");
		return *dht_var;
	}
	JPEG_SOF0& sof0() {
		assert_cond(sof0_exists, "struct field sof0 does not exist");
		return *sof0_var;
	}
	JPEG_DRI& dri() {
		assert_cond(dri_exists, "struct field dri does not exist");
		return *dri_var;
	}
	JPEG_COM& com() {
		assert_cond(com_exists, "struct field com does not exist");
		return *com_var;
	}
	JPEG_SOS& sos() {
		assert_cond(sos_exists, "struct field sos does not exist");
		return *sos_var;
	}
	JPEG_SCAN_DATA& scan() {
		assert_cond(scan_exists, "struct field scan does not exist");
		return *scan_var;
	}
	JPEG_EOI& eoi() {
		assert_cond(eoi_exists, "struct field eoi does not exist");
		return *eoi_var;
	}

	/* locals */
	std::string tag;
	std::vector<std::string> all_choices;
	std::vector<std::string> preferred;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	jpeg_file& operator () () { return *instances.back(); }
	jpeg_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	jpeg_file(std::vector<jpeg_file*>& instances) : instances(instances) { instances.push_back(this); }
	~jpeg_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			jpeg_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	jpeg_file* generate();
};

int jpeg_file::_parent_id = 0;
int jpeg_file::_index_start = 0;

std::vector<byte> ReadByteInitValues;
std::vector<ubyte> ReadUByteInitValues;
std::vector<short> ReadShortInitValues;
std::vector<ushort> ReadUShortInitValues;
std::vector<int> ReadIntInitValues;
std::vector<uint> ReadUIntInitValues;
std::vector<int64> ReadQuadInitValues;
std::vector<uint64> ReadUQuadInitValues;
std::vector<int64> ReadInt64InitValues;
std::vector<uint64> ReadUInt64InitValues;
std::vector<hfloat> ReadHFloatInitValues;
std::vector<float> ReadFloatInitValues;
std::vector<double> ReadDoubleInitValues;
std::vector<std::string> ReadBytesInitValues = { "\xFF\xD8", "\xFF\xE0", "\xFF\xE1", "\xFF\xE2", "\xFF\xED", "\xFF\xEE", "\xFF\xDB", "\xFF\xC4", "\xFF\xC0", "\xFF\xC2", "\xFF\xDA", "\xFF\xDD", "\xFF\xFE", "\xFF\xD9" };


std::vector<JPEG_SOI*> JPEG_SOI_soi_instances;
std::vector<JPEG_APP0_JFIF*> JPEG_APP0_JFIF_app0_instances;
std::vector<TIFF_IFD_ENTRY*> TIFF_IFD_ENTRY_entry_instances;
std::vector<EXIF_IFD*> EXIF_IFD_ifd0_instances;
std::vector<JPEG_APP1_EXIF*> JPEG_APP1_EXIF_app1_exif_instances;
std::vector<JPEG_APP2_ICC*> JPEG_APP2_ICC_app2_icc_instances;
std::vector<IPTC_DATASET*> IPTC_DATASET_iptc1_instances;
std::vector<IPTC_DATASET*> IPTC_DATASET_iptc2_instances;
std::vector<JPEG_APP13*> JPEG_APP13_app13_instances;
std::vector<JPEG_APP14_ADOBE*> JPEG_APP14_ADOBE_app14_instances;
std::vector<JPEG_DQT*> JPEG_DQT_dqt_instances;
std::vector<JPEG_DHT*> JPEG_DHT_dht_instances;
std::vector<SOF_COMPONENT*> SOF_COMPONENT_comp_instances;
std::vector<JPEG_SOF0*> JPEG_SOF0_sof0_instances;
std::vector<JPEG_DRI*> JPEG_DRI_dri_instances;
std::vector<JPEG_COM*> JPEG_COM_com_instances;
std::vector<SOS_COMPONENT*> SOS_COMPONENT_comp__instances;
std::vector<JPEG_SOS*> JPEG_SOS_sos_instances;
std::vector<JPEG_SCAN_DATA*> JPEG_SCAN_DATA_scan_instances;
std::vector<JPEG_EOI*> JPEG_EOI_eoi_instances;
std::vector<jpeg_file*> jpeg_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "marker1", "ubyte_class" }, { "marker2", "ubyte_class" }, { "soi", "JPEG_SOI" }, { "length", "uint16_class" }, { "identifier", "char_array_class" }, { "version_major", "ubyte_class" }, { "version_minor", "ubyte_class" }, { "density_units", "ubyte_class" }, { "x_density", "uint16_class" }, { "y_density", "uint16_class" }, { "x_thumbnail", "ubyte_class" }, { "y_thumbnail", "ubyte_class" }, { "app0", "JPEG_APP0_JFIF" }, { "byte_order", "char_array_class" }, { "magic", "uint16_class" }, { "ifd0_offset", "uint32_class" }, { "entry_count", "uint16_class" }, { "tag_id", "uint16_class" }, { "data_format", "uint16_class" }, { "num_components", "uint32_class" }, { "data_value", "uint32_class" }, { "entry", "TIFF_IFD_ENTRY" }, { "next_ifd_offset", "uint32_class" }, { "ifd0", "EXIF_IFD" }, { "app1_exif", "JPEG_APP1_EXIF" }, { "chunk_number", "ubyte_class" }, { "total_chunks", "ubyte_class" }, { "profile_size", "uint32_class" }, { "preferred_cmm", "char_array_class" }, { "profile_version", "uint32_class" }, { "device_class", "char_array_class" }, { "color_space", "char_array_class" }, { "pcs", "char_array_class" }, { "creation_date", "ubyte_array_class" }, { "icc_signature", "char_array_class" }, { "primary_platform", "char_array_class" }, { "profile_flags", "uint32_class" }, { "device_manufacturer", "char_array_class" }, { "device_model", "char_array_class" }, { "device_attributes", "ubyte_array_class" }, { "rendering_intent", "uint32_class" }, { "pcs_illuminant", "ubyte_array_class" }, { "profile_creator", "char_array_class" }, { "profile_id", "ubyte_array_class" }, { "icc_reserved", "ubyte_array_class" }, { "icc_tag_data", "ubyte_array_class" }, { "app2_icc", "JPEG_APP2_ICC" }, { "resource_type", "char_array_class" }, { "resource_id", "uint16_class" }, { "name_length", "ubyte_class" }, { "name_pad", "ubyte_class" }, { "iptc_data_size", "uint32_class" }, { "tag_marker", "ubyte_class" }, { "record_number", "ubyte_class" }, { "dataset_number", "ubyte_class" }, { "data_size", "uint16_class" }, { "data", "ubyte_array_class" }, { "iptc1", "IPTC_DATASET" }, { "iptc2", "IPTC_DATASET" }, { "app13", "JPEG_APP13" }, { "version", "uint16_class" }, { "flags0", "uint16_class" }, { "flags1", "uint16_class" }, { "color_transform", "ubyte_class" }, { "app14", "JPEG_APP14_ADOBE" }, { "prec_and_id", "ubyte_class" }, { "qt_values", "ubyte_array_class" }, { "dqt", "JPEG_DQT" }, { "class_and_id", "ubyte_class" }, { "num_codes", "ubyte_array_class" }, { "huff_values", "ubyte_array_class" }, { "dht", "JPEG_DHT" }, { "precision", "ubyte_class" }, { "image_height", "uint16_class" }, { "image_width", "uint16_class" }, { "num_components_", "ubyte_class" }, { "component_id", "ubyte_class" }, { "sampling_factors", "ubyte_class" }, { "quant_table_id", "ubyte_class" }, { "comp", "SOF_COMPONENT" }, { "sof0", "JPEG_SOF0" }, { "restart_interval", "uint16_class" }, { "dri", "JPEG_DRI" }, { "comment_data", "char_array_class" }, { "com", "JPEG_COM" }, { "component_selector", "ubyte_class" }, { "table_selectors", "ubyte_class" }, { "comp_", "SOS_COMPONENT" }, { "start_spectral", "ubyte_class" }, { "end_spectral", "ubyte_class" }, { "approx_bits", "ubyte_class" }, { "sos", "JPEG_SOS" }, { "scan_data", "ubyte_array_class" }, { "scan", "JPEG_SCAN_DATA" }, { "eoi", "JPEG_EOI" }, { "file", "jpeg_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 16, 64 }, { 0, 2 }, { 1, 300 }, { 1, 300 }, { 1, 12 }, { 1, 12 }, { 1, 256 }, { 0, 3 }, { 1, 256 }, { 0, 2 }, { 0, 3 }, { 1, 4096 }, { 1, 4096 }, { 0, 3 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	ubyte_class marker1;
	ubyte_class marker2;
	JPEG_SOI soi;
	uint16_class length;
	char_class identifier_element;
	char_array_class identifier;
	ubyte_class version_major;
	ubyte_class version_minor;
	ubyte_class density_units;
	uint16_class x_density;
	uint16_class y_density;
	ubyte_class x_thumbnail;
	ubyte_class y_thumbnail;
	JPEG_APP0_JFIF app0;
	char_class byte_order_element;
	char_array_class byte_order;
	uint16_class magic;
	uint32_class ifd0_offset;
	uint16_class entry_count;
	uint16_class tag_id;
	uint16_class data_format;
	uint32_class num_components;
	uint32_class data_value;
	TIFF_IFD_ENTRY entry;
	uint32_class next_ifd_offset;
	EXIF_IFD ifd0;
	JPEG_APP1_EXIF app1_exif;
	ubyte_class chunk_number;
	ubyte_class total_chunks;
	uint32_class profile_size;
	char_class preferred_cmm_element;
	char_array_class preferred_cmm;
	uint32_class profile_version;
	char_class device_class_element;
	char_array_class device_class;
	char_class color_space_element;
	char_array_class color_space;
	char_class pcs_element;
	char_array_class pcs;
	ubyte_class creation_date_element;
	ubyte_array_class creation_date;
	char_class icc_signature_element;
	char_array_class icc_signature;
	char_class primary_platform_element;
	char_array_class primary_platform;
	uint32_class profile_flags;
	char_class device_manufacturer_element;
	char_array_class device_manufacturer;
	char_class device_model_element;
	char_array_class device_model;
	ubyte_class device_attributes_element;
	ubyte_array_class device_attributes;
	uint32_class rendering_intent;
	ubyte_class pcs_illuminant_element;
	ubyte_array_class pcs_illuminant;
	char_class profile_creator_element;
	char_array_class profile_creator;
	ubyte_class profile_id_element;
	ubyte_array_class profile_id;
	ubyte_class icc_reserved_element;
	ubyte_array_class icc_reserved;
	ubyte_class icc_tag_data_element;
	ubyte_array_class icc_tag_data;
	JPEG_APP2_ICC app2_icc;
	char_class resource_type_element;
	char_array_class resource_type;
	uint16_class resource_id;
	ubyte_class name_length;
	ubyte_class name_pad;
	uint32_class iptc_data_size;
	ubyte_class tag_marker;
	ubyte_class record_number;
	ubyte_class dataset_number;
	uint16_class data_size;
	ubyte_class data_element;
	ubyte_array_class data;
	IPTC_DATASET iptc1;
	IPTC_DATASET iptc2;
	JPEG_APP13 app13;
	uint16_class version;
	uint16_class flags0;
	uint16_class flags1;
	ubyte_class color_transform;
	JPEG_APP14_ADOBE app14;
	ubyte_class prec_and_id;
	ubyte_class qt_values_element;
	ubyte_array_class qt_values;
	JPEG_DQT dqt;
	ubyte_class class_and_id;
	ubyte_class num_codes_element;
	ubyte_array_class num_codes;
	ubyte_class huff_values_element;
	ubyte_array_class huff_values;
	JPEG_DHT dht;
	ubyte_class precision;
	uint16_class image_height;
	uint16_class image_width;
	ubyte_class num_components_;
	ubyte_class component_id;
	ubyte_class sampling_factors;
	ubyte_class quant_table_id;
	SOF_COMPONENT comp;
	JPEG_SOF0 sof0;
	uint16_class restart_interval;
	JPEG_DRI dri;
	char_class comment_data_element;
	char_array_class comment_data;
	JPEG_COM com;
	ubyte_class component_selector;
	ubyte_class table_selectors;
	SOS_COMPONENT comp_;
	ubyte_class start_spectral;
	ubyte_class end_spectral;
	ubyte_class approx_bits;
	JPEG_SOS sos;
	ubyte_class scan_data_element;
	ubyte_array_class scan_data;
	JPEG_SCAN_DATA scan;
	JPEG_EOI eoi;
	jpeg_file file;


	globals_class() :
		marker1(1),
		marker2(1),
		soi(JPEG_SOI_soi_instances),
		length(3),
		identifier_element(false),
		identifier(identifier_element),
		version_major(1),
		version_minor(1),
		density_units(4),
		x_density(5),
		y_density(6),
		x_thumbnail(1),
		y_thumbnail(1),
		app0(JPEG_APP0_JFIF_app0_instances),
		byte_order_element(false),
		byte_order(byte_order_element),
		magic(1),
		ifd0_offset(1),
		entry_count(7),
		tag_id(1),
		data_format(8),
		num_components(9),
		data_value(1),
		entry(TIFF_IFD_ENTRY_entry_instances),
		next_ifd_offset(1),
		ifd0(EXIF_IFD_ifd0_instances),
		app1_exif(JPEG_APP1_EXIF_app1_exif_instances),
		chunk_number(1),
		total_chunks(1),
		profile_size(1),
		preferred_cmm_element(false),
		preferred_cmm(preferred_cmm_element),
		profile_version(1),
		device_class_element(false),
		device_class(device_class_element),
		color_space_element(false),
		color_space(color_space_element),
		pcs_element(false),
		pcs(pcs_element),
		creation_date_element(false),
		creation_date(creation_date_element),
		icc_signature_element(false),
		icc_signature(icc_signature_element),
		primary_platform_element(false),
		primary_platform(primary_platform_element),
		profile_flags(1),
		device_manufacturer_element(false),
		device_manufacturer(device_manufacturer_element),
		device_model_element(false),
		device_model(device_model_element),
		device_attributes_element(false),
		device_attributes(device_attributes_element),
		rendering_intent(10),
		pcs_illuminant_element(false),
		pcs_illuminant(pcs_illuminant_element),
		profile_creator_element(false),
		profile_creator(profile_creator_element),
		profile_id_element(false),
		profile_id(profile_id_element),
		icc_reserved_element(false),
		icc_reserved(icc_reserved_element),
		icc_tag_data_element(false),
		icc_tag_data(icc_tag_data_element),
		app2_icc(JPEG_APP2_ICC_app2_icc_instances),
		resource_type_element(false),
		resource_type(resource_type_element),
		resource_id(1),
		name_length(1),
		name_pad(1),
		iptc_data_size(1),
		tag_marker(1),
		record_number(1),
		dataset_number(1),
		data_size(11),
		data_element(false),
		data(data_element),
		iptc1(IPTC_DATASET_iptc1_instances),
		iptc2(IPTC_DATASET_iptc2_instances),
		app13(JPEG_APP13_app13_instances),
		version(1),
		flags0(1),
		flags1(1),
		color_transform(12),
		app14(JPEG_APP14_ADOBE_app14_instances),
		prec_and_id(13),
		qt_values_element(false),
		qt_values(qt_values_element),
		dqt(JPEG_DQT_dqt_instances),
		class_and_id(1),
		num_codes_element(false),
		num_codes(num_codes_element),
		huff_values_element(false),
		huff_values(huff_values_element),
		dht(JPEG_DHT_dht_instances),
		precision(1),
		image_height(14),
		image_width(15),
		num_components_(1),
		component_id(1),
		sampling_factors(1),
		quant_table_id(16),
		comp(SOF_COMPONENT_comp_instances),
		sof0(JPEG_SOF0_sof0_instances),
		restart_interval(1),
		dri(JPEG_DRI_dri_instances),
		comment_data_element(false),
		comment_data(comment_data_element),
		com(JPEG_COM_com_instances),
		component_selector(1),
		table_selectors(1),
		comp_(SOS_COMPONENT_comp__instances),
		start_spectral(1),
		end_spectral(1),
		approx_bits(1),
		sos(JPEG_SOS_sos_instances),
		scan_data_element(false),
		scan_data(scan_data_element),
		scan(JPEG_SCAN_DATA_scan_instances),
		eoi(JPEG_EOI_eoi_instances),
		file(jpeg_file_file_instances)
	{}
};

globals_class* g;


JPEG_SOI* JPEG_SOI::generate() {
	if (generated == 1) {
		JPEG_SOI* new_instance = new JPEG_SOI(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xD8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_APP0_JFIF* JPEG_APP0_JFIF::generate() {
	if (generated == 1) {
		JPEG_APP0_JFIF* new_instance = new JPEG_APP0_JFIF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xE0 }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(identifier, ::g->identifier.generate(5, { std::string("JFIF\x00", 5) }));
	GENERATE_VAR(version_major, ::g->version_major.generate({ 1 }));
	GENERATE_VAR(version_minor, ::g->version_minor.generate({ 0, 1, 2 }));
	GENERATE_VAR(density_units, ::g->density_units.generate());
	GENERATE_VAR(x_density, ::g->x_density.generate());
	GENERATE_VAR(y_density, ::g->y_density.generate());
	GENERATE_VAR(x_thumbnail, ::g->x_thumbnail.generate({ 0 }));
	GENERATE_VAR(y_thumbnail, ::g->y_thumbnail.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


TIFF_IFD_ENTRY* TIFF_IFD_ENTRY::generate() {
	if (generated == 1) {
		TIFF_IFD_ENTRY* new_instance = new TIFF_IFD_ENTRY(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(tag_id, ::g->tag_id.generate());
	GENERATE_VAR(data_format, ::g->data_format.generate());
	GENERATE_VAR(num_components, ::g->num_components.generate());
	GENERATE_VAR(data_value, ::g->data_value.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EXIF_IFD* EXIF_IFD::generate() {
	if (generated == 1) {
		EXIF_IFD* new_instance = new EXIF_IFD(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(entry_count, ::g->entry_count.generate());
	real_count = entry_count();
	if ((real_count > 12)) {
	real_count = 12;
	};
	for (i = 0; (i < real_count); i++) {
			GENERATE_VAR(entry, ::g->entry.generate());
	;
	};
	GENERATE_VAR(next_ifd_offset, ::g->next_ifd_offset.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_APP1_EXIF* JPEG_APP1_EXIF::generate() {
	if (generated == 1) {
		JPEG_APP1_EXIF* new_instance = new JPEG_APP1_EXIF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xE1 }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(identifier, ::g->identifier.generate(6, { std::string("Exif\x00\x00", 6) }));
	GENERATE_VAR(byte_order, ::g->byte_order.generate(2, { "MM" }));
	GENERATE_VAR(magic, ::g->magic.generate({ 42 }));
	GENERATE_VAR(ifd0_offset, ::g->ifd0_offset.generate({ 8 }));
	GENERATE_VAR(ifd0, ::g->ifd0.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_APP2_ICC* JPEG_APP2_ICC::generate() {
	if (generated == 1) {
		JPEG_APP2_ICC* new_instance = new JPEG_APP2_ICC(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xE2 }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(identifier, ::g->identifier.generate(12, { std::string("ICC_PROFILE\x00", 12) }));
	GENERATE_VAR(chunk_number, ::g->chunk_number.generate({ 1 }));
	GENERATE_VAR(total_chunks, ::g->total_chunks.generate({ 1 }));
	icc_data_size = ((length() - 2) - 14);
	if (((icc_data_size > 0) && (icc_data_size < 65536))) {
		GENERATE_VAR(profile_size, ::g->profile_size.generate());
		GENERATE_VAR(preferred_cmm, ::g->preferred_cmm.generate(4));
		GENERATE_VAR(profile_version, ::g->profile_version.generate());
		GENERATE_VAR(device_class, ::g->device_class.generate(4, { "mntr", "scnr", "prtr" }));
		GENERATE_VAR(color_space, ::g->color_space.generate(4, { "RGB ", "GRAY", "CMYK" }));
		GENERATE_VAR(pcs, ::g->pcs.generate(4, { "XYZ " }));
		GENERATE_VAR(creation_date, ::g->creation_date.generate(12));
		GENERATE_VAR(icc_signature, ::g->icc_signature.generate(4, { "acsp" }));
		GENERATE_VAR(primary_platform, ::g->primary_platform.generate(4, { "APPL", "MSFT" }));
		GENERATE_VAR(profile_flags, ::g->profile_flags.generate());
		GENERATE_VAR(device_manufacturer, ::g->device_manufacturer.generate(4));
		GENERATE_VAR(device_model, ::g->device_model.generate(4));
		GENERATE_VAR(device_attributes, ::g->device_attributes.generate(8));
		GENERATE_VAR(rendering_intent, ::g->rendering_intent.generate());
		GENERATE_VAR(pcs_illuminant, ::g->pcs_illuminant.generate(12));
		GENERATE_VAR(profile_creator, ::g->profile_creator.generate(4));
		GENERATE_VAR(profile_id, ::g->profile_id.generate(16));
		GENERATE_VAR(icc_reserved, ::g->icc_reserved.generate(28));
		remaining = (icc_data_size - 128);
		if (((remaining > 0) && (remaining < 65536))) {
			GENERATE_VAR(icc_tag_data, ::g->icc_tag_data.generate(remaining));
		};
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IPTC_DATASET* IPTC_DATASET::generate() {
	if (generated == 1) {
		IPTC_DATASET* new_instance = new IPTC_DATASET(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(tag_marker, ::g->tag_marker.generate({ 0x1C }));
	GENERATE_VAR(record_number, ::g->record_number.generate({ 2 }));
	GENERATE_VAR(dataset_number, ::g->dataset_number.generate());
	GENERATE_VAR(data_size, ::g->data_size.generate());
	if (((data_size() > 0) && (data_size() < 4096))) {
		GENERATE_VAR(data, ::g->data.generate(data_size()));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_APP13* JPEG_APP13::generate() {
	if (generated == 1) {
		JPEG_APP13* new_instance = new JPEG_APP13(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xED }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(identifier, ::g->identifier.generate(14, { std::string("Photoshop 3.0\x00", 14) }));
	GENERATE_VAR(resource_type, ::g->resource_type.generate(4, { "8BIM" }));
	GENERATE_VAR(resource_id, ::g->resource_id.generate({ 1028 }));
	GENERATE_VAR(name_length, ::g->name_length.generate({ 0 }));
	GENERATE_VAR(name_pad, ::g->name_pad.generate({ 0 }));
	iptc_block_size = (((((length() - 2) - 14) - 4) - 2) - 2);
	if (((iptc_block_size > 6) && (iptc_block_size < 4096))) {
		GENERATE_VAR(iptc_data_size, ::g->iptc_data_size.generate());
		GENERATE_VAR(iptc1, ::g->iptc1.generate());
		GENERATE_VAR(iptc2, ::g->iptc2.generate());
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_APP14_ADOBE* JPEG_APP14_ADOBE::generate() {
	if (generated == 1) {
		JPEG_APP14_ADOBE* new_instance = new JPEG_APP14_ADOBE(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xEE }));
	GENERATE_VAR(length, ::g->length.generate({ 14 }));
	GENERATE_VAR(identifier, ::g->identifier.generate(5, { "Adobe" }));
	GENERATE_VAR(version, ::g->version.generate({ 100 }));
	GENERATE_VAR(flags0, ::g->flags0.generate({ 0 }));
	GENERATE_VAR(flags1, ::g->flags1.generate({ 0 }));
	GENERATE_VAR(color_transform, ::g->color_transform.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_DQT* JPEG_DQT::generate() {
	if (generated == 1) {
		JPEG_DQT* new_instance = new JPEG_DQT(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xDB }));
	GENERATE_VAR(length, ::g->length.generate({ 67 }));
	GENERATE_VAR(prec_and_id, ::g->prec_and_id.generate());
	GENERATE_VAR(qt_values, ::g->qt_values.generate(64));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_DHT* JPEG_DHT::generate() {
	if (generated == 1) {
		JPEG_DHT* new_instance = new JPEG_DHT(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xC4 }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(class_and_id, ::g->class_and_id.generate({ 0x00, 0x01, 0x10, 0x11 }));
	GENERATE_VAR(num_codes, ::g->num_codes.generate(16));
	total_codes = 0;
	for (ci = 0; (ci < 16); ci++) {
			total_codes += num_codes()[ci];
	;
	};
	if (((total_codes > 0) && (total_codes < 256))) {
		GENERATE_VAR(huff_values, ::g->huff_values.generate(total_codes));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SOF_COMPONENT* SOF_COMPONENT::generate() {
	if (generated == 1) {
		SOF_COMPONENT* new_instance = new SOF_COMPONENT(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(component_id, ::g->component_id.generate());
	GENERATE_VAR(sampling_factors, ::g->sampling_factors.generate());
	GENERATE_VAR(quant_table_id, ::g->quant_table_id.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_SOF0* JPEG_SOF0::generate() {
	if (generated == 1) {
		JPEG_SOF0* new_instance = new JPEG_SOF0(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xC0 }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(precision, ::g->precision.generate({ 8 }));
	GENERATE_VAR(image_height, ::g->image_height.generate());
	GENERATE_VAR(image_width, ::g->image_width.generate());
	GENERATE_VAR(num_components, ::g->num_components_.generate({ 1, 3 }));
	nc = num_components();
	if ((nc > 4)) {
	nc = 4;
	};
	for (i = 0; (i < nc); i++) {
			GENERATE_VAR(comp, ::g->comp.generate());
	;
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_DRI* JPEG_DRI::generate() {
	if (generated == 1) {
		JPEG_DRI* new_instance = new JPEG_DRI(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xDD }));
	GENERATE_VAR(length, ::g->length.generate({ 4 }));
	GENERATE_VAR(restart_interval, ::g->restart_interval.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_COM* JPEG_COM::generate() {
	if (generated == 1) {
		JPEG_COM* new_instance = new JPEG_COM(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xFE }));
	GENERATE_VAR(length, ::g->length.generate());
	comment_size = (length() - 2);
	if (((comment_size > 0) && (comment_size < 65534))) {
		GENERATE_VAR(comment_data, ::g->comment_data.generate(comment_size));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SOS_COMPONENT* SOS_COMPONENT::generate() {
	if (generated == 1) {
		SOS_COMPONENT* new_instance = new SOS_COMPONENT(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(component_selector, ::g->component_selector.generate());
	GENERATE_VAR(table_selectors, ::g->table_selectors.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_SOS* JPEG_SOS::generate() {
	if (generated == 1) {
		JPEG_SOS* new_instance = new JPEG_SOS(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xDA }));
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(num_components, ::g->num_components_.generate());
	nc = num_components();
	if ((nc > 4)) {
	nc = 4;
	};
	for (i = 0; (i < nc); i++) {
			GENERATE_VAR(comp, ::g->comp_.generate());
	;
	};
	GENERATE_VAR(start_spectral, ::g->start_spectral.generate({ 0 }));
	GENERATE_VAR(end_spectral, ::g->end_spectral.generate({ 63 }));
	GENERATE_VAR(approx_bits, ::g->approx_bits.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_SCAN_DATA* JPEG_SCAN_DATA::generate() {
	if (generated == 1) {
		JPEG_SCAN_DATA* new_instance = new JPEG_SCAN_DATA(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(scan_data, ::g->scan_data.generate(64));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JPEG_EOI* JPEG_EOI::generate() {
	if (generated == 1) {
		JPEG_EOI* new_instance = new JPEG_EOI(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(marker1, ::g->marker1.generate({ 0xFF }));
	GENERATE_VAR(marker2, ::g->marker2.generate({ 0xD9 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


jpeg_file* jpeg_file::generate() {
	if (generated == 1) {
		jpeg_file* new_instance = new jpeg_file(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(soi, ::g->soi.generate());
	tag.resize(2);
	all_choices = { "\xFF\xE0", "\xFF\xE1", "\xFF\xE2", "\xFF\xED", "\xFF\xEE", "\xFF\xDB", "\xFF\xC4", "\xFF\xC0", "\xFF\xDD", "\xFF\xFE" };
	preferred = { "\xFF\xE0", "\xFF\xDB", "\xFF\xC0" };
	while (ReadBytes(tag, FTell(), 2, preferred, all_choices)) {
		switch (STR2INT(tag)) {
		case STR2INT("\xFF\xE0"):
			GENERATE_VAR(app0, ::g->app0.generate());
			VectorRemove(all_choices, { "\xFF\xE0" });
			VectorRemove(preferred, { "\xFF\xE0" });
			break;
		case STR2INT("\xFF\xE1"):
			GENERATE_VAR(app1_exif, ::g->app1_exif.generate());
			VectorRemove(all_choices, { "\xFF\xE1" });
			VectorRemove(preferred, { "\xFF\xE1" });
			break;
		case STR2INT("\xFF\xE2"):
			GENERATE_VAR(app2_icc, ::g->app2_icc.generate());
			VectorRemove(all_choices, { "\xFF\xE2" });
			VectorRemove(preferred, { "\xFF\xE2" });
			break;
		case STR2INT("\xFF\xED"):
			GENERATE_VAR(app13, ::g->app13.generate());
			VectorRemove(all_choices, { "\xFF\xED" });
			VectorRemove(preferred, { "\xFF\xED" });
			break;
		case STR2INT("\xFF\xEE"):
			GENERATE_VAR(app14, ::g->app14.generate());
			VectorRemove(all_choices, { "\xFF\xEE" });
			VectorRemove(preferred, { "\xFF\xEE" });
			break;
		case STR2INT("\xFF\xDB"):
			GENERATE_VAR(dqt, ::g->dqt.generate());
			VectorRemove(all_choices, { "\xFF\xDB" });
			VectorRemove(preferred, { "\xFF\xDB" });
			break;
		case STR2INT("\xFF\xC4"):
			GENERATE_VAR(dht, ::g->dht.generate());
			VectorRemove(all_choices, { "\xFF\xC4" });
			VectorRemove(preferred, { "\xFF\xC4" });
			break;
		case STR2INT("\xFF\xC0"):
			GENERATE_VAR(sof0, ::g->sof0.generate());
			VectorRemove(all_choices, { "\xFF\xC0" });
			VectorRemove(preferred, { "\xFF\xC0" });
			break;
		case STR2INT("\xFF\xDD"):
			GENERATE_VAR(dri, ::g->dri.generate());
			VectorRemove(all_choices, { "\xFF\xDD" });
			VectorRemove(preferred, { "\xFF\xDD" });
			break;
		case STR2INT("\xFF\xFE"):
			GENERATE_VAR(com, ::g->com.generate());
			VectorRemove(all_choices, { "\xFF\xFE" });
			VectorRemove(preferred, { "\xFF\xFE" });
			break;
		default:
			break;
		};
	};
	GENERATE_VAR(sos, ::g->sos.generate());
	GENERATE_VAR(scan, ::g->scan.generate());
	GENERATE_VAR(eoi, ::g->eoi.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}



void generate_file() {
	::g = new globals_class();

	BigEndian();
	GENERATE(file, ::g->file.generate());

	file_acc.finish();
	delete_globals();
}

void delete_globals() { delete ::g; }

