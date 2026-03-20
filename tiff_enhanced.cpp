#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"


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

	uint16 tag_var;
	uint16 field_type_var;
	uint32 count_var;
	uint32 value_offset_var;

public:
	bool tag_exists = false;
	bool field_type_exists = false;
	bool count_exists = false;
	bool value_offset_exists = false;

	uint16& tag() {
		assert_cond(tag_exists, "struct field tag does not exist");
		return tag_var;
	}
	uint16& field_type() {
		assert_cond(field_type_exists, "struct field field_type does not exist");
		return field_type_var;
	}
	uint32& count() {
		assert_cond(count_exists, "struct field count does not exist");
		return count_var;
	}
	uint32& value_offset() {
		assert_cond(value_offset_exists, "struct field value_offset does not exist");
		return value_offset_var;
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



class tiff_file {
	std::vector<tiff_file*>& instances;

	std::string byte_order_var;
	uint16 magic_var;
	uint32 ifd_offset_var;
	uint16 entry_count_var;
	uint16 t_width_tag_var;
	uint16 t_width_type_var;
	uint32 t_width_count_var;
	uint32 t_width_value_var;
	uint16 t_height_tag_var;
	uint16 t_height_type_var;
	uint32 t_height_count_var;
	uint32 t_height_value_var;
	uint16 t_bps_tag_var;
	uint16 t_bps_type_var;
	uint32 t_bps_count_var;
	uint32 t_bps_value_var;
	uint16 t_comp_tag_var;
	uint16 t_comp_type_var;
	uint32 t_comp_count_var;
	uint32 t_comp_value_var;
	uint16 t_photo_tag_var;
	uint16 t_photo_type_var;
	uint32 t_photo_count_var;
	uint32 t_photo_value_var;
	uint16 t_soff_tag_var;
	uint16 t_soff_type_var;
	uint32 t_soff_count_var;
	uint32 t_soff_value_var;
	uint16 t_spp_tag_var;
	uint16 t_spp_type_var;
	uint32 t_spp_count_var;
	uint32 t_spp_value_var;
	uint16 t_rps_tag_var;
	uint16 t_rps_type_var;
	uint32 t_rps_count_var;
	uint32 t_rps_value_var;
	uint16 t_sbc_tag_var;
	uint16 t_sbc_type_var;
	uint32 t_sbc_count_var;
	uint32 t_sbc_value_var;
	uint16 t_xres_tag_var;
	uint16 t_xres_type_var;
	uint32 t_xres_count_var;
	uint32 t_xres_offset_var;
	uint16 t_yres_tag_var;
	uint16 t_yres_type_var;
	uint32 t_yres_count_var;
	uint32 t_yres_offset_var;
	uint16 t_ru_tag_var;
	uint16 t_ru_type_var;
	uint32 t_ru_count_var;
	uint32 t_ru_value_var;
	TIFF_IFD_ENTRY* extra_entry_var;
	uint32 next_ifd_var;
	uint32 xres_num_var;
	uint32 xres_den_var;
	uint32 yres_num_var;
	uint32 yres_den_var;
	std::vector<ubyte> strip_data_var;

public:
	bool byte_order_exists = false;
	bool magic_exists = false;
	bool ifd_offset_exists = false;
	bool entry_count_exists = false;
	bool t_width_tag_exists = false;
	bool t_width_type_exists = false;
	bool t_width_count_exists = false;
	bool t_width_value_exists = false;
	bool t_height_tag_exists = false;
	bool t_height_type_exists = false;
	bool t_height_count_exists = false;
	bool t_height_value_exists = false;
	bool t_bps_tag_exists = false;
	bool t_bps_type_exists = false;
	bool t_bps_count_exists = false;
	bool t_bps_value_exists = false;
	bool t_comp_tag_exists = false;
	bool t_comp_type_exists = false;
	bool t_comp_count_exists = false;
	bool t_comp_value_exists = false;
	bool t_photo_tag_exists = false;
	bool t_photo_type_exists = false;
	bool t_photo_count_exists = false;
	bool t_photo_value_exists = false;
	bool t_soff_tag_exists = false;
	bool t_soff_type_exists = false;
	bool t_soff_count_exists = false;
	bool t_soff_value_exists = false;
	bool t_spp_tag_exists = false;
	bool t_spp_type_exists = false;
	bool t_spp_count_exists = false;
	bool t_spp_value_exists = false;
	bool t_rps_tag_exists = false;
	bool t_rps_type_exists = false;
	bool t_rps_count_exists = false;
	bool t_rps_value_exists = false;
	bool t_sbc_tag_exists = false;
	bool t_sbc_type_exists = false;
	bool t_sbc_count_exists = false;
	bool t_sbc_value_exists = false;
	bool t_xres_tag_exists = false;
	bool t_xres_type_exists = false;
	bool t_xres_count_exists = false;
	bool t_xres_offset_exists = false;
	bool t_yres_tag_exists = false;
	bool t_yres_type_exists = false;
	bool t_yres_count_exists = false;
	bool t_yres_offset_exists = false;
	bool t_ru_tag_exists = false;
	bool t_ru_type_exists = false;
	bool t_ru_count_exists = false;
	bool t_ru_value_exists = false;
	bool extra_entry_exists = false;
	bool next_ifd_exists = false;
	bool xres_num_exists = false;
	bool xres_den_exists = false;
	bool yres_num_exists = false;
	bool yres_den_exists = false;
	bool strip_data_exists = false;

	std::string& byte_order() {
		assert_cond(byte_order_exists, "struct field byte_order does not exist");
		return byte_order_var;
	}
	uint16& magic() {
		assert_cond(magic_exists, "struct field magic does not exist");
		return magic_var;
	}
	uint32& ifd_offset() {
		assert_cond(ifd_offset_exists, "struct field ifd_offset does not exist");
		return ifd_offset_var;
	}
	uint16& entry_count() {
		assert_cond(entry_count_exists, "struct field entry_count does not exist");
		return entry_count_var;
	}
	uint16& t_width_tag() {
		assert_cond(t_width_tag_exists, "struct field t_width_tag does not exist");
		return t_width_tag_var;
	}
	uint16& t_width_type() {
		assert_cond(t_width_type_exists, "struct field t_width_type does not exist");
		return t_width_type_var;
	}
	uint32& t_width_count() {
		assert_cond(t_width_count_exists, "struct field t_width_count does not exist");
		return t_width_count_var;
	}
	uint32& t_width_value() {
		assert_cond(t_width_value_exists, "struct field t_width_value does not exist");
		return t_width_value_var;
	}
	uint16& t_height_tag() {
		assert_cond(t_height_tag_exists, "struct field t_height_tag does not exist");
		return t_height_tag_var;
	}
	uint16& t_height_type() {
		assert_cond(t_height_type_exists, "struct field t_height_type does not exist");
		return t_height_type_var;
	}
	uint32& t_height_count() {
		assert_cond(t_height_count_exists, "struct field t_height_count does not exist");
		return t_height_count_var;
	}
	uint32& t_height_value() {
		assert_cond(t_height_value_exists, "struct field t_height_value does not exist");
		return t_height_value_var;
	}
	uint16& t_bps_tag() {
		assert_cond(t_bps_tag_exists, "struct field t_bps_tag does not exist");
		return t_bps_tag_var;
	}
	uint16& t_bps_type() {
		assert_cond(t_bps_type_exists, "struct field t_bps_type does not exist");
		return t_bps_type_var;
	}
	uint32& t_bps_count() {
		assert_cond(t_bps_count_exists, "struct field t_bps_count does not exist");
		return t_bps_count_var;
	}
	uint32& t_bps_value() {
		assert_cond(t_bps_value_exists, "struct field t_bps_value does not exist");
		return t_bps_value_var;
	}
	uint16& t_comp_tag() {
		assert_cond(t_comp_tag_exists, "struct field t_comp_tag does not exist");
		return t_comp_tag_var;
	}
	uint16& t_comp_type() {
		assert_cond(t_comp_type_exists, "struct field t_comp_type does not exist");
		return t_comp_type_var;
	}
	uint32& t_comp_count() {
		assert_cond(t_comp_count_exists, "struct field t_comp_count does not exist");
		return t_comp_count_var;
	}
	uint32& t_comp_value() {
		assert_cond(t_comp_value_exists, "struct field t_comp_value does not exist");
		return t_comp_value_var;
	}
	uint16& t_photo_tag() {
		assert_cond(t_photo_tag_exists, "struct field t_photo_tag does not exist");
		return t_photo_tag_var;
	}
	uint16& t_photo_type() {
		assert_cond(t_photo_type_exists, "struct field t_photo_type does not exist");
		return t_photo_type_var;
	}
	uint32& t_photo_count() {
		assert_cond(t_photo_count_exists, "struct field t_photo_count does not exist");
		return t_photo_count_var;
	}
	uint32& t_photo_value() {
		assert_cond(t_photo_value_exists, "struct field t_photo_value does not exist");
		return t_photo_value_var;
	}
	uint16& t_soff_tag() {
		assert_cond(t_soff_tag_exists, "struct field t_soff_tag does not exist");
		return t_soff_tag_var;
	}
	uint16& t_soff_type() {
		assert_cond(t_soff_type_exists, "struct field t_soff_type does not exist");
		return t_soff_type_var;
	}
	uint32& t_soff_count() {
		assert_cond(t_soff_count_exists, "struct field t_soff_count does not exist");
		return t_soff_count_var;
	}
	uint32& t_soff_value() {
		assert_cond(t_soff_value_exists, "struct field t_soff_value does not exist");
		return t_soff_value_var;
	}
	uint16& t_spp_tag() {
		assert_cond(t_spp_tag_exists, "struct field t_spp_tag does not exist");
		return t_spp_tag_var;
	}
	uint16& t_spp_type() {
		assert_cond(t_spp_type_exists, "struct field t_spp_type does not exist");
		return t_spp_type_var;
	}
	uint32& t_spp_count() {
		assert_cond(t_spp_count_exists, "struct field t_spp_count does not exist");
		return t_spp_count_var;
	}
	uint32& t_spp_value() {
		assert_cond(t_spp_value_exists, "struct field t_spp_value does not exist");
		return t_spp_value_var;
	}
	uint16& t_rps_tag() {
		assert_cond(t_rps_tag_exists, "struct field t_rps_tag does not exist");
		return t_rps_tag_var;
	}
	uint16& t_rps_type() {
		assert_cond(t_rps_type_exists, "struct field t_rps_type does not exist");
		return t_rps_type_var;
	}
	uint32& t_rps_count() {
		assert_cond(t_rps_count_exists, "struct field t_rps_count does not exist");
		return t_rps_count_var;
	}
	uint32& t_rps_value() {
		assert_cond(t_rps_value_exists, "struct field t_rps_value does not exist");
		return t_rps_value_var;
	}
	uint16& t_sbc_tag() {
		assert_cond(t_sbc_tag_exists, "struct field t_sbc_tag does not exist");
		return t_sbc_tag_var;
	}
	uint16& t_sbc_type() {
		assert_cond(t_sbc_type_exists, "struct field t_sbc_type does not exist");
		return t_sbc_type_var;
	}
	uint32& t_sbc_count() {
		assert_cond(t_sbc_count_exists, "struct field t_sbc_count does not exist");
		return t_sbc_count_var;
	}
	uint32& t_sbc_value() {
		assert_cond(t_sbc_value_exists, "struct field t_sbc_value does not exist");
		return t_sbc_value_var;
	}
	uint16& t_xres_tag() {
		assert_cond(t_xres_tag_exists, "struct field t_xres_tag does not exist");
		return t_xres_tag_var;
	}
	uint16& t_xres_type() {
		assert_cond(t_xres_type_exists, "struct field t_xres_type does not exist");
		return t_xres_type_var;
	}
	uint32& t_xres_count() {
		assert_cond(t_xres_count_exists, "struct field t_xres_count does not exist");
		return t_xres_count_var;
	}
	uint32& t_xres_offset() {
		assert_cond(t_xres_offset_exists, "struct field t_xres_offset does not exist");
		return t_xres_offset_var;
	}
	uint16& t_yres_tag() {
		assert_cond(t_yres_tag_exists, "struct field t_yres_tag does not exist");
		return t_yres_tag_var;
	}
	uint16& t_yres_type() {
		assert_cond(t_yres_type_exists, "struct field t_yres_type does not exist");
		return t_yres_type_var;
	}
	uint32& t_yres_count() {
		assert_cond(t_yres_count_exists, "struct field t_yres_count does not exist");
		return t_yres_count_var;
	}
	uint32& t_yres_offset() {
		assert_cond(t_yres_offset_exists, "struct field t_yres_offset does not exist");
		return t_yres_offset_var;
	}
	uint16& t_ru_tag() {
		assert_cond(t_ru_tag_exists, "struct field t_ru_tag does not exist");
		return t_ru_tag_var;
	}
	uint16& t_ru_type() {
		assert_cond(t_ru_type_exists, "struct field t_ru_type does not exist");
		return t_ru_type_var;
	}
	uint32& t_ru_count() {
		assert_cond(t_ru_count_exists, "struct field t_ru_count does not exist");
		return t_ru_count_var;
	}
	uint32& t_ru_value() {
		assert_cond(t_ru_value_exists, "struct field t_ru_value does not exist");
		return t_ru_value_var;
	}
	TIFF_IFD_ENTRY& extra_entry() {
		assert_cond(extra_entry_exists, "struct field extra_entry does not exist");
		return *extra_entry_var;
	}
	uint32& next_ifd() {
		assert_cond(next_ifd_exists, "struct field next_ifd does not exist");
		return next_ifd_var;
	}
	uint32& xres_num() {
		assert_cond(xres_num_exists, "struct field xres_num does not exist");
		return xres_num_var;
	}
	uint32& xres_den() {
		assert_cond(xres_den_exists, "struct field xres_den does not exist");
		return xres_den_var;
	}
	uint32& yres_num() {
		assert_cond(yres_num_exists, "struct field yres_num does not exist");
		return yres_num_var;
	}
	uint32& yres_den() {
		assert_cond(yres_den_exists, "struct field yres_den does not exist");
		return yres_den_var;
	}
	std::vector<ubyte>& strip_data() {
		assert_cond(strip_data_exists, "struct field strip_data does not exist");
		return strip_data_var;
	}

	/* locals */
	int i;
	int real_count;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	tiff_file& operator () () { return *instances.back(); }
	tiff_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	tiff_file(std::vector<tiff_file*>& instances) : instances(instances) { instances.push_back(this); }
	~tiff_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			tiff_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	tiff_file* generate();
};

int tiff_file::_parent_id = 0;
int tiff_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "II", "MM" };


