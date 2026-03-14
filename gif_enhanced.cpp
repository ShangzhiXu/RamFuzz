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



class GIF_HEADER {
	std::vector<GIF_HEADER*>& instances;

	std::string signature_var;
	std::string version_var;

public:
	bool signature_exists = false;
	bool version_exists = false;

	std::string& signature() {
		assert_cond(signature_exists, "struct field signature does not exist");
		return signature_var;
	}
	std::string& version() {
		assert_cond(version_exists, "struct field version does not exist");
		return version_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	GIF_HEADER& operator () () { return *instances.back(); }
	GIF_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	GIF_HEADER(std::vector<GIF_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~GIF_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			GIF_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	GIF_HEADER* generate();
};

int GIF_HEADER::_parent_id = 0;
int GIF_HEADER::_index_start = 0;



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



class LOGICAL_SCREEN_DESCRIPTOR {
	std::vector<LOGICAL_SCREEN_DESCRIPTOR*>& instances;

	uint16 width_var;
	uint16 height_var;
	ubyte packed_var;
	ubyte background_color_index_var;
	ubyte pixel_aspect_ratio_var;

public:
	bool width_exists = false;
	bool height_exists = false;
	bool packed_exists = false;
	bool background_color_index_exists = false;
	bool pixel_aspect_ratio_exists = false;

	uint16& width() {
		assert_cond(width_exists, "struct field width does not exist");
		return width_var;
	}
	uint16& height() {
		assert_cond(height_exists, "struct field height does not exist");
		return height_var;
	}
	ubyte& packed() {
		assert_cond(packed_exists, "struct field packed does not exist");
		return packed_var;
	}
	ubyte& background_color_index() {
		assert_cond(background_color_index_exists, "struct field background_color_index does not exist");
		return background_color_index_var;
	}
	ubyte& pixel_aspect_ratio() {
		assert_cond(pixel_aspect_ratio_exists, "struct field pixel_aspect_ratio does not exist");
		return pixel_aspect_ratio_var;
	}

	/* locals */
	ubyte gct_flag;
	ubyte gct_size_field;
	uint32 gct_entries;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGICAL_SCREEN_DESCRIPTOR& operator () () { return *instances.back(); }
	LOGICAL_SCREEN_DESCRIPTOR& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGICAL_SCREEN_DESCRIPTOR(std::vector<LOGICAL_SCREEN_DESCRIPTOR*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGICAL_SCREEN_DESCRIPTOR() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGICAL_SCREEN_DESCRIPTOR* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGICAL_SCREEN_DESCRIPTOR* generate();
};

int LOGICAL_SCREEN_DESCRIPTOR::_parent_id = 0;
int LOGICAL_SCREEN_DESCRIPTOR::_index_start = 0;



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



class COLOR_TABLE {
	std::vector<COLOR_TABLE*>& instances;

	std::vector<ubyte> colors_var;

public:
	bool colors_exists = false;

	std::vector<ubyte>& colors() {
		assert_cond(colors_exists, "struct field colors does not exist");
		return colors_var;
	}

	/* locals */
	uint32 data_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	COLOR_TABLE& operator () () { return *instances.back(); }
	COLOR_TABLE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	COLOR_TABLE(std::vector<COLOR_TABLE*>& instances) : instances(instances) { instances.push_back(this); }
	~COLOR_TABLE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			COLOR_TABLE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	COLOR_TABLE* generate(uint32 num_entries);
};

int COLOR_TABLE::_parent_id = 0;
int COLOR_TABLE::_index_start = 0;



class GRAPHIC_CONTROL_EXT {
	std::vector<GRAPHIC_CONTROL_EXT*>& instances;

	ubyte introducer_var;
	ubyte label_var;
	ubyte block_size_var;
	ubyte packed_var;
	uint16 delay_time_var;
	ubyte transparent_color_index_var;
	ubyte block_terminator_var;

public:
	bool introducer_exists = false;
	bool label_exists = false;
	bool block_size_exists = false;
	bool packed_exists = false;
	bool delay_time_exists = false;
	bool transparent_color_index_exists = false;
	bool block_terminator_exists = false;

	ubyte& introducer() {
		assert_cond(introducer_exists, "struct field introducer does not exist");
		return introducer_var;
	}
	ubyte& label() {
		assert_cond(label_exists, "struct field label does not exist");
		return label_var;
	}
	ubyte& block_size() {
		assert_cond(block_size_exists, "struct field block_size does not exist");
		return block_size_var;
	}
	ubyte& packed() {
		assert_cond(packed_exists, "struct field packed does not exist");
		return packed_var;
	}
	uint16& delay_time() {
		assert_cond(delay_time_exists, "struct field delay_time does not exist");
		return delay_time_var;
	}
	ubyte& transparent_color_index() {
		assert_cond(transparent_color_index_exists, "struct field transparent_color_index does not exist");
		return transparent_color_index_var;
	}
	ubyte& block_terminator() {
		assert_cond(block_terminator_exists, "struct field block_terminator does not exist");
		return block_terminator_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	GRAPHIC_CONTROL_EXT& operator () () { return *instances.back(); }
	GRAPHIC_CONTROL_EXT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	GRAPHIC_CONTROL_EXT(std::vector<GRAPHIC_CONTROL_EXT*>& instances) : instances(instances) { instances.push_back(this); }
	~GRAPHIC_CONTROL_EXT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			GRAPHIC_CONTROL_EXT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	GRAPHIC_CONTROL_EXT* generate();
};

int GRAPHIC_CONTROL_EXT::_parent_id = 0;
int GRAPHIC_CONTROL_EXT::_index_start = 0;



class COMMENT_EXT {
	std::vector<COMMENT_EXT*>& instances;

	ubyte introducer_var;
	ubyte label_var;
	ubyte sub_block_size_var;
	std::string comment_data_var;
	ubyte block_terminator_var;

public:
	bool introducer_exists = false;
	bool label_exists = false;
	bool sub_block_size_exists = false;
	bool comment_data_exists = false;
	bool block_terminator_exists = false;

	ubyte& introducer() {
		assert_cond(introducer_exists, "struct field introducer does not exist");
		return introducer_var;
	}
	ubyte& label() {
		assert_cond(label_exists, "struct field label does not exist");
		return label_var;
	}
	ubyte& sub_block_size() {
		assert_cond(sub_block_size_exists, "struct field sub_block_size does not exist");
		return sub_block_size_var;
	}
	std::string& comment_data() {
		assert_cond(comment_data_exists, "struct field comment_data does not exist");
		return comment_data_var;
	}
	ubyte& block_terminator() {
		assert_cond(block_terminator_exists, "struct field block_terminator does not exist");
		return block_terminator_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	COMMENT_EXT& operator () () { return *instances.back(); }
	COMMENT_EXT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	COMMENT_EXT(std::vector<COMMENT_EXT*>& instances) : instances(instances) { instances.push_back(this); }
	~COMMENT_EXT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			COMMENT_EXT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	COMMENT_EXT* generate();
};

int COMMENT_EXT::_parent_id = 0;
int COMMENT_EXT::_index_start = 0;



class APP_EXT_NETSCAPE {
	std::vector<APP_EXT_NETSCAPE*>& instances;

	ubyte introducer_var;
	ubyte label_var;
	ubyte block_size_var;
	std::string app_id_var;
	std::string auth_code_var;
	ubyte sub_block_size_var;
	ubyte sub_block_id_var;
	uint16 loop_count_var;
	ubyte block_terminator_var;

public:
	bool introducer_exists = false;
	bool label_exists = false;
	bool block_size_exists = false;
	bool app_id_exists = false;
	bool auth_code_exists = false;
	bool sub_block_size_exists = false;
	bool sub_block_id_exists = false;
	bool loop_count_exists = false;
	bool block_terminator_exists = false;

	ubyte& introducer() {
		assert_cond(introducer_exists, "struct field introducer does not exist");
		return introducer_var;
	}
	ubyte& label() {
		assert_cond(label_exists, "struct field label does not exist");
		return label_var;
	}
	ubyte& block_size() {
		assert_cond(block_size_exists, "struct field block_size does not exist");
		return block_size_var;
	}
	std::string& app_id() {
		assert_cond(app_id_exists, "struct field app_id does not exist");
		return app_id_var;
	}
	std::string& auth_code() {
		assert_cond(auth_code_exists, "struct field auth_code does not exist");
		return auth_code_var;
	}
	ubyte& sub_block_size() {
		assert_cond(sub_block_size_exists, "struct field sub_block_size does not exist");
		return sub_block_size_var;
	}
	ubyte& sub_block_id() {
		assert_cond(sub_block_id_exists, "struct field sub_block_id does not exist");
		return sub_block_id_var;
	}
	uint16& loop_count() {
		assert_cond(loop_count_exists, "struct field loop_count does not exist");
		return loop_count_var;
	}
	ubyte& block_terminator() {
		assert_cond(block_terminator_exists, "struct field block_terminator does not exist");
		return block_terminator_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	APP_EXT_NETSCAPE& operator () () { return *instances.back(); }
	APP_EXT_NETSCAPE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	APP_EXT_NETSCAPE(std::vector<APP_EXT_NETSCAPE*>& instances) : instances(instances) { instances.push_back(this); }
	~APP_EXT_NETSCAPE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			APP_EXT_NETSCAPE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	APP_EXT_NETSCAPE* generate();
};

int APP_EXT_NETSCAPE::_parent_id = 0;
int APP_EXT_NETSCAPE::_index_start = 0;



class IMAGE_DESCRIPTOR {
	std::vector<IMAGE_DESCRIPTOR*>& instances;

	ubyte separator_var;
	uint16 left_position_var;
	uint16 top_position_var;
	uint16 img_width_var;
	uint16 img_height_var;
	ubyte packed_var;

public:
	bool separator_exists = false;
	bool left_position_exists = false;
	bool top_position_exists = false;
	bool img_width_exists = false;
	bool img_height_exists = false;
	bool packed_exists = false;

	ubyte& separator() {
		assert_cond(separator_exists, "struct field separator does not exist");
		return separator_var;
	}
	uint16& left_position() {
		assert_cond(left_position_exists, "struct field left_position does not exist");
		return left_position_var;
	}
	uint16& top_position() {
		assert_cond(top_position_exists, "struct field top_position does not exist");
		return top_position_var;
	}
	uint16& img_width() {
		assert_cond(img_width_exists, "struct field img_width does not exist");
		return img_width_var;
	}
	uint16& img_height() {
		assert_cond(img_height_exists, "struct field img_height does not exist");
		return img_height_var;
	}
	ubyte& packed() {
		assert_cond(packed_exists, "struct field packed does not exist");
		return packed_var;
	}

	/* locals */
	ubyte lct_flag;
	ubyte lct_size_field;
	uint32 lct_entries;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IMAGE_DESCRIPTOR& operator () () { return *instances.back(); }
	IMAGE_DESCRIPTOR& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IMAGE_DESCRIPTOR(std::vector<IMAGE_DESCRIPTOR*>& instances) : instances(instances) { instances.push_back(this); }
	~IMAGE_DESCRIPTOR() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IMAGE_DESCRIPTOR* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IMAGE_DESCRIPTOR* generate();
};

int IMAGE_DESCRIPTOR::_parent_id = 0;
int IMAGE_DESCRIPTOR::_index_start = 0;



class IMAGE_DATA {
	std::vector<IMAGE_DATA*>& instances;

	ubyte lzw_min_code_size_var;
	ubyte sub_block_size_var;
	std::vector<ubyte> sub_block_data_var;
	ubyte block_terminator_var;

public:
	bool lzw_min_code_size_exists = false;
	bool sub_block_size_exists = false;
	bool sub_block_data_exists = false;
	bool block_terminator_exists = false;

	ubyte& lzw_min_code_size() {
		assert_cond(lzw_min_code_size_exists, "struct field lzw_min_code_size does not exist");
		return lzw_min_code_size_var;
	}
	ubyte& sub_block_size() {
		assert_cond(sub_block_size_exists, "struct field sub_block_size does not exist");
		return sub_block_size_var;
	}
	std::vector<ubyte>& sub_block_data() {
		assert_cond(sub_block_data_exists, "struct field sub_block_data does not exist");
		return sub_block_data_var;
	}
	ubyte& block_terminator() {
		assert_cond(block_terminator_exists, "struct field block_terminator does not exist");
		return block_terminator_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IMAGE_DATA& operator () () { return *instances.back(); }
	IMAGE_DATA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IMAGE_DATA(std::vector<IMAGE_DATA*>& instances) : instances(instances) { instances.push_back(this); }
	~IMAGE_DATA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IMAGE_DATA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IMAGE_DATA* generate();
};

int IMAGE_DATA::_parent_id = 0;
int IMAGE_DATA::_index_start = 0;



class GIF_TRAILER {
	std::vector<GIF_TRAILER*>& instances;

	ubyte trailer_var;

public:
	bool trailer_exists = false;

	ubyte& trailer() {
		assert_cond(trailer_exists, "struct field trailer does not exist");
		return trailer_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	GIF_TRAILER& operator () () { return *instances.back(); }
	GIF_TRAILER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	GIF_TRAILER(std::vector<GIF_TRAILER*>& instances) : instances(instances) { instances.push_back(this); }
	~GIF_TRAILER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			GIF_TRAILER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	GIF_TRAILER* generate();
};

int GIF_TRAILER::_parent_id = 0;
int GIF_TRAILER::_index_start = 0;



class gif_file {
	std::vector<gif_file*>& instances;

	GIF_HEADER* header_var;
	LOGICAL_SCREEN_DESCRIPTOR* lsd_var;
	COLOR_TABLE* gct_var;
	GRAPHIC_CONTROL_EXT* gce_var;
	COMMENT_EXT* comment_var;
	APP_EXT_NETSCAPE* netscape_var;
	IMAGE_DESCRIPTOR* img_desc_var;
	COLOR_TABLE* lct_var;
	IMAGE_DATA* img_data_var;
	GIF_TRAILER* trailer_var;

public:
	bool header_exists = false;
	bool lsd_exists = false;
	bool gct_exists = false;
	bool gce_exists = false;
	bool comment_exists = false;
	bool netscape_exists = false;
	bool img_desc_exists = false;
	bool lct_exists = false;
	bool img_data_exists = false;
	bool trailer_exists = false;

	GIF_HEADER& header() {
		assert_cond(header_exists, "struct field header does not exist");
		return *header_var;
	}
	LOGICAL_SCREEN_DESCRIPTOR& lsd() {
		assert_cond(lsd_exists, "struct field lsd does not exist");
		return *lsd_var;
	}
	COLOR_TABLE& gct() {
		assert_cond(gct_exists, "struct field gct does not exist");
		return *gct_var;
	}
	GRAPHIC_CONTROL_EXT& gce() {
		assert_cond(gce_exists, "struct field gce does not exist");
		return *gce_var;
	}
	COMMENT_EXT& comment() {
		assert_cond(comment_exists, "struct field comment does not exist");
		return *comment_var;
	}
	APP_EXT_NETSCAPE& netscape() {
		assert_cond(netscape_exists, "struct field netscape does not exist");
		return *netscape_var;
	}
	IMAGE_DESCRIPTOR& img_desc() {
		assert_cond(img_desc_exists, "struct field img_desc does not exist");
		return *img_desc_var;
	}
	COLOR_TABLE& lct() {
		assert_cond(lct_exists, "struct field lct does not exist");
		return *lct_var;
	}
	IMAGE_DATA& img_data() {
		assert_cond(img_data_exists, "struct field img_data does not exist");
		return *img_data_var;
	}
	GIF_TRAILER& trailer() {
		assert_cond(trailer_exists, "struct field trailer does not exist");
		return *trailer_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	gif_file& operator () () { return *instances.back(); }
	gif_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	gif_file(std::vector<gif_file*>& instances) : instances(instances) { instances.push_back(this); }
	~gif_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			gif_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	gif_file* generate();
};

int gif_file::_parent_id = 0;
int gif_file::_index_start = 0;

std::vector<byte> ReadByteInitValues;
std::vector<ubyte> ReadUByteInitValues = {  };
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
std::vector<std::string> ReadBytesInitValues = { "GIF", "\x21\xF9", "\x21\xFE", "\x21\x01", "\x21\xFF", "\x2C", "\x3B" };


std::vector<GIF_HEADER*> GIF_HEADER_header_instances;
std::vector<LOGICAL_SCREEN_DESCRIPTOR*> LOGICAL_SCREEN_DESCRIPTOR_lsd_instances;
std::vector<COLOR_TABLE*> COLOR_TABLE_gct_instances;
std::vector<GRAPHIC_CONTROL_EXT*> GRAPHIC_CONTROL_EXT_gce_instances;
std::vector<COMMENT_EXT*> COMMENT_EXT_comment_instances;
std::vector<APP_EXT_NETSCAPE*> APP_EXT_NETSCAPE_netscape_instances;
std::vector<IMAGE_DESCRIPTOR*> IMAGE_DESCRIPTOR_img_desc_instances;
std::vector<COLOR_TABLE*> COLOR_TABLE_lct_instances;
std::vector<IMAGE_DATA*> IMAGE_DATA_img_data_instances;
std::vector<GIF_TRAILER*> GIF_TRAILER_trailer__instances;
std::vector<gif_file*> gif_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "signature", "char_array_class" }, { "version", "char_array_class" }, { "header", "GIF_HEADER" }, { "width", "uint16_class" }, { "height", "uint16_class" }, { "packed", "ubyte_class" }, { "background_color_index", "ubyte_class" }, { "pixel_aspect_ratio", "ubyte_class" }, { "lsd", "LOGICAL_SCREEN_DESCRIPTOR" }, { "colors", "ubyte_array_class" }, { "gct", "COLOR_TABLE" }, { "introducer", "ubyte_class" }, { "label", "ubyte_class" }, { "block_size", "ubyte_class" }, { "delay_time", "uint16_class" }, { "transparent_color_index", "ubyte_class" }, { "block_terminator", "ubyte_class" }, { "gce", "GRAPHIC_CONTROL_EXT" }, { "sub_block_size", "ubyte_class" }, { "comment_data", "char_array_class" }, { "comment", "COMMENT_EXT" }, { "app_id", "char_array_class" }, { "auth_code", "char_array_class" }, { "sub_block_id", "ubyte_class" }, { "loop_count", "uint16_class" }, { "netscape", "APP_EXT_NETSCAPE" }, { "separator", "ubyte_class" }, { "left_position", "uint16_class" }, { "top_position", "uint16_class" }, { "img_width", "uint16_class" }, { "img_height", "uint16_class" }, { "img_desc", "IMAGE_DESCRIPTOR" }, { "lct", "COLOR_TABLE" }, { "lzw_min_code_size", "ubyte_class" }, { "sub_block_data", "ubyte_array_class" }, { "img_data", "IMAGE_DATA" }, { "trailer", "ubyte_class" }, { "trailer_", "GIF_TRAILER" }, { "file", "gif_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 1, 1024 }, { 1, 1024 }, { 1, 255 }, { 1, 1024 }, { 1, 1024 }, { 2, 12 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class signature_element;
	char_array_class signature;
	char_class version_element;
	char_array_class version;
	GIF_HEADER header;
	uint16_class width;
	uint16_class height;
	ubyte_class packed;
	ubyte_class background_color_index;
	ubyte_class pixel_aspect_ratio;
	LOGICAL_SCREEN_DESCRIPTOR lsd;
	ubyte_class colors_element;
	ubyte_array_class colors;
	COLOR_TABLE gct;
	ubyte_class introducer;
	ubyte_class label;
	ubyte_class block_size;
	uint16_class delay_time;
	ubyte_class transparent_color_index;
	ubyte_class block_terminator;
	GRAPHIC_CONTROL_EXT gce;
	ubyte_class sub_block_size;
	char_class comment_data_element;
	char_array_class comment_data;
	COMMENT_EXT comment;
	char_class app_id_element;
	char_array_class app_id;
	char_class auth_code_element;
	char_array_class auth_code;
	ubyte_class sub_block_id;
	uint16_class loop_count;
	APP_EXT_NETSCAPE netscape;
	ubyte_class separator;
	uint16_class left_position;
	uint16_class top_position;
	uint16_class img_width;
	uint16_class img_height;
	IMAGE_DESCRIPTOR img_desc;
	COLOR_TABLE lct;
	ubyte_class lzw_min_code_size;
	ubyte_class sub_block_data_element;
	ubyte_array_class sub_block_data;
	IMAGE_DATA img_data;
	ubyte_class trailer;
	GIF_TRAILER trailer_;
	gif_file file;


	globals_class() :
		signature_element(false),
		signature(signature_element),
		version_element(false),
		version(version_element),
		header(GIF_HEADER_header_instances),
		width(3),
		height(4),
		packed(1),
		background_color_index(1),
		pixel_aspect_ratio(1),
		lsd(LOGICAL_SCREEN_DESCRIPTOR_lsd_instances),
		colors_element(false),
		colors(colors_element),
		gct(COLOR_TABLE_gct_instances),
		introducer(1),
		label(1),
		block_size(1),
		delay_time(1),
		transparent_color_index(1),
		block_terminator(1),
		gce(GRAPHIC_CONTROL_EXT_gce_instances),
		sub_block_size(5),
		comment_data_element(false),
		comment_data(comment_data_element),
		comment(COMMENT_EXT_comment_instances),
		app_id_element(false),
		app_id(app_id_element),
		auth_code_element(false),
		auth_code(auth_code_element),
		sub_block_id(1),
		loop_count(1),
		netscape(APP_EXT_NETSCAPE_netscape_instances),
		separator(1),
		left_position(1),
		top_position(1),
		img_width(6),
		img_height(7),
		img_desc(IMAGE_DESCRIPTOR_img_desc_instances),
		lct(COLOR_TABLE_lct_instances),
		lzw_min_code_size(8),
		sub_block_data_element(false),
		sub_block_data(sub_block_data_element),
		img_data(IMAGE_DATA_img_data_instances),
		trailer(1),
		trailer_(GIF_TRAILER_trailer__instances),
		file(gif_file_file_instances)
	{}
};

globals_class* g;


GIF_HEADER* GIF_HEADER::generate() {
	if (generated == 1) {
		GIF_HEADER* new_instance = new GIF_HEADER(instances);
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

	GENERATE_VAR(signature, ::g->signature.generate(3, { "GIF" }));
	GENERATE_VAR(version, ::g->version.generate(3, { "89a" }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGICAL_SCREEN_DESCRIPTOR* LOGICAL_SCREEN_DESCRIPTOR::generate() {
	if (generated == 1) {
		LOGICAL_SCREEN_DESCRIPTOR* new_instance = new LOGICAL_SCREEN_DESCRIPTOR(instances);
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

	GENERATE_VAR(width, ::g->width.generate());
	GENERATE_VAR(height, ::g->height.generate());
	GENERATE_VAR(packed, ::g->packed.generate({ 0x87, 0xF7, 0x77, 0x47, 0x37, 0x27, 0x17 }));
	GENERATE_VAR(background_color_index, ::g->background_color_index.generate());
	GENERATE_VAR(pixel_aspect_ratio, ::g->pixel_aspect_ratio.generate({ 0 }));
	gct_flag = ((packed() >> 7) & 1);
	gct_size_field = (packed() & 7);
	gct_entries = (1 << (gct_size_field + 1));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


COLOR_TABLE* COLOR_TABLE::generate(uint32 num_entries) {
	if (generated == 1) {
		COLOR_TABLE* new_instance = new COLOR_TABLE(instances);
		new_instance->generated = 2;
		return new_instance->generate(num_entries);
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	data_size = (num_entries * 3);
	GENERATE_VAR(colors, ::g->colors.generate(data_size));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


GRAPHIC_CONTROL_EXT* GRAPHIC_CONTROL_EXT::generate() {
	if (generated == 1) {
		GRAPHIC_CONTROL_EXT* new_instance = new GRAPHIC_CONTROL_EXT(instances);
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

	GENERATE_VAR(introducer, ::g->introducer.generate({ 0x21 }));
	GENERATE_VAR(label, ::g->label.generate({ 0xF9 }));
	GENERATE_VAR(block_size, ::g->block_size.generate({ 4 }));
	GENERATE_VAR(packed, ::g->packed.generate());
	GENERATE_VAR(delay_time, ::g->delay_time.generate());
	GENERATE_VAR(transparent_color_index, ::g->transparent_color_index.generate());
	GENERATE_VAR(block_terminator, ::g->block_terminator.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


COMMENT_EXT* COMMENT_EXT::generate() {
	if (generated == 1) {
		COMMENT_EXT* new_instance = new COMMENT_EXT(instances);
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

	GENERATE_VAR(introducer, ::g->introducer.generate({ 0x21 }));
	GENERATE_VAR(label, ::g->label.generate({ 0xFE }));
	GENERATE_VAR(sub_block_size, ::g->sub_block_size.generate());
	GENERATE_VAR(comment_data, ::g->comment_data.generate(sub_block_size()));
	GENERATE_VAR(block_terminator, ::g->block_terminator.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


APP_EXT_NETSCAPE* APP_EXT_NETSCAPE::generate() {
	if (generated == 1) {
		APP_EXT_NETSCAPE* new_instance = new APP_EXT_NETSCAPE(instances);
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

	GENERATE_VAR(introducer, ::g->introducer.generate({ 0x21 }));
	GENERATE_VAR(label, ::g->label.generate({ 0xFF }));
	GENERATE_VAR(block_size, ::g->block_size.generate({ 11 }));
	GENERATE_VAR(app_id, ::g->app_id.generate(8, { "NETSCAPE" }));
	GENERATE_VAR(auth_code, ::g->auth_code.generate(3, { "2.0" }));
	GENERATE_VAR(sub_block_size, ::g->sub_block_size.generate({ 3 }));
	GENERATE_VAR(sub_block_id, ::g->sub_block_id.generate({ 1 }));
	GENERATE_VAR(loop_count, ::g->loop_count.generate());
	GENERATE_VAR(block_terminator, ::g->block_terminator.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IMAGE_DESCRIPTOR* IMAGE_DESCRIPTOR::generate() {
	if (generated == 1) {
		IMAGE_DESCRIPTOR* new_instance = new IMAGE_DESCRIPTOR(instances);
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

	GENERATE_VAR(separator, ::g->separator.generate({ 0x2C }));
	GENERATE_VAR(left_position, ::g->left_position.generate());
	GENERATE_VAR(top_position, ::g->top_position.generate());
	GENERATE_VAR(img_width, ::g->img_width.generate());
	GENERATE_VAR(img_height, ::g->img_height.generate());
	GENERATE_VAR(packed, ::g->packed.generate());
	lct_flag = ((packed() >> 7) & 1);
	lct_size_field = (packed() & 7);
	lct_entries = (1 << (lct_size_field + 1));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IMAGE_DATA* IMAGE_DATA::generate() {
	if (generated == 1) {
		IMAGE_DATA* new_instance = new IMAGE_DATA(instances);
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

	GENERATE_VAR(lzw_min_code_size, ::g->lzw_min_code_size.generate());
	GENERATE_VAR(sub_block_size, ::g->sub_block_size.generate());
	GENERATE_VAR(sub_block_data, ::g->sub_block_data.generate(sub_block_size()));
	GENERATE_VAR(block_terminator, ::g->block_terminator.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


GIF_TRAILER* GIF_TRAILER::generate() {
	if (generated == 1) {
		GIF_TRAILER* new_instance = new GIF_TRAILER(instances);
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

	GENERATE_VAR(trailer, ::g->trailer.generate({ 0x3B }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


gif_file* gif_file::generate() {
	if (generated == 1) {
		gif_file* new_instance = new gif_file(instances);
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

	GENERATE_VAR(header, ::g->header.generate());
	GENERATE_VAR(lsd, ::g->lsd.generate());
	if (lsd().gct_flag) {
		GENERATE_VAR(gct, ::g->gct.generate(lsd().gct_entries));
	};
	GENERATE_VAR(gce, ::g->gce.generate());
	GENERATE_VAR(comment, ::g->comment.generate());
	GENERATE_VAR(netscape, ::g->netscape.generate());
	GENERATE_VAR(img_desc, ::g->img_desc.generate());
	if (img_desc().lct_flag) {
		GENERATE_VAR(lct, ::g->lct.generate(img_desc().lct_entries));
	};
	GENERATE_VAR(img_data, ::g->img_data.generate());
	GENERATE_VAR(trailer, ::g->trailer_.generate());

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

