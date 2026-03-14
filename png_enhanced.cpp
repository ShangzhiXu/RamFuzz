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



class PNG_SIGNATURE {
	std::vector<PNG_SIGNATURE*>& instances;

	ubyte s0_var;
	ubyte s1_var;
	ubyte s2_var;
	ubyte s3_var;
	ubyte s4_var;
	ubyte s5_var;
	ubyte s6_var;
	ubyte s7_var;

public:
	bool s0_exists = false;
	bool s1_exists = false;
	bool s2_exists = false;
	bool s3_exists = false;
	bool s4_exists = false;
	bool s5_exists = false;
	bool s6_exists = false;
	bool s7_exists = false;

	ubyte& s0() {
		assert_cond(s0_exists, "struct field s0 does not exist");
		return s0_var;
	}
	ubyte& s1() {
		assert_cond(s1_exists, "struct field s1 does not exist");
		return s1_var;
	}
	ubyte& s2() {
		assert_cond(s2_exists, "struct field s2 does not exist");
		return s2_var;
	}
	ubyte& s3() {
		assert_cond(s3_exists, "struct field s3 does not exist");
		return s3_var;
	}
	ubyte& s4() {
		assert_cond(s4_exists, "struct field s4 does not exist");
		return s4_var;
	}
	ubyte& s5() {
		assert_cond(s5_exists, "struct field s5 does not exist");
		return s5_var;
	}
	ubyte& s6() {
		assert_cond(s6_exists, "struct field s6 does not exist");
		return s6_var;
	}
	ubyte& s7() {
		assert_cond(s7_exists, "struct field s7 does not exist");
		return s7_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PNG_SIGNATURE& operator () () { return *instances.back(); }
	PNG_SIGNATURE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PNG_SIGNATURE(std::vector<PNG_SIGNATURE*>& instances) : instances(instances) { instances.push_back(this); }
	~PNG_SIGNATURE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PNG_SIGNATURE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PNG_SIGNATURE* generate();
};

int PNG_SIGNATURE::_parent_id = 0;
int PNG_SIGNATURE::_index_start = 0;



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



class CHUNK_IHDR {
	std::vector<CHUNK_IHDR*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 width_var;
	uint32 height_var;
	ubyte bit_depth_var;
	ubyte color_type_var;
	ubyte compression_method_var;
	ubyte filter_method_var;
	ubyte interlace_method_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool width_exists = false;
	bool height_exists = false;
	bool bit_depth_exists = false;
	bool color_type_exists = false;
	bool compression_method_exists = false;
	bool filter_method_exists = false;
	bool interlace_method_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& width() {
		assert_cond(width_exists, "struct field width does not exist");
		return width_var;
	}
	uint32& height() {
		assert_cond(height_exists, "struct field height does not exist");
		return height_var;
	}
	ubyte& bit_depth() {
		assert_cond(bit_depth_exists, "struct field bit_depth does not exist");
		return bit_depth_var;
	}
	ubyte& color_type() {
		assert_cond(color_type_exists, "struct field color_type does not exist");
		return color_type_var;
	}
	ubyte& compression_method() {
		assert_cond(compression_method_exists, "struct field compression_method does not exist");
		return compression_method_var;
	}
	ubyte& filter_method() {
		assert_cond(filter_method_exists, "struct field filter_method does not exist");
		return filter_method_var;
	}
	ubyte& interlace_method() {
		assert_cond(interlace_method_exists, "struct field interlace_method does not exist");
		return interlace_method_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_IHDR& operator () () { return *instances.back(); }
	CHUNK_IHDR& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_IHDR(std::vector<CHUNK_IHDR*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_IHDR() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_IHDR* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_IHDR* generate();
};

int CHUNK_IHDR::_parent_id = 0;
int CHUNK_IHDR::_index_start = 0;



class CHUNK_sRGB {
	std::vector<CHUNK_sRGB*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	ubyte rendering_intent_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool rendering_intent_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	ubyte& rendering_intent() {
		assert_cond(rendering_intent_exists, "struct field rendering_intent does not exist");
		return rendering_intent_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_sRGB& operator () () { return *instances.back(); }
	CHUNK_sRGB& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_sRGB(std::vector<CHUNK_sRGB*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_sRGB() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_sRGB* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_sRGB* generate();
};

int CHUNK_sRGB::_parent_id = 0;
int CHUNK_sRGB::_index_start = 0;



class CHUNK_gAMA {
	std::vector<CHUNK_gAMA*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 gamma_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool gamma_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& gamma() {
		assert_cond(gamma_exists, "struct field gamma does not exist");
		return gamma_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_gAMA& operator () () { return *instances.back(); }
	CHUNK_gAMA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_gAMA(std::vector<CHUNK_gAMA*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_gAMA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_gAMA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_gAMA* generate();
};

int CHUNK_gAMA::_parent_id = 0;
int CHUNK_gAMA::_index_start = 0;



class CHUNK_cHRM {
	std::vector<CHUNK_cHRM*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 white_point_x_var;
	uint32 white_point_y_var;
	uint32 red_x_var;
	uint32 red_y_var;
	uint32 green_x_var;
	uint32 green_y_var;
	uint32 blue_x_var;
	uint32 blue_y_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool white_point_x_exists = false;
	bool white_point_y_exists = false;
	bool red_x_exists = false;
	bool red_y_exists = false;
	bool green_x_exists = false;
	bool green_y_exists = false;
	bool blue_x_exists = false;
	bool blue_y_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& white_point_x() {
		assert_cond(white_point_x_exists, "struct field white_point_x does not exist");
		return white_point_x_var;
	}
	uint32& white_point_y() {
		assert_cond(white_point_y_exists, "struct field white_point_y does not exist");
		return white_point_y_var;
	}
	uint32& red_x() {
		assert_cond(red_x_exists, "struct field red_x does not exist");
		return red_x_var;
	}
	uint32& red_y() {
		assert_cond(red_y_exists, "struct field red_y does not exist");
		return red_y_var;
	}
	uint32& green_x() {
		assert_cond(green_x_exists, "struct field green_x does not exist");
		return green_x_var;
	}
	uint32& green_y() {
		assert_cond(green_y_exists, "struct field green_y does not exist");
		return green_y_var;
	}
	uint32& blue_x() {
		assert_cond(blue_x_exists, "struct field blue_x does not exist");
		return blue_x_var;
	}
	uint32& blue_y() {
		assert_cond(blue_y_exists, "struct field blue_y does not exist");
		return blue_y_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_cHRM& operator () () { return *instances.back(); }
	CHUNK_cHRM& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_cHRM(std::vector<CHUNK_cHRM*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_cHRM() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_cHRM* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_cHRM* generate();
};

int CHUNK_cHRM::_parent_id = 0;
int CHUNK_cHRM::_index_start = 0;



class CHUNK_cICP {
	std::vector<CHUNK_cICP*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	ubyte color_primaries_var;
	ubyte transfer_function_var;
	ubyte matrix_coefficients_var;
	ubyte video_full_range_flag_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool color_primaries_exists = false;
	bool transfer_function_exists = false;
	bool matrix_coefficients_exists = false;
	bool video_full_range_flag_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	ubyte& color_primaries() {
		assert_cond(color_primaries_exists, "struct field color_primaries does not exist");
		return color_primaries_var;
	}
	ubyte& transfer_function() {
		assert_cond(transfer_function_exists, "struct field transfer_function does not exist");
		return transfer_function_var;
	}
	ubyte& matrix_coefficients() {
		assert_cond(matrix_coefficients_exists, "struct field matrix_coefficients does not exist");
		return matrix_coefficients_var;
	}
	ubyte& video_full_range_flag() {
		assert_cond(video_full_range_flag_exists, "struct field video_full_range_flag does not exist");
		return video_full_range_flag_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_cICP& operator () () { return *instances.back(); }
	CHUNK_cICP& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_cICP(std::vector<CHUNK_cICP*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_cICP() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_cICP* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_cICP* generate();
};

int CHUNK_cICP::_parent_id = 0;
int CHUNK_cICP::_index_start = 0;



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



class CHUNK_iCCP {
	std::vector<CHUNK_iCCP*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> iccp_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool iccp_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& iccp_data() {
		assert_cond(iccp_data_exists, "struct field iccp_data does not exist");
		return iccp_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_iCCP& operator () () { return *instances.back(); }
	CHUNK_iCCP& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_iCCP(std::vector<CHUNK_iCCP*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_iCCP() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_iCCP* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_iCCP* generate();
};

int CHUNK_iCCP::_parent_id = 0;
int CHUNK_iCCP::_index_start = 0;



class CHUNK_sBIT {
	std::vector<CHUNK_sBIT*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> significant_bits_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool significant_bits_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& significant_bits() {
		assert_cond(significant_bits_exists, "struct field significant_bits does not exist");
		return significant_bits_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_sBIT& operator () () { return *instances.back(); }
	CHUNK_sBIT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_sBIT(std::vector<CHUNK_sBIT*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_sBIT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_sBIT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_sBIT* generate();
};

int CHUNK_sBIT::_parent_id = 0;
int CHUNK_sBIT::_index_start = 0;



class CHUNK_PLTE {
	std::vector<CHUNK_PLTE*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> palette_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool palette_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& palette_data() {
		assert_cond(palette_data_exists, "struct field palette_data does not exist");
		return palette_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	/* locals */
	uint32 num_entries;
	uint32 data_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_PLTE& operator () () { return *instances.back(); }
	CHUNK_PLTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_PLTE(std::vector<CHUNK_PLTE*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_PLTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_PLTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_PLTE* generate();
};

int CHUNK_PLTE::_parent_id = 0;
int CHUNK_PLTE::_index_start = 0;



class CHUNK_tRNS {
	std::vector<CHUNK_tRNS*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> alpha_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool alpha_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& alpha_data() {
		assert_cond(alpha_data_exists, "struct field alpha_data does not exist");
		return alpha_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_tRNS& operator () () { return *instances.back(); }
	CHUNK_tRNS& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_tRNS(std::vector<CHUNK_tRNS*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_tRNS() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_tRNS* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_tRNS* generate();
};

int CHUNK_tRNS::_parent_id = 0;
int CHUNK_tRNS::_index_start = 0;



class CHUNK_bKGD {
	std::vector<CHUNK_bKGD*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> bkgd_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool bkgd_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& bkgd_data() {
		assert_cond(bkgd_data_exists, "struct field bkgd_data does not exist");
		return bkgd_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_bKGD& operator () () { return *instances.back(); }
	CHUNK_bKGD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_bKGD(std::vector<CHUNK_bKGD*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_bKGD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_bKGD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_bKGD* generate();
};

int CHUNK_bKGD::_parent_id = 0;
int CHUNK_bKGD::_index_start = 0;



class CHUNK_hIST {
	std::vector<CHUNK_hIST*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> hist_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool hist_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& hist_data() {
		assert_cond(hist_data_exists, "struct field hist_data does not exist");
		return hist_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_hIST& operator () () { return *instances.back(); }
	CHUNK_hIST& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_hIST(std::vector<CHUNK_hIST*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_hIST() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_hIST* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_hIST* generate();
};

int CHUNK_hIST::_parent_id = 0;
int CHUNK_hIST::_index_start = 0;



class CHUNK_pHYs {
	std::vector<CHUNK_pHYs*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 pixels_per_unit_x_var;
	uint32 pixels_per_unit_y_var;
	ubyte unit_specifier_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool pixels_per_unit_x_exists = false;
	bool pixels_per_unit_y_exists = false;
	bool unit_specifier_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& pixels_per_unit_x() {
		assert_cond(pixels_per_unit_x_exists, "struct field pixels_per_unit_x does not exist");
		return pixels_per_unit_x_var;
	}
	uint32& pixels_per_unit_y() {
		assert_cond(pixels_per_unit_y_exists, "struct field pixels_per_unit_y does not exist");
		return pixels_per_unit_y_var;
	}
	ubyte& unit_specifier() {
		assert_cond(unit_specifier_exists, "struct field unit_specifier does not exist");
		return unit_specifier_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_pHYs& operator () () { return *instances.back(); }
	CHUNK_pHYs& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_pHYs(std::vector<CHUNK_pHYs*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_pHYs() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_pHYs* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_pHYs* generate();
};

int CHUNK_pHYs::_parent_id = 0;
int CHUNK_pHYs::_index_start = 0;



class int32_class {
	int small;
	std::vector<int32> known_values;
	int32 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(int32);
	int32 operator () () { return value; }
	int32_class(int small, std::vector<int32> known_values = {}) : small(small), known_values(known_values) {}

	int32 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(int32), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(int32), 0, known_values);
		}
		return value;
	}

	int32 generate(std::vector<int32> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(int32), 0, possible_values);
		return value;
	}
};



class CHUNK_oFFs {
	std::vector<CHUNK_oFFs*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	int32 x_position_var;
	int32 y_position_var;
	ubyte unit_specifier_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool x_position_exists = false;
	bool y_position_exists = false;
	bool unit_specifier_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	int32& x_position() {
		assert_cond(x_position_exists, "struct field x_position does not exist");
		return x_position_var;
	}
	int32& y_position() {
		assert_cond(y_position_exists, "struct field y_position does not exist");
		return y_position_var;
	}
	ubyte& unit_specifier() {
		assert_cond(unit_specifier_exists, "struct field unit_specifier does not exist");
		return unit_specifier_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_oFFs& operator () () { return *instances.back(); }
	CHUNK_oFFs& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_oFFs(std::vector<CHUNK_oFFs*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_oFFs() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_oFFs* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_oFFs* generate();
};

int CHUNK_oFFs::_parent_id = 0;
int CHUNK_oFFs::_index_start = 0;



class CHUNK_sTER {
	std::vector<CHUNK_sTER*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	ubyte mode_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool mode_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	ubyte& mode() {
		assert_cond(mode_exists, "struct field mode does not exist");
		return mode_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_sTER& operator () () { return *instances.back(); }
	CHUNK_sTER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_sTER(std::vector<CHUNK_sTER*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_sTER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_sTER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_sTER* generate();
};

int CHUNK_sTER::_parent_id = 0;
int CHUNK_sTER::_index_start = 0;



class CHUNK_tEXt {
	std::vector<CHUNK_tEXt*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> text_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool text_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& text_data() {
		assert_cond(text_data_exists, "struct field text_data does not exist");
		return text_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_tEXt& operator () () { return *instances.back(); }
	CHUNK_tEXt& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_tEXt(std::vector<CHUNK_tEXt*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_tEXt() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_tEXt* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_tEXt* generate();
};

int CHUNK_tEXt::_parent_id = 0;
int CHUNK_tEXt::_index_start = 0;



class CHUNK_zTXt {
	std::vector<CHUNK_zTXt*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> ztxt_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool ztxt_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& ztxt_data() {
		assert_cond(ztxt_data_exists, "struct field ztxt_data does not exist");
		return ztxt_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_zTXt& operator () () { return *instances.back(); }
	CHUNK_zTXt& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_zTXt(std::vector<CHUNK_zTXt*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_zTXt() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_zTXt* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_zTXt* generate();
};

int CHUNK_zTXt::_parent_id = 0;
int CHUNK_zTXt::_index_start = 0;



class CHUNK_iTXt {
	std::vector<CHUNK_iTXt*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> itxt_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool itxt_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& itxt_data() {
		assert_cond(itxt_data_exists, "struct field itxt_data does not exist");
		return itxt_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_iTXt& operator () () { return *instances.back(); }
	CHUNK_iTXt& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_iTXt(std::vector<CHUNK_iTXt*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_iTXt() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_iTXt* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_iTXt* generate();
};

int CHUNK_iTXt::_parent_id = 0;
int CHUNK_iTXt::_index_start = 0;



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



class CHUNK_tIME {
	std::vector<CHUNK_tIME*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint16 year_var;
	ubyte month_var;
	ubyte day_var;
	ubyte hour_var;
	ubyte minute_var;
	ubyte second_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool year_exists = false;
	bool month_exists = false;
	bool day_exists = false;
	bool hour_exists = false;
	bool minute_exists = false;
	bool second_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint16& year() {
		assert_cond(year_exists, "struct field year does not exist");
		return year_var;
	}
	ubyte& month() {
		assert_cond(month_exists, "struct field month does not exist");
		return month_var;
	}
	ubyte& day() {
		assert_cond(day_exists, "struct field day does not exist");
		return day_var;
	}
	ubyte& hour() {
		assert_cond(hour_exists, "struct field hour does not exist");
		return hour_var;
	}
	ubyte& minute() {
		assert_cond(minute_exists, "struct field minute does not exist");
		return minute_var;
	}
	ubyte& second() {
		assert_cond(second_exists, "struct field second does not exist");
		return second_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_tIME& operator () () { return *instances.back(); }
	CHUNK_tIME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_tIME(std::vector<CHUNK_tIME*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_tIME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_tIME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_tIME* generate();
};

int CHUNK_tIME::_parent_id = 0;
int CHUNK_tIME::_index_start = 0;



class CHUNK_eXIf {
	std::vector<CHUNK_eXIf*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> exif_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool exif_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& exif_data() {
		assert_cond(exif_data_exists, "struct field exif_data does not exist");
		return exif_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_eXIf& operator () () { return *instances.back(); }
	CHUNK_eXIf& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_eXIf(std::vector<CHUNK_eXIf*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_eXIf() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_eXIf* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_eXIf* generate();
};

int CHUNK_eXIf::_parent_id = 0;
int CHUNK_eXIf::_index_start = 0;



class CHUNK_sPLT {
	std::vector<CHUNK_sPLT*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> splt_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool splt_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& splt_data() {
		assert_cond(splt_data_exists, "struct field splt_data does not exist");
		return splt_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_sPLT& operator () () { return *instances.back(); }
	CHUNK_sPLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_sPLT(std::vector<CHUNK_sPLT*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_sPLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_sPLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_sPLT* generate();
};

int CHUNK_sPLT::_parent_id = 0;
int CHUNK_sPLT::_index_start = 0;



class CHUNK_acTL {
	std::vector<CHUNK_acTL*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 num_frames_var;
	uint32 num_plays_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool num_frames_exists = false;
	bool num_plays_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& num_frames() {
		assert_cond(num_frames_exists, "struct field num_frames does not exist");
		return num_frames_var;
	}
	uint32& num_plays() {
		assert_cond(num_plays_exists, "struct field num_plays does not exist");
		return num_plays_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_acTL& operator () () { return *instances.back(); }
	CHUNK_acTL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_acTL(std::vector<CHUNK_acTL*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_acTL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_acTL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_acTL* generate();
};

int CHUNK_acTL::_parent_id = 0;
int CHUNK_acTL::_index_start = 0;



class CHUNK_fcTL {
	std::vector<CHUNK_fcTL*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 sequence_number_var;
	uint32 fc_width_var;
	uint32 fc_height_var;
	uint32 x_offset_var;
	uint32 y_offset_var;
	uint16 delay_num_var;
	uint16 delay_den_var;
	ubyte dispose_op_var;
	ubyte blend_op_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool sequence_number_exists = false;
	bool fc_width_exists = false;
	bool fc_height_exists = false;
	bool x_offset_exists = false;
	bool y_offset_exists = false;
	bool delay_num_exists = false;
	bool delay_den_exists = false;
	bool dispose_op_exists = false;
	bool blend_op_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& sequence_number() {
		assert_cond(sequence_number_exists, "struct field sequence_number does not exist");
		return sequence_number_var;
	}
	uint32& fc_width() {
		assert_cond(fc_width_exists, "struct field fc_width does not exist");
		return fc_width_var;
	}
	uint32& fc_height() {
		assert_cond(fc_height_exists, "struct field fc_height does not exist");
		return fc_height_var;
	}
	uint32& x_offset() {
		assert_cond(x_offset_exists, "struct field x_offset does not exist");
		return x_offset_var;
	}
	uint32& y_offset() {
		assert_cond(y_offset_exists, "struct field y_offset does not exist");
		return y_offset_var;
	}
	uint16& delay_num() {
		assert_cond(delay_num_exists, "struct field delay_num does not exist");
		return delay_num_var;
	}
	uint16& delay_den() {
		assert_cond(delay_den_exists, "struct field delay_den does not exist");
		return delay_den_var;
	}
	ubyte& dispose_op() {
		assert_cond(dispose_op_exists, "struct field dispose_op does not exist");
		return dispose_op_var;
	}
	ubyte& blend_op() {
		assert_cond(blend_op_exists, "struct field blend_op does not exist");
		return blend_op_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_fcTL& operator () () { return *instances.back(); }
	CHUNK_fcTL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_fcTL(std::vector<CHUNK_fcTL*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_fcTL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_fcTL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_fcTL* generate();
};

int CHUNK_fcTL::_parent_id = 0;
int CHUNK_fcTL::_index_start = 0;



class CHUNK_pCAL {
	std::vector<CHUNK_pCAL*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> pcal_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool pcal_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& pcal_data() {
		assert_cond(pcal_data_exists, "struct field pcal_data does not exist");
		return pcal_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_pCAL& operator () () { return *instances.back(); }
	CHUNK_pCAL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_pCAL(std::vector<CHUNK_pCAL*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_pCAL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_pCAL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_pCAL* generate();
};

int CHUNK_pCAL::_parent_id = 0;
int CHUNK_pCAL::_index_start = 0;



class CHUNK_sCAL {
	std::vector<CHUNK_sCAL*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> scal_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool scal_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& scal_data() {
		assert_cond(scal_data_exists, "struct field scal_data does not exist");
		return scal_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_sCAL& operator () () { return *instances.back(); }
	CHUNK_sCAL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_sCAL(std::vector<CHUNK_sCAL*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_sCAL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_sCAL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_sCAL* generate();
};

int CHUNK_sCAL::_parent_id = 0;
int CHUNK_sCAL::_index_start = 0;



class CHUNK_dSIG {
	std::vector<CHUNK_dSIG*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> sig_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool sig_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& sig_data() {
		assert_cond(sig_data_exists, "struct field sig_data does not exist");
		return sig_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_dSIG& operator () () { return *instances.back(); }
	CHUNK_dSIG& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_dSIG(std::vector<CHUNK_dSIG*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_dSIG() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_dSIG* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_dSIG* generate();
};

int CHUNK_dSIG::_parent_id = 0;
int CHUNK_dSIG::_index_start = 0;



class CHUNK_IDAT {
	std::vector<CHUNK_IDAT*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	std::vector<ubyte> compressed_data_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool compressed_data_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	std::vector<ubyte>& compressed_data() {
		assert_cond(compressed_data_exists, "struct field compressed_data does not exist");
		return compressed_data_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_IDAT& operator () () { return *instances.back(); }
	CHUNK_IDAT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_IDAT(std::vector<CHUNK_IDAT*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_IDAT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_IDAT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_IDAT* generate();
};

int CHUNK_IDAT::_parent_id = 0;
int CHUNK_IDAT::_index_start = 0;



class CHUNK_IEND {
	std::vector<CHUNK_IEND*>& instances;

	uint32 length_var;
	std::string chunk_type_var;
	uint32 crc_var;

public:
	bool length_exists = false;
	bool chunk_type_exists = false;
	bool crc_exists = false;

	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	std::string& chunk_type() {
		assert_cond(chunk_type_exists, "struct field chunk_type does not exist");
		return chunk_type_var;
	}
	uint32& crc() {
		assert_cond(crc_exists, "struct field crc does not exist");
		return crc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CHUNK_IEND& operator () () { return *instances.back(); }
	CHUNK_IEND& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CHUNK_IEND(std::vector<CHUNK_IEND*>& instances) : instances(instances) { instances.push_back(this); }
	~CHUNK_IEND() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CHUNK_IEND* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CHUNK_IEND* generate();
};

int CHUNK_IEND::_parent_id = 0;
int CHUNK_IEND::_index_start = 0;



class png_file {
	std::vector<png_file*>& instances;

	PNG_SIGNATURE* signature_var;
	CHUNK_IHDR* ihdr_var;
	CHUNK_sRGB* srgb_var;
	CHUNK_gAMA* gama_var;
	CHUNK_cHRM* chrm_var;
	CHUNK_cICP* cicp_var;
	CHUNK_iCCP* iccp_var;
	CHUNK_sBIT* sbit_var;
	CHUNK_PLTE* plte_var;
	CHUNK_tRNS* trns_var;
	CHUNK_bKGD* bkgd_var;
	CHUNK_hIST* hist_var;
	CHUNK_pHYs* phys_var;
	CHUNK_oFFs* offs_var;
	CHUNK_sTER* ster_var;
	CHUNK_tEXt* text_var;
	CHUNK_zTXt* ztxt_var;
	CHUNK_iTXt* itxt_var;
	CHUNK_tIME* time_var;
	CHUNK_eXIf* exif_var;
	CHUNK_sPLT* splt_var;
	CHUNK_acTL* actl_var;
	CHUNK_fcTL* fctl_var;
	CHUNK_pCAL* pcal_var;
	CHUNK_sCAL* scal_var;
	CHUNK_dSIG* dsig_var;
	CHUNK_IDAT* idat_var;
	CHUNK_IEND* iend_var;

public:
	bool signature_exists = false;
	bool ihdr_exists = false;
	bool srgb_exists = false;
	bool gama_exists = false;
	bool chrm_exists = false;
	bool cicp_exists = false;
	bool iccp_exists = false;
	bool sbit_exists = false;
	bool plte_exists = false;
	bool trns_exists = false;
	bool bkgd_exists = false;
	bool hist_exists = false;
	bool phys_exists = false;
	bool offs_exists = false;
	bool ster_exists = false;
	bool text_exists = false;
	bool ztxt_exists = false;
	bool itxt_exists = false;
	bool time_exists = false;
	bool exif_exists = false;
	bool splt_exists = false;
	bool actl_exists = false;
	bool fctl_exists = false;
	bool pcal_exists = false;
	bool scal_exists = false;
	bool dsig_exists = false;
	bool idat_exists = false;
	bool iend_exists = false;

	PNG_SIGNATURE& signature() {
		assert_cond(signature_exists, "struct field signature does not exist");
		return *signature_var;
	}
	CHUNK_IHDR& ihdr() {
		assert_cond(ihdr_exists, "struct field ihdr does not exist");
		return *ihdr_var;
	}
	CHUNK_sRGB& srgb() {
		assert_cond(srgb_exists, "struct field srgb does not exist");
		return *srgb_var;
	}
	CHUNK_gAMA& gama() {
		assert_cond(gama_exists, "struct field gama does not exist");
		return *gama_var;
	}
	CHUNK_cHRM& chrm() {
		assert_cond(chrm_exists, "struct field chrm does not exist");
		return *chrm_var;
	}
	CHUNK_cICP& cicp() {
		assert_cond(cicp_exists, "struct field cicp does not exist");
		return *cicp_var;
	}
	CHUNK_iCCP& iccp() {
		assert_cond(iccp_exists, "struct field iccp does not exist");
		return *iccp_var;
	}
	CHUNK_sBIT& sbit() {
		assert_cond(sbit_exists, "struct field sbit does not exist");
		return *sbit_var;
	}
	CHUNK_PLTE& plte() {
		assert_cond(plte_exists, "struct field plte does not exist");
		return *plte_var;
	}
	CHUNK_tRNS& trns() {
		assert_cond(trns_exists, "struct field trns does not exist");
		return *trns_var;
	}
	CHUNK_bKGD& bkgd() {
		assert_cond(bkgd_exists, "struct field bkgd does not exist");
		return *bkgd_var;
	}
	CHUNK_hIST& hist() {
		assert_cond(hist_exists, "struct field hist does not exist");
		return *hist_var;
	}
	CHUNK_pHYs& phys() {
		assert_cond(phys_exists, "struct field phys does not exist");
		return *phys_var;
	}
	CHUNK_oFFs& offs() {
		assert_cond(offs_exists, "struct field offs does not exist");
		return *offs_var;
	}
	CHUNK_sTER& ster() {
		assert_cond(ster_exists, "struct field ster does not exist");
		return *ster_var;
	}
	CHUNK_tEXt& text() {
		assert_cond(text_exists, "struct field text does not exist");
		return *text_var;
	}
	CHUNK_zTXt& ztxt() {
		assert_cond(ztxt_exists, "struct field ztxt does not exist");
		return *ztxt_var;
	}
	CHUNK_iTXt& itxt() {
		assert_cond(itxt_exists, "struct field itxt does not exist");
		return *itxt_var;
	}
	CHUNK_tIME& time() {
		assert_cond(time_exists, "struct field time does not exist");
		return *time_var;
	}
	CHUNK_eXIf& exif() {
		assert_cond(exif_exists, "struct field exif does not exist");
		return *exif_var;
	}
	CHUNK_sPLT& splt() {
		assert_cond(splt_exists, "struct field splt does not exist");
		return *splt_var;
	}
	CHUNK_acTL& actl() {
		assert_cond(actl_exists, "struct field actl does not exist");
		return *actl_var;
	}
	CHUNK_fcTL& fctl() {
		assert_cond(fctl_exists, "struct field fctl does not exist");
		return *fctl_var;
	}
	CHUNK_pCAL& pcal() {
		assert_cond(pcal_exists, "struct field pcal does not exist");
		return *pcal_var;
	}
	CHUNK_sCAL& scal() {
		assert_cond(scal_exists, "struct field scal does not exist");
		return *scal_var;
	}
	CHUNK_dSIG& dsig() {
		assert_cond(dsig_exists, "struct field dsig does not exist");
		return *dsig_var;
	}
	CHUNK_IDAT& idat() {
		assert_cond(idat_exists, "struct field idat does not exist");
		return *idat_var;
	}
	CHUNK_IEND& iend() {
		assert_cond(iend_exists, "struct field iend does not exist");
		return *iend_var;
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
	png_file& operator () () { return *instances.back(); }
	png_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	png_file(std::vector<png_file*>& instances) : instances(instances) { instances.push_back(this); }
	~png_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			png_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	png_file* generate();
};

int png_file::_parent_id = 0;
int png_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "\x89PNG", "IHDR", "PLTE", "IDAT", "IEND", "tRNS", "cHRM", "gAMA", "iCCP", "sBIT", "sRGB", "cICP", "tEXt", "zTXt", "iTXt", "bKGD", "hIST", "pHYs", "sPLT", "eXIf", "tIME", "acTL", "fcTL", "fdAT", "oFFs", "pCAL", "sCAL", "sTER", "dSIG" };


std::vector<PNG_SIGNATURE*> PNG_SIGNATURE_signature_instances;
std::vector<CHUNK_IHDR*> CHUNK_IHDR_ihdr_instances;
std::vector<CHUNK_sRGB*> CHUNK_sRGB_srgb_instances;
std::vector<CHUNK_gAMA*> CHUNK_gAMA_gama_instances;
std::vector<CHUNK_cHRM*> CHUNK_cHRM_chrm_instances;
std::vector<CHUNK_cICP*> CHUNK_cICP_cicp_instances;
std::vector<CHUNK_iCCP*> CHUNK_iCCP_iccp_instances;
std::vector<CHUNK_sBIT*> CHUNK_sBIT_sbit_instances;
std::vector<CHUNK_PLTE*> CHUNK_PLTE_plte_instances;
std::vector<CHUNK_tRNS*> CHUNK_tRNS_trns_instances;
std::vector<CHUNK_bKGD*> CHUNK_bKGD_bkgd_instances;
std::vector<CHUNK_hIST*> CHUNK_hIST_hist_instances;
std::vector<CHUNK_pHYs*> CHUNK_pHYs_phys_instances;
std::vector<CHUNK_oFFs*> CHUNK_oFFs_offs_instances;
std::vector<CHUNK_sTER*> CHUNK_sTER_ster_instances;
std::vector<CHUNK_tEXt*> CHUNK_tEXt_text_instances;
std::vector<CHUNK_zTXt*> CHUNK_zTXt_ztxt_instances;
std::vector<CHUNK_iTXt*> CHUNK_iTXt_itxt_instances;
std::vector<CHUNK_tIME*> CHUNK_tIME_time__instances;
std::vector<CHUNK_eXIf*> CHUNK_eXIf_exif_instances;
std::vector<CHUNK_sPLT*> CHUNK_sPLT_splt_instances;
std::vector<CHUNK_acTL*> CHUNK_acTL_actl_instances;
std::vector<CHUNK_fcTL*> CHUNK_fcTL_fctl_instances;
std::vector<CHUNK_pCAL*> CHUNK_pCAL_pcal_instances;
std::vector<CHUNK_sCAL*> CHUNK_sCAL_scal_instances;
std::vector<CHUNK_dSIG*> CHUNK_dSIG_dsig_instances;
std::vector<CHUNK_IDAT*> CHUNK_IDAT_idat_instances;
std::vector<CHUNK_IEND*> CHUNK_IEND_iend_instances;
std::vector<png_file*> png_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "s0", "ubyte_class" }, { "s1", "ubyte_class" }, { "s2", "ubyte_class" }, { "s3", "ubyte_class" }, { "s4", "ubyte_class" }, { "s5", "ubyte_class" }, { "s6", "ubyte_class" }, { "s7", "ubyte_class" }, { "signature", "PNG_SIGNATURE" }, { "length", "uint32_class" }, { "chunk_type", "char_array_class" }, { "width", "uint32_class" }, { "height", "uint32_class" }, { "bit_depth", "ubyte_class" }, { "color_type", "ubyte_class" }, { "compression_method", "ubyte_class" }, { "filter_method", "ubyte_class" }, { "interlace_method", "ubyte_class" }, { "crc", "uint32_class" }, { "ihdr", "CHUNK_IHDR" }, { "rendering_intent", "ubyte_class" }, { "srgb", "CHUNK_sRGB" }, { "gamma", "uint32_class" }, { "gama", "CHUNK_gAMA" }, { "white_point_x", "uint32_class" }, { "white_point_y", "uint32_class" }, { "red_x", "uint32_class" }, { "red_y", "uint32_class" }, { "green_x", "uint32_class" }, { "green_y", "uint32_class" }, { "blue_x", "uint32_class" }, { "blue_y", "uint32_class" }, { "chrm", "CHUNK_cHRM" }, { "color_primaries", "ubyte_class" }, { "transfer_function", "ubyte_class" }, { "matrix_coefficients", "ubyte_class" }, { "video_full_range_flag", "ubyte_class" }, { "cicp", "CHUNK_cICP" }, { "iccp_data", "ubyte_array_class" }, { "iccp", "CHUNK_iCCP" }, { "significant_bits", "ubyte_array_class" }, { "sbit", "CHUNK_sBIT" }, { "palette_data", "ubyte_array_class" }, { "plte", "CHUNK_PLTE" }, { "alpha_data", "ubyte_array_class" }, { "trns", "CHUNK_tRNS" }, { "bkgd_data", "ubyte_array_class" }, { "bkgd", "CHUNK_bKGD" }, { "hist_data", "ubyte_array_class" }, { "hist", "CHUNK_hIST" }, { "pixels_per_unit_x", "uint32_class" }, { "pixels_per_unit_y", "uint32_class" }, { "unit_specifier", "ubyte_class" }, { "phys", "CHUNK_pHYs" }, { "x_position", "int32_class" }, { "y_position", "int32_class" }, { "offs", "CHUNK_oFFs" }, { "mode", "ubyte_class" }, { "ster", "CHUNK_sTER" }, { "text_data", "ubyte_array_class" }, { "text", "CHUNK_tEXt" }, { "ztxt_data", "ubyte_array_class" }, { "ztxt", "CHUNK_zTXt" }, { "itxt_data", "ubyte_array_class" }, { "itxt", "CHUNK_iTXt" }, { "year", "uint16_class" }, { "month", "ubyte_class" }, { "day", "ubyte_class" }, { "hour", "ubyte_class" }, { "minute", "ubyte_class" }, { "second", "ubyte_class" }, { "time_", "CHUNK_tIME" }, { "exif_data", "ubyte_array_class" }, { "exif", "CHUNK_eXIf" }, { "splt_data", "ubyte_array_class" }, { "splt", "CHUNK_sPLT" }, { "num_frames", "uint32_class" }, { "num_plays", "uint32_class" }, { "actl", "CHUNK_acTL" }, { "sequence_number", "uint32_class" }, { "fc_width", "uint32_class" }, { "fc_height", "uint32_class" }, { "x_offset", "uint32_class" }, { "y_offset", "uint32_class" }, { "delay_num", "uint16_class" }, { "delay_den", "uint16_class" }, { "dispose_op", "ubyte_class" }, { "blend_op", "ubyte_class" }, { "fctl", "CHUNK_fcTL" }, { "pcal_data", "ubyte_array_class" }, { "pcal", "CHUNK_pCAL" }, { "scal_data", "ubyte_array_class" }, { "scal", "CHUNK_sCAL" }, { "sig_data", "ubyte_array_class" }, { "dsig", "CHUNK_dSIG" }, { "compressed_data", "ubyte_array_class" }, { "idat", "CHUNK_IDAT" }, { "iend", "CHUNK_IEND" }, { "file", "png_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 1, 1024 }, { 1, 1024 }, { 0, 3 }, { 0, 1 }, { 0, 1 }, { 1, 12 }, { 1, 31 }, { 0, 23 }, { 0, 59 }, { 0, 60 }, { 1, 100 }, { 1, 1024 }, { 1, 1024 }, { 0, 2 }, { 0, 1 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	ubyte_class s0;
	ubyte_class s1;
	ubyte_class s2;
	ubyte_class s3;
	ubyte_class s4;
	ubyte_class s5;
	ubyte_class s6;
	ubyte_class s7;
	PNG_SIGNATURE signature;
	uint32_class length;
	char_class chunk_type_element;
	char_array_class chunk_type;
	uint32_class width;
	uint32_class height;
	ubyte_class bit_depth;
	ubyte_class color_type;
	ubyte_class compression_method;
	ubyte_class filter_method;
	ubyte_class interlace_method;
	uint32_class crc;
	CHUNK_IHDR ihdr;
	ubyte_class rendering_intent;
	CHUNK_sRGB srgb;
	uint32_class gamma;
	CHUNK_gAMA gama;
	uint32_class white_point_x;
	uint32_class white_point_y;
	uint32_class red_x;
	uint32_class red_y;
	uint32_class green_x;
	uint32_class green_y;
	uint32_class blue_x;
	uint32_class blue_y;
	CHUNK_cHRM chrm;
	ubyte_class color_primaries;
	ubyte_class transfer_function;
	ubyte_class matrix_coefficients;
	ubyte_class video_full_range_flag;
	CHUNK_cICP cicp;
	ubyte_class iccp_data_element;
	ubyte_array_class iccp_data;
	CHUNK_iCCP iccp;
	ubyte_class significant_bits_element;
	ubyte_array_class significant_bits;
	CHUNK_sBIT sbit;
	ubyte_class palette_data_element;
	ubyte_array_class palette_data;
	CHUNK_PLTE plte;
	ubyte_class alpha_data_element;
	ubyte_array_class alpha_data;
	CHUNK_tRNS trns;
	ubyte_class bkgd_data_element;
	ubyte_array_class bkgd_data;
	CHUNK_bKGD bkgd;
	ubyte_class hist_data_element;
	ubyte_array_class hist_data;
	CHUNK_hIST hist;
	uint32_class pixels_per_unit_x;
	uint32_class pixels_per_unit_y;
	ubyte_class unit_specifier;
	CHUNK_pHYs phys;
	int32_class x_position;
	int32_class y_position;
	CHUNK_oFFs offs;
	ubyte_class mode;
	CHUNK_sTER ster;
	ubyte_class text_data_element;
	ubyte_array_class text_data;
	CHUNK_tEXt text;
	ubyte_class ztxt_data_element;
	ubyte_array_class ztxt_data;
	CHUNK_zTXt ztxt;
	ubyte_class itxt_data_element;
	ubyte_array_class itxt_data;
	CHUNK_iTXt itxt;
	uint16_class year;
	ubyte_class month;
	ubyte_class day;
	ubyte_class hour;
	ubyte_class minute;
	ubyte_class second;
	CHUNK_tIME time_;
	ubyte_class exif_data_element;
	ubyte_array_class exif_data;
	CHUNK_eXIf exif;
	ubyte_class splt_data_element;
	ubyte_array_class splt_data;
	CHUNK_sPLT splt;
	uint32_class num_frames;
	uint32_class num_plays;
	CHUNK_acTL actl;
	uint32_class sequence_number;
	uint32_class fc_width;
	uint32_class fc_height;
	uint32_class x_offset;
	uint32_class y_offset;
	uint16_class delay_num;
	uint16_class delay_den;
	ubyte_class dispose_op;
	ubyte_class blend_op;
	CHUNK_fcTL fctl;
	ubyte_class pcal_data_element;
	ubyte_array_class pcal_data;
	CHUNK_pCAL pcal;
	ubyte_class scal_data_element;
	ubyte_array_class scal_data;
	CHUNK_sCAL scal;
	ubyte_class sig_data_element;
	ubyte_array_class sig_data;
	CHUNK_dSIG dsig;
	ubyte_class compressed_data_element;
	ubyte_array_class compressed_data;
	CHUNK_IDAT idat;
	CHUNK_IEND iend;
	png_file file;


	globals_class() :
		s0(1),
		s1(1),
		s2(1),
		s3(1),
		s4(1),
		s5(1),
		s6(1),
		s7(1),
		signature(PNG_SIGNATURE_signature_instances),
		length(1),
		chunk_type_element(false),
		chunk_type(chunk_type_element),
		width(3),
		height(4),
		bit_depth(1),
		color_type(1),
		compression_method(1),
		filter_method(1),
		interlace_method(1),
		crc(1),
		ihdr(CHUNK_IHDR_ihdr_instances),
		rendering_intent(5),
		srgb(CHUNK_sRGB_srgb_instances),
		gamma(1),
		gama(CHUNK_gAMA_gama_instances),
		white_point_x(1),
		white_point_y(1),
		red_x(1),
		red_y(1),
		green_x(1),
		green_y(1),
		blue_x(1),
		blue_y(1),
		chrm(CHUNK_cHRM_chrm_instances),
		color_primaries(1),
		transfer_function(1),
		matrix_coefficients(1),
		video_full_range_flag(1),
		cicp(CHUNK_cICP_cicp_instances),
		iccp_data_element(false),
		iccp_data(iccp_data_element),
		iccp(CHUNK_iCCP_iccp_instances),
		significant_bits_element(false),
		significant_bits(significant_bits_element),
		sbit(CHUNK_sBIT_sbit_instances),
		palette_data_element(false),
		palette_data(palette_data_element),
		plte(CHUNK_PLTE_plte_instances),
		alpha_data_element(false),
		alpha_data(alpha_data_element),
		trns(CHUNK_tRNS_trns_instances),
		bkgd_data_element(false),
		bkgd_data(bkgd_data_element),
		bkgd(CHUNK_bKGD_bkgd_instances),
		hist_data_element(false),
		hist_data(hist_data_element),
		hist(CHUNK_hIST_hist_instances),
		pixels_per_unit_x(1),
		pixels_per_unit_y(1),
		unit_specifier(6),
		phys(CHUNK_pHYs_phys_instances),
		x_position(1),
		y_position(1),
		offs(CHUNK_oFFs_offs_instances),
		mode(7),
		ster(CHUNK_sTER_ster_instances),
		text_data_element(false),
		text_data(text_data_element),
		text(CHUNK_tEXt_text_instances),
		ztxt_data_element(false),
		ztxt_data(ztxt_data_element),
		ztxt(CHUNK_zTXt_ztxt_instances),
		itxt_data_element(false),
		itxt_data(itxt_data_element),
		itxt(CHUNK_iTXt_itxt_instances),
		year(1),
		month(8),
		day(9),
		hour(10),
		minute(11),
		second(12),
		time_(CHUNK_tIME_time__instances),
		exif_data_element(false),
		exif_data(exif_data_element),
		exif(CHUNK_eXIf_exif_instances),
		splt_data_element(false),
		splt_data(splt_data_element),
		splt(CHUNK_sPLT_splt_instances),
		num_frames(13),
		num_plays(1),
		actl(CHUNK_acTL_actl_instances),
		sequence_number(1),
		fc_width(14),
		fc_height(15),
		x_offset(1),
		y_offset(1),
		delay_num(1),
		delay_den(1),
		dispose_op(16),
		blend_op(17),
		fctl(CHUNK_fcTL_fctl_instances),
		pcal_data_element(false),
		pcal_data(pcal_data_element),
		pcal(CHUNK_pCAL_pcal_instances),
		scal_data_element(false),
		scal_data(scal_data_element),
		scal(CHUNK_sCAL_scal_instances),
		sig_data_element(false),
		sig_data(sig_data_element),
		dsig(CHUNK_dSIG_dsig_instances),
		compressed_data_element(false),
		compressed_data(compressed_data_element),
		idat(CHUNK_IDAT_idat_instances),
		iend(CHUNK_IEND_iend_instances),
		file(png_file_file_instances)
	{}
};

globals_class* g;


PNG_SIGNATURE* PNG_SIGNATURE::generate() {
	if (generated == 1) {
		PNG_SIGNATURE* new_instance = new PNG_SIGNATURE(instances);
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

	GENERATE_VAR(s0, ::g->s0.generate({ 0x89 }));
	GENERATE_VAR(s1, ::g->s1.generate({ 0x50 }));
	GENERATE_VAR(s2, ::g->s2.generate({ 0x4E }));
	GENERATE_VAR(s3, ::g->s3.generate({ 0x47 }));
	GENERATE_VAR(s4, ::g->s4.generate({ 0x0D }));
	GENERATE_VAR(s5, ::g->s5.generate({ 0x0A }));
	GENERATE_VAR(s6, ::g->s6.generate({ 0x1A }));
	GENERATE_VAR(s7, ::g->s7.generate({ 0x0A }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_IHDR* CHUNK_IHDR::generate() {
	if (generated == 1) {
		CHUNK_IHDR* new_instance = new CHUNK_IHDR(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 13 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "IHDR" }));
	GENERATE_VAR(width, ::g->width.generate());
	GENERATE_VAR(height, ::g->height.generate());
	GENERATE_VAR(bit_depth, ::g->bit_depth.generate({ 8 }));
	GENERATE_VAR(color_type, ::g->color_type.generate({ 0, 2, 3, 4, 6 }));
	GENERATE_VAR(compression_method, ::g->compression_method.generate({ 0 }));
	GENERATE_VAR(filter_method, ::g->filter_method.generate({ 0 }));
	GENERATE_VAR(interlace_method, ::g->interlace_method.generate({ 0, 1 }));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_sRGB* CHUNK_sRGB::generate() {
	if (generated == 1) {
		CHUNK_sRGB* new_instance = new CHUNK_sRGB(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 1 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "sRGB" }));
	GENERATE_VAR(rendering_intent, ::g->rendering_intent.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_gAMA* CHUNK_gAMA::generate() {
	if (generated == 1) {
		CHUNK_gAMA* new_instance = new CHUNK_gAMA(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 4 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "gAMA" }));
	GENERATE_VAR(gamma, ::g->gamma.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_cHRM* CHUNK_cHRM::generate() {
	if (generated == 1) {
		CHUNK_cHRM* new_instance = new CHUNK_cHRM(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 32 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "cHRM" }));
	GENERATE_VAR(white_point_x, ::g->white_point_x.generate());
	GENERATE_VAR(white_point_y, ::g->white_point_y.generate());
	GENERATE_VAR(red_x, ::g->red_x.generate());
	GENERATE_VAR(red_y, ::g->red_y.generate());
	GENERATE_VAR(green_x, ::g->green_x.generate());
	GENERATE_VAR(green_y, ::g->green_y.generate());
	GENERATE_VAR(blue_x, ::g->blue_x.generate());
	GENERATE_VAR(blue_y, ::g->blue_y.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_cICP* CHUNK_cICP::generate() {
	if (generated == 1) {
		CHUNK_cICP* new_instance = new CHUNK_cICP(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 4 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "cICP" }));
	GENERATE_VAR(color_primaries, ::g->color_primaries.generate());
	GENERATE_VAR(transfer_function, ::g->transfer_function.generate());
	GENERATE_VAR(matrix_coefficients, ::g->matrix_coefficients.generate({ 0 }));
	GENERATE_VAR(video_full_range_flag, ::g->video_full_range_flag.generate({ 1 }));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_iCCP* CHUNK_iCCP::generate() {
	if (generated == 1) {
		CHUNK_iCCP* new_instance = new CHUNK_iCCP(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "iCCP" }));
	GENERATE_VAR(iccp_data, ::g->iccp_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_sBIT* CHUNK_sBIT::generate() {
	if (generated == 1) {
		CHUNK_sBIT* new_instance = new CHUNK_sBIT(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "sBIT" }));
	GENERATE_VAR(significant_bits, ::g->significant_bits.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_PLTE* CHUNK_PLTE::generate() {
	if (generated == 1) {
		CHUNK_PLTE* new_instance = new CHUNK_PLTE(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "PLTE" }));
	num_entries = (length() / 3);
	if ((num_entries > 256)) {
	num_entries = 256;
	};
	data_size = (num_entries * 3);
	if ((data_size > 0)) {
		GENERATE_VAR(palette_data, ::g->palette_data.generate(data_size));
	};
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_tRNS* CHUNK_tRNS::generate() {
	if (generated == 1) {
		CHUNK_tRNS* new_instance = new CHUNK_tRNS(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "tRNS" }));
	GENERATE_VAR(alpha_data, ::g->alpha_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_bKGD* CHUNK_bKGD::generate() {
	if (generated == 1) {
		CHUNK_bKGD* new_instance = new CHUNK_bKGD(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "bKGD" }));
	GENERATE_VAR(bkgd_data, ::g->bkgd_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_hIST* CHUNK_hIST::generate() {
	if (generated == 1) {
		CHUNK_hIST* new_instance = new CHUNK_hIST(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "hIST" }));
	GENERATE_VAR(hist_data, ::g->hist_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_pHYs* CHUNK_pHYs::generate() {
	if (generated == 1) {
		CHUNK_pHYs* new_instance = new CHUNK_pHYs(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 9 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "pHYs" }));
	GENERATE_VAR(pixels_per_unit_x, ::g->pixels_per_unit_x.generate());
	GENERATE_VAR(pixels_per_unit_y, ::g->pixels_per_unit_y.generate());
	GENERATE_VAR(unit_specifier, ::g->unit_specifier.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_oFFs* CHUNK_oFFs::generate() {
	if (generated == 1) {
		CHUNK_oFFs* new_instance = new CHUNK_oFFs(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 9 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "oFFs" }));
	GENERATE_VAR(x_position, ::g->x_position.generate());
	GENERATE_VAR(y_position, ::g->y_position.generate());
	GENERATE_VAR(unit_specifier, ::g->unit_specifier.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_sTER* CHUNK_sTER::generate() {
	if (generated == 1) {
		CHUNK_sTER* new_instance = new CHUNK_sTER(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 1 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "sTER" }));
	GENERATE_VAR(mode, ::g->mode.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_tEXt* CHUNK_tEXt::generate() {
	if (generated == 1) {
		CHUNK_tEXt* new_instance = new CHUNK_tEXt(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "tEXt" }));
	GENERATE_VAR(text_data, ::g->text_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_zTXt* CHUNK_zTXt::generate() {
	if (generated == 1) {
		CHUNK_zTXt* new_instance = new CHUNK_zTXt(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "zTXt" }));
	GENERATE_VAR(ztxt_data, ::g->ztxt_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_iTXt* CHUNK_iTXt::generate() {
	if (generated == 1) {
		CHUNK_iTXt* new_instance = new CHUNK_iTXt(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "iTXt" }));
	GENERATE_VAR(itxt_data, ::g->itxt_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_tIME* CHUNK_tIME::generate() {
	if (generated == 1) {
		CHUNK_tIME* new_instance = new CHUNK_tIME(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 7 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "tIME" }));
	GENERATE_VAR(year, ::g->year.generate());
	GENERATE_VAR(month, ::g->month.generate());
	GENERATE_VAR(day, ::g->day.generate());
	GENERATE_VAR(hour, ::g->hour.generate());
	GENERATE_VAR(minute, ::g->minute.generate());
	GENERATE_VAR(second, ::g->second.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_eXIf* CHUNK_eXIf::generate() {
	if (generated == 1) {
		CHUNK_eXIf* new_instance = new CHUNK_eXIf(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "eXIf" }));
	GENERATE_VAR(exif_data, ::g->exif_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_sPLT* CHUNK_sPLT::generate() {
	if (generated == 1) {
		CHUNK_sPLT* new_instance = new CHUNK_sPLT(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "sPLT" }));
	GENERATE_VAR(splt_data, ::g->splt_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_acTL* CHUNK_acTL::generate() {
	if (generated == 1) {
		CHUNK_acTL* new_instance = new CHUNK_acTL(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 8 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "acTL" }));
	GENERATE_VAR(num_frames, ::g->num_frames.generate());
	GENERATE_VAR(num_plays, ::g->num_plays.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_fcTL* CHUNK_fcTL::generate() {
	if (generated == 1) {
		CHUNK_fcTL* new_instance = new CHUNK_fcTL(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 26 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "fcTL" }));
	GENERATE_VAR(sequence_number, ::g->sequence_number.generate());
	GENERATE_VAR(fc_width, ::g->fc_width.generate());
	GENERATE_VAR(fc_height, ::g->fc_height.generate());
	GENERATE_VAR(x_offset, ::g->x_offset.generate());
	GENERATE_VAR(y_offset, ::g->y_offset.generate());
	GENERATE_VAR(delay_num, ::g->delay_num.generate());
	GENERATE_VAR(delay_den, ::g->delay_den.generate());
	GENERATE_VAR(dispose_op, ::g->dispose_op.generate());
	GENERATE_VAR(blend_op, ::g->blend_op.generate());
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_pCAL* CHUNK_pCAL::generate() {
	if (generated == 1) {
		CHUNK_pCAL* new_instance = new CHUNK_pCAL(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "pCAL" }));
	GENERATE_VAR(pcal_data, ::g->pcal_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_sCAL* CHUNK_sCAL::generate() {
	if (generated == 1) {
		CHUNK_sCAL* new_instance = new CHUNK_sCAL(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "sCAL" }));
	GENERATE_VAR(scal_data, ::g->scal_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_dSIG* CHUNK_dSIG::generate() {
	if (generated == 1) {
		CHUNK_dSIG* new_instance = new CHUNK_dSIG(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "dSIG" }));
	GENERATE_VAR(sig_data, ::g->sig_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_IDAT* CHUNK_IDAT::generate() {
	if (generated == 1) {
		CHUNK_IDAT* new_instance = new CHUNK_IDAT(instances);
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

	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "IDAT" }));
	GENERATE_VAR(compressed_data, ::g->compressed_data.generate(length()));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CHUNK_IEND* CHUNK_IEND::generate() {
	if (generated == 1) {
		CHUNK_IEND* new_instance = new CHUNK_IEND(instances);
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

	GENERATE_VAR(length, ::g->length.generate({ 0 }));
	GENERATE_VAR(chunk_type, ::g->chunk_type.generate(4, { "IEND" }));
	GENERATE_VAR(crc, ::g->crc.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


png_file* png_file::generate() {
	if (generated == 1) {
		png_file* new_instance = new png_file(instances);
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

	GENERATE_VAR(signature, ::g->signature.generate());
	GENERATE_VAR(ihdr, ::g->ihdr.generate());
	tag.resize(4);
	all_choices = { "sRGB", "gAMA", "cHRM", "cICP", "iCCP", "sBIT", "PLTE", "tRNS", "bKGD", "hIST", "pHYs", "oFFs", "sTER", "tEXt", "zTXt", "iTXt", "tIME", "eXIf", "sPLT", "acTL", "fcTL", "pCAL", "sCAL", "dSIG" };
	preferred = { "sRGB", "gAMA", "PLTE", "pHYs", "tEXt" };
	while (ReadBytes(tag, (FTell() + 4), 4, preferred, all_choices)) {
		switch (STR2INT(tag)) {
		case STR2INT("sRGB"):
			GENERATE_VAR(srgb, ::g->srgb.generate());
			VectorRemove(all_choices, { "sRGB" });
			VectorRemove(preferred, { "sRGB" });
			break;
		case STR2INT("gAMA"):
			GENERATE_VAR(gama, ::g->gama.generate());
			VectorRemove(all_choices, { "gAMA" });
			VectorRemove(preferred, { "gAMA" });
			break;
		case STR2INT("cHRM"):
			GENERATE_VAR(chrm, ::g->chrm.generate());
			VectorRemove(all_choices, { "cHRM" });
			break;
		case STR2INT("cICP"):
			GENERATE_VAR(cicp, ::g->cicp.generate());
			VectorRemove(all_choices, { "cICP" });
			break;
		case STR2INT("iCCP"):
			GENERATE_VAR(iccp, ::g->iccp.generate());
			VectorRemove(all_choices, { "iCCP" });
			break;
		case STR2INT("sBIT"):
			GENERATE_VAR(sbit, ::g->sbit.generate());
			VectorRemove(all_choices, { "sBIT" });
			break;
		case STR2INT("PLTE"):
			GENERATE_VAR(plte, ::g->plte.generate());
			VectorRemove(all_choices, { "PLTE" });
			VectorRemove(preferred, { "PLTE" });
			break;
		case STR2INT("tRNS"):
			GENERATE_VAR(trns, ::g->trns.generate());
			VectorRemove(all_choices, { "tRNS" });
			break;
		case STR2INT("bKGD"):
			GENERATE_VAR(bkgd, ::g->bkgd.generate());
			VectorRemove(all_choices, { "bKGD" });
			break;
		case STR2INT("hIST"):
			GENERATE_VAR(hist, ::g->hist.generate());
			VectorRemove(all_choices, { "hIST" });
			break;
		case STR2INT("pHYs"):
			GENERATE_VAR(phys, ::g->phys.generate());
			VectorRemove(all_choices, { "pHYs" });
			VectorRemove(preferred, { "pHYs" });
			break;
		case STR2INT("oFFs"):
			GENERATE_VAR(offs, ::g->offs.generate());
			VectorRemove(all_choices, { "oFFs" });
			break;
		case STR2INT("sTER"):
			GENERATE_VAR(ster, ::g->ster.generate());
			VectorRemove(all_choices, { "sTER" });
			break;
		case STR2INT("tEXt"):
			GENERATE_VAR(text, ::g->text.generate());
			VectorRemove(all_choices, { "tEXt" });
			VectorRemove(preferred, { "tEXt" });
			break;
		case STR2INT("zTXt"):
			GENERATE_VAR(ztxt, ::g->ztxt.generate());
			VectorRemove(all_choices, { "zTXt" });
			break;
		case STR2INT("iTXt"):
			GENERATE_VAR(itxt, ::g->itxt.generate());
			VectorRemove(all_choices, { "iTXt" });
			break;
		case STR2INT("tIME"):
			GENERATE_VAR(time, ::g->time_.generate());
			VectorRemove(all_choices, { "tIME" });
			break;
		case STR2INT("eXIf"):
			GENERATE_VAR(exif, ::g->exif.generate());
			VectorRemove(all_choices, { "eXIf" });
			break;
		case STR2INT("sPLT"):
			GENERATE_VAR(splt, ::g->splt.generate());
			VectorRemove(all_choices, { "sPLT" });
			break;
		case STR2INT("acTL"):
			GENERATE_VAR(actl, ::g->actl.generate());
			VectorRemove(all_choices, { "acTL" });
			break;
		case STR2INT("fcTL"):
			GENERATE_VAR(fctl, ::g->fctl.generate());
			VectorRemove(all_choices, { "fcTL" });
			break;
		case STR2INT("pCAL"):
			GENERATE_VAR(pcal, ::g->pcal.generate());
			VectorRemove(all_choices, { "pCAL" });
			break;
		case STR2INT("sCAL"):
			GENERATE_VAR(scal, ::g->scal.generate());
			VectorRemove(all_choices, { "sCAL" });
			break;
		case STR2INT("dSIG"):
			GENERATE_VAR(dsig, ::g->dsig.generate());
			VectorRemove(all_choices, { "dSIG" });
			break;
		default:
			break;
		};
	};
	GENERATE_VAR(idat, ::g->idat.generate());
	GENERATE_VAR(iend, ::g->iend.generate());

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

