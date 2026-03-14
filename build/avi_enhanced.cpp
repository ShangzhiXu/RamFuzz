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



class uint32_array_class {
	uint32_class& element;
	std::unordered_map<int, std::vector<uint32>> element_known_values;
	std::vector<uint32> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<uint32>& operator () () { return value; }
	uint32 operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	uint32_array_class(uint32_class& element, std::unordered_map<int, std::vector<uint32>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<uint32> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(uint32), 0, known->second));
				_sizeof += sizeof(uint32);
			}
		}
		return value;
	}
};



class AVI_MAIN_HEADER {
	std::vector<AVI_MAIN_HEADER*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 us_per_frame_var;
	uint32 max_bytes_per_sec_var;
	uint32 padding_granularity_var;
	uint32 flags_var;
	uint32 total_frames_var;
	uint32 initial_frames_var;
	uint32 num_streams_var;
	uint32 suggested_buf_size_var;
	uint32 width_var;
	uint32 height_var;
	std::vector<uint32> reserved_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool us_per_frame_exists = false;
	bool max_bytes_per_sec_exists = false;
	bool padding_granularity_exists = false;
	bool flags_exists = false;
	bool total_frames_exists = false;
	bool initial_frames_exists = false;
	bool num_streams_exists = false;
	bool suggested_buf_size_exists = false;
	bool width_exists = false;
	bool height_exists = false;
	bool reserved_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& us_per_frame() {
		assert_cond(us_per_frame_exists, "struct field us_per_frame does not exist");
		return us_per_frame_var;
	}
	uint32& max_bytes_per_sec() {
		assert_cond(max_bytes_per_sec_exists, "struct field max_bytes_per_sec does not exist");
		return max_bytes_per_sec_var;
	}
	uint32& padding_granularity() {
		assert_cond(padding_granularity_exists, "struct field padding_granularity does not exist");
		return padding_granularity_var;
	}
	uint32& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return flags_var;
	}
	uint32& total_frames() {
		assert_cond(total_frames_exists, "struct field total_frames does not exist");
		return total_frames_var;
	}
	uint32& initial_frames() {
		assert_cond(initial_frames_exists, "struct field initial_frames does not exist");
		return initial_frames_var;
	}
	uint32& num_streams() {
		assert_cond(num_streams_exists, "struct field num_streams does not exist");
		return num_streams_var;
	}
	uint32& suggested_buf_size() {
		assert_cond(suggested_buf_size_exists, "struct field suggested_buf_size does not exist");
		return suggested_buf_size_var;
	}
	uint32& width() {
		assert_cond(width_exists, "struct field width does not exist");
		return width_var;
	}
	uint32& height() {
		assert_cond(height_exists, "struct field height does not exist");
		return height_var;
	}
	std::vector<uint32>& reserved() {
		assert_cond(reserved_exists, "struct field reserved does not exist");
		return reserved_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	AVI_MAIN_HEADER& operator () () { return *instances.back(); }
	AVI_MAIN_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	AVI_MAIN_HEADER(std::vector<AVI_MAIN_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~AVI_MAIN_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			AVI_MAIN_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	AVI_MAIN_HEADER* generate();
};

int AVI_MAIN_HEADER::_parent_id = 0;
int AVI_MAIN_HEADER::_index_start = 0;



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



class int16_class {
	int small;
	std::vector<int16> known_values;
	int16 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(int16);
	int16 operator () () { return value; }
	int16_class(int small, std::vector<int16> known_values = {}) : small(small), known_values(known_values) {}

	int16 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(int16), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(int16), 0, known_values);
		}
		return value;
	}

	int16 generate(std::vector<int16> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(int16), 0, possible_values);
		return value;
	}
};