std::vector<TIFF_IFD_ENTRY*> TIFF_IFD_ENTRY_extra_entry_instances;
std::vector<tiff_file*> tiff_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "byte_order", "char_array_class" }, { "magic", "uint16_class" }, { "ifd_offset", "uint32_class" }, { "entry_count", "uint16_class" }, { "t_width_tag", "uint16_class" }, { "t_width_type", "uint16_class" }, { "t_width_count", "uint32_class" }, { "t_width_value", "uint32_class" }, { "t_height_tag", "uint16_class" }, { "t_height_type", "uint16_class" }, { "t_height_count", "uint32_class" }, { "t_height_value", "uint32_class" }, { "t_bps_tag", "uint16_class" }, { "t_bps_type", "uint16_class" }, { "t_bps_count", "uint32_class" }, { "t_bps_value", "uint32_class" }, { "t_comp_tag", "uint16_class" }, { "t_comp_type", "uint16_class" }, { "t_comp_count", "uint32_class" }, { "t_comp_value", "uint32_class" }, { "t_photo_tag", "uint16_class" }, { "t_photo_type", "uint16_class" }, { "t_photo_count", "uint32_class" }, { "t_photo_value", "uint32_class" }, { "t_soff_tag", "uint16_class" }, { "t_soff_type", "uint16_class" }, { "t_soff_count", "uint32_class" }, { "t_soff_value", "uint32_class" }, { "t_spp_tag", "uint16_class" }, { "t_spp_type", "uint16_class" }, { "t_spp_count", "uint32_class" }, { "t_spp_value", "uint32_class" }, { "t_rps_tag", "uint16_class" }, { "t_rps_type", "uint16_class" }, { "t_rps_count", "uint32_class" }, { "t_rps_value", "uint32_class" }, { "t_sbc_tag", "uint16_class" }, { "t_sbc_type", "uint16_class" }, { "t_sbc_count", "uint32_class" }, { "t_sbc_value", "uint32_class" }, { "t_xres_tag", "uint16_class" }, { "t_xres_type", "uint16_class" }, { "t_xres_count", "uint32_class" }, { "t_xres_offset", "uint32_class" }, { "t_yres_tag", "uint16_class" }, { "t_yres_type", "uint16_class" }, { "t_yres_count", "uint32_class" }, { "t_yres_offset", "uint32_class" }, { "t_ru_tag", "uint16_class" }, { "t_ru_type", "uint16_class" }, { "t_ru_count", "uint32_class" }, { "t_ru_value", "uint32_class" }, { "tag", "uint16_class" }, { "field_type", "uint16_class" }, { "count", "uint32_class" }, { "value_offset", "uint32_class" }, { "extra_entry", "TIFF_IFD_ENTRY" }, { "next_ifd", "uint32_class" }, { "xres_num", "uint32_class" }, { "xres_den", "uint32_class" }, { "yres_num", "uint32_class" }, { "yres_den", "uint32_class" }, { "strip_data", "ubyte_array_class" }, { "file", "tiff_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 4, 16 }, { 1, 1024 }, { 1, 1024 }, { 1, 12 }, { 1, 256 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class byte_order_element;
	char_array_class byte_order;
	uint16_class magic;
	uint32_class ifd_offset;
	uint16_class entry_count;
	uint16_class t_width_tag;
	uint16_class t_width_type;
	uint32_class t_width_count;
	uint32_class t_width_value;
	uint16_class t_height_tag;
	uint16_class t_height_type;
	uint32_class t_height_count;
	uint32_class t_height_value;
	uint16_class t_bps_tag;
	uint16_class t_bps_type;
	uint32_class t_bps_count;
	uint32_class t_bps_value;
	uint16_class t_comp_tag;
	uint16_class t_comp_type;
	uint32_class t_comp_count;
	uint32_class t_comp_value;
	uint16_class t_photo_tag;
	uint16_class t_photo_type;
	uint32_class t_photo_count;
	uint32_class t_photo_value;
	uint16_class t_soff_tag;
	uint16_class t_soff_type;
	uint32_class t_soff_count;
	uint32_class t_soff_value;
	uint16_class t_spp_tag;
	uint16_class t_spp_type;
	uint32_class t_spp_count;
	uint32_class t_spp_value;
	uint16_class t_rps_tag;
	uint16_class t_rps_type;
	uint32_class t_rps_count;
	uint32_class t_rps_value;
	uint16_class t_sbc_tag;
	uint16_class t_sbc_type;
	uint32_class t_sbc_count;
	uint32_class t_sbc_value;
	uint16_class t_xres_tag;
	uint16_class t_xres_type;
	uint32_class t_xres_count;
	uint32_class t_xres_offset;
	uint16_class t_yres_tag;
	uint16_class t_yres_type;
	uint32_class t_yres_count;
	uint32_class t_yres_offset;
	uint16_class t_ru_tag;
	uint16_class t_ru_type;
	uint32_class t_ru_count;
	uint32_class t_ru_value;
	uint16_class tag;
	uint16_class field_type;
	uint32_class count;
	uint32_class value_offset;
	TIFF_IFD_ENTRY extra_entry;
	uint32_class next_ifd;
	uint32_class xres_num;
	uint32_class xres_den;
	uint32_class yres_num;
	uint32_class yres_den;
	ubyte_class strip_data_element;
	ubyte_array_class strip_data;
	tiff_file file;


	globals_class() :
		byte_order_element(false),
		byte_order(byte_order_element),
		magic(1),
		ifd_offset(1),
		entry_count(3),
		t_width_tag(1),
		t_width_type(1),
		t_width_count(1),
		t_width_value(4),
		t_height_tag(1),
		t_height_type(1),
		t_height_count(1),
		t_height_value(5),
		t_bps_tag(1),
		t_bps_type(1),
		t_bps_count(1),
		t_bps_value(1),
		t_comp_tag(1),
		t_comp_type(1),
		t_comp_count(1),
		t_comp_value(1),
		t_photo_tag(1),
		t_photo_type(1),
		t_photo_count(1),
		t_photo_value(1),
		t_soff_tag(1),
		t_soff_type(1),
		t_soff_count(1),
		t_soff_value(1),
		t_spp_tag(1),
		t_spp_type(1),
		t_spp_count(1),
		t_spp_value(1),
		t_rps_tag(1),
		t_rps_type(1),
		t_rps_count(1),
		t_rps_value(1),
		t_sbc_tag(1),
		t_sbc_type(1),
		t_sbc_count(1),
		t_sbc_value(1),
		t_xres_tag(1),
		t_xres_type(1),
		t_xres_count(1),
		t_xres_offset(1),
		t_yres_tag(1),
		t_yres_type(1),
		t_yres_count(1),
		t_yres_offset(1),
		t_ru_tag(1),
		t_ru_type(1),
		t_ru_count(1),
		t_ru_value(1),
		tag(1),
		field_type(6),
		count(7),
		value_offset(1),
		extra_entry(TIFF_IFD_ENTRY_extra_entry_instances),
		next_ifd(1),
		xres_num(1),
		xres_den(1),
		yres_num(1),
		yres_den(1),
		strip_data_element(false),
		strip_data(strip_data_element),
		file(tiff_file_file_instances)
	{}
};

