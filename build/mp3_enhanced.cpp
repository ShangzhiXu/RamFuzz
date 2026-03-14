#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"
/*local*/ const std::vector<uint32> bitrate_table = { 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, 0, 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0, 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0, 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0, 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 0, 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0 };/*local*/ const std::vector<uint32> samplerate_table = { 11025, 12000, 8000, 0, 0, 0, 0, 0, 22050, 24000, 16000, 0, 44100, 48000, 32000, 0 };/*local*/ const std::vector<uint32> samples_per_frame = { 0, 576, 1152, 384, 0, 0, 0, 0, 0, 576, 1152, 384, 0, 1152, 1152, 384 };/*local*/ const std::vector<uint32> slot_size_table = { 0, 1, 1, 4 };

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



class ID3V2_FRAME_FLAGS {
	std::vector<ID3V2_FRAME_FLAGS*>& instances;

	ubyte flags1_var;
	ubyte flags2_var;

public:
	bool flags1_exists = false;
	bool flags2_exists = false;

	ubyte& flags1() {
		assert_cond(flags1_exists, "struct field flags1 does not exist");
		return flags1_var;
	}
	ubyte& flags2() {
		assert_cond(flags2_exists, "struct field flags2 does not exist");
		return flags2_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_FRAME_FLAGS& operator () () { return *instances.back(); }
	ID3V2_FRAME_FLAGS& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_FRAME_FLAGS(std::vector<ID3V2_FRAME_FLAGS*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_FRAME_FLAGS() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_FRAME_FLAGS* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_FRAME_FLAGS* generate();
};

int ID3V2_FRAME_FLAGS::_parent_id = 0;
int ID3V2_FRAME_FLAGS::_index_start = 0;



class ID3V2_TEXT_FRAME {
	std::vector<ID3V2_TEXT_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string text_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool text_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& text_data() {
		assert_cond(text_data_exists, "struct field text_data does not exist");
		return text_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_TEXT_FRAME& operator () () { return *instances.back(); }
	ID3V2_TEXT_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_TEXT_FRAME(std::vector<ID3V2_TEXT_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_TEXT_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_TEXT_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_TEXT_FRAME* generate();
};

int ID3V2_TEXT_FRAME::_parent_id = 0;
int ID3V2_TEXT_FRAME::_index_start = 0;



class ID3V2_COMM_FRAME {
	std::vector<ID3V2_COMM_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string language_var;
	std::string comment_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool language_exists = false;
	bool comment_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return language_var;
	}
	std::string& comment_data() {
		assert_cond(comment_data_exists, "struct field comment_data does not exist");
		return comment_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_COMM_FRAME& operator () () { return *instances.back(); }
	ID3V2_COMM_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_COMM_FRAME(std::vector<ID3V2_COMM_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_COMM_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_COMM_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_COMM_FRAME* generate();
};

int ID3V2_COMM_FRAME::_parent_id = 0;
int ID3V2_COMM_FRAME::_index_start = 0;



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



class ID3V2_APIC_FRAME {
	std::vector<ID3V2_APIC_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string mime_type_var;
	ubyte null_term1_var;
	ubyte picture_type_var;
	ubyte null_term2_var;
	std::vector<ubyte> picture_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool mime_type_exists = false;
	bool null_term1_exists = false;
	bool picture_type_exists = false;
	bool null_term2_exists = false;
	bool picture_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& mime_type() {
		assert_cond(mime_type_exists, "struct field mime_type does not exist");
		return mime_type_var;
	}
	ubyte& null_term1() {
		assert_cond(null_term1_exists, "struct field null_term1 does not exist");
		return null_term1_var;
	}
	ubyte& picture_type() {
		assert_cond(picture_type_exists, "struct field picture_type does not exist");
		return picture_type_var;
	}
	ubyte& null_term2() {
		assert_cond(null_term2_exists, "struct field null_term2 does not exist");
		return null_term2_var;
	}
	std::vector<ubyte>& picture_data() {
		assert_cond(picture_data_exists, "struct field picture_data does not exist");
		return picture_data_var;
	}

	/* locals */
	uint32 pic_data_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_APIC_FRAME& operator () () { return *instances.back(); }
	ID3V2_APIC_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_APIC_FRAME(std::vector<ID3V2_APIC_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_APIC_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_APIC_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_APIC_FRAME* generate();
};

int ID3V2_APIC_FRAME::_parent_id = 0;
int ID3V2_APIC_FRAME::_index_start = 0;



class ID3V2_USLT_FRAME {
	std::vector<ID3V2_USLT_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string language_var;
	std::string lyrics_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool language_exists = false;
	bool lyrics_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return language_var;
	}
	std::string& lyrics_data() {
		assert_cond(lyrics_data_exists, "struct field lyrics_data does not exist");
		return lyrics_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_USLT_FRAME& operator () () { return *instances.back(); }
	ID3V2_USLT_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_USLT_FRAME(std::vector<ID3V2_USLT_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_USLT_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_USLT_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_USLT_FRAME* generate();
};

int ID3V2_USLT_FRAME::_parent_id = 0;
int ID3V2_USLT_FRAME::_index_start = 0;



class ID3V2_TXXX_FRAME {
	std::vector<ID3V2_TXXX_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string txxx_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool txxx_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& txxx_data() {
		assert_cond(txxx_data_exists, "struct field txxx_data does not exist");
		return txxx_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_TXXX_FRAME& operator () () { return *instances.back(); }
	ID3V2_TXXX_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_TXXX_FRAME(std::vector<ID3V2_TXXX_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_TXXX_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_TXXX_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_TXXX_FRAME* generate();
};

int ID3V2_TXXX_FRAME::_parent_id = 0;
int ID3V2_TXXX_FRAME::_index_start = 0;



class ID3V2_WXXX_FRAME {
	std::vector<ID3V2_WXXX_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string wxxx_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool wxxx_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& wxxx_data() {
		assert_cond(wxxx_data_exists, "struct field wxxx_data does not exist");
		return wxxx_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_WXXX_FRAME& operator () () { return *instances.back(); }
	ID3V2_WXXX_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_WXXX_FRAME(std::vector<ID3V2_WXXX_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_WXXX_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_WXXX_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_WXXX_FRAME* generate();
};

int ID3V2_WXXX_FRAME::_parent_id = 0;
int ID3V2_WXXX_FRAME::_index_start = 0;



class ID3V2_URL_FRAME {
	std::vector<ID3V2_URL_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::string url_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool url_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::string& url() {
		assert_cond(url_exists, "struct field url does not exist");
		return url_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_URL_FRAME& operator () () { return *instances.back(); }
	ID3V2_URL_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_URL_FRAME(std::vector<ID3V2_URL_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_URL_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_URL_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_URL_FRAME* generate();
};

int ID3V2_URL_FRAME::_parent_id = 0;
int ID3V2_URL_FRAME::_index_start = 0;



class ID3V2_PCNT_FRAME {
	std::vector<ID3V2_PCNT_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	uint32 counter_var;
	std::vector<ubyte> extra_counter_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool counter_exists = false;
	bool extra_counter_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	uint32& counter() {
		assert_cond(counter_exists, "struct field counter does not exist");
		return counter_var;
	}
	std::vector<ubyte>& extra_counter() {
		assert_cond(extra_counter_exists, "struct field extra_counter does not exist");
		return extra_counter_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_PCNT_FRAME& operator () () { return *instances.back(); }
	ID3V2_PCNT_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_PCNT_FRAME(std::vector<ID3V2_PCNT_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_PCNT_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_PCNT_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_PCNT_FRAME* generate();
};

int ID3V2_PCNT_FRAME::_parent_id = 0;
int ID3V2_PCNT_FRAME::_index_start = 0;



class ID3V2_POPM_FRAME {
	std::vector<ID3V2_POPM_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> popm_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool popm_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& popm_data() {
		assert_cond(popm_data_exists, "struct field popm_data does not exist");
		return popm_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_POPM_FRAME& operator () () { return *instances.back(); }
	ID3V2_POPM_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_POPM_FRAME(std::vector<ID3V2_POPM_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_POPM_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_POPM_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_POPM_FRAME* generate();
};

int ID3V2_POPM_FRAME::_parent_id = 0;
int ID3V2_POPM_FRAME::_index_start = 0;



class ID3V2_PRIV_FRAME {
	std::vector<ID3V2_PRIV_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> priv_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool priv_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& priv_data() {
		assert_cond(priv_data_exists, "struct field priv_data does not exist");
		return priv_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_PRIV_FRAME& operator () () { return *instances.back(); }
	ID3V2_PRIV_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_PRIV_FRAME(std::vector<ID3V2_PRIV_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_PRIV_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_PRIV_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_PRIV_FRAME* generate();
};

int ID3V2_PRIV_FRAME::_parent_id = 0;
int ID3V2_PRIV_FRAME::_index_start = 0;



class ID3V2_UFID_FRAME {
	std::vector<ID3V2_UFID_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> ufid_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool ufid_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& ufid_data() {
		assert_cond(ufid_data_exists, "struct field ufid_data does not exist");
		return ufid_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_UFID_FRAME& operator () () { return *instances.back(); }
	ID3V2_UFID_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_UFID_FRAME(std::vector<ID3V2_UFID_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_UFID_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_UFID_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_UFID_FRAME* generate();
};

int ID3V2_UFID_FRAME::_parent_id = 0;
int ID3V2_UFID_FRAME::_index_start = 0;



class ID3V2_GEOB_FRAME {
	std::vector<ID3V2_GEOB_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::vector<ubyte> geob_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool geob_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::vector<ubyte>& geob_data() {
		assert_cond(geob_data_exists, "struct field geob_data does not exist");
		return geob_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_GEOB_FRAME& operator () () { return *instances.back(); }
	ID3V2_GEOB_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_GEOB_FRAME(std::vector<ID3V2_GEOB_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_GEOB_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_GEOB_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_GEOB_FRAME* generate();
};

int ID3V2_GEOB_FRAME::_parent_id = 0;
int ID3V2_GEOB_FRAME::_index_start = 0;



class ID3V2_MCDI_FRAME {
	std::vector<ID3V2_MCDI_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> cd_toc_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool cd_toc_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& cd_toc() {
		assert_cond(cd_toc_exists, "struct field cd_toc does not exist");
		return cd_toc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_MCDI_FRAME& operator () () { return *instances.back(); }
	ID3V2_MCDI_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_MCDI_FRAME(std::vector<ID3V2_MCDI_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_MCDI_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_MCDI_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_MCDI_FRAME* generate();
};

int ID3V2_MCDI_FRAME::_parent_id = 0;
int ID3V2_MCDI_FRAME::_index_start = 0;



class ID3V2_ETCO_FRAME {
	std::vector<ID3V2_ETCO_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte timestamp_format_var;
	std::vector<ubyte> event_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool timestamp_format_exists = false;
	bool event_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& timestamp_format() {
		assert_cond(timestamp_format_exists, "struct field timestamp_format does not exist");
		return timestamp_format_var;
	}
	std::vector<ubyte>& event_data() {
		assert_cond(event_data_exists, "struct field event_data does not exist");
		return event_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_ETCO_FRAME& operator () () { return *instances.back(); }
	ID3V2_ETCO_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_ETCO_FRAME(std::vector<ID3V2_ETCO_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_ETCO_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_ETCO_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_ETCO_FRAME* generate();
};

int ID3V2_ETCO_FRAME::_parent_id = 0;
int ID3V2_ETCO_FRAME::_index_start = 0;



class ID3V2_SYLT_FRAME {
	std::vector<ID3V2_SYLT_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string language_var;
	ubyte timestamp_format_var;
	ubyte content_type_var;
	std::vector<ubyte> sylt_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool language_exists = false;
	bool timestamp_format_exists = false;
	bool content_type_exists = false;
	bool sylt_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return language_var;
	}
	ubyte& timestamp_format() {
		assert_cond(timestamp_format_exists, "struct field timestamp_format does not exist");
		return timestamp_format_var;
	}
	ubyte& content_type() {
		assert_cond(content_type_exists, "struct field content_type does not exist");
		return content_type_var;
	}
	std::vector<ubyte>& sylt_data() {
		assert_cond(sylt_data_exists, "struct field sylt_data does not exist");
		return sylt_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_SYLT_FRAME& operator () () { return *instances.back(); }
	ID3V2_SYLT_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_SYLT_FRAME(std::vector<ID3V2_SYLT_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_SYLT_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_SYLT_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_SYLT_FRAME* generate();
};

int ID3V2_SYLT_FRAME::_parent_id = 0;
int ID3V2_SYLT_FRAME::_index_start = 0;



class ID3V2_RVA2_FRAME {
	std::vector<ID3V2_RVA2_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> rva2_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool rva2_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& rva2_data() {
		assert_cond(rva2_data_exists, "struct field rva2_data does not exist");
		return rva2_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_RVA2_FRAME& operator () () { return *instances.back(); }
	ID3V2_RVA2_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_RVA2_FRAME(std::vector<ID3V2_RVA2_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_RVA2_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_RVA2_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_RVA2_FRAME* generate();
};

int ID3V2_RVA2_FRAME::_parent_id = 0;
int ID3V2_RVA2_FRAME::_index_start = 0;



class ID3V2_EQU2_FRAME {
	std::vector<ID3V2_EQU2_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte interpolation_method_var;
	std::vector<ubyte> equ2_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool interpolation_method_exists = false;
	bool equ2_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& interpolation_method() {
		assert_cond(interpolation_method_exists, "struct field interpolation_method does not exist");
		return interpolation_method_var;
	}
	std::vector<ubyte>& equ2_data() {
		assert_cond(equ2_data_exists, "struct field equ2_data does not exist");
		return equ2_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_EQU2_FRAME& operator () () { return *instances.back(); }
	ID3V2_EQU2_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_EQU2_FRAME(std::vector<ID3V2_EQU2_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_EQU2_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_EQU2_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_EQU2_FRAME* generate();
};

int ID3V2_EQU2_FRAME::_parent_id = 0;
int ID3V2_EQU2_FRAME::_index_start = 0;



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



class ID3V2_RVRB_FRAME {
	std::vector<ID3V2_RVRB_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	uint16 reverb_left_var;
	uint16 reverb_right_var;
	ubyte reverb_bounces_left_var;
	ubyte reverb_bounces_right_var;
	ubyte feedback_ll_var;
	ubyte feedback_lr_var;
	ubyte feedback_rr_var;
	ubyte feedback_rl_var;
	ubyte premix_lr_var;
	ubyte premix_rl_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool reverb_left_exists = false;
	bool reverb_right_exists = false;
	bool reverb_bounces_left_exists = false;
	bool reverb_bounces_right_exists = false;
	bool feedback_ll_exists = false;
	bool feedback_lr_exists = false;
	bool feedback_rr_exists = false;
	bool feedback_rl_exists = false;
	bool premix_lr_exists = false;
	bool premix_rl_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	uint16& reverb_left() {
		assert_cond(reverb_left_exists, "struct field reverb_left does not exist");
		return reverb_left_var;
	}
	uint16& reverb_right() {
		assert_cond(reverb_right_exists, "struct field reverb_right does not exist");
		return reverb_right_var;
	}
	ubyte& reverb_bounces_left() {
		assert_cond(reverb_bounces_left_exists, "struct field reverb_bounces_left does not exist");
		return reverb_bounces_left_var;
	}
	ubyte& reverb_bounces_right() {
		assert_cond(reverb_bounces_right_exists, "struct field reverb_bounces_right does not exist");
		return reverb_bounces_right_var;
	}
	ubyte& feedback_ll() {
		assert_cond(feedback_ll_exists, "struct field feedback_ll does not exist");
		return feedback_ll_var;
	}
	ubyte& feedback_lr() {
		assert_cond(feedback_lr_exists, "struct field feedback_lr does not exist");
		return feedback_lr_var;
	}
	ubyte& feedback_rr() {
		assert_cond(feedback_rr_exists, "struct field feedback_rr does not exist");
		return feedback_rr_var;
	}
	ubyte& feedback_rl() {
		assert_cond(feedback_rl_exists, "struct field feedback_rl does not exist");
		return feedback_rl_var;
	}
	ubyte& premix_lr() {
		assert_cond(premix_lr_exists, "struct field premix_lr does not exist");
		return premix_lr_var;
	}
	ubyte& premix_rl() {
		assert_cond(premix_rl_exists, "struct field premix_rl does not exist");
		return premix_rl_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_RVRB_FRAME& operator () () { return *instances.back(); }
	ID3V2_RVRB_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_RVRB_FRAME(std::vector<ID3V2_RVRB_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_RVRB_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_RVRB_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_RVRB_FRAME* generate();
};

int ID3V2_RVRB_FRAME::_parent_id = 0;
int ID3V2_RVRB_FRAME::_index_start = 0;



class ID3V2_SYTC_FRAME {
	std::vector<ID3V2_SYTC_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte timestamp_format_var;
	std::vector<ubyte> tempo_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool timestamp_format_exists = false;
	bool tempo_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& timestamp_format() {
		assert_cond(timestamp_format_exists, "struct field timestamp_format does not exist");
		return timestamp_format_var;
	}
	std::vector<ubyte>& tempo_data() {
		assert_cond(tempo_data_exists, "struct field tempo_data does not exist");
		return tempo_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_SYTC_FRAME& operator () () { return *instances.back(); }
	ID3V2_SYTC_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_SYTC_FRAME(std::vector<ID3V2_SYTC_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_SYTC_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_SYTC_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_SYTC_FRAME* generate();
};

int ID3V2_SYTC_FRAME::_parent_id = 0;
int ID3V2_SYTC_FRAME::_index_start = 0;



class ID3V2_MLLT_FRAME {
	std::vector<ID3V2_MLLT_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	uint16 frames_between_ref_var;
	ubyte bbr_hi_var;
	uint16 bbr_lo_var;
	ubyte mbr_hi_var;
	uint16 mbr_lo_var;
	ubyte bits_for_bytes_dev_var;
	ubyte bits_for_ms_dev_var;
	std::vector<ubyte> deviation_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool frames_between_ref_exists = false;
	bool bbr_hi_exists = false;
	bool bbr_lo_exists = false;
	bool mbr_hi_exists = false;
	bool mbr_lo_exists = false;
	bool bits_for_bytes_dev_exists = false;
	bool bits_for_ms_dev_exists = false;
	bool deviation_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	uint16& frames_between_ref() {
		assert_cond(frames_between_ref_exists, "struct field frames_between_ref does not exist");
		return frames_between_ref_var;
	}
	ubyte& bbr_hi() {
		assert_cond(bbr_hi_exists, "struct field bbr_hi does not exist");
		return bbr_hi_var;
	}
	uint16& bbr_lo() {
		assert_cond(bbr_lo_exists, "struct field bbr_lo does not exist");
		return bbr_lo_var;
	}
	ubyte& mbr_hi() {
		assert_cond(mbr_hi_exists, "struct field mbr_hi does not exist");
		return mbr_hi_var;
	}
	uint16& mbr_lo() {
		assert_cond(mbr_lo_exists, "struct field mbr_lo does not exist");
		return mbr_lo_var;
	}
	ubyte& bits_for_bytes_dev() {
		assert_cond(bits_for_bytes_dev_exists, "struct field bits_for_bytes_dev does not exist");
		return bits_for_bytes_dev_var;
	}
	ubyte& bits_for_ms_dev() {
		assert_cond(bits_for_ms_dev_exists, "struct field bits_for_ms_dev does not exist");
		return bits_for_ms_dev_var;
	}
	std::vector<ubyte>& deviation_data() {
		assert_cond(deviation_data_exists, "struct field deviation_data does not exist");
		return deviation_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_MLLT_FRAME& operator () () { return *instances.back(); }
	ID3V2_MLLT_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_MLLT_FRAME(std::vector<ID3V2_MLLT_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_MLLT_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_MLLT_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_MLLT_FRAME* generate();
};

int ID3V2_MLLT_FRAME::_parent_id = 0;
int ID3V2_MLLT_FRAME::_index_start = 0;



class ID3V2_RBUF_FRAME {
	std::vector<ID3V2_RBUF_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte buf_hi_var;
	uint16 buf_lo_var;
	ubyte embedded_info_flag_var;
	uint32 offset_to_next_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool buf_hi_exists = false;
	bool buf_lo_exists = false;
	bool embedded_info_flag_exists = false;
	bool offset_to_next_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& buf_hi() {
		assert_cond(buf_hi_exists, "struct field buf_hi does not exist");
		return buf_hi_var;
	}
	uint16& buf_lo() {
		assert_cond(buf_lo_exists, "struct field buf_lo does not exist");
		return buf_lo_var;
	}
	ubyte& embedded_info_flag() {
		assert_cond(embedded_info_flag_exists, "struct field embedded_info_flag does not exist");
		return embedded_info_flag_var;
	}
	uint32& offset_to_next() {
		assert_cond(offset_to_next_exists, "struct field offset_to_next does not exist");
		return offset_to_next_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_RBUF_FRAME& operator () () { return *instances.back(); }
	ID3V2_RBUF_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_RBUF_FRAME(std::vector<ID3V2_RBUF_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_RBUF_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_RBUF_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_RBUF_FRAME* generate();
};

int ID3V2_RBUF_FRAME::_parent_id = 0;
int ID3V2_RBUF_FRAME::_index_start = 0;



class ID3V2_AENC_FRAME {
	std::vector<ID3V2_AENC_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> aenc_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool aenc_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& aenc_data() {
		assert_cond(aenc_data_exists, "struct field aenc_data does not exist");
		return aenc_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_AENC_FRAME& operator () () { return *instances.back(); }
	ID3V2_AENC_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_AENC_FRAME(std::vector<ID3V2_AENC_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_AENC_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_AENC_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_AENC_FRAME* generate();
};

int ID3V2_AENC_FRAME::_parent_id = 0;
int ID3V2_AENC_FRAME::_index_start = 0;



class ID3V2_ENCR_FRAME {
	std::vector<ID3V2_ENCR_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> encr_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encr_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& encr_data() {
		assert_cond(encr_data_exists, "struct field encr_data does not exist");
		return encr_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_ENCR_FRAME& operator () () { return *instances.back(); }
	ID3V2_ENCR_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_ENCR_FRAME(std::vector<ID3V2_ENCR_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_ENCR_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_ENCR_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_ENCR_FRAME* generate();
};

int ID3V2_ENCR_FRAME::_parent_id = 0;
int ID3V2_ENCR_FRAME::_index_start = 0;



class ID3V2_GRID_FRAME {
	std::vector<ID3V2_GRID_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> grid_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool grid_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& grid_data() {
		assert_cond(grid_data_exists, "struct field grid_data does not exist");
		return grid_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_GRID_FRAME& operator () () { return *instances.back(); }
	ID3V2_GRID_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_GRID_FRAME(std::vector<ID3V2_GRID_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_GRID_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_GRID_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_GRID_FRAME* generate();
};

int ID3V2_GRID_FRAME::_parent_id = 0;
int ID3V2_GRID_FRAME::_index_start = 0;



class ID3V2_LINK_FRAME {
	std::vector<ID3V2_LINK_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::string frame_identifier_var;
	std::vector<ubyte> link_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool frame_identifier_exists = false;
	bool link_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::string& frame_identifier() {
		assert_cond(frame_identifier_exists, "struct field frame_identifier does not exist");
		return frame_identifier_var;
	}
	std::vector<ubyte>& link_data() {
		assert_cond(link_data_exists, "struct field link_data does not exist");
		return link_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_LINK_FRAME& operator () () { return *instances.back(); }
	ID3V2_LINK_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_LINK_FRAME(std::vector<ID3V2_LINK_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_LINK_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_LINK_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_LINK_FRAME* generate();
};

int ID3V2_LINK_FRAME::_parent_id = 0;
int ID3V2_LINK_FRAME::_index_start = 0;



class ID3V2_USER_FRAME {
	std::vector<ID3V2_USER_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::string language_var;
	std::string terms_text_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool language_exists = false;
	bool terms_text_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::string& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return language_var;
	}
	std::string& terms_text() {
		assert_cond(terms_text_exists, "struct field terms_text does not exist");
		return terms_text_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_USER_FRAME& operator () () { return *instances.back(); }
	ID3V2_USER_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_USER_FRAME(std::vector<ID3V2_USER_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_USER_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_USER_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_USER_FRAME* generate();
};

int ID3V2_USER_FRAME::_parent_id = 0;
int ID3V2_USER_FRAME::_index_start = 0;



class ID3V2_OWNE_FRAME {
	std::vector<ID3V2_OWNE_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte encoding_var;
	std::vector<ubyte> owne_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool encoding_exists = false;
	bool owne_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& encoding() {
		assert_cond(encoding_exists, "struct field encoding does not exist");
		return encoding_var;
	}
	std::vector<ubyte>& owne_data() {
		assert_cond(owne_data_exists, "struct field owne_data does not exist");
		return owne_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_OWNE_FRAME& operator () () { return *instances.back(); }
	ID3V2_OWNE_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_OWNE_FRAME(std::vector<ID3V2_OWNE_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_OWNE_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_OWNE_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_OWNE_FRAME* generate();
};

int ID3V2_OWNE_FRAME::_parent_id = 0;
int ID3V2_OWNE_FRAME::_index_start = 0;



class ID3V2_CHAP_FRAME {
	std::vector<ID3V2_CHAP_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> chap_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool chap_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& chap_data() {
		assert_cond(chap_data_exists, "struct field chap_data does not exist");
		return chap_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_CHAP_FRAME& operator () () { return *instances.back(); }
	ID3V2_CHAP_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_CHAP_FRAME(std::vector<ID3V2_CHAP_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_CHAP_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_CHAP_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_CHAP_FRAME* generate();
};

int ID3V2_CHAP_FRAME::_parent_id = 0;
int ID3V2_CHAP_FRAME::_index_start = 0;



class ID3V2_CTOC_FRAME {
	std::vector<ID3V2_CTOC_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> ctoc_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool ctoc_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& ctoc_data() {
		assert_cond(ctoc_data_exists, "struct field ctoc_data does not exist");
		return ctoc_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_CTOC_FRAME& operator () () { return *instances.back(); }
	ID3V2_CTOC_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_CTOC_FRAME(std::vector<ID3V2_CTOC_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_CTOC_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_CTOC_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_CTOC_FRAME* generate();
};

int ID3V2_CTOC_FRAME::_parent_id = 0;
int ID3V2_CTOC_FRAME::_index_start = 0;



class ID3V2_SIGN_FRAME {
	std::vector<ID3V2_SIGN_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	ubyte group_symbol_var;
	std::vector<ubyte> signature_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool group_symbol_exists = false;
	bool signature_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	ubyte& group_symbol() {
		assert_cond(group_symbol_exists, "struct field group_symbol does not exist");
		return group_symbol_var;
	}
	std::vector<ubyte>& signature() {
		assert_cond(signature_exists, "struct field signature does not exist");
		return signature_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_SIGN_FRAME& operator () () { return *instances.back(); }
	ID3V2_SIGN_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_SIGN_FRAME(std::vector<ID3V2_SIGN_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_SIGN_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_SIGN_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_SIGN_FRAME* generate();
};

int ID3V2_SIGN_FRAME::_parent_id = 0;
int ID3V2_SIGN_FRAME::_index_start = 0;



class ID3V2_ASPI_FRAME {
	std::vector<ID3V2_ASPI_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	uint32 indexed_data_start_var;
	uint32 indexed_data_length_var;
	uint16 num_index_points_var;
	ubyte bits_per_index_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool indexed_data_start_exists = false;
	bool indexed_data_length_exists = false;
	bool num_index_points_exists = false;
	bool bits_per_index_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	uint32& indexed_data_start() {
		assert_cond(indexed_data_start_exists, "struct field indexed_data_start does not exist");
		return indexed_data_start_var;
	}
	uint32& indexed_data_length() {
		assert_cond(indexed_data_length_exists, "struct field indexed_data_length does not exist");
		return indexed_data_length_var;
	}
	uint16& num_index_points() {
		assert_cond(num_index_points_exists, "struct field num_index_points does not exist");
		return num_index_points_var;
	}
	ubyte& bits_per_index() {
		assert_cond(bits_per_index_exists, "struct field bits_per_index does not exist");
		return bits_per_index_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_ASPI_FRAME& operator () () { return *instances.back(); }
	ID3V2_ASPI_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_ASPI_FRAME(std::vector<ID3V2_ASPI_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_ASPI_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_ASPI_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_ASPI_FRAME* generate();
};

int ID3V2_ASPI_FRAME::_parent_id = 0;
int ID3V2_ASPI_FRAME::_index_start = 0;



class ID3V2_RGAD_FRAME {
	std::vector<ID3V2_RGAD_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	uint32 peak_signal_var;
	uint16 radio_gain_var;
	uint16 audiophile_gain_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool peak_signal_exists = false;
	bool radio_gain_exists = false;
	bool audiophile_gain_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	uint32& peak_signal() {
		assert_cond(peak_signal_exists, "struct field peak_signal does not exist");
		return peak_signal_var;
	}
	uint16& radio_gain() {
		assert_cond(radio_gain_exists, "struct field radio_gain does not exist");
		return radio_gain_var;
	}
	uint16& audiophile_gain() {
		assert_cond(audiophile_gain_exists, "struct field audiophile_gain does not exist");
		return audiophile_gain_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_RGAD_FRAME& operator () () { return *instances.back(); }
	ID3V2_RGAD_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_RGAD_FRAME(std::vector<ID3V2_RGAD_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_RGAD_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_RGAD_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_RGAD_FRAME* generate();
};

int ID3V2_RGAD_FRAME::_parent_id = 0;
int ID3V2_RGAD_FRAME::_index_start = 0;



class ID3V2_GENERIC_FRAME {
	std::vector<ID3V2_GENERIC_FRAME*>& instances;

	std::string id_var;
	uint32 size_var;
	ID3V2_FRAME_FLAGS* flags_var;
	std::vector<ubyte> frame_data_var;

public:
	bool id_exists = false;
	bool size_exists = false;
	bool flags_exists = false;
	bool frame_data_exists = false;

	std::string& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	ID3V2_FRAME_FLAGS& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return *flags_var;
	}
	std::vector<ubyte>& frame_data() {
		assert_cond(frame_data_exists, "struct field frame_data does not exist");
		return frame_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ID3V2_GENERIC_FRAME& operator () () { return *instances.back(); }
	ID3V2_GENERIC_FRAME& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ID3V2_GENERIC_FRAME(std::vector<ID3V2_GENERIC_FRAME*>& instances) : instances(instances) { instances.push_back(this); }
	~ID3V2_GENERIC_FRAME() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ID3V2_GENERIC_FRAME* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ID3V2_GENERIC_FRAME* generate();
};

int ID3V2_GENERIC_FRAME::_parent_id = 0;
int ID3V2_GENERIC_FRAME::_index_start = 0;



class mp3_id3v2_tag {
	std::vector<mp3_id3v2_tag*>& instances;

	std::string header_id_var;
	ubyte version_major_var;
	ubyte version_minor_var;
	ubyte header_flags_var;
	uint32 raw_size_var;
	ID3V2_TEXT_FRAME* text_frame_var;
	ID3V2_COMM_FRAME* comm_frame_var;
	ID3V2_APIC_FRAME* apic_frame_var;
	ID3V2_USLT_FRAME* uslt_frame_var;
	ID3V2_TXXX_FRAME* txxx_frame_var;
	ID3V2_WXXX_FRAME* wxxx_frame_var;
	ID3V2_URL_FRAME* url_frame_var;
	ID3V2_PCNT_FRAME* pcnt_frame_var;
	ID3V2_POPM_FRAME* popm_frame_var;
	ID3V2_PRIV_FRAME* priv_frame_var;
	ID3V2_UFID_FRAME* ufid_frame_var;
	ID3V2_GEOB_FRAME* geob_frame_var;
	ID3V2_MCDI_FRAME* mcdi_frame_var;
	ID3V2_ETCO_FRAME* etco_frame_var;
	ID3V2_SYLT_FRAME* sylt_frame_var;
	ID3V2_RVA2_FRAME* rva2_frame_var;
	ID3V2_EQU2_FRAME* equ2_frame_var;
	ID3V2_RVRB_FRAME* rvrb_frame_var;
	ID3V2_SYTC_FRAME* sytc_frame_var;
	ID3V2_MLLT_FRAME* mllt_frame_var;
	ID3V2_RBUF_FRAME* rbuf_frame_var;
	ID3V2_AENC_FRAME* aenc_frame_var;
	ID3V2_ENCR_FRAME* encr_frame_var;
	ID3V2_GRID_FRAME* grid_frame_var;
	ID3V2_LINK_FRAME* link_frame_var;
	ID3V2_USER_FRAME* user_frame_var;
	ID3V2_OWNE_FRAME* owne_frame_var;
	ID3V2_CHAP_FRAME* chap_frame_var;
	ID3V2_CTOC_FRAME* ctoc_frame_var;
	ID3V2_SIGN_FRAME* sign_frame_var;
	ID3V2_ASPI_FRAME* aspi_frame_var;
	ID3V2_RGAD_FRAME* rgad_frame_var;
	ID3V2_GENERIC_FRAME* gen_frame_var;
	std::vector<ubyte> padding_var;

public:
	bool header_id_exists = false;
	bool version_major_exists = false;
	bool version_minor_exists = false;
	bool header_flags_exists = false;
	bool raw_size_exists = false;
	bool text_frame_exists = false;
	bool comm_frame_exists = false;
	bool apic_frame_exists = false;
	bool uslt_frame_exists = false;
	bool txxx_frame_exists = false;
	bool wxxx_frame_exists = false;
	bool url_frame_exists = false;
	bool pcnt_frame_exists = false;
	bool popm_frame_exists = false;
	bool priv_frame_exists = false;
	bool ufid_frame_exists = false;
	bool geob_frame_exists = false;
	bool mcdi_frame_exists = false;
	bool etco_frame_exists = false;
	bool sylt_frame_exists = false;
	bool rva2_frame_exists = false;
	bool equ2_frame_exists = false;
	bool rvrb_frame_exists = false;
	bool sytc_frame_exists = false;
	bool mllt_frame_exists = false;
	bool rbuf_frame_exists = false;
	bool aenc_frame_exists = false;
	bool encr_frame_exists = false;
	bool grid_frame_exists = false;
	bool link_frame_exists = false;
	bool user_frame_exists = false;
	bool owne_frame_exists = false;
	bool chap_frame_exists = false;
	bool ctoc_frame_exists = false;
	bool sign_frame_exists = false;
	bool aspi_frame_exists = false;
	bool rgad_frame_exists = false;
	bool gen_frame_exists = false;
	bool padding_exists = false;

	std::string& header_id() {
		assert_cond(header_id_exists, "struct field header_id does not exist");
		return header_id_var;
	}
	ubyte& version_major() {
		assert_cond(version_major_exists, "struct field version_major does not exist");
		return version_major_var;
	}
	ubyte& version_minor() {
		assert_cond(version_minor_exists, "struct field version_minor does not exist");
		return version_minor_var;
	}
	ubyte& header_flags() {
		assert_cond(header_flags_exists, "struct field header_flags does not exist");
		return header_flags_var;
	}
	uint32& raw_size() {
		assert_cond(raw_size_exists, "struct field raw_size does not exist");
		return raw_size_var;
	}
	ID3V2_TEXT_FRAME& text_frame() {
		assert_cond(text_frame_exists, "struct field text_frame does not exist");
		return *text_frame_var;
	}
	ID3V2_COMM_FRAME& comm_frame() {
		assert_cond(comm_frame_exists, "struct field comm_frame does not exist");
		return *comm_frame_var;
	}
	ID3V2_APIC_FRAME& apic_frame() {
		assert_cond(apic_frame_exists, "struct field apic_frame does not exist");
		return *apic_frame_var;
	}
	ID3V2_USLT_FRAME& uslt_frame() {
		assert_cond(uslt_frame_exists, "struct field uslt_frame does not exist");
		return *uslt_frame_var;
	}
	ID3V2_TXXX_FRAME& txxx_frame() {
		assert_cond(txxx_frame_exists, "struct field txxx_frame does not exist");
		return *txxx_frame_var;
	}
	ID3V2_WXXX_FRAME& wxxx_frame() {
		assert_cond(wxxx_frame_exists, "struct field wxxx_frame does not exist");
		return *wxxx_frame_var;
	}
	ID3V2_URL_FRAME& url_frame() {
		assert_cond(url_frame_exists, "struct field url_frame does not exist");
		return *url_frame_var;
	}
	ID3V2_PCNT_FRAME& pcnt_frame() {
		assert_cond(pcnt_frame_exists, "struct field pcnt_frame does not exist");
		return *pcnt_frame_var;
	}
	ID3V2_POPM_FRAME& popm_frame() {
		assert_cond(popm_frame_exists, "struct field popm_frame does not exist");
		return *popm_frame_var;
	}
	ID3V2_PRIV_FRAME& priv_frame() {
		assert_cond(priv_frame_exists, "struct field priv_frame does not exist");
		return *priv_frame_var;
	}
	ID3V2_UFID_FRAME& ufid_frame() {
		assert_cond(ufid_frame_exists, "struct field ufid_frame does not exist");
		return *ufid_frame_var;
	}
	ID3V2_GEOB_FRAME& geob_frame() {
		assert_cond(geob_frame_exists, "struct field geob_frame does not exist");
		return *geob_frame_var;
	}
	ID3V2_MCDI_FRAME& mcdi_frame() {
		assert_cond(mcdi_frame_exists, "struct field mcdi_frame does not exist");
		return *mcdi_frame_var;
	}
	ID3V2_ETCO_FRAME& etco_frame() {
		assert_cond(etco_frame_exists, "struct field etco_frame does not exist");
		return *etco_frame_var;
	}
	ID3V2_SYLT_FRAME& sylt_frame() {
		assert_cond(sylt_frame_exists, "struct field sylt_frame does not exist");
		return *sylt_frame_var;
	}
	ID3V2_RVA2_FRAME& rva2_frame() {
		assert_cond(rva2_frame_exists, "struct field rva2_frame does not exist");
		return *rva2_frame_var;
	}
	ID3V2_EQU2_FRAME& equ2_frame() {
		assert_cond(equ2_frame_exists, "struct field equ2_frame does not exist");
		return *equ2_frame_var;
	}
	ID3V2_RVRB_FRAME& rvrb_frame() {
		assert_cond(rvrb_frame_exists, "struct field rvrb_frame does not exist");
		return *rvrb_frame_var;
	}
	ID3V2_SYTC_FRAME& sytc_frame() {
		assert_cond(sytc_frame_exists, "struct field sytc_frame does not exist");
		return *sytc_frame_var;
	}
	ID3V2_MLLT_FRAME& mllt_frame() {
		assert_cond(mllt_frame_exists, "struct field mllt_frame does not exist");
		return *mllt_frame_var;
	}
	ID3V2_RBUF_FRAME& rbuf_frame() {
		assert_cond(rbuf_frame_exists, "struct field rbuf_frame does not exist");
		return *rbuf_frame_var;
	}
	ID3V2_AENC_FRAME& aenc_frame() {
		assert_cond(aenc_frame_exists, "struct field aenc_frame does not exist");
		return *aenc_frame_var;
	}
	ID3V2_ENCR_FRAME& encr_frame() {
		assert_cond(encr_frame_exists, "struct field encr_frame does not exist");
		return *encr_frame_var;
	}
	ID3V2_GRID_FRAME& grid_frame() {
		assert_cond(grid_frame_exists, "struct field grid_frame does not exist");
		return *grid_frame_var;
	}
	ID3V2_LINK_FRAME& link_frame() {
		assert_cond(link_frame_exists, "struct field link_frame does not exist");
		return *link_frame_var;
	}
	ID3V2_USER_FRAME& user_frame() {
		assert_cond(user_frame_exists, "struct field user_frame does not exist");
		return *user_frame_var;
	}
	ID3V2_OWNE_FRAME& owne_frame() {
		assert_cond(owne_frame_exists, "struct field owne_frame does not exist");
		return *owne_frame_var;
	}
	ID3V2_CHAP_FRAME& chap_frame() {
		assert_cond(chap_frame_exists, "struct field chap_frame does not exist");
		return *chap_frame_var;
	}
	ID3V2_CTOC_FRAME& ctoc_frame() {
		assert_cond(ctoc_frame_exists, "struct field ctoc_frame does not exist");
		return *ctoc_frame_var;
	}
	ID3V2_SIGN_FRAME& sign_frame() {
		assert_cond(sign_frame_exists, "struct field sign_frame does not exist");
		return *sign_frame_var;
	}
	ID3V2_ASPI_FRAME& aspi_frame() {
		assert_cond(aspi_frame_exists, "struct field aspi_frame does not exist");
		return *aspi_frame_var;
	}
	ID3V2_RGAD_FRAME& rgad_frame() {
		assert_cond(rgad_frame_exists, "struct field rgad_frame does not exist");
		return *rgad_frame_var;
	}
	ID3V2_GENERIC_FRAME& gen_frame() {
		assert_cond(gen_frame_exists, "struct field gen_frame does not exist");
		return *gen_frame_var;
	}
	std::vector<ubyte>& padding() {
		assert_cond(padding_exists, "struct field padding does not exist");
		return padding_var;
	}

	/* locals */
	int64 size_pos;
	uint32 tag_body_size;
	int64 tag_data_start;
	int frame_count;
	std::vector<std::string> frame_choices;
	std::string next_frame;
	int64 bytes_written;
	int64 padding_needed;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp3_id3v2_tag& operator () () { return *instances.back(); }
	mp3_id3v2_tag& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp3_id3v2_tag(std::vector<mp3_id3v2_tag*>& instances) : instances(instances) { instances.push_back(this); }
	~mp3_id3v2_tag() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp3_id3v2_tag* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp3_id3v2_tag* generate();
};

int mp3_id3v2_tag::_parent_id = 0;
int mp3_id3v2_tag::_index_start = 0;



class mp3_mpeg_header {
	std::vector<mp3_mpeg_header*>& instances;

	ubyte sync_byte1_var;
	ubyte sync_byte2_var;
	ubyte header_byte3_var;
	ubyte header_byte4_var;
	uint16 crc16_var;

public:
	bool sync_byte1_exists = false;
	bool sync_byte2_exists = false;
	bool header_byte3_exists = false;
	bool header_byte4_exists = false;
	bool crc16_exists = false;

	ubyte& sync_byte1() {
		assert_cond(sync_byte1_exists, "struct field sync_byte1 does not exist");
		return sync_byte1_var;
	}
	ubyte& sync_byte2() {
		assert_cond(sync_byte2_exists, "struct field sync_byte2 does not exist");
		return sync_byte2_var;
	}
	ubyte& header_byte3() {
		assert_cond(header_byte3_exists, "struct field header_byte3 does not exist");
		return header_byte3_var;
	}
	ubyte& header_byte4() {
		assert_cond(header_byte4_exists, "struct field header_byte4 does not exist");
		return header_byte4_var;
	}
	uint16& crc16() {
		assert_cond(crc16_exists, "struct field crc16 does not exist");
		return crc16_var;
	}

	/* locals */
	ubyte mpeg_version;
	ubyte layer;
	ubyte protection;
	ubyte bitrate_index;
	ubyte sample_rate_index;
	ubyte padding_bit;
	ubyte private_bit;
	ubyte channel_mode;
	ubyte mode_extension;
	ubyte copyright_bit;
	ubyte original_bit;
	ubyte emphasis;
	uint32 ver_idx;
	uint32 lay_idx;
	uint32 bi;
	uint32 si;
	uint32 br;
	uint32 sr;
	uint32 spf;
	uint32 frame_data_size;
	uint32 hdr_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp3_mpeg_header& operator () () { return *instances.back(); }
	mp3_mpeg_header& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp3_mpeg_header(std::vector<mp3_mpeg_header*>& instances) : instances(instances) { instances.push_back(this); }
	~mp3_mpeg_header() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp3_mpeg_header* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp3_mpeg_header* generate();
};

int mp3_mpeg_header::_parent_id = 0;
int mp3_mpeg_header::_index_start = 0;



class mp3_mpeg_frame {
	std::vector<mp3_mpeg_frame*>& instances;

	mp3_mpeg_header* hdr_var;
	std::vector<ubyte> frame_data_var;

public:
	bool hdr_exists = false;
	bool frame_data_exists = false;

	mp3_mpeg_header& hdr() {
		assert_cond(hdr_exists, "struct field hdr does not exist");
		return *hdr_var;
	}
	std::vector<ubyte>& frame_data() {
		assert_cond(frame_data_exists, "struct field frame_data does not exist");
		return frame_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp3_mpeg_frame& operator () () { return *instances.back(); }
	mp3_mpeg_frame& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp3_mpeg_frame(std::vector<mp3_mpeg_frame*>& instances) : instances(instances) { instances.push_back(this); }
	~mp3_mpeg_frame() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp3_mpeg_frame* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp3_mpeg_frame* generate();
};

int mp3_mpeg_frame::_parent_id = 0;
int mp3_mpeg_frame::_index_start = 0;



class mp3_id3v1_tag {
	std::vector<mp3_id3v1_tag*>& instances;

	std::string tag_id_var;
	std::string title_var;
	std::string artist_var;
	std::string album_var;
	std::string year_var;
	std::string comment_var;
	ubyte zero_byte_var;
	ubyte track_var;
	ubyte genre_var;

public:
	bool tag_id_exists = false;
	bool title_exists = false;
	bool artist_exists = false;
	bool album_exists = false;
	bool year_exists = false;
	bool comment_exists = false;
	bool zero_byte_exists = false;
	bool track_exists = false;
	bool genre_exists = false;

	std::string& tag_id() {
		assert_cond(tag_id_exists, "struct field tag_id does not exist");
		return tag_id_var;
	}
	std::string& title() {
		assert_cond(title_exists, "struct field title does not exist");
		return title_var;
	}
	std::string& artist() {
		assert_cond(artist_exists, "struct field artist does not exist");
		return artist_var;
	}
	std::string& album() {
		assert_cond(album_exists, "struct field album does not exist");
		return album_var;
	}
	std::string& year() {
		assert_cond(year_exists, "struct field year does not exist");
		return year_var;
	}
	std::string& comment() {
		assert_cond(comment_exists, "struct field comment does not exist");
		return comment_var;
	}
	ubyte& zero_byte() {
		assert_cond(zero_byte_exists, "struct field zero_byte does not exist");
		return zero_byte_var;
	}
	ubyte& track() {
		assert_cond(track_exists, "struct field track does not exist");
		return track_var;
	}
	ubyte& genre() {
		assert_cond(genre_exists, "struct field genre does not exist");
		return genre_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp3_id3v1_tag& operator () () { return *instances.back(); }
	mp3_id3v1_tag& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp3_id3v1_tag(std::vector<mp3_id3v1_tag*>& instances) : instances(instances) { instances.push_back(this); }
	~mp3_id3v1_tag() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp3_id3v1_tag* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp3_id3v1_tag* generate();
};

int mp3_id3v1_tag::_parent_id = 0;
int mp3_id3v1_tag::_index_start = 0;



class mp3_file {
	std::vector<mp3_file*>& instances;

	mp3_id3v2_tag* id3v2_var;
	mp3_mpeg_frame* frame_var;
	mp3_id3v1_tag* id3v1_var;

public:
	bool id3v2_exists = false;
	bool frame_exists = false;
	bool id3v1_exists = false;

	mp3_id3v2_tag& id3v2() {
		assert_cond(id3v2_exists, "struct field id3v2 does not exist");
		return *id3v2_var;
	}
	mp3_mpeg_frame& frame() {
		assert_cond(frame_exists, "struct field frame does not exist");
		return *frame_var;
	}
	mp3_id3v1_tag& id3v1() {
		assert_cond(id3v1_exists, "struct field id3v1 does not exist");
		return *id3v1_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp3_file& operator () () { return *instances.back(); }
	mp3_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp3_file(std::vector<mp3_file*>& instances) : instances(instances) { instances.push_back(this); }
	~mp3_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp3_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp3_file* generate();
};

int mp3_file::_parent_id = 0;
int mp3_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "ID3", "\xFF\xFB", "\xFF\xFA", "\xFF\xF3", "\xFF\xF2", "\xFF\xFF", "\xFF\xFE", "\xFF\xFD", "\xFF\xFC", "\xFF\xF7", "\xFF\xF6", "\xFF\xF5", "\xFF\xF4", "TAG" };


std::vector<ID3V2_FRAME_FLAGS*> ID3V2_FRAME_FLAGS_flags_instances;
std::vector<ID3V2_TEXT_FRAME*> ID3V2_TEXT_FRAME_text_frame_instances;
std::vector<ID3V2_COMM_FRAME*> ID3V2_COMM_FRAME_comm_frame_instances;
std::vector<ID3V2_APIC_FRAME*> ID3V2_APIC_FRAME_apic_frame_instances;
std::vector<ID3V2_USLT_FRAME*> ID3V2_USLT_FRAME_uslt_frame_instances;
std::vector<ID3V2_TXXX_FRAME*> ID3V2_TXXX_FRAME_txxx_frame_instances;
std::vector<ID3V2_WXXX_FRAME*> ID3V2_WXXX_FRAME_wxxx_frame_instances;
std::vector<ID3V2_URL_FRAME*> ID3V2_URL_FRAME_url_frame_instances;
std::vector<ID3V2_PCNT_FRAME*> ID3V2_PCNT_FRAME_pcnt_frame_instances;
std::vector<ID3V2_POPM_FRAME*> ID3V2_POPM_FRAME_popm_frame_instances;
std::vector<ID3V2_PRIV_FRAME*> ID3V2_PRIV_FRAME_priv_frame_instances;
std::vector<ID3V2_UFID_FRAME*> ID3V2_UFID_FRAME_ufid_frame_instances;
std::vector<ID3V2_GEOB_FRAME*> ID3V2_GEOB_FRAME_geob_frame_instances;
std::vector<ID3V2_MCDI_FRAME*> ID3V2_MCDI_FRAME_mcdi_frame_instances;
std::vector<ID3V2_ETCO_FRAME*> ID3V2_ETCO_FRAME_etco_frame_instances;
std::vector<ID3V2_SYLT_FRAME*> ID3V2_SYLT_FRAME_sylt_frame_instances;
std::vector<ID3V2_RVA2_FRAME*> ID3V2_RVA2_FRAME_rva2_frame_instances;
std::vector<ID3V2_EQU2_FRAME*> ID3V2_EQU2_FRAME_equ2_frame_instances;
std::vector<ID3V2_RVRB_FRAME*> ID3V2_RVRB_FRAME_rvrb_frame_instances;
std::vector<ID3V2_SYTC_FRAME*> ID3V2_SYTC_FRAME_sytc_frame_instances;
std::vector<ID3V2_MLLT_FRAME*> ID3V2_MLLT_FRAME_mllt_frame_instances;
std::vector<ID3V2_RBUF_FRAME*> ID3V2_RBUF_FRAME_rbuf_frame_instances;
std::vector<ID3V2_AENC_FRAME*> ID3V2_AENC_FRAME_aenc_frame_instances;
std::vector<ID3V2_ENCR_FRAME*> ID3V2_ENCR_FRAME_encr_frame_instances;
std::vector<ID3V2_GRID_FRAME*> ID3V2_GRID_FRAME_grid_frame_instances;
std::vector<ID3V2_LINK_FRAME*> ID3V2_LINK_FRAME_link_frame_instances;
std::vector<ID3V2_USER_FRAME*> ID3V2_USER_FRAME_user_frame_instances;
std::vector<ID3V2_OWNE_FRAME*> ID3V2_OWNE_FRAME_owne_frame_instances;
std::vector<ID3V2_CHAP_FRAME*> ID3V2_CHAP_FRAME_chap_frame_instances;
std::vector<ID3V2_CTOC_FRAME*> ID3V2_CTOC_FRAME_ctoc_frame_instances;
std::vector<ID3V2_SIGN_FRAME*> ID3V2_SIGN_FRAME_sign_frame_instances;
std::vector<ID3V2_ASPI_FRAME*> ID3V2_ASPI_FRAME_aspi_frame_instances;
std::vector<ID3V2_RGAD_FRAME*> ID3V2_RGAD_FRAME_rgad_frame_instances;
std::vector<ID3V2_GENERIC_FRAME*> ID3V2_GENERIC_FRAME_gen_frame_instances;
std::vector<mp3_id3v2_tag*> mp3_id3v2_tag_id3v2_instances;
std::vector<mp3_mpeg_header*> mp3_mpeg_header_hdr_instances;
std::vector<mp3_mpeg_frame*> mp3_mpeg_frame_frame_instances;
std::vector<mp3_id3v1_tag*> mp3_id3v1_tag_id3v1_instances;
std::vector<mp3_file*> mp3_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "header_id", "char_array_class" }, { "version_major", "ubyte_class" }, { "version_minor", "ubyte_class" }, { "header_flags", "ubyte_class" }, { "raw_size", "uint32_class" }, { "ss_b0", "ubyte_class" }, { "ss_b1", "ubyte_class" }, { "ss_b2", "ubyte_class" }, { "ss_b3", "ubyte_class" }, { "id", "char_array_class" }, { "size", "uint32_class" }, { "flags1", "ubyte_class" }, { "flags2", "ubyte_class" }, { "flags", "ID3V2_FRAME_FLAGS" }, { "encoding", "ubyte_class" }, { "text_data", "char_array_class" }, { "text_frame", "ID3V2_TEXT_FRAME" }, { "language", "char_array_class" }, { "comment_data", "char_array_class" }, { "comm_frame", "ID3V2_COMM_FRAME" }, { "mime_type", "char_array_class" }, { "null_term1", "ubyte_class" }, { "picture_type", "ubyte_class" }, { "null_term2", "ubyte_class" }, { "picture_data", "ubyte_array_class" }, { "apic_frame", "ID3V2_APIC_FRAME" }, { "lyrics_data", "char_array_class" }, { "uslt_frame", "ID3V2_USLT_FRAME" }, { "txxx_data", "char_array_class" }, { "txxx_frame", "ID3V2_TXXX_FRAME" }, { "wxxx_data", "char_array_class" }, { "wxxx_frame", "ID3V2_WXXX_FRAME" }, { "url", "char_array_class" }, { "url_frame", "ID3V2_URL_FRAME" }, { "counter", "uint32_class" }, { "extra_counter", "ubyte_array_class" }, { "pcnt_frame", "ID3V2_PCNT_FRAME" }, { "popm_data", "ubyte_array_class" }, { "popm_frame", "ID3V2_POPM_FRAME" }, { "priv_data", "ubyte_array_class" }, { "priv_frame", "ID3V2_PRIV_FRAME" }, { "ufid_data", "ubyte_array_class" }, { "ufid_frame", "ID3V2_UFID_FRAME" }, { "geob_data", "ubyte_array_class" }, { "geob_frame", "ID3V2_GEOB_FRAME" }, { "cd_toc", "ubyte_array_class" }, { "mcdi_frame", "ID3V2_MCDI_FRAME" }, { "timestamp_format", "ubyte_class" }, { "event_data", "ubyte_array_class" }, { "etco_frame", "ID3V2_ETCO_FRAME" }, { "content_type", "ubyte_class" }, { "sylt_data", "ubyte_array_class" }, { "sylt_frame", "ID3V2_SYLT_FRAME" }, { "rva2_data", "ubyte_array_class" }, { "rva2_frame", "ID3V2_RVA2_FRAME" }, { "interpolation_method", "ubyte_class" }, { "equ2_data", "ubyte_array_class" }, { "equ2_frame", "ID3V2_EQU2_FRAME" }, { "reverb_left", "uint16_class" }, { "reverb_right", "uint16_class" }, { "reverb_bounces_left", "ubyte_class" }, { "reverb_bounces_right", "ubyte_class" }, { "feedback_ll", "ubyte_class" }, { "feedback_lr", "ubyte_class" }, { "feedback_rr", "ubyte_class" }, { "feedback_rl", "ubyte_class" }, { "premix_lr", "ubyte_class" }, { "premix_rl", "ubyte_class" }, { "rvrb_frame", "ID3V2_RVRB_FRAME" }, { "tempo_data", "ubyte_array_class" }, { "sytc_frame", "ID3V2_SYTC_FRAME" }, { "frames_between_ref", "uint16_class" }, { "bbr_hi", "ubyte_class" }, { "bbr_lo", "uint16_class" }, { "mbr_hi", "ubyte_class" }, { "mbr_lo", "uint16_class" }, { "bits_for_bytes_dev", "ubyte_class" }, { "bits_for_ms_dev", "ubyte_class" }, { "deviation_data", "ubyte_array_class" }, { "mllt_frame", "ID3V2_MLLT_FRAME" }, { "buf_hi", "ubyte_class" }, { "buf_lo", "uint16_class" }, { "embedded_info_flag", "ubyte_class" }, { "offset_to_next", "uint32_class" }, { "rbuf_frame", "ID3V2_RBUF_FRAME" }, { "aenc_data", "ubyte_array_class" }, { "aenc_frame", "ID3V2_AENC_FRAME" }, { "encr_data", "ubyte_array_class" }, { "encr_frame", "ID3V2_ENCR_FRAME" }, { "grid_data", "ubyte_array_class" }, { "grid_frame", "ID3V2_GRID_FRAME" }, { "frame_identifier", "char_array_class" }, { "link_data", "ubyte_array_class" }, { "link_frame", "ID3V2_LINK_FRAME" }, { "terms_text", "char_array_class" }, { "user_frame", "ID3V2_USER_FRAME" }, { "owne_data", "ubyte_array_class" }, { "owne_frame", "ID3V2_OWNE_FRAME" }, { "chap_data", "ubyte_array_class" }, { "chap_frame", "ID3V2_CHAP_FRAME" }, { "ctoc_data", "ubyte_array_class" }, { "ctoc_frame", "ID3V2_CTOC_FRAME" }, { "group_symbol", "ubyte_class" }, { "signature", "ubyte_array_class" }, { "sign_frame", "ID3V2_SIGN_FRAME" }, { "indexed_data_start", "uint32_class" }, { "indexed_data_length", "uint32_class" }, { "num_index_points", "uint16_class" }, { "bits_per_index", "ubyte_class" }, { "aspi_frame", "ID3V2_ASPI_FRAME" }, { "peak_signal", "uint32_class" }, { "radio_gain", "uint16_class" }, { "audiophile_gain", "uint16_class" }, { "rgad_frame", "ID3V2_RGAD_FRAME" }, { "frame_data", "ubyte_array_class" }, { "gen_frame", "ID3V2_GENERIC_FRAME" }, { "padding", "ubyte_array_class" }, { "id3v2", "mp3_id3v2_tag" }, { "sync_byte1", "ubyte_class" }, { "sync_byte2", "ubyte_class" }, { "header_byte3", "ubyte_class" }, { "header_byte4", "ubyte_class" }, { "crc16", "uint16_class" }, { "hdr", "mp3_mpeg_header" }, { "frame", "mp3_mpeg_frame" }, { "tag_id", "char_array_class" }, { "title", "char_array_class" }, { "artist", "char_array_class" }, { "album", "char_array_class" }, { "year", "char_array_class" }, { "comment", "char_array_class" }, { "zero_byte", "ubyte_class" }, { "track", "ubyte_class" }, { "genre", "ubyte_class" }, { "id3v1", "mp3_id3v1_tag" }, { "file", "mp3_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 40, 2048 }, { 4, 128 }, { 0, 3 }, { 0, 20 }, { 1, 2 }, { 0, 8 }, { 0, 1 }, { 0, 1 }, { 8, 16 }, { 0x10, 0xFD }, { 1, 255 }, { 0, 191 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class header_id_element;
	char_array_class header_id;
	ubyte_class version_major;
	ubyte_class version_minor;
	ubyte_class header_flags;
	uint32_class raw_size;
	ubyte_class ss_b0;
	ubyte_class ss_b1;
	ubyte_class ss_b2;
	ubyte_class ss_b3;
	char_class id_element;
	char_array_class id;
	uint32_class size;
	ubyte_class flags1;
	ubyte_class flags2;
	ID3V2_FRAME_FLAGS flags;
	ubyte_class encoding;
	char_class text_data_element;
	char_array_class text_data;
	ID3V2_TEXT_FRAME text_frame;
	char_class language_element;
	char_array_class language;
	char_class comment_data_element;
	char_array_class comment_data;
	ID3V2_COMM_FRAME comm_frame;
	char_class mime_type_element;
	char_array_class mime_type;
	ubyte_class null_term1;
	ubyte_class picture_type;
	ubyte_class null_term2;
	ubyte_class picture_data_element;
	ubyte_array_class picture_data;
	ID3V2_APIC_FRAME apic_frame;
	char_class lyrics_data_element;
	char_array_class lyrics_data;
	ID3V2_USLT_FRAME uslt_frame;
	char_class txxx_data_element;
	char_array_class txxx_data;
	ID3V2_TXXX_FRAME txxx_frame;
	char_class wxxx_data_element;
	char_array_class wxxx_data;
	ID3V2_WXXX_FRAME wxxx_frame;
	char_class url_element;
	char_array_class url;
	ID3V2_URL_FRAME url_frame;
	uint32_class counter;
	ubyte_class extra_counter_element;
	ubyte_array_class extra_counter;
	ID3V2_PCNT_FRAME pcnt_frame;
	ubyte_class popm_data_element;
	ubyte_array_class popm_data;
	ID3V2_POPM_FRAME popm_frame;
	ubyte_class priv_data_element;
	ubyte_array_class priv_data;
	ID3V2_PRIV_FRAME priv_frame;
	ubyte_class ufid_data_element;
	ubyte_array_class ufid_data;
	ID3V2_UFID_FRAME ufid_frame;
	ubyte_class geob_data_element;
	ubyte_array_class geob_data;
	ID3V2_GEOB_FRAME geob_frame;
	ubyte_class cd_toc_element;
	ubyte_array_class cd_toc;
	ID3V2_MCDI_FRAME mcdi_frame;
	ubyte_class timestamp_format;
	ubyte_class event_data_element;
	ubyte_array_class event_data;
	ID3V2_ETCO_FRAME etco_frame;
	ubyte_class content_type;
	ubyte_class sylt_data_element;
	ubyte_array_class sylt_data;
	ID3V2_SYLT_FRAME sylt_frame;
	ubyte_class rva2_data_element;
	ubyte_array_class rva2_data;
	ID3V2_RVA2_FRAME rva2_frame;
	ubyte_class interpolation_method;
	ubyte_class equ2_data_element;
	ubyte_array_class equ2_data;
	ID3V2_EQU2_FRAME equ2_frame;
	uint16_class reverb_left;
	uint16_class reverb_right;
	ubyte_class reverb_bounces_left;
	ubyte_class reverb_bounces_right;
	ubyte_class feedback_ll;
	ubyte_class feedback_lr;
	ubyte_class feedback_rr;
	ubyte_class feedback_rl;
	ubyte_class premix_lr;
	ubyte_class premix_rl;
	ID3V2_RVRB_FRAME rvrb_frame;
	ubyte_class tempo_data_element;
	ubyte_array_class tempo_data;
	ID3V2_SYTC_FRAME sytc_frame;
	uint16_class frames_between_ref;
	ubyte_class bbr_hi;
	uint16_class bbr_lo;
	ubyte_class mbr_hi;
	uint16_class mbr_lo;
	ubyte_class bits_for_bytes_dev;
	ubyte_class bits_for_ms_dev;
	ubyte_class deviation_data_element;
	ubyte_array_class deviation_data;
	ID3V2_MLLT_FRAME mllt_frame;
	ubyte_class buf_hi;
	uint16_class buf_lo;
	ubyte_class embedded_info_flag;
	uint32_class offset_to_next;
	ID3V2_RBUF_FRAME rbuf_frame;
	ubyte_class aenc_data_element;
	ubyte_array_class aenc_data;
	ID3V2_AENC_FRAME aenc_frame;
	ubyte_class encr_data_element;
	ubyte_array_class encr_data;
	ID3V2_ENCR_FRAME encr_frame;
	ubyte_class grid_data_element;
	ubyte_array_class grid_data;
	ID3V2_GRID_FRAME grid_frame;
	char_class frame_identifier_element;
	char_array_class frame_identifier;
	ubyte_class link_data_element;
	ubyte_array_class link_data;
	ID3V2_LINK_FRAME link_frame;
	char_class terms_text_element;
	char_array_class terms_text;
	ID3V2_USER_FRAME user_frame;
	ubyte_class owne_data_element;
	ubyte_array_class owne_data;
	ID3V2_OWNE_FRAME owne_frame;
	ubyte_class chap_data_element;
	ubyte_array_class chap_data;
	ID3V2_CHAP_FRAME chap_frame;
	ubyte_class ctoc_data_element;
	ubyte_array_class ctoc_data;
	ID3V2_CTOC_FRAME ctoc_frame;
	ubyte_class group_symbol;
	ubyte_class signature_element;
	ubyte_array_class signature;
	ID3V2_SIGN_FRAME sign_frame;
	uint32_class indexed_data_start;
	uint32_class indexed_data_length;
	uint16_class num_index_points;
	ubyte_class bits_per_index;
	ID3V2_ASPI_FRAME aspi_frame;
	uint32_class peak_signal;
	uint16_class radio_gain;
	uint16_class audiophile_gain;
	ID3V2_RGAD_FRAME rgad_frame;
	ubyte_class frame_data_element;
	ubyte_array_class frame_data;
	ID3V2_GENERIC_FRAME gen_frame;
	ubyte_class padding_element;
	ubyte_array_class padding;
	mp3_id3v2_tag id3v2;
	ubyte_class sync_byte1;
	ubyte_class sync_byte2;
	ubyte_class header_byte3;
	ubyte_class header_byte4;
	uint16_class crc16;
	mp3_mpeg_header hdr;
	mp3_mpeg_frame frame;
	char_class tag_id_element;
	char_array_class tag_id;
	char_class title_element;
	char_array_class title;
	char_class artist_element;
	char_array_class artist;
	char_class album_element;
	char_array_class album;
	char_class year_element;
	char_array_class year;
	char_class comment_element;
	char_array_class comment;
	ubyte_class zero_byte;
	ubyte_class track;
	ubyte_class genre;
	mp3_id3v1_tag id3v1;
	mp3_file file;


	globals_class() :
		header_id_element(false),
		header_id(header_id_element),
		version_major(1),
		version_minor(1),
		header_flags(1),
		raw_size(3),
		ss_b0(1),
		ss_b1(1),
		ss_b2(1),
		ss_b3(1),
		id_element(false),
		id(id_element),
		size(4),
		flags1(1),
		flags2(1),
		flags(ID3V2_FRAME_FLAGS_flags_instances),
		encoding(5),
		text_data_element(false),
		text_data(text_data_element),
		text_frame(ID3V2_TEXT_FRAME_text_frame_instances),
		language_element(false),
		language(language_element),
		comment_data_element(false),
		comment_data(comment_data_element),
		comm_frame(ID3V2_COMM_FRAME_comm_frame_instances),
		mime_type_element(false),
		mime_type(mime_type_element),
		null_term1(1),
		picture_type(6),
		null_term2(1),
		picture_data_element(false),
		picture_data(picture_data_element),
		apic_frame(ID3V2_APIC_FRAME_apic_frame_instances),
		lyrics_data_element(false),
		lyrics_data(lyrics_data_element),
		uslt_frame(ID3V2_USLT_FRAME_uslt_frame_instances),
		txxx_data_element(false),
		txxx_data(txxx_data_element),
		txxx_frame(ID3V2_TXXX_FRAME_txxx_frame_instances),
		wxxx_data_element(false),
		wxxx_data(wxxx_data_element),
		wxxx_frame(ID3V2_WXXX_FRAME_wxxx_frame_instances),
		url_element(false),
		url(url_element),
		url_frame(ID3V2_URL_FRAME_url_frame_instances),
		counter(1),
		extra_counter_element(false),
		extra_counter(extra_counter_element),
		pcnt_frame(ID3V2_PCNT_FRAME_pcnt_frame_instances),
		popm_data_element(false),
		popm_data(popm_data_element),
		popm_frame(ID3V2_POPM_FRAME_popm_frame_instances),
		priv_data_element(false),
		priv_data(priv_data_element),
		priv_frame(ID3V2_PRIV_FRAME_priv_frame_instances),
		ufid_data_element(false),
		ufid_data(ufid_data_element),
		ufid_frame(ID3V2_UFID_FRAME_ufid_frame_instances),
		geob_data_element(false),
		geob_data(geob_data_element),
		geob_frame(ID3V2_GEOB_FRAME_geob_frame_instances),
		cd_toc_element(false),
		cd_toc(cd_toc_element),
		mcdi_frame(ID3V2_MCDI_FRAME_mcdi_frame_instances),
		timestamp_format(7),
		event_data_element(false),
		event_data(event_data_element),
		etco_frame(ID3V2_ETCO_FRAME_etco_frame_instances),
		content_type(8),
		sylt_data_element(false),
		sylt_data(sylt_data_element),
		sylt_frame(ID3V2_SYLT_FRAME_sylt_frame_instances),
		rva2_data_element(false),
		rva2_data(rva2_data_element),
		rva2_frame(ID3V2_RVA2_FRAME_rva2_frame_instances),
		interpolation_method(9),
		equ2_data_element(false),
		equ2_data(equ2_data_element),
		equ2_frame(ID3V2_EQU2_FRAME_equ2_frame_instances),
		reverb_left(1),
		reverb_right(1),
		reverb_bounces_left(1),
		reverb_bounces_right(1),
		feedback_ll(1),
		feedback_lr(1),
		feedback_rr(1),
		feedback_rl(1),
		premix_lr(1),
		premix_rl(1),
		rvrb_frame(ID3V2_RVRB_FRAME_rvrb_frame_instances),
		tempo_data_element(false),
		tempo_data(tempo_data_element),
		sytc_frame(ID3V2_SYTC_FRAME_sytc_frame_instances),
		frames_between_ref(1),
		bbr_hi(1),
		bbr_lo(1),
		mbr_hi(1),
		mbr_lo(1),
		bits_for_bytes_dev(1),
		bits_for_ms_dev(1),
		deviation_data_element(false),
		deviation_data(deviation_data_element),
		mllt_frame(ID3V2_MLLT_FRAME_mllt_frame_instances),
		buf_hi(1),
		buf_lo(1),
		embedded_info_flag(10),
		offset_to_next(1),
		rbuf_frame(ID3V2_RBUF_FRAME_rbuf_frame_instances),
		aenc_data_element(false),
		aenc_data(aenc_data_element),
		aenc_frame(ID3V2_AENC_FRAME_aenc_frame_instances),
		encr_data_element(false),
		encr_data(encr_data_element),
		encr_frame(ID3V2_ENCR_FRAME_encr_frame_instances),
		grid_data_element(false),
		grid_data(grid_data_element),
		grid_frame(ID3V2_GRID_FRAME_grid_frame_instances),
		frame_identifier_element(false),
		frame_identifier(frame_identifier_element),
		link_data_element(false),
		link_data(link_data_element),
		link_frame(ID3V2_LINK_FRAME_link_frame_instances),
		terms_text_element(false),
		terms_text(terms_text_element),
		user_frame(ID3V2_USER_FRAME_user_frame_instances),
		owne_data_element(false),
		owne_data(owne_data_element),
		owne_frame(ID3V2_OWNE_FRAME_owne_frame_instances),
		chap_data_element(false),
		chap_data(chap_data_element),
		chap_frame(ID3V2_CHAP_FRAME_chap_frame_instances),
		ctoc_data_element(false),
		ctoc_data(ctoc_data_element),
		ctoc_frame(ID3V2_CTOC_FRAME_ctoc_frame_instances),
		group_symbol(1),
		signature_element(false),
		signature(signature_element),
		sign_frame(ID3V2_SIGN_FRAME_sign_frame_instances),
		indexed_data_start(1),
		indexed_data_length(1),
		num_index_points(1),
		bits_per_index(11),
		aspi_frame(ID3V2_ASPI_FRAME_aspi_frame_instances),
		peak_signal(1),
		radio_gain(1),
		audiophile_gain(1),
		rgad_frame(ID3V2_RGAD_FRAME_rgad_frame_instances),
		frame_data_element(false),
		frame_data(frame_data_element),
		gen_frame(ID3V2_GENERIC_FRAME_gen_frame_instances),
		padding_element(false),
		padding(padding_element),
		id3v2(mp3_id3v2_tag_id3v2_instances),
		sync_byte1(1),
		sync_byte2(1),
		header_byte3(12),
		header_byte4(1),
		crc16(1),
		hdr(mp3_mpeg_header_hdr_instances),
		frame(mp3_mpeg_frame_frame_instances),
		tag_id_element(false),
		tag_id(tag_id_element),
		title_element(false),
		title(title_element),
		artist_element(false),
		artist(artist_element),
		album_element(false),
		album(album_element),
		year_element(false),
		year(year_element),
		comment_element(false),
		comment(comment_element),
		zero_byte(1),
		track(13),
		genre(14),
		id3v1(mp3_id3v1_tag_id3v1_instances),
		file(mp3_file_file_instances)
	{}
};

globals_class* g;

void write_syncsafe_at(uint32 value, int64 pos) {
	/*local*/ ubyte b3 = (value & 0x7F);
	/*local*/ ubyte b2 = ((value >> 7) & 0x7F);
	/*local*/ ubyte b1 = ((value >> 14) & 0x7F);
	/*local*/ ubyte b0 = ((value >> 21) & 0x7F);
	/*local*/ int64 save = FTell();
	FSeek(pos);
	GENERATE(ss_b0, ::g->ss_b0.generate({ b0 }));
	GENERATE(ss_b1, ::g->ss_b1.generate({ b1 }));
	GENERATE(ss_b2, ::g->ss_b2.generate({ b2 }));
	GENERATE(ss_b3, ::g->ss_b3.generate({ b3 }));
	FSeek(save);
}

ID3V2_FRAME_FLAGS* ID3V2_FRAME_FLAGS::generate() {
	if (generated == 1) {
		ID3V2_FRAME_FLAGS* new_instance = new ID3V2_FRAME_FLAGS(instances);
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

	GENERATE_VAR(flags1, ::g->flags1.generate({ 0 }));
	GENERATE_VAR(flags2, ::g->flags2.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_TEXT_FRAME* ID3V2_TEXT_FRAME::generate() {
	if (generated == 1) {
		ID3V2_TEXT_FRAME* new_instance = new ID3V2_TEXT_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "TIT2", "TIT3", "TPE1", "TPE2", "TPE3", "TPE4", "TALB", "TYER", "TDRC", "TRCK", "TPOS", "TCON", "TCOM", "TPUB", "TEXT", "TENC", "TSSE", "TLEN", "TBPM", "TKEY", "TLAN", "TFLT", "TMED", "TSRC", "TOAL", "TOFN", "TOLY", "TOPE", "TOWN", "TRSN", "TRSO", "TSOA", "TSOP", "TSOT", "TSST", "TMOO", "TPRO", "TDEN", "TDOR", "TDRL", "TDTG", "TSIZ" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	if ((size() > 1)) {
		GENERATE_VAR(text_data, ::g->text_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_COMM_FRAME* ID3V2_COMM_FRAME::generate() {
	if (generated == 1) {
		ID3V2_COMM_FRAME* new_instance = new ID3V2_COMM_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "COMM" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	GENERATE_VAR(language, ::g->language.generate(3));
	if ((size() > 4)) {
		GENERATE_VAR(comment_data, ::g->comment_data.generate((size() - 4)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_APIC_FRAME* ID3V2_APIC_FRAME::generate() {
	if (generated == 1) {
		ID3V2_APIC_FRAME* new_instance = new ID3V2_APIC_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "APIC" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	GENERATE_VAR(mime_type, ::g->mime_type.generate(10, { "image/jpeg" }));
	GENERATE_VAR(null_term1, ::g->null_term1.generate({ 0 }));
	GENERATE_VAR(picture_type, ::g->picture_type.generate());
	GENERATE_VAR(null_term2, ::g->null_term2.generate({ 0 }));
	pic_data_size = (size() - 14);
	if ((pic_data_size > 0)) {
		GENERATE_VAR(picture_data, ::g->picture_data.generate(pic_data_size));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_USLT_FRAME* ID3V2_USLT_FRAME::generate() {
	if (generated == 1) {
		ID3V2_USLT_FRAME* new_instance = new ID3V2_USLT_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "USLT" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	GENERATE_VAR(language, ::g->language.generate(3));
	if ((size() > 4)) {
		GENERATE_VAR(lyrics_data, ::g->lyrics_data.generate((size() - 4)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_TXXX_FRAME* ID3V2_TXXX_FRAME::generate() {
	if (generated == 1) {
		ID3V2_TXXX_FRAME* new_instance = new ID3V2_TXXX_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "TXXX" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	if ((size() > 1)) {
		GENERATE_VAR(txxx_data, ::g->txxx_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_WXXX_FRAME* ID3V2_WXXX_FRAME::generate() {
	if (generated == 1) {
		ID3V2_WXXX_FRAME* new_instance = new ID3V2_WXXX_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "WXXX" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	if ((size() > 1)) {
		GENERATE_VAR(wxxx_data, ::g->wxxx_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_URL_FRAME* ID3V2_URL_FRAME::generate() {
	if (generated == 1) {
		ID3V2_URL_FRAME* new_instance = new ID3V2_URL_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "WOAR", "WOAF", "WOAS", "WORS", "WPAY", "WPUB" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(url, ::g->url.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_PCNT_FRAME* ID3V2_PCNT_FRAME::generate() {
	if (generated == 1) {
		ID3V2_PCNT_FRAME* new_instance = new ID3V2_PCNT_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "PCNT" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(counter, ::g->counter.generate());
	if ((size() > 4)) {
		GENERATE_VAR(extra_counter, ::g->extra_counter.generate((size() - 4)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_POPM_FRAME* ID3V2_POPM_FRAME::generate() {
	if (generated == 1) {
		ID3V2_POPM_FRAME* new_instance = new ID3V2_POPM_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "POPM" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	if ((size() > 0)) {
		GENERATE_VAR(popm_data, ::g->popm_data.generate(size()));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_PRIV_FRAME* ID3V2_PRIV_FRAME::generate() {
	if (generated == 1) {
		ID3V2_PRIV_FRAME* new_instance = new ID3V2_PRIV_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "PRIV" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(priv_data, ::g->priv_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_UFID_FRAME* ID3V2_UFID_FRAME::generate() {
	if (generated == 1) {
		ID3V2_UFID_FRAME* new_instance = new ID3V2_UFID_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "UFID" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(ufid_data, ::g->ufid_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_GEOB_FRAME* ID3V2_GEOB_FRAME::generate() {
	if (generated == 1) {
		ID3V2_GEOB_FRAME* new_instance = new ID3V2_GEOB_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "GEOB" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	if ((size() > 1)) {
		GENERATE_VAR(geob_data, ::g->geob_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_MCDI_FRAME* ID3V2_MCDI_FRAME::generate() {
	if (generated == 1) {
		ID3V2_MCDI_FRAME* new_instance = new ID3V2_MCDI_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "MCDI" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(cd_toc, ::g->cd_toc.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_ETCO_FRAME* ID3V2_ETCO_FRAME::generate() {
	if (generated == 1) {
		ID3V2_ETCO_FRAME* new_instance = new ID3V2_ETCO_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "ETCO" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(timestamp_format, ::g->timestamp_format.generate());
	if ((size() > 1)) {
		GENERATE_VAR(event_data, ::g->event_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_SYLT_FRAME* ID3V2_SYLT_FRAME::generate() {
	if (generated == 1) {
		ID3V2_SYLT_FRAME* new_instance = new ID3V2_SYLT_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "SYLT" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	GENERATE_VAR(language, ::g->language.generate(3));
	GENERATE_VAR(timestamp_format, ::g->timestamp_format.generate());
	GENERATE_VAR(content_type, ::g->content_type.generate());
	if ((size() > 6)) {
		GENERATE_VAR(sylt_data, ::g->sylt_data.generate((size() - 6)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_RVA2_FRAME* ID3V2_RVA2_FRAME::generate() {
	if (generated == 1) {
		ID3V2_RVA2_FRAME* new_instance = new ID3V2_RVA2_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "RVA2" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(rva2_data, ::g->rva2_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_EQU2_FRAME* ID3V2_EQU2_FRAME::generate() {
	if (generated == 1) {
		ID3V2_EQU2_FRAME* new_instance = new ID3V2_EQU2_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "EQU2" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(interpolation_method, ::g->interpolation_method.generate());
	if ((size() > 1)) {
		GENERATE_VAR(equ2_data, ::g->equ2_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_RVRB_FRAME* ID3V2_RVRB_FRAME::generate() {
	if (generated == 1) {
		ID3V2_RVRB_FRAME* new_instance = new ID3V2_RVRB_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "RVRB" }));
	GENERATE_VAR(size, ::g->size.generate({ 12 }));
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(reverb_left, ::g->reverb_left.generate());
	GENERATE_VAR(reverb_right, ::g->reverb_right.generate());
	GENERATE_VAR(reverb_bounces_left, ::g->reverb_bounces_left.generate());
	GENERATE_VAR(reverb_bounces_right, ::g->reverb_bounces_right.generate());
	GENERATE_VAR(feedback_ll, ::g->feedback_ll.generate());
	GENERATE_VAR(feedback_lr, ::g->feedback_lr.generate());
	GENERATE_VAR(feedback_rr, ::g->feedback_rr.generate());
	GENERATE_VAR(feedback_rl, ::g->feedback_rl.generate());
	GENERATE_VAR(premix_lr, ::g->premix_lr.generate());
	GENERATE_VAR(premix_rl, ::g->premix_rl.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_SYTC_FRAME* ID3V2_SYTC_FRAME::generate() {
	if (generated == 1) {
		ID3V2_SYTC_FRAME* new_instance = new ID3V2_SYTC_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "SYTC" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(timestamp_format, ::g->timestamp_format.generate());
	if ((size() > 1)) {
		GENERATE_VAR(tempo_data, ::g->tempo_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_MLLT_FRAME* ID3V2_MLLT_FRAME::generate() {
	if (generated == 1) {
		ID3V2_MLLT_FRAME* new_instance = new ID3V2_MLLT_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "MLLT" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(frames_between_ref, ::g->frames_between_ref.generate());
	GENERATE_VAR(bbr_hi, ::g->bbr_hi.generate());
	GENERATE_VAR(bbr_lo, ::g->bbr_lo.generate());
	GENERATE_VAR(mbr_hi, ::g->mbr_hi.generate());
	GENERATE_VAR(mbr_lo, ::g->mbr_lo.generate());
	GENERATE_VAR(bits_for_bytes_dev, ::g->bits_for_bytes_dev.generate());
	GENERATE_VAR(bits_for_ms_dev, ::g->bits_for_ms_dev.generate());
	if ((size() > 10)) {
		GENERATE_VAR(deviation_data, ::g->deviation_data.generate((size() - 10)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_RBUF_FRAME* ID3V2_RBUF_FRAME::generate() {
	if (generated == 1) {
		ID3V2_RBUF_FRAME* new_instance = new ID3V2_RBUF_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "RBUF" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(buf_hi, ::g->buf_hi.generate());
	GENERATE_VAR(buf_lo, ::g->buf_lo.generate());
	GENERATE_VAR(embedded_info_flag, ::g->embedded_info_flag.generate());
	if ((size() > 4)) {
		GENERATE_VAR(offset_to_next, ::g->offset_to_next.generate());
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_AENC_FRAME* ID3V2_AENC_FRAME::generate() {
	if (generated == 1) {
		ID3V2_AENC_FRAME* new_instance = new ID3V2_AENC_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "AENC" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(aenc_data, ::g->aenc_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_ENCR_FRAME* ID3V2_ENCR_FRAME::generate() {
	if (generated == 1) {
		ID3V2_ENCR_FRAME* new_instance = new ID3V2_ENCR_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "ENCR" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encr_data, ::g->encr_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_GRID_FRAME* ID3V2_GRID_FRAME::generate() {
	if (generated == 1) {
		ID3V2_GRID_FRAME* new_instance = new ID3V2_GRID_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "GRID" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(grid_data, ::g->grid_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_LINK_FRAME* ID3V2_LINK_FRAME::generate() {
	if (generated == 1) {
		ID3V2_LINK_FRAME* new_instance = new ID3V2_LINK_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "LINK" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(frame_identifier, ::g->frame_identifier.generate(4));
	if ((size() > 4)) {
		GENERATE_VAR(link_data, ::g->link_data.generate((size() - 4)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_USER_FRAME* ID3V2_USER_FRAME::generate() {
	if (generated == 1) {
		ID3V2_USER_FRAME* new_instance = new ID3V2_USER_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "USER" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	GENERATE_VAR(language, ::g->language.generate(3));
	if ((size() > 4)) {
		GENERATE_VAR(terms_text, ::g->terms_text.generate((size() - 4)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_OWNE_FRAME* ID3V2_OWNE_FRAME::generate() {
	if (generated == 1) {
		ID3V2_OWNE_FRAME* new_instance = new ID3V2_OWNE_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "OWNE" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(encoding, ::g->encoding.generate());
	if ((size() > 1)) {
		GENERATE_VAR(owne_data, ::g->owne_data.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_CHAP_FRAME* ID3V2_CHAP_FRAME::generate() {
	if (generated == 1) {
		ID3V2_CHAP_FRAME* new_instance = new ID3V2_CHAP_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "CHAP" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(chap_data, ::g->chap_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_CTOC_FRAME* ID3V2_CTOC_FRAME::generate() {
	if (generated == 1) {
		ID3V2_CTOC_FRAME* new_instance = new ID3V2_CTOC_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "CTOC" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(ctoc_data, ::g->ctoc_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_SIGN_FRAME* ID3V2_SIGN_FRAME::generate() {
	if (generated == 1) {
		ID3V2_SIGN_FRAME* new_instance = new ID3V2_SIGN_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "SIGN" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(group_symbol, ::g->group_symbol.generate());
	if ((size() > 1)) {
		GENERATE_VAR(signature, ::g->signature.generate((size() - 1)));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_ASPI_FRAME* ID3V2_ASPI_FRAME::generate() {
	if (generated == 1) {
		ID3V2_ASPI_FRAME* new_instance = new ID3V2_ASPI_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "ASPI" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(indexed_data_start, ::g->indexed_data_start.generate());
	GENERATE_VAR(indexed_data_length, ::g->indexed_data_length.generate());
	GENERATE_VAR(num_index_points, ::g->num_index_points.generate());
	GENERATE_VAR(bits_per_index, ::g->bits_per_index.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_RGAD_FRAME* ID3V2_RGAD_FRAME::generate() {
	if (generated == 1) {
		ID3V2_RGAD_FRAME* new_instance = new ID3V2_RGAD_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "RGAD" }));
	GENERATE_VAR(size, ::g->size.generate({ 8 }));
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(peak_signal, ::g->peak_signal.generate());
	GENERATE_VAR(radio_gain, ::g->radio_gain.generate());
	GENERATE_VAR(audiophile_gain, ::g->audiophile_gain.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ID3V2_GENERIC_FRAME* ID3V2_GENERIC_FRAME::generate() {
	if (generated == 1) {
		ID3V2_GENERIC_FRAME* new_instance = new ID3V2_GENERIC_FRAME(instances);
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

	GENERATE_VAR(id, ::g->id.generate(4, { "COMR", "POSS" }));
	GENERATE_VAR(size, ::g->size.generate());
	GENERATE_VAR(flags, ::g->flags.generate());
	GENERATE_VAR(frame_data, ::g->frame_data.generate(size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp3_id3v2_tag* mp3_id3v2_tag::generate() {
	if (generated == 1) {
		mp3_id3v2_tag* new_instance = new mp3_id3v2_tag(instances);
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

	Printf("=== ID3v2 Tag ===\n");
	GENERATE_VAR(header_id, ::g->header_id.generate(3, { "ID3" }));
	GENERATE_VAR(version_major, ::g->version_major.generate({ 3, 4 }));
	GENERATE_VAR(version_minor, ::g->version_minor.generate({ 0 }));
	GENERATE_VAR(header_flags, ::g->header_flags.generate({ 0 }));
	size_pos = FTell();
	GENERATE_VAR(raw_size, ::g->raw_size.generate());
	FSeek(size_pos);
	write_syncsafe_at(raw_size(), size_pos);
	tag_body_size = raw_size();
	tag_data_start = FTell();
	frame_count = 0;
	frame_choices = { "TEXT", "COMM", "APIC", "USLT", "TXXX", "WXXX", "WURL", "PCNT", "POPM", "PRIV", "UFID", "GEOB", "MCDI", "ETCO", "SYLT", "RVA2", "EQU2", "RVRB", "SYTC", "MLLT", "RBUF", "AENC", "ENCR", "GRID", "LINK", "USER", "OWNE", "CHAP", "CTOC", "SIGN", "ASPI", "RGAD" };
	next_frame.resize(4);
	while ((((frame_count < 12) && ((FTell() - tag_data_start) < (tag_body_size - 10))) && ReadBytes(next_frame, FTell(), 4, frame_choices, frame_choices))) {
		switch (STR2INT(next_frame)) {
		case STR2INT("TEXT"):
			GENERATE_VAR(text_frame, ::g->text_frame.generate());
			break;
		case STR2INT("COMM"):
			GENERATE_VAR(comm_frame, ::g->comm_frame.generate());
			break;
		case STR2INT("APIC"):
			GENERATE_VAR(apic_frame, ::g->apic_frame.generate());
			break;
		case STR2INT("USLT"):
			GENERATE_VAR(uslt_frame, ::g->uslt_frame.generate());
			break;
		case STR2INT("TXXX"):
			GENERATE_VAR(txxx_frame, ::g->txxx_frame.generate());
			break;
		case STR2INT("WXXX"):
			GENERATE_VAR(wxxx_frame, ::g->wxxx_frame.generate());
			break;
		case STR2INT("WURL"):
			GENERATE_VAR(url_frame, ::g->url_frame.generate());
			break;
		case STR2INT("PCNT"):
			GENERATE_VAR(pcnt_frame, ::g->pcnt_frame.generate());
			break;
		case STR2INT("POPM"):
			GENERATE_VAR(popm_frame, ::g->popm_frame.generate());
			break;
		case STR2INT("PRIV"):
			GENERATE_VAR(priv_frame, ::g->priv_frame.generate());
			break;
		case STR2INT("UFID"):
			GENERATE_VAR(ufid_frame, ::g->ufid_frame.generate());
			break;
		case STR2INT("GEOB"):
			GENERATE_VAR(geob_frame, ::g->geob_frame.generate());
			break;
		case STR2INT("MCDI"):
			GENERATE_VAR(mcdi_frame, ::g->mcdi_frame.generate());
			break;
		case STR2INT("ETCO"):
			GENERATE_VAR(etco_frame, ::g->etco_frame.generate());
			break;
		case STR2INT("SYLT"):
			GENERATE_VAR(sylt_frame, ::g->sylt_frame.generate());
			break;
		case STR2INT("RVA2"):
			GENERATE_VAR(rva2_frame, ::g->rva2_frame.generate());
			break;
		case STR2INT("EQU2"):
			GENERATE_VAR(equ2_frame, ::g->equ2_frame.generate());
			break;
		case STR2INT("RVRB"):
			GENERATE_VAR(rvrb_frame, ::g->rvrb_frame.generate());
			break;
		case STR2INT("SYTC"):
			GENERATE_VAR(sytc_frame, ::g->sytc_frame.generate());
			break;
		case STR2INT("MLLT"):
			GENERATE_VAR(mllt_frame, ::g->mllt_frame.generate());
			break;
		case STR2INT("RBUF"):
			GENERATE_VAR(rbuf_frame, ::g->rbuf_frame.generate());
			break;
		case STR2INT("AENC"):
			GENERATE_VAR(aenc_frame, ::g->aenc_frame.generate());
			break;
		case STR2INT("ENCR"):
			GENERATE_VAR(encr_frame, ::g->encr_frame.generate());
			break;
		case STR2INT("GRID"):
			GENERATE_VAR(grid_frame, ::g->grid_frame.generate());
			break;
		case STR2INT("LINK"):
			GENERATE_VAR(link_frame, ::g->link_frame.generate());
			break;
		case STR2INT("USER"):
			GENERATE_VAR(user_frame, ::g->user_frame.generate());
			break;
		case STR2INT("OWNE"):
			GENERATE_VAR(owne_frame, ::g->owne_frame.generate());
			break;
		case STR2INT("CHAP"):
			GENERATE_VAR(chap_frame, ::g->chap_frame.generate());
			break;
		case STR2INT("CTOC"):
			GENERATE_VAR(ctoc_frame, ::g->ctoc_frame.generate());
			break;
		case STR2INT("SIGN"):
			GENERATE_VAR(sign_frame, ::g->sign_frame.generate());
			break;
		case STR2INT("ASPI"):
			GENERATE_VAR(aspi_frame, ::g->aspi_frame.generate());
			break;
		case STR2INT("RGAD"):
			GENERATE_VAR(rgad_frame, ::g->rgad_frame.generate());
			break;
		default:
			GENERATE_VAR(gen_frame, ::g->gen_frame.generate());
			break;
		};
		frame_count++;
		VectorRemove(frame_choices, { next_frame });
	};
	bytes_written = (FTell() - tag_data_start);
	padding_needed = (tag_body_size - bytes_written);
	if (((padding_needed > 0) && (padding_needed < 65536))) {
		GENERATE_VAR(padding, ::g->padding.generate(padding_needed));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp3_mpeg_header* mp3_mpeg_header::generate() {
	if (generated == 1) {
		mp3_mpeg_header* new_instance = new mp3_mpeg_header(instances);
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

	GENERATE_VAR(sync_byte1, ::g->sync_byte1.generate({ 0xFF }));
	GENERATE_VAR(sync_byte2, ::g->sync_byte2.generate({ 0xFB, 0xFA, 0xF3, 0xF2, 0xFF, 0xFE, 0xFD, 0xFC }));
	mpeg_version = ((sync_byte2() >> 3) & 3);
	layer = ((sync_byte2() >> 1) & 3);
	protection = (sync_byte2() & 1);
	GENERATE_VAR(header_byte3, ::g->header_byte3.generate());
	bitrate_index = ((header_byte3() >> 4) & 0xF);
	sample_rate_index = ((header_byte3() >> 2) & 3);
	padding_bit = ((header_byte3() >> 1) & 1);
	private_bit = (header_byte3() & 1);
	GENERATE_VAR(header_byte4, ::g->header_byte4.generate());
	channel_mode = ((header_byte4() >> 6) & 3);
	mode_extension = ((header_byte4() >> 4) & 3);
	copyright_bit = ((header_byte4() >> 3) & 1);
	original_bit = ((header_byte4() >> 2) & 1);
	emphasis = (header_byte4() & 3);
	if ((protection == 0)) {
		GENERATE_VAR(crc16, ::g->crc16.generate());
	};
	ver_idx = ((mpeg_version == 3) ? 1 : 0);
	if ((layer == 3)) {
	lay_idx = 0;
	} else {
	if ((layer == 2)) {
	lay_idx = 1;
	} else {
	lay_idx = 2;
	};
	};
	bi = bitrate_index;
	if ((bi < 1)) {
	bi = 1;
	};
	if ((bi > 14)) {
	bi = 14;
	};
	si = sample_rate_index;
	if ((si > 2)) {
	si = 0;
	};
	br = bitrate_table[((((ver_idx * 3) + lay_idx) * 16) + bi)];
	sr = samplerate_table[((mpeg_version * 4) + si)];
	spf = samples_per_frame[((mpeg_version * 4) + layer)];
	frame_data_size = 0;
	if (((sr > 0) && (br > 0))) {
		if ((layer == 3)) {
			frame_data_size = (((((12 * br) * 1000) / sr) + padding_bit) * 4);
		} else {
			frame_data_size = (((((spf / 8) * br) * 1000) / sr) + padding_bit);
		};
		hdr_size = (4 + ((protection == 0) ? 2 : 0));
		if ((frame_data_size > hdr_size)) {
		frame_data_size -= hdr_size;
		} else {
		frame_data_size = 32;
		};
	} else {
		frame_data_size = 128;
	};
	if ((frame_data_size > 4096)) {
	frame_data_size = 1024;
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp3_mpeg_frame* mp3_mpeg_frame::generate() {
	if (generated == 1) {
		mp3_mpeg_frame* new_instance = new mp3_mpeg_frame(instances);
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

	Printf("=== MPEG Frame ===\n");
	GENERATE_VAR(hdr, ::g->hdr.generate());
	if ((hdr().frame_data_size > 0)) {
		GENERATE_VAR(frame_data, ::g->frame_data.generate(hdr().frame_data_size));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp3_id3v1_tag* mp3_id3v1_tag::generate() {
	if (generated == 1) {
		mp3_id3v1_tag* new_instance = new mp3_id3v1_tag(instances);
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

	Printf("=== ID3v1 Tag ===\n");
	GENERATE_VAR(tag_id, ::g->tag_id.generate(3, { "TAG" }));
	GENERATE_VAR(title, ::g->title.generate(30));
	GENERATE_VAR(artist, ::g->artist.generate(30));
	GENERATE_VAR(album, ::g->album.generate(30));
	GENERATE_VAR(year, ::g->year.generate(4));
	GENERATE_VAR(comment, ::g->comment.generate(28));
	GENERATE_VAR(zero_byte, ::g->zero_byte.generate({ 0 }));
	GENERATE_VAR(track, ::g->track.generate());
	GENERATE_VAR(genre, ::g->genre.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp3_file* mp3_file::generate() {
	if (generated == 1) {
		mp3_file* new_instance = new mp3_file(instances);
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

	GENERATE_VAR(id3v2, ::g->id3v2.generate());
	GENERATE_VAR(frame, ::g->frame.generate());
	GENERATE_VAR(id3v1, ::g->id3v1.generate());

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