class STREAM_HEADER {
	std::vector<STREAM_HEADER*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	std::string fcc_type_var;
	std::string fcc_handler_var;
	uint32 flags_var;
	uint16 priority_var;
	uint16 language_var;
	uint32 initial_frames_var;
	uint32 scale_var;
	uint32 rate_var;
	uint32 start_var;
	uint32 length_var;
	uint32 suggested_buf_size_var;
	uint32 quality_var;
	uint32 sample_size_var;
	int16 frame_left_var;
	int16 frame_top_var;
	int16 frame_right_var;
	int16 frame_bottom_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool fcc_type_exists = false;
	bool fcc_handler_exists = false;
	bool flags_exists = false;
	bool priority_exists = false;
	bool language_exists = false;
	bool initial_frames_exists = false;
	bool scale_exists = false;
	bool rate_exists = false;
	bool start_exists = false;
	bool length_exists = false;
	bool suggested_buf_size_exists = false;
	bool quality_exists = false;
	bool sample_size_exists = false;
	bool frame_left_exists = false;
	bool frame_top_exists = false;
	bool frame_right_exists = false;
	bool frame_bottom_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	std::string& fcc_type() {
		assert_cond(fcc_type_exists, "struct field fcc_type does not exist");
		return fcc_type_var;
	}
	std::string& fcc_handler() {
		assert_cond(fcc_handler_exists, "struct field fcc_handler does not exist");
		return fcc_handler_var;
	}
	uint32& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return flags_var;
	}
	uint16& priority() {
		assert_cond(priority_exists, "struct field priority does not exist");
		return priority_var;
	}
	uint16& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return language_var;
	}
	uint32& initial_frames() {
		assert_cond(initial_frames_exists, "struct field initial_frames does not exist");
		return initial_frames_var;
	}
	uint32& scale() {
		assert_cond(scale_exists, "struct field scale does not exist");
		return scale_var;
	}
	uint32& rate() {
		assert_cond(rate_exists, "struct field rate does not exist");
		return rate_var;
	}
	uint32& start() {
		assert_cond(start_exists, "struct field start does not exist");
		return start_var;
	}
	uint32& length() {
		assert_cond(length_exists, "struct field length does not exist");
		return length_var;
	}
	uint32& suggested_buf_size() {
		assert_cond(suggested_buf_size_exists, "struct field suggested_buf_size does not exist");
		return suggested_buf_size_var;
	}
	uint32& quality() {
		assert_cond(quality_exists, "struct field quality does not exist");
		return quality_var;
	}
	uint32& sample_size() {
		assert_cond(sample_size_exists, "struct field sample_size does not exist");
		return sample_size_var;
	}
	int16& frame_left() {
		assert_cond(frame_left_exists, "struct field frame_left does not exist");
		return frame_left_var;
	}
	int16& frame_top() {
		assert_cond(frame_top_exists, "struct field frame_top does not exist");
		return frame_top_var;
	}
	int16& frame_right() {
		assert_cond(frame_right_exists, "struct field frame_right does not exist");
		return frame_right_var;
	}
	int16& frame_bottom() {
		assert_cond(frame_bottom_exists, "struct field frame_bottom does not exist");
		return frame_bottom_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	STREAM_HEADER& operator () () { return *instances.back(); }
	STREAM_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	STREAM_HEADER(std::vector<STREAM_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~STREAM_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			STREAM_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	STREAM_HEADER* generate();
};

int STREAM_HEADER::_parent_id = 0;
int STREAM_HEADER::_index_start = 0;



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



class STREAM_FORMAT_VIDEO {
	std::vector<STREAM_FORMAT_VIDEO*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 bi_size_var;
	int32 bi_width_var;
	int32 bi_height_var;
	uint16 bi_planes_var;
	uint16 bi_bit_count_var;
	uint32 bi_compression_var;
	uint32 bi_size_image_var;
	int32 bi_x_ppm_var;
	int32 bi_y_ppm_var;
	uint32 bi_clr_used_var;
	uint32 bi_clr_important_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool bi_size_exists = false;
	bool bi_width_exists = false;
	bool bi_height_exists = false;
	bool bi_planes_exists = false;
	bool bi_bit_count_exists = false;
	bool bi_compression_exists = false;
	bool bi_size_image_exists = false;
	bool bi_x_ppm_exists = false;
	bool bi_y_ppm_exists = false;
	bool bi_clr_used_exists = false;
	bool bi_clr_important_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& bi_size() {
		assert_cond(bi_size_exists, "struct field bi_size does not exist");
		return bi_size_var;
	}
	int32& bi_width() {
		assert_cond(bi_width_exists, "struct field bi_width does not exist");
		return bi_width_var;
	}
	int32& bi_height() {
		assert_cond(bi_height_exists, "struct field bi_height does not exist");
		return bi_height_var;
	}
	uint16& bi_planes() {
		assert_cond(bi_planes_exists, "struct field bi_planes does not exist");
		return bi_planes_var;
	}
	uint16& bi_bit_count() {
		assert_cond(bi_bit_count_exists, "struct field bi_bit_count does not exist");
		return bi_bit_count_var;
	}
	uint32& bi_compression() {
		assert_cond(bi_compression_exists, "struct field bi_compression does not exist");
		return bi_compression_var;
	}
	uint32& bi_size_image() {
		assert_cond(bi_size_image_exists, "struct field bi_size_image does not exist");
		return bi_size_image_var;
	}
	int32& bi_x_ppm() {
		assert_cond(bi_x_ppm_exists, "struct field bi_x_ppm does not exist");
		return bi_x_ppm_var;
	}
	int32& bi_y_ppm() {
		assert_cond(bi_y_ppm_exists, "struct field bi_y_ppm does not exist");
		return bi_y_ppm_var;
	}
	uint32& bi_clr_used() {
		assert_cond(bi_clr_used_exists, "struct field bi_clr_used does not exist");
		return bi_clr_used_var;
	}
	uint32& bi_clr_important() {
		assert_cond(bi_clr_important_exists, "struct field bi_clr_important does not exist");
		return bi_clr_important_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	STREAM_FORMAT_VIDEO& operator () () { return *instances.back(); }
	STREAM_FORMAT_VIDEO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	STREAM_FORMAT_VIDEO(std::vector<STREAM_FORMAT_VIDEO*>& instances) : instances(instances) { instances.push_back(this); }
	~STREAM_FORMAT_VIDEO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			STREAM_FORMAT_VIDEO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	STREAM_FORMAT_VIDEO* generate();
};

int STREAM_FORMAT_VIDEO::_parent_id = 0;
int STREAM_FORMAT_VIDEO::_index_start = 0;



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



class JUNK_CHUNK {
	std::vector<JUNK_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	std::vector<ubyte> data_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool data_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
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
	JUNK_CHUNK& operator () () { return *instances.back(); }
	JUNK_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	JUNK_CHUNK(std::vector<JUNK_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~JUNK_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			JUNK_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	JUNK_CHUNK* generate();
};

int JUNK_CHUNK::_parent_id = 0;
int JUNK_CHUNK::_index_start = 0;



class IDX1_ENTRY {
	std::vector<IDX1_ENTRY*>& instances;

	std::string ck_id_var;
	uint32 flags_var;
	uint32 offset_var;
	uint32 size_var;

public:
	bool ck_id_exists = false;
	bool flags_exists = false;
	bool offset_exists = false;
	bool size_exists = false;

	std::string& ck_id() {
		assert_cond(ck_id_exists, "struct field ck_id does not exist");
		return ck_id_var;
	}
	uint32& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return flags_var;
	}
	uint32& offset() {
		assert_cond(offset_exists, "struct field offset does not exist");
		return offset_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IDX1_ENTRY& operator () () { return *instances.back(); }
	IDX1_ENTRY& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IDX1_ENTRY(std::vector<IDX1_ENTRY*>& instances) : instances(instances) { instances.push_back(this); }
	~IDX1_ENTRY() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IDX1_ENTRY* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IDX1_ENTRY* generate();
};

int IDX1_ENTRY::_parent_id = 0;
int IDX1_ENTRY::_index_start = 0;



class avi_file {
	std::vector<avi_file*>& instances;

	std::string riff_id_var;
	uint32 riff_size_var;
	std::string form_type_var;
	std::string hdrl_list_id_var;
	uint32 hdrl_size_var;
	std::string hdrl_type_var;
	AVI_MAIN_HEADER* avih_var;
	std::string strl_list_id_var;
	uint32 strl_size_var;
	std::string strl_type_var;
	STREAM_HEADER* strh_var;
	STREAM_FORMAT_VIDEO* strf_v_var;
	JUNK_CHUNK* junk_var;
	std::string movi_list_id_var;
	uint32 movi_size_var;
	std::string movi_type_var;
	std::string vchunk_id_var;
	uint32 vchunk_size_var;
	std::vector<ubyte> vchunk_data_var;
	std::string idx1_id_var;
	uint32 idx1_size_var;
	IDX1_ENTRY* idx1_entry_var;

public:
	bool riff_id_exists = false;
	bool riff_size_exists = false;
	bool form_type_exists = false;
	bool hdrl_list_id_exists = false;
	bool hdrl_size_exists = false;
	bool hdrl_type_exists = false;
	bool avih_exists = false;
	bool strl_list_id_exists = false;
	bool strl_size_exists = false;
	bool strl_type_exists = false;
	bool strh_exists = false;
	bool strf_v_exists = false;
	bool junk_exists = false;
	bool movi_list_id_exists = false;
	bool movi_size_exists = false;
	bool movi_type_exists = false;
	bool vchunk_id_exists = false;
	bool vchunk_size_exists = false;
	bool vchunk_data_exists = false;
	bool idx1_id_exists = false;
	bool idx1_size_exists = false;
	bool idx1_entry_exists = false;

	std::string& riff_id() {
		assert_cond(riff_id_exists, "struct field riff_id does not exist");
		return riff_id_var;
	}
	uint32& riff_size() {
		assert_cond(riff_size_exists, "struct field riff_size does not exist");
		return riff_size_var;
	}
	std::string& form_type() {
		assert_cond(form_type_exists, "struct field form_type does not exist");
		return form_type_var;
	}
	std::string& hdrl_list_id() {
		assert_cond(hdrl_list_id_exists, "struct field hdrl_list_id does not exist");
		return hdrl_list_id_var;
	}
	uint32& hdrl_size() {
		assert_cond(hdrl_size_exists, "struct field hdrl_size does not exist");
		return hdrl_size_var;
	}
	std::string& hdrl_type() {
		assert_cond(hdrl_type_exists, "struct field hdrl_type does not exist");
		return hdrl_type_var;
	}
	AVI_MAIN_HEADER& avih() {
		assert_cond(avih_exists, "struct field avih does not exist");
		return *avih_var;
	}
	std::string& strl_list_id() {
		assert_cond(strl_list_id_exists, "struct field strl_list_id does not exist");
		return strl_list_id_var;
	}
	uint32& strl_size() {
		assert_cond(strl_size_exists, "struct field strl_size does not exist");
		return strl_size_var;
	}
	std::string& strl_type() {
		assert_cond(strl_type_exists, "struct field strl_type does not exist");
		return strl_type_var;
	}
	STREAM_HEADER& strh() {
		assert_cond(strh_exists, "struct field strh does not exist");
		return *strh_var;
	}
	STREAM_FORMAT_VIDEO& strf_v() {
		assert_cond(strf_v_exists, "struct field strf_v does not exist");
		return *strf_v_var;
	}
	JUNK_CHUNK& junk() {
		assert_cond(junk_exists, "struct field junk does not exist");
		return *junk_var;
	}
	std::string& movi_list_id() {
		assert_cond(movi_list_id_exists, "struct field movi_list_id does not exist");
		return movi_list_id_var;
	}
	uint32& movi_size() {
		assert_cond(movi_size_exists, "struct field movi_size does not exist");
		return movi_size_var;
	}
	std::string& movi_type() {
		assert_cond(movi_type_exists, "struct field movi_type does not exist");
		return movi_type_var;
	}
	std::string& vchunk_id() {
		assert_cond(vchunk_id_exists, "struct field vchunk_id does not exist");
		return vchunk_id_var;
	}
	uint32& vchunk_size() {
		assert_cond(vchunk_size_exists, "struct field vchunk_size does not exist");
		return vchunk_size_var;
	}
	std::vector<ubyte>& vchunk_data() {
		assert_cond(vchunk_data_exists, "struct field vchunk_data does not exist");
		return vchunk_data_var;
	}
	std::string& idx1_id() {
		assert_cond(idx1_id_exists, "struct field idx1_id does not exist");
		return idx1_id_var;
	}
	uint32& idx1_size() {
		assert_cond(idx1_size_exists, "struct field idx1_size does not exist");
		return idx1_size_var;
	}
	IDX1_ENTRY& idx1_entry() {
		assert_cond(idx1_entry_exists, "struct field idx1_entry does not exist");
		return *idx1_entry_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	avi_file& operator () () { return *instances.back(); }
	avi_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	avi_file(std::vector<avi_file*>& instances) : instances(instances) { instances.push_back(this); }
	~avi_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			avi_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	avi_file* generate();
};

int avi_file::_parent_id = 0;
int avi_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "RIFF", "LIST", "avih", "strh", "strf", "movi", "idx1", "JUNK" };


std::vector<AVI_MAIN_HEADER*> AVI_MAIN_HEADER_avih_instances;
std::vector<STREAM_HEADER*> STREAM_HEADER_strh_instances;
std::vector<STREAM_FORMAT_VIDEO*> STREAM_FORMAT_VIDEO_strf_v_instances;
std::vector<JUNK_CHUNK*> JUNK_CHUNK_junk_instances;
std::vector<IDX1_ENTRY*> IDX1_ENTRY_idx1_entry_instances;
std::vector<avi_file*> avi_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "riff_id", "char_array_class" }, { "riff_size", "uint32_class" }, { "form_type", "char_array_class" }, { "hdrl_list_id", "char_array_class" }, { "hdrl_size", "uint32_class" }, { "hdrl_type", "char_array_class" }, { "chunk_id", "char_array_class" }, { "chunk_size", "uint32_class" }, { "us_per_frame", "uint32_class" }, { "max_bytes_per_sec", "uint32_class" }, { "padding_granularity", "uint32_class" }, { "flags", "uint32_class" }, { "total_frames", "uint32_class" }, { "initial_frames", "uint32_class" }, { "num_streams", "uint32_class" }, { "suggested_buf_size", "uint32_class" }, { "width", "uint32_class" }, { "height", "uint32_class" }, { "reserved", "uint32_array_class" }, { "avih", "AVI_MAIN_HEADER" }, { "strl_list_id", "char_array_class" }, { "strl_size", "uint32_class" }, { "strl_type", "char_array_class" }, { "fcc_type", "char_array_class" }, { "fcc_handler", "char_array_class" }, { "priority", "uint16_class" }, { "language", "uint16_class" }, { "scale", "uint32_class" }, { "rate", "uint32_class" }, { "start", "uint32_class" }, { "length", "uint32_class" }, { "quality", "uint32_class" }, { "sample_size", "uint32_class" }, { "frame_left", "int16_class" }, { "frame_top", "int16_class" }, { "frame_right", "int16_class" }, { "frame_bottom", "int16_class" }, { "strh", "STREAM_HEADER" }, { "bi_size", "uint32_class" }, { "bi_width", "int32_class" }, { "bi_height", "int32_class" }, { "bi_planes", "uint16_class" }, { "bi_bit_count", "uint16_class" }, { "bi_compression", "uint32_class" }, { "bi_size_image", "uint32_class" }, { "bi_x_ppm", "int32_class" }, { "bi_y_ppm", "int32_class" }, { "bi_clr_used", "uint32_class" }, { "bi_clr_important", "uint32_class" }, { "strf_v", "STREAM_FORMAT_VIDEO" }, { "data", "ubyte_array_class" }, { "junk", "JUNK_CHUNK" }, { "movi_list_id", "char_array_class" }, { "movi_size", "uint32_class" }, { "movi_type", "char_array_class" }, { "vchunk_id", "char_array_class" }, { "vchunk_size", "uint32_class" }, { "vchunk_data", "ubyte_array_class" }, { "idx1_id", "char_array_class" }, { "idx1_size", "uint32_class" }, { "ck_id", "char_array_class" }, { "offset", "uint32_class" }, { "size", "uint32_class" }, { "idx1_entry", "IDX1_ENTRY" }, { "file", "avi_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 1, 1000000 }, { 1, 1000 }, { 1, 1920 }, { 1, 1080 }, { 1, 48000 }, { 1, 48000 }, { 1, 1920 }, { 1, 1080 }, { 8, 4096 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class riff_id_element;
	char_array_class riff_id;
	uint32_class riff_size;
	char_class form_type_element;
	char_array_class form_type;
	char_class hdrl_list_id_element;
	char_array_class hdrl_list_id;
	uint32_class hdrl_size;
	char_class hdrl_type_element;
	char_array_class hdrl_type;
	char_class chunk_id_element;
	char_array_class chunk_id;
	uint32_class chunk_size;
	uint32_class us_per_frame;
	uint32_class max_bytes_per_sec;
	uint32_class padding_granularity;
	uint32_class flags;
	uint32_class total_frames;
	uint32_class initial_frames;
	uint32_class num_streams;
	uint32_class suggested_buf_size;
	uint32_class width;
	uint32_class height;
	uint32_class reserved_element;
	uint32_array_class reserved;
	AVI_MAIN_HEADER avih;
	char_class strl_list_id_element;
	char_array_class strl_list_id;
	uint32_class strl_size;
	char_class strl_type_element;
	char_array_class strl_type;
	char_class fcc_type_element;
	char_array_class fcc_type;
	char_class fcc_handler_element;
	char_array_class fcc_handler;
	uint16_class priority;
	uint16_class language;
	uint32_class scale;
	uint32_class rate;
	uint32_class start;
	uint32_class length;
	uint32_class quality;
	uint32_class sample_size;
	int16_class frame_left;
	int16_class frame_top;
	int16_class frame_right;
	int16_class frame_bottom;
	STREAM_HEADER strh;
	uint32_class bi_size;
	int32_class bi_width;
	int32_class bi_height;
	uint16_class bi_planes;
	uint16_class bi_bit_count;
	uint32_class bi_compression;
	uint32_class bi_size_image;
	int32_class bi_x_ppm;
	int32_class bi_y_ppm;
	uint32_class bi_clr_used;
	uint32_class bi_clr_important;
	STREAM_FORMAT_VIDEO strf_v;
	ubyte_class data_element;
	ubyte_array_class data;
	JUNK_CHUNK junk;
	char_class movi_list_id_element;
	char_array_class movi_list_id;
	uint32_class movi_size;
	char_class movi_type_element;
	char_array_class movi_type;
	char_class vchunk_id_element;
	char_array_class vchunk_id;
	uint32_class vchunk_size;
	ubyte_class vchunk_data_element;
	ubyte_array_class vchunk_data;
	char_class idx1_id_element;
	char_array_class idx1_id;
	uint32_class idx1_size;
	char_class ck_id_element;
	char_array_class ck_id;
	uint32_class offset;
	uint32_class size;
	IDX1_ENTRY idx1_entry;
	avi_file file;


	globals_class() :
		riff_id_element(false),
		riff_id(riff_id_element),
		riff_size(1),
		form_type_element(false),
		form_type(form_type_element),
		hdrl_list_id_element(false),
		hdrl_list_id(hdrl_list_id_element),
		hdrl_size(1),
		hdrl_type_element(false),
		hdrl_type(hdrl_type_element),
		chunk_id_element(false),
		chunk_id(chunk_id_element),
		chunk_size(1),
		us_per_frame(3),
		max_bytes_per_sec(1),
		padding_granularity(1),
		flags(1),
		total_frames(4),
		initial_frames(1),
		num_streams(1),
		suggested_buf_size(1),
		width(5),
		height(6),
		reserved_element(false),
		reserved(reserved_element),
		avih(AVI_MAIN_HEADER_avih_instances),
		strl_list_id_element(false),
		strl_list_id(strl_list_id_element),
		strl_size(1),
		strl_type_element(false),
		strl_type(strl_type_element),
		fcc_type_element(false),
		fcc_type(fcc_type_element),
		fcc_handler_element(false),
		fcc_handler(fcc_handler_element),
		priority(1),
		language(1),
		scale(7),
		rate(8),
		start(1),
		length(1),
		quality(1),
		sample_size(1),
		frame_left(1),
		frame_top(1),
		frame_right(1),
		frame_bottom(1),
		strh(STREAM_HEADER_strh_instances),
		bi_size(1),
		bi_width(9),
		bi_height(10),
		bi_planes(1),
		bi_bit_count(1),
		bi_compression(1),
		bi_size_image(1),
		bi_x_ppm(1),
		bi_y_ppm(1),
		bi_clr_used(1),
		bi_clr_important(1),
		strf_v(STREAM_FORMAT_VIDEO_strf_v_instances),
		data_element(false),
		data(data_element),
		junk(JUNK_CHUNK_junk_instances),
		movi_list_id_element(false),
		movi_list_id(movi_list_id_element),
		movi_size(1),
		movi_type_element(false),
		movi_type(movi_type_element),
		vchunk_id_element(false),
		vchunk_id(vchunk_id_element),
		vchunk_size(11),
		vchunk_data_element(false),
		vchunk_data(vchunk_data_element),
		idx1_id_element(false),
		idx1_id(idx1_id_element),
		idx1_size(1),
		ck_id_element(false),
		ck_id(ck_id_element),
		offset(1),
		size(1),
		idx1_entry(IDX1_ENTRY_idx1_entry_instances),
		file(avi_file_file_instances)
	{}
};

globals_class* g;


AVI_MAIN_HEADER* AVI_MAIN_HEADER::generate() {
	if (generated == 1) {
		AVI_MAIN_HEADER* new_instance = new AVI_MAIN_HEADER(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "avih" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 56 }));
	GENERATE_VAR(us_per_frame, ::g->us_per_frame.generate());
	GENERATE_VAR(max_bytes_per_sec, ::g->max_bytes_per_sec.generate());
	GENERATE_VAR(padding_granularity, ::g->padding_granularity.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(total_frames, ::g->total_frames.generate());
	GENERATE_VAR(initial_frames, ::g->initial_frames.generate());
	GENERATE_VAR(num_streams, ::g->num_streams.generate({ 1, 2 }));
	GENERATE_VAR(suggested_buf_size, ::g->suggested_buf_size.generate());
	GENERATE_VAR(width, ::g->width.generate());
	GENERATE_VAR(height, ::g->height.generate());
	GENERATE_VAR(reserved, ::g->reserved.generate(4));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


STREAM_HEADER* STREAM_HEADER::generate() {
	if (generated == 1) {
		STREAM_HEADER* new_instance = new STREAM_HEADER(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "strh" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 56 }));
	GENERATE_VAR(fcc_type, ::g->fcc_type.generate(4, { "vids", "auds" }));
	GENERATE_VAR(fcc_handler, ::g->fcc_handler.generate(4));
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(priority, ::g->priority.generate());
	GENERATE_VAR(language, ::g->language.generate());
	GENERATE_VAR(initial_frames, ::g->initial_frames.generate());
	GENERATE_VAR(scale, ::g->scale.generate());
	GENERATE_VAR(rate, ::g->rate.generate());
	GENERATE_VAR(start, ::g->start.generate());
	GENERATE_VAR(length, ::g->length.generate());
	GENERATE_VAR(suggested_buf_size, ::g->suggested_buf_size.generate());
	GENERATE_VAR(quality, ::g->quality.generate());
	GENERATE_VAR(sample_size, ::g->sample_size.generate());
	GENERATE_VAR(frame_left, ::g->frame_left.generate());
	GENERATE_VAR(frame_top, ::g->frame_top.generate());
	GENERATE_VAR(frame_right, ::g->frame_right.generate());
	GENERATE_VAR(frame_bottom, ::g->frame_bottom.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


STREAM_FORMAT_VIDEO* STREAM_FORMAT_VIDEO::generate() {
	if (generated == 1) {
		STREAM_FORMAT_VIDEO* new_instance = new STREAM_FORMAT_VIDEO(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "strf" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 40 }));
	GENERATE_VAR(bi_size, ::g->bi_size.generate({ 40 }));
	GENERATE_VAR(bi_width, ::g->bi_width.generate());
	GENERATE_VAR(bi_height, ::g->bi_height.generate());
	GENERATE_VAR(bi_planes, ::g->bi_planes.generate({ 1 }));
	GENERATE_VAR(bi_bit_count, ::g->bi_bit_count.generate({ 24 }));
	GENERATE_VAR(bi_compression, ::g->bi_compression.generate({ 0 }));
	GENERATE_VAR(bi_size_image, ::g->bi_size_image.generate());
	GENERATE_VAR(bi_x_ppm, ::g->bi_x_ppm.generate());
	GENERATE_VAR(bi_y_ppm, ::g->bi_y_ppm.generate());
	GENERATE_VAR(bi_clr_used, ::g->bi_clr_used.generate());
	GENERATE_VAR(bi_clr_important, ::g->bi_clr_important.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


JUNK_CHUNK* JUNK_CHUNK::generate() {
	if (generated == 1) {
		JUNK_CHUNK* new_instance = new JUNK_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "JUNK" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(data, ::g->data.generate(chunk_size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IDX1_ENTRY* IDX1_ENTRY::generate() {
	if (generated == 1) {
		IDX1_ENTRY* new_instance = new IDX1_ENTRY(instances);
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

	GENERATE_VAR(ck_id, ::g->ck_id.generate(4));
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(offset, ::g->offset.generate());
	GENERATE_VAR(size, ::g->size.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


avi_file* avi_file::generate() {
	if (generated == 1) {
		avi_file* new_instance = new avi_file(instances);
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

	GENERATE_VAR(riff_id, ::g->riff_id.generate(4, { "RIFF" }));
	GENERATE_VAR(riff_size, ::g->riff_size.generate());
	GENERATE_VAR(form_type, ::g->form_type.generate(4, { "AVI " }));
	GENERATE_VAR(hdrl_list_id, ::g->hdrl_list_id.generate(4, { "LIST" }));
	GENERATE_VAR(hdrl_size, ::g->hdrl_size.generate());
	GENERATE_VAR(hdrl_type, ::g->hdrl_type.generate(4, { "hdrl" }));
	GENERATE_VAR(avih, ::g->avih.generate());
	GENERATE_VAR(strl_list_id, ::g->strl_list_id.generate(4, { "LIST" }));
	GENERATE_VAR(strl_size, ::g->strl_size.generate());
	GENERATE_VAR(strl_type, ::g->strl_type.generate(4, { "strl" }));
	GENERATE_VAR(strh, ::g->strh.generate());
	GENERATE_VAR(strf_v, ::g->strf_v.generate());
	GENERATE_VAR(junk, ::g->junk.generate());
	GENERATE_VAR(movi_list_id, ::g->movi_list_id.generate(4, { "LIST" }));
	GENERATE_VAR(movi_size, ::g->movi_size.generate());
	GENERATE_VAR(movi_type, ::g->movi_type.generate(4, { "movi" }));
	GENERATE_VAR(vchunk_id, ::g->vchunk_id.generate(4, { "00dc" }));
	GENERATE_VAR(vchunk_size, ::g->vchunk_size.generate());
	GENERATE_VAR(vchunk_data, ::g->vchunk_data.generate(vchunk_size()));
	GENERATE_VAR(idx1_id, ::g->idx1_id.generate(4, { "idx1" }));
	GENERATE_VAR(idx1_size, ::g->idx1_size.generate({ 16 }));
	GENERATE_VAR(idx1_entry, ::g->idx1_entry.generate());

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