globals_class* g;


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

	GENERATE_VAR(tag, ::g->tag.generate());
	GENERATE_VAR(field_type, ::g->field_type.generate());
	GENERATE_VAR(count, ::g->count.generate());
	GENERATE_VAR(value_offset, ::g->value_offset.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


tiff_file* tiff_file::generate() {
	if (generated == 1) {
		tiff_file* new_instance = new tiff_file(instances);
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

	GENERATE_VAR(byte_order, ::g->byte_order.generate(2, { "II" }));
	GENERATE_VAR(magic, ::g->magic.generate({ 42 }));
	GENERATE_VAR(ifd_offset, ::g->ifd_offset.generate({ 8 }));
	GENERATE_VAR(entry_count, ::g->entry_count.generate());
	real_count = entry_count();
	if ((real_count > 16)) {
	real_count = 16;
	};
	GENERATE_VAR(t_width_tag, ::g->t_width_tag.generate({ 256 }));
	GENERATE_VAR(t_width_type, ::g->t_width_type.generate({ 3 }));
	GENERATE_VAR(t_width_count, ::g->t_width_count.generate({ 1 }));
	GENERATE_VAR(t_width_value, ::g->t_width_value.generate());
	GENERATE_VAR(t_height_tag, ::g->t_height_tag.generate({ 257 }));
	GENERATE_VAR(t_height_type, ::g->t_height_type.generate({ 3 }));
	GENERATE_VAR(t_height_count, ::g->t_height_count.generate({ 1 }));
	GENERATE_VAR(t_height_value, ::g->t_height_value.generate());
	GENERATE_VAR(t_bps_tag, ::g->t_bps_tag.generate({ 258 }));
	GENERATE_VAR(t_bps_type, ::g->t_bps_type.generate({ 3 }));
	GENERATE_VAR(t_bps_count, ::g->t_bps_count.generate({ 1 }));
	GENERATE_VAR(t_bps_value, ::g->t_bps_value.generate({ 1, 4, 8, 16 }));
	GENERATE_VAR(t_comp_tag, ::g->t_comp_tag.generate({ 259 }));
	GENERATE_VAR(t_comp_type, ::g->t_comp_type.generate({ 3 }));
	GENERATE_VAR(t_comp_count, ::g->t_comp_count.generate({ 1 }));
	GENERATE_VAR(t_comp_value, ::g->t_comp_value.generate({ 1, 5, 6, 7, 8, 32773 }));
	GENERATE_VAR(t_photo_tag, ::g->t_photo_tag.generate({ 262 }));
	GENERATE_VAR(t_photo_type, ::g->t_photo_type.generate({ 3 }));
	GENERATE_VAR(t_photo_count, ::g->t_photo_count.generate({ 1 }));
	GENERATE_VAR(t_photo_value, ::g->t_photo_value.generate({ 0, 1, 2, 3, 5, 6, 8 }));
	GENERATE_VAR(t_soff_tag, ::g->t_soff_tag.generate({ 273 }));
	GENERATE_VAR(t_soff_type, ::g->t_soff_type.generate({ 4 }));
	GENERATE_VAR(t_soff_count, ::g->t_soff_count.generate({ 1 }));
	GENERATE_VAR(t_soff_value, ::g->t_soff_value.generate());
	GENERATE_VAR(t_spp_tag, ::g->t_spp_tag.generate({ 277 }));
	GENERATE_VAR(t_spp_type, ::g->t_spp_type.generate({ 3 }));
	GENERATE_VAR(t_spp_count, ::g->t_spp_count.generate({ 1 }));
	GENERATE_VAR(t_spp_value, ::g->t_spp_value.generate({ 1, 3, 4 }));
	GENERATE_VAR(t_rps_tag, ::g->t_rps_tag.generate({ 278 }));
	GENERATE_VAR(t_rps_type, ::g->t_rps_type.generate({ 3 }));
	GENERATE_VAR(t_rps_count, ::g->t_rps_count.generate({ 1 }));
	GENERATE_VAR(t_rps_value, ::g->t_rps_value.generate());
	GENERATE_VAR(t_sbc_tag, ::g->t_sbc_tag.generate({ 279 }));
	GENERATE_VAR(t_sbc_type, ::g->t_sbc_type.generate({ 4 }));
	GENERATE_VAR(t_sbc_count, ::g->t_sbc_count.generate({ 1 }));
	GENERATE_VAR(t_sbc_value, ::g->t_sbc_value.generate());
	GENERATE_VAR(t_xres_tag, ::g->t_xres_tag.generate({ 282 }));
	GENERATE_VAR(t_xres_type, ::g->t_xres_type.generate({ 5 }));
	GENERATE_VAR(t_xres_count, ::g->t_xres_count.generate({ 1 }));
	GENERATE_VAR(t_xres_offset, ::g->t_xres_offset.generate());
	GENERATE_VAR(t_yres_tag, ::g->t_yres_tag.generate({ 283 }));
	GENERATE_VAR(t_yres_type, ::g->t_yres_type.generate({ 5 }));
	GENERATE_VAR(t_yres_count, ::g->t_yres_count.generate({ 1 }));
	GENERATE_VAR(t_yres_offset, ::g->t_yres_offset.generate());
	GENERATE_VAR(t_ru_tag, ::g->t_ru_tag.generate({ 296 }));
	GENERATE_VAR(t_ru_type, ::g->t_ru_type.generate({ 3 }));
	GENERATE_VAR(t_ru_count, ::g->t_ru_count.generate({ 1 }));
	GENERATE_VAR(t_ru_value, ::g->t_ru_value.generate({ 1, 2, 3 }));
	for (i = 0; (i < (real_count - 12)); i++) {
			GENERATE_VAR(extra_entry, ::g->extra_entry.generate());
	;
	};
	GENERATE_VAR(next_ifd, ::g->next_ifd.generate({ 0 }));
	GENERATE_VAR(xres_num, ::g->xres_num.generate({ 72 }));
	GENERATE_VAR(xres_den, ::g->xres_den.generate({ 1 }));
	GENERATE_VAR(yres_num, ::g->yres_num.generate({ 72 }));
	GENERATE_VAR(yres_den, ::g->yres_den.generate({ 1 }));
	GENERATE_VAR(strip_data, ::g->strip_data.generate(64));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}



void generate_file() {
	::g = new globals_class();

	LittleEndian();
	GENERATE(file, ::g->file.generate());

	file_acc.finish();
	delete_globals();
}

void delete_globals() { delete ::g; }

