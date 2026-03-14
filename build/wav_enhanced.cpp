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



class FMT_CHUNK {
	std::vector<FMT_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint16 audio_format_var;
	uint16 num_channels_var;
	uint32 sample_rate_var;
	uint32 byte_rate_var;
	uint16 block_align_var;
	uint16 bits_per_sample_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool audio_format_exists = false;
	bool num_channels_exists = false;
	bool sample_rate_exists = false;
	bool byte_rate_exists = false;
	bool block_align_exists = false;
	bool bits_per_sample_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint16& audio_format() {
		assert_cond(audio_format_exists, "struct field audio_format does not exist");
		return audio_format_var;
	}
	uint16& num_channels() {
		assert_cond(num_channels_exists, "struct field num_channels does not exist");
		return num_channels_var;
	}
	uint32& sample_rate() {
		assert_cond(sample_rate_exists, "struct field sample_rate does not exist");
		return sample_rate_var;
	}
	uint32& byte_rate() {
		assert_cond(byte_rate_exists, "struct field byte_rate does not exist");
		return byte_rate_var;
	}
	uint16& block_align() {
		assert_cond(block_align_exists, "struct field block_align does not exist");
		return block_align_var;
	}
	uint16& bits_per_sample() {
		assert_cond(bits_per_sample_exists, "struct field bits_per_sample does not exist");
		return bits_per_sample_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	FMT_CHUNK& operator () () { return *instances.back(); }
	FMT_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	FMT_CHUNK(std::vector<FMT_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~FMT_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			FMT_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	FMT_CHUNK* generate();
};

int FMT_CHUNK::_parent_id = 0;
int FMT_CHUNK::_index_start = 0;



class FACT_CHUNK {
	std::vector<FACT_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 num_samples_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool num_samples_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& num_samples() {
		assert_cond(num_samples_exists, "struct field num_samples does not exist");
		return num_samples_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	FACT_CHUNK& operator () () { return *instances.back(); }
	FACT_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	FACT_CHUNK(std::vector<FACT_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~FACT_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			FACT_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	FACT_CHUNK* generate();
};

int FACT_CHUNK::_parent_id = 0;
int FACT_CHUNK::_index_start = 0;



class SMPL_LOOP {
	std::vector<SMPL_LOOP*>& instances;

	uint32 id_var;
	uint32 loop_type_var;
	uint32 start_var;
	uint32 end_var;
	uint32 fraction_var;
	uint32 play_count_var;

public:
	bool id_exists = false;
	bool loop_type_exists = false;
	bool start_exists = false;
	bool end_exists = false;
	bool fraction_exists = false;
	bool play_count_exists = false;

	uint32& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& loop_type() {
		assert_cond(loop_type_exists, "struct field loop_type does not exist");
		return loop_type_var;
	}
	uint32& start() {
		assert_cond(start_exists, "struct field start does not exist");
		return start_var;
	}
	uint32& end() {
		assert_cond(end_exists, "struct field end does not exist");
		return end_var;
	}
	uint32& fraction() {
		assert_cond(fraction_exists, "struct field fraction does not exist");
		return fraction_var;
	}
	uint32& play_count() {
		assert_cond(play_count_exists, "struct field play_count does not exist");
		return play_count_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SMPL_LOOP& operator () () { return *instances.back(); }
	SMPL_LOOP& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SMPL_LOOP(std::vector<SMPL_LOOP*>& instances) : instances(instances) { instances.push_back(this); }
	~SMPL_LOOP() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SMPL_LOOP* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SMPL_LOOP* generate();
};

int SMPL_LOOP::_parent_id = 0;
int SMPL_LOOP::_index_start = 0;



class SMPL_CHUNK {
	std::vector<SMPL_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 manufacturer_var;
	uint32 product_var;
	uint32 sample_period_var;
	uint32 midi_unity_note_var;
	uint32 midi_pitch_fraction_var;
	uint32 smpte_format_var;
	uint32 smpte_offset_var;
	uint32 num_loops_var;
	uint32 sampler_data_size_var;
	SMPL_LOOP* loop_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool manufacturer_exists = false;
	bool product_exists = false;
	bool sample_period_exists = false;
	bool midi_unity_note_exists = false;
	bool midi_pitch_fraction_exists = false;
	bool smpte_format_exists = false;
	bool smpte_offset_exists = false;
	bool num_loops_exists = false;
	bool sampler_data_size_exists = false;
	bool loop_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& manufacturer() {
		assert_cond(manufacturer_exists, "struct field manufacturer does not exist");
		return manufacturer_var;
	}
	uint32& product() {
		assert_cond(product_exists, "struct field product does not exist");
		return product_var;
	}
	uint32& sample_period() {
		assert_cond(sample_period_exists, "struct field sample_period does not exist");
		return sample_period_var;
	}
	uint32& midi_unity_note() {
		assert_cond(midi_unity_note_exists, "struct field midi_unity_note does not exist");
		return midi_unity_note_var;
	}
	uint32& midi_pitch_fraction() {
		assert_cond(midi_pitch_fraction_exists, "struct field midi_pitch_fraction does not exist");
		return midi_pitch_fraction_var;
	}
	uint32& smpte_format() {
		assert_cond(smpte_format_exists, "struct field smpte_format does not exist");
		return smpte_format_var;
	}
	uint32& smpte_offset() {
		assert_cond(smpte_offset_exists, "struct field smpte_offset does not exist");
		return smpte_offset_var;
	}
	uint32& num_loops() {
		assert_cond(num_loops_exists, "struct field num_loops does not exist");
		return num_loops_var;
	}
	uint32& sampler_data_size() {
		assert_cond(sampler_data_size_exists, "struct field sampler_data_size does not exist");
		return sampler_data_size_var;
	}
	SMPL_LOOP& loop() {
		assert_cond(loop_exists, "struct field loop does not exist");
		return *loop_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SMPL_CHUNK& operator () () { return *instances.back(); }
	SMPL_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SMPL_CHUNK(std::vector<SMPL_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~SMPL_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SMPL_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SMPL_CHUNK* generate();
};

int SMPL_CHUNK::_parent_id = 0;
int SMPL_CHUNK::_index_start = 0;



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



class byte_class {
	int small;
	std::vector<byte> known_values;
	byte value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(byte);
	byte operator () () { return value; }
	byte_class(int small, std::vector<byte> known_values = {}) : small(small), known_values(known_values) {}

	byte generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(byte), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(byte), 0, known_values);
		}
		return value;
	}

	byte generate(std::vector<byte> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(byte), 0, possible_values);
		return value;
	}
};



class INST_CHUNK {
	std::vector<INST_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	ubyte unshifted_note_var;
	byte fine_tune_var;
	byte gain_var;
	ubyte low_note_var;
	ubyte high_note_var;
	ubyte low_velocity_var;
	ubyte high_velocity_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool unshifted_note_exists = false;
	bool fine_tune_exists = false;
	bool gain_exists = false;
	bool low_note_exists = false;
	bool high_note_exists = false;
	bool low_velocity_exists = false;
	bool high_velocity_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	ubyte& unshifted_note() {
		assert_cond(unshifted_note_exists, "struct field unshifted_note does not exist");
		return unshifted_note_var;
	}
	byte& fine_tune() {
		assert_cond(fine_tune_exists, "struct field fine_tune does not exist");
		return fine_tune_var;
	}
	byte& gain() {
		assert_cond(gain_exists, "struct field gain does not exist");
		return gain_var;
	}
	ubyte& low_note() {
		assert_cond(low_note_exists, "struct field low_note does not exist");
		return low_note_var;
	}
	ubyte& high_note() {
		assert_cond(high_note_exists, "struct field high_note does not exist");
		return high_note_var;
	}
	ubyte& low_velocity() {
		assert_cond(low_velocity_exists, "struct field low_velocity does not exist");
		return low_velocity_var;
	}
	ubyte& high_velocity() {
		assert_cond(high_velocity_exists, "struct field high_velocity does not exist");
		return high_velocity_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	INST_CHUNK& operator () () { return *instances.back(); }
	INST_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	INST_CHUNK(std::vector<INST_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~INST_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			INST_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	INST_CHUNK* generate();
};

int INST_CHUNK::_parent_id = 0;
int INST_CHUNK::_index_start = 0;



class CUE_POINT {
	std::vector<CUE_POINT*>& instances;

	uint32 id_var;
	uint32 position_var;
	std::string data_chunk_id_var;
	uint32 chunk_start_var;
	uint32 block_start_var;
	uint32 sample_offset_var;

public:
	bool id_exists = false;
	bool position_exists = false;
	bool data_chunk_id_exists = false;
	bool chunk_start_exists = false;
	bool block_start_exists = false;
	bool sample_offset_exists = false;

	uint32& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint32& position() {
		assert_cond(position_exists, "struct field position does not exist");
		return position_var;
	}
	std::string& data_chunk_id() {
		assert_cond(data_chunk_id_exists, "struct field data_chunk_id does not exist");
		return data_chunk_id_var;
	}
	uint32& chunk_start() {
		assert_cond(chunk_start_exists, "struct field chunk_start does not exist");
		return chunk_start_var;
	}
	uint32& block_start() {
		assert_cond(block_start_exists, "struct field block_start does not exist");
		return block_start_var;
	}
	uint32& sample_offset() {
		assert_cond(sample_offset_exists, "struct field sample_offset does not exist");
		return sample_offset_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CUE_POINT& operator () () { return *instances.back(); }
	CUE_POINT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CUE_POINT(std::vector<CUE_POINT*>& instances) : instances(instances) { instances.push_back(this); }
	~CUE_POINT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CUE_POINT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CUE_POINT* generate();
};

int CUE_POINT::_parent_id = 0;
int CUE_POINT::_index_start = 0;



class CUE_CHUNK {
	std::vector<CUE_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 num_cue_points_var;
	CUE_POINT* cue_pt_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool num_cue_points_exists = false;
	bool cue_pt_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& num_cue_points() {
		assert_cond(num_cue_points_exists, "struct field num_cue_points does not exist");
		return num_cue_points_var;
	}
	CUE_POINT& cue_pt() {
		assert_cond(cue_pt_exists, "struct field cue_pt does not exist");
		return *cue_pt_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CUE_CHUNK& operator () () { return *instances.back(); }
	CUE_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CUE_CHUNK(std::vector<CUE_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~CUE_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CUE_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CUE_CHUNK* generate();
};

int CUE_CHUNK::_parent_id = 0;
int CUE_CHUNK::_index_start = 0;



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



class BEXT_CHUNK {
	std::vector<BEXT_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	std::string description_var;
	std::string originator_var;
	std::string originator_ref_var;
	std::string orig_date_var;
	std::string orig_time_var;
	uint32 time_ref_low_var;
	uint32 time_ref_high_var;
	uint16 version_var;
	std::vector<ubyte> umid_var;
	int16 loudness_value_var;
	int16 loudness_range_var;
	int16 max_true_peak_var;
	int16 max_momentary_var;
	int16 max_short_term_var;
	std::vector<ubyte> reserved_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool description_exists = false;
	bool originator_exists = false;
	bool originator_ref_exists = false;
	bool orig_date_exists = false;
	bool orig_time_exists = false;
	bool time_ref_low_exists = false;
	bool time_ref_high_exists = false;
	bool version_exists = false;
	bool umid_exists = false;
	bool loudness_value_exists = false;
	bool loudness_range_exists = false;
	bool max_true_peak_exists = false;
	bool max_momentary_exists = false;
	bool max_short_term_exists = false;
	bool reserved_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	std::string& description() {
		assert_cond(description_exists, "struct field description does not exist");
		return description_var;
	}
	std::string& originator() {
		assert_cond(originator_exists, "struct field originator does not exist");
		return originator_var;
	}
	std::string& originator_ref() {
		assert_cond(originator_ref_exists, "struct field originator_ref does not exist");
		return originator_ref_var;
	}
	std::string& orig_date() {
		assert_cond(orig_date_exists, "struct field orig_date does not exist");
		return orig_date_var;
	}
	std::string& orig_time() {
		assert_cond(orig_time_exists, "struct field orig_time does not exist");
		return orig_time_var;
	}
	uint32& time_ref_low() {
		assert_cond(time_ref_low_exists, "struct field time_ref_low does not exist");
		return time_ref_low_var;
	}
	uint32& time_ref_high() {
		assert_cond(time_ref_high_exists, "struct field time_ref_high does not exist");
		return time_ref_high_var;
	}
	uint16& version() {
		assert_cond(version_exists, "struct field version does not exist");
		return version_var;
	}
	std::vector<ubyte>& umid() {
		assert_cond(umid_exists, "struct field umid does not exist");
		return umid_var;
	}
	int16& loudness_value() {
		assert_cond(loudness_value_exists, "struct field loudness_value does not exist");
		return loudness_value_var;
	}
	int16& loudness_range() {
		assert_cond(loudness_range_exists, "struct field loudness_range does not exist");
		return loudness_range_var;
	}
	int16& max_true_peak() {
		assert_cond(max_true_peak_exists, "struct field max_true_peak does not exist");
		return max_true_peak_var;
	}
	int16& max_momentary() {
		assert_cond(max_momentary_exists, "struct field max_momentary does not exist");
		return max_momentary_var;
	}
	int16& max_short_term() {
		assert_cond(max_short_term_exists, "struct field max_short_term does not exist");
		return max_short_term_var;
	}
	std::vector<ubyte>& reserved() {
		assert_cond(reserved_exists, "struct field reserved does not exist");
		return reserved_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BEXT_CHUNK& operator () () { return *instances.back(); }
	BEXT_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BEXT_CHUNK(std::vector<BEXT_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~BEXT_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BEXT_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BEXT_CHUNK* generate();
};

int BEXT_CHUNK::_parent_id = 0;
int BEXT_CHUNK::_index_start = 0;



class IXML_CHUNK {
	std::vector<IXML_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	std::vector<ubyte> xml_data_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool xml_data_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	std::vector<ubyte>& xml_data() {
		assert_cond(xml_data_exists, "struct field xml_data does not exist");
		return xml_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IXML_CHUNK& operator () () { return *instances.back(); }
	IXML_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IXML_CHUNK(std::vector<IXML_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~IXML_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IXML_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IXML_CHUNK* generate();
};

int IXML_CHUNK::_parent_id = 0;
int IXML_CHUNK::_index_start = 0;



class ACID_CHUNK {
	std::vector<ACID_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	uint32 type_flags_var;
	uint16 root_note_var;
	uint16 unknown1_var;
	uint32 unknown2_var;
	uint32 num_beats_var;
	uint16 meter_denom_var;
	uint16 meter_numer_var;
	uint32 tempo_var;

public:
	bool chunk_id_exists = false;
	bool chunk_size_exists = false;
	bool type_flags_exists = false;
	bool root_note_exists = false;
	bool unknown1_exists = false;
	bool unknown2_exists = false;
	bool num_beats_exists = false;
	bool meter_denom_exists = false;
	bool meter_numer_exists = false;
	bool tempo_exists = false;

	std::string& chunk_id() {
		assert_cond(chunk_id_exists, "struct field chunk_id does not exist");
		return chunk_id_var;
	}
	uint32& chunk_size() {
		assert_cond(chunk_size_exists, "struct field chunk_size does not exist");
		return chunk_size_var;
	}
	uint32& type_flags() {
		assert_cond(type_flags_exists, "struct field type_flags does not exist");
		return type_flags_var;
	}
	uint16& root_note() {
		assert_cond(root_note_exists, "struct field root_note does not exist");
		return root_note_var;
	}
	uint16& unknown1() {
		assert_cond(unknown1_exists, "struct field unknown1 does not exist");
		return unknown1_var;
	}
	uint32& unknown2() {
		assert_cond(unknown2_exists, "struct field unknown2 does not exist");
		return unknown2_var;
	}
	uint32& num_beats() {
		assert_cond(num_beats_exists, "struct field num_beats does not exist");
		return num_beats_var;
	}
	uint16& meter_denom() {
		assert_cond(meter_denom_exists, "struct field meter_denom does not exist");
		return meter_denom_var;
	}
	uint16& meter_numer() {
		assert_cond(meter_numer_exists, "struct field meter_numer does not exist");
		return meter_numer_var;
	}
	uint32& tempo() {
		assert_cond(tempo_exists, "struct field tempo does not exist");
		return tempo_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ACID_CHUNK& operator () () { return *instances.back(); }
	ACID_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ACID_CHUNK(std::vector<ACID_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~ACID_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ACID_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ACID_CHUNK* generate();
};

int ACID_CHUNK::_parent_id = 0;
int ACID_CHUNK::_index_start = 0;



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



class INFO_CHUNK {
	std::vector<INFO_CHUNK*>& instances;

	std::string chunk_id_var;
	uint32 chunk_size_var;
	std::string data_var;

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
	std::string& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	INFO_CHUNK& operator () () { return *instances.back(); }
	INFO_CHUNK& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	INFO_CHUNK(std::vector<INFO_CHUNK*>& instances) : instances(instances) { instances.push_back(this); }
	~INFO_CHUNK() {
		if (generated == 2)
			return;
		while (instances.size()) {
			INFO_CHUNK* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	INFO_CHUNK* generate();
};

int INFO_CHUNK::_parent_id = 0;
int INFO_CHUNK::_index_start = 0;



class wav_file {
	std::vector<wav_file*>& instances;

	std::string riff_id_var;
	uint32 riff_size_var;
	std::string wave_id_var;
	FMT_CHUNK* fmt_var;
	FACT_CHUNK* fact_var;
	SMPL_CHUNK* smpl_var;
	INST_CHUNK* inst_var;
	CUE_CHUNK* cue_var;
	BEXT_CHUNK* bext_var;
	IXML_CHUNK* ixml_var;
	ACID_CHUNK* acid_var;
	JUNK_CHUNK* junk_var;
	std::string info_list_id_var;
	uint32 info_list_size_var;
	std::string info_list_type_var;
	INFO_CHUNK* info1_var;
	INFO_CHUNK* info2_var;
	std::string data_id_var;
	uint32 data_size_var;
	std::vector<ubyte> audio_data_var;

public:
	bool riff_id_exists = false;
	bool riff_size_exists = false;
	bool wave_id_exists = false;
	bool fmt_exists = false;
	bool fact_exists = false;
	bool smpl_exists = false;
	bool inst_exists = false;
	bool cue_exists = false;
	bool bext_exists = false;
	bool ixml_exists = false;
	bool acid_exists = false;
	bool junk_exists = false;
	bool info_list_id_exists = false;
	bool info_list_size_exists = false;
	bool info_list_type_exists = false;
	bool info1_exists = false;
	bool info2_exists = false;
	bool data_id_exists = false;
	bool data_size_exists = false;
	bool audio_data_exists = false;

	std::string& riff_id() {
		assert_cond(riff_id_exists, "struct field riff_id does not exist");
		return riff_id_var;
	}
	uint32& riff_size() {
		assert_cond(riff_size_exists, "struct field riff_size does not exist");
		return riff_size_var;
	}
	std::string& wave_id() {
		assert_cond(wave_id_exists, "struct field wave_id does not exist");
		return wave_id_var;
	}
	FMT_CHUNK& fmt() {
		assert_cond(fmt_exists, "struct field fmt does not exist");
		return *fmt_var;
	}
	FACT_CHUNK& fact() {
		assert_cond(fact_exists, "struct field fact does not exist");
		return *fact_var;
	}
	SMPL_CHUNK& smpl() {
		assert_cond(smpl_exists, "struct field smpl does not exist");
		return *smpl_var;
	}
	INST_CHUNK& inst() {
		assert_cond(inst_exists, "struct field inst does not exist");
		return *inst_var;
	}
	CUE_CHUNK& cue() {
		assert_cond(cue_exists, "struct field cue does not exist");
		return *cue_var;
	}
	BEXT_CHUNK& bext() {
		assert_cond(bext_exists, "struct field bext does not exist");
		return *bext_var;
	}
	IXML_CHUNK& ixml() {
		assert_cond(ixml_exists, "struct field ixml does not exist");
		return *ixml_var;
	}
	ACID_CHUNK& acid() {
		assert_cond(acid_exists, "struct field acid does not exist");
		return *acid_var;
	}
	JUNK_CHUNK& junk() {
		assert_cond(junk_exists, "struct field junk does not exist");
		return *junk_var;
	}
	std::string& info_list_id() {
		assert_cond(info_list_id_exists, "struct field info_list_id does not exist");
		return info_list_id_var;
	}
	uint32& info_list_size() {
		assert_cond(info_list_size_exists, "struct field info_list_size does not exist");
		return info_list_size_var;
	}
	std::string& info_list_type() {
		assert_cond(info_list_type_exists, "struct field info_list_type does not exist");
		return info_list_type_var;
	}
	INFO_CHUNK& info1() {
		assert_cond(info1_exists, "struct field info1 does not exist");
		return *info1_var;
	}
	INFO_CHUNK& info2() {
		assert_cond(info2_exists, "struct field info2 does not exist");
		return *info2_var;
	}
	std::string& data_id() {
		assert_cond(data_id_exists, "struct field data_id does not exist");
		return data_id_var;
	}
	uint32& data_size() {
		assert_cond(data_size_exists, "struct field data_size does not exist");
		return data_size_var;
	}
	std::vector<ubyte>& audio_data() {
		assert_cond(audio_data_exists, "struct field audio_data does not exist");
		return audio_data_var;
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
	wav_file& operator () () { return *instances.back(); }
	wav_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	wav_file(std::vector<wav_file*>& instances) : instances(instances) { instances.push_back(this); }
	~wav_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			wav_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	wav_file* generate();
};

int wav_file::_parent_id = 0;
int wav_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "RIFF", "WAVE", "fmt ", "data", "fact", "cue ", "smpl", "inst", "LIST", "JUNK", "bext", "iXML", "acid" };


std::vector<FMT_CHUNK*> FMT_CHUNK_fmt_instances;
std::vector<FACT_CHUNK*> FACT_CHUNK_fact_instances;
std::vector<SMPL_LOOP*> SMPL_LOOP_loop_instances;
std::vector<SMPL_CHUNK*> SMPL_CHUNK_smpl_instances;
std::vector<INST_CHUNK*> INST_CHUNK_inst_instances;
std::vector<CUE_POINT*> CUE_POINT_cue_pt_instances;
std::vector<CUE_CHUNK*> CUE_CHUNK_cue_instances;
std::vector<BEXT_CHUNK*> BEXT_CHUNK_bext_instances;
std::vector<IXML_CHUNK*> IXML_CHUNK_ixml_instances;
std::vector<ACID_CHUNK*> ACID_CHUNK_acid_instances;
std::vector<JUNK_CHUNK*> JUNK_CHUNK_junk_instances;
std::vector<INFO_CHUNK*> INFO_CHUNK_info1_instances;
std::vector<INFO_CHUNK*> INFO_CHUNK_info2_instances;
std::vector<wav_file*> wav_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "riff_id", "char_array_class" }, { "riff_size", "uint32_class" }, { "wave_id", "char_array_class" }, { "chunk_id", "char_array_class" }, { "chunk_size", "uint32_class" }, { "audio_format", "uint16_class" }, { "num_channels", "uint16_class" }, { "sample_rate", "uint32_class" }, { "byte_rate", "uint32_class" }, { "block_align", "uint16_class" }, { "bits_per_sample", "uint16_class" }, { "fmt", "FMT_CHUNK" }, { "num_samples", "uint32_class" }, { "fact", "FACT_CHUNK" }, { "manufacturer", "uint32_class" }, { "product", "uint32_class" }, { "sample_period", "uint32_class" }, { "midi_unity_note", "uint32_class" }, { "midi_pitch_fraction", "uint32_class" }, { "smpte_format", "uint32_class" }, { "smpte_offset", "uint32_class" }, { "num_loops", "uint32_class" }, { "sampler_data_size", "uint32_class" }, { "id", "uint32_class" }, { "loop_type", "uint32_class" }, { "start", "uint32_class" }, { "end", "uint32_class" }, { "fraction", "uint32_class" }, { "play_count", "uint32_class" }, { "loop", "SMPL_LOOP" }, { "smpl", "SMPL_CHUNK" }, { "unshifted_note", "ubyte_class" }, { "fine_tune", "byte_class" }, { "gain", "byte_class" }, { "low_note", "ubyte_class" }, { "high_note", "ubyte_class" }, { "low_velocity", "ubyte_class" }, { "high_velocity", "ubyte_class" }, { "inst", "INST_CHUNK" }, { "num_cue_points", "uint32_class" }, { "position", "uint32_class" }, { "data_chunk_id", "char_array_class" }, { "chunk_start", "uint32_class" }, { "block_start", "uint32_class" }, { "sample_offset", "uint32_class" }, { "cue_pt", "CUE_POINT" }, { "cue", "CUE_CHUNK" }, { "description", "char_array_class" }, { "originator", "char_array_class" }, { "originator_ref", "char_array_class" }, { "orig_date", "char_array_class" }, { "orig_time", "char_array_class" }, { "time_ref_low", "uint32_class" }, { "time_ref_high", "uint32_class" }, { "version", "uint16_class" }, { "umid", "ubyte_array_class" }, { "loudness_value", "int16_class" }, { "loudness_range", "int16_class" }, { "max_true_peak", "int16_class" }, { "max_momentary", "int16_class" }, { "max_short_term", "int16_class" }, { "reserved", "ubyte_array_class" }, { "bext", "BEXT_CHUNK" }, { "xml_data", "ubyte_array_class" }, { "ixml", "IXML_CHUNK" }, { "type_flags", "uint32_class" }, { "root_note", "uint16_class" }, { "unknown1", "uint16_class" }, { "unknown2", "uint32_class" }, { "num_beats", "uint32_class" }, { "meter_denom", "uint16_class" }, { "meter_numer", "uint16_class" }, { "tempo", "uint32_class" }, { "acid", "ACID_CHUNK" }, { "data", "ubyte_array_class" }, { "junk", "JUNK_CHUNK" }, { "info_list_id", "char_array_class" }, { "info_list_size", "uint32_class" }, { "info_list_type", "char_array_class" }, { "data_", "char_array_class" }, { "info1", "INFO_CHUNK" }, { "info2", "INFO_CHUNK" }, { "data_id", "char_array_class" }, { "data_size", "uint32_class" }, { "audio_data", "ubyte_array_class" }, { "file", "wav_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 0, 127 }, { 0, 2 }, { 0, 127 }, { 0, 127 }, { 0, 127 }, { 0, 127 }, { 0, 127 }, { 0, 127 }, { 4, 4096 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class riff_id_element;
	char_array_class riff_id;
	uint32_class riff_size;
	char_class wave_id_element;
	char_array_class wave_id;
	char_class chunk_id_element;
	char_array_class chunk_id;
	uint32_class chunk_size;
	uint16_class audio_format;
	uint16_class num_channels;
	uint32_class sample_rate;
	uint32_class byte_rate;
	uint16_class block_align;
	uint16_class bits_per_sample;
	FMT_CHUNK fmt;
	uint32_class num_samples;
	FACT_CHUNK fact;
	uint32_class manufacturer;
	uint32_class product;
	uint32_class sample_period;
	uint32_class midi_unity_note;
	uint32_class midi_pitch_fraction;
	uint32_class smpte_format;
	uint32_class smpte_offset;
	uint32_class num_loops;
	uint32_class sampler_data_size;
	uint32_class id;
	uint32_class loop_type;
	uint32_class start;
	uint32_class end;
	uint32_class fraction;
	uint32_class play_count;
	SMPL_LOOP loop;
	SMPL_CHUNK smpl;
	ubyte_class unshifted_note;
	byte_class fine_tune;
	byte_class gain;
	ubyte_class low_note;
	ubyte_class high_note;
	ubyte_class low_velocity;
	ubyte_class high_velocity;
	INST_CHUNK inst;
	uint32_class num_cue_points;
	uint32_class position;
	char_class data_chunk_id_element;
	char_array_class data_chunk_id;
	uint32_class chunk_start;
	uint32_class block_start;
	uint32_class sample_offset;
	CUE_POINT cue_pt;
	CUE_CHUNK cue;
	char_class description_element;
	char_array_class description;
	char_class originator_element;
	char_array_class originator;
	char_class originator_ref_element;
	char_array_class originator_ref;
	char_class orig_date_element;
	char_array_class orig_date;
	char_class orig_time_element;
	char_array_class orig_time;
	uint32_class time_ref_low;
	uint32_class time_ref_high;
	uint16_class version;
	ubyte_class umid_element;
	ubyte_array_class umid;
	int16_class loudness_value;
	int16_class loudness_range;
	int16_class max_true_peak;
	int16_class max_momentary;
	int16_class max_short_term;
	ubyte_class reserved_element;
	ubyte_array_class reserved;
	BEXT_CHUNK bext;
	ubyte_class xml_data_element;
	ubyte_array_class xml_data;
	IXML_CHUNK ixml;
	uint32_class type_flags;
	uint16_class root_note;
	uint16_class unknown1;
	uint32_class unknown2;
	uint32_class num_beats;
	uint16_class meter_denom;
	uint16_class meter_numer;
	uint32_class tempo;
	ACID_CHUNK acid;
	ubyte_class data_element;
	ubyte_array_class data;
	JUNK_CHUNK junk;
	char_class info_list_id_element;
	char_array_class info_list_id;
	uint32_class info_list_size;
	char_class info_list_type_element;
	char_array_class info_list_type;
	char_class data__element;
	char_array_class data_;
	INFO_CHUNK info1;
	INFO_CHUNK info2;
	char_class data_id_element;
	char_array_class data_id;
	uint32_class data_size;
	ubyte_class audio_data_element;
	ubyte_array_class audio_data;
	wav_file file;


	globals_class() :
		riff_id_element(false),
		riff_id(riff_id_element),
		riff_size(1),
		wave_id_element(false),
		wave_id(wave_id_element),
		chunk_id_element(false),
		chunk_id(chunk_id_element),
		chunk_size(1),
		audio_format(1),
		num_channels(1),
		sample_rate(1),
		byte_rate(1),
		block_align(1),
		bits_per_sample(1),
		fmt(FMT_CHUNK_fmt_instances),
		num_samples(1),
		fact(FACT_CHUNK_fact_instances),
		manufacturer(1),
		product(1),
		sample_period(1),
		midi_unity_note(3),
		midi_pitch_fraction(1),
		smpte_format(1),
		smpte_offset(1),
		num_loops(1),
		sampler_data_size(1),
		id(1),
		loop_type(4),
		start(1),
		end(1),
		fraction(1),
		play_count(1),
		loop(SMPL_LOOP_loop_instances),
		smpl(SMPL_CHUNK_smpl_instances),
		unshifted_note(5),
		fine_tune(1),
		gain(1),
		low_note(6),
		high_note(7),
		low_velocity(8),
		high_velocity(9),
		inst(INST_CHUNK_inst_instances),
		num_cue_points(1),
		position(1),
		data_chunk_id_element(false),
		data_chunk_id(data_chunk_id_element),
		chunk_start(1),
		block_start(1),
		sample_offset(1),
		cue_pt(CUE_POINT_cue_pt_instances),
		cue(CUE_CHUNK_cue_instances),
		description_element(false),
		description(description_element),
		originator_element(false),
		originator(originator_element),
		originator_ref_element(false),
		originator_ref(originator_ref_element),
		orig_date_element(false),
		orig_date(orig_date_element),
		orig_time_element(false),
		orig_time(orig_time_element),
		time_ref_low(1),
		time_ref_high(1),
		version(1),
		umid_element(false),
		umid(umid_element),
		loudness_value(1),
		loudness_range(1),
		max_true_peak(1),
		max_momentary(1),
		max_short_term(1),
		reserved_element(false),
		reserved(reserved_element),
		bext(BEXT_CHUNK_bext_instances),
		xml_data_element(false),
		xml_data(xml_data_element),
		ixml(IXML_CHUNK_ixml_instances),
		type_flags(1),
		root_note(10),
		unknown1(1),
		unknown2(1),
		num_beats(1),
		meter_denom(1),
		meter_numer(1),
		tempo(1),
		acid(ACID_CHUNK_acid_instances),
		data_element(false),
		data(data_element),
		junk(JUNK_CHUNK_junk_instances),
		info_list_id_element(false),
		info_list_id(info_list_id_element),
		info_list_size(1),
		info_list_type_element(false),
		info_list_type(info_list_type_element),
		data__element(false),
		data_(data__element),
		info1(INFO_CHUNK_info1_instances),
		info2(INFO_CHUNK_info2_instances),
		data_id_element(false),
		data_id(data_id_element),
		data_size(11),
		audio_data_element(false),
		audio_data(audio_data_element),
		file(wav_file_file_instances)
	{}
};

globals_class* g;


FMT_CHUNK* FMT_CHUNK::generate() {
	if (generated == 1) {
		FMT_CHUNK* new_instance = new FMT_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "fmt " }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 16 }));
	GENERATE_VAR(audio_format, ::g->audio_format.generate({ 1 }));
	GENERATE_VAR(num_channels, ::g->num_channels.generate({ 1, 2 }));
	GENERATE_VAR(sample_rate, ::g->sample_rate.generate({ 44100, 48000, 22050, 8000, 96000 }));
	GENERATE_VAR(byte_rate, ::g->byte_rate.generate());
	GENERATE_VAR(block_align, ::g->block_align.generate());
	GENERATE_VAR(bits_per_sample, ::g->bits_per_sample.generate({ 8, 16, 24, 32 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


FACT_CHUNK* FACT_CHUNK::generate() {
	if (generated == 1) {
		FACT_CHUNK* new_instance = new FACT_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "fact" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 4 }));
	GENERATE_VAR(num_samples, ::g->num_samples.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SMPL_LOOP* SMPL_LOOP::generate() {
	if (generated == 1) {
		SMPL_LOOP* new_instance = new SMPL_LOOP(instances);
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

	GENERATE_VAR(id, ::g->id.generate());
	GENERATE_VAR(loop_type, ::g->loop_type.generate());
	GENERATE_VAR(start, ::g->start.generate());
	GENERATE_VAR(end, ::g->end.generate());
	GENERATE_VAR(fraction, ::g->fraction.generate());
	GENERATE_VAR(play_count, ::g->play_count.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SMPL_CHUNK* SMPL_CHUNK::generate() {
	if (generated == 1) {
		SMPL_CHUNK* new_instance = new SMPL_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "smpl" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(manufacturer, ::g->manufacturer.generate());
	GENERATE_VAR(product, ::g->product.generate());
	GENERATE_VAR(sample_period, ::g->sample_period.generate());
	GENERATE_VAR(midi_unity_note, ::g->midi_unity_note.generate());
	GENERATE_VAR(midi_pitch_fraction, ::g->midi_pitch_fraction.generate());
	GENERATE_VAR(smpte_format, ::g->smpte_format.generate({ 0, 24, 25, 30 }));
	GENERATE_VAR(smpte_offset, ::g->smpte_offset.generate());
	GENERATE_VAR(num_loops, ::g->num_loops.generate({ 0, 1 }));
	GENERATE_VAR(sampler_data_size, ::g->sampler_data_size.generate({ 0 }));
	if ((num_loops() > 0)) {
		GENERATE_VAR(loop, ::g->loop.generate());
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


INST_CHUNK* INST_CHUNK::generate() {
	if (generated == 1) {
		INST_CHUNK* new_instance = new INST_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "inst" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 7 }));
	GENERATE_VAR(unshifted_note, ::g->unshifted_note.generate());
	GENERATE_VAR(fine_tune, ::g->fine_tune.generate());
	GENERATE_VAR(gain, ::g->gain.generate());
	GENERATE_VAR(low_note, ::g->low_note.generate());
	GENERATE_VAR(high_note, ::g->high_note.generate());
	GENERATE_VAR(low_velocity, ::g->low_velocity.generate());
	GENERATE_VAR(high_velocity, ::g->high_velocity.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CUE_POINT* CUE_POINT::generate() {
	if (generated == 1) {
		CUE_POINT* new_instance = new CUE_POINT(instances);
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

	GENERATE_VAR(id, ::g->id.generate());
	GENERATE_VAR(position, ::g->position.generate());
	GENERATE_VAR(data_chunk_id, ::g->data_chunk_id.generate(4, { "data" }));
	GENERATE_VAR(chunk_start, ::g->chunk_start.generate());
	GENERATE_VAR(block_start, ::g->block_start.generate());
	GENERATE_VAR(sample_offset, ::g->sample_offset.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CUE_CHUNK* CUE_CHUNK::generate() {
	if (generated == 1) {
		CUE_CHUNK* new_instance = new CUE_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "cue " }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(num_cue_points, ::g->num_cue_points.generate({ 1 }));
	GENERATE_VAR(cue_pt, ::g->cue_pt.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


BEXT_CHUNK* BEXT_CHUNK::generate() {
	if (generated == 1) {
		BEXT_CHUNK* new_instance = new BEXT_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "bext" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(description, ::g->description.generate(256));
	GENERATE_VAR(originator, ::g->originator.generate(32));
	GENERATE_VAR(originator_ref, ::g->originator_ref.generate(32));
	GENERATE_VAR(orig_date, ::g->orig_date.generate(10));
	GENERATE_VAR(orig_time, ::g->orig_time.generate(8));
	GENERATE_VAR(time_ref_low, ::g->time_ref_low.generate());
	GENERATE_VAR(time_ref_high, ::g->time_ref_high.generate());
	GENERATE_VAR(version, ::g->version.generate({ 0, 1, 2 }));
	GENERATE_VAR(umid, ::g->umid.generate(64));
	GENERATE_VAR(loudness_value, ::g->loudness_value.generate());
	GENERATE_VAR(loudness_range, ::g->loudness_range.generate());
	GENERATE_VAR(max_true_peak, ::g->max_true_peak.generate());
	GENERATE_VAR(max_momentary, ::g->max_momentary.generate());
	GENERATE_VAR(max_short_term, ::g->max_short_term.generate());
	GENERATE_VAR(reserved, ::g->reserved.generate(180));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IXML_CHUNK* IXML_CHUNK::generate() {
	if (generated == 1) {
		IXML_CHUNK* new_instance = new IXML_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "iXML" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(xml_data, ::g->xml_data.generate(chunk_size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ACID_CHUNK* ACID_CHUNK::generate() {
	if (generated == 1) {
		ACID_CHUNK* new_instance = new ACID_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "acid" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate({ 24 }));
	GENERATE_VAR(type_flags, ::g->type_flags.generate());
	GENERATE_VAR(root_note, ::g->root_note.generate());
	GENERATE_VAR(unknown1, ::g->unknown1.generate());
	GENERATE_VAR(unknown2, ::g->unknown2.generate());
	GENERATE_VAR(num_beats, ::g->num_beats.generate());
	GENERATE_VAR(meter_denom, ::g->meter_denom.generate({ 4 }));
	GENERATE_VAR(meter_numer, ::g->meter_numer.generate({ 4 }));
	GENERATE_VAR(tempo, ::g->tempo.generate());

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


INFO_CHUNK* INFO_CHUNK::generate() {
	if (generated == 1) {
		INFO_CHUNK* new_instance = new INFO_CHUNK(instances);
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

	GENERATE_VAR(chunk_id, ::g->chunk_id.generate(4, { "INAM", "IART", "ICMT", "ICOP", "ICRD", "IGNR", "ISFT" }));
	GENERATE_VAR(chunk_size, ::g->chunk_size.generate());
	GENERATE_VAR(data, ::g->data_.generate(chunk_size()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


wav_file* wav_file::generate() {
	if (generated == 1) {
		wav_file* new_instance = new wav_file(instances);
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
	GENERATE_VAR(wave_id, ::g->wave_id.generate(4, { "WAVE" }));
	GENERATE_VAR(fmt, ::g->fmt.generate());
	GENERATE_VAR(fact, ::g->fact.generate());
	tag.resize(4);
	all_choices = { "smpl", "inst", "cue ", "bext", "iXML", "acid", "JUNK", "LIST" };
	preferred = { "smpl", "LIST" };
	while (ReadBytes(tag, FTell(), 4, preferred, all_choices)) {
		switch (STR2INT(tag)) {
		case STR2INT("smpl"):
			GENERATE_VAR(smpl, ::g->smpl.generate());
			VectorRemove(all_choices, { "smpl" });
			VectorRemove(preferred, { "smpl" });
			break;
		case STR2INT("inst"):
			GENERATE_VAR(inst, ::g->inst.generate());
			VectorRemove(all_choices, { "inst" });
			break;
		case STR2INT("cue "):
			GENERATE_VAR(cue, ::g->cue.generate());
			VectorRemove(all_choices, { "cue " });
			break;
		case STR2INT("bext"):
			GENERATE_VAR(bext, ::g->bext.generate());
			VectorRemove(all_choices, { "bext" });
			break;
		case STR2INT("iXML"):
			GENERATE_VAR(ixml, ::g->ixml.generate());
			VectorRemove(all_choices, { "iXML" });
			break;
		case STR2INT("acid"):
			GENERATE_VAR(acid, ::g->acid.generate());
			VectorRemove(all_choices, { "acid" });
			break;
		case STR2INT("JUNK"):
			GENERATE_VAR(junk, ::g->junk.generate());
			VectorRemove(all_choices, { "JUNK" });
			break;
		case STR2INT("LIST"):
			GENERATE_VAR(info_list_id, ::g->info_list_id.generate(4, { "LIST" }));
			GENERATE_VAR(info_list_size, ::g->info_list_size.generate());
			GENERATE_VAR(info_list_type, ::g->info_list_type.generate(4, { "INFO" }));
			GENERATE_VAR(info1, ::g->info1.generate());
			GENERATE_VAR(info2, ::g->info2.generate());
			VectorRemove(all_choices, { "LIST" });
			VectorRemove(preferred, { "LIST" });
			break;
		default:
			break;
		};
	};
	GENERATE_VAR(data_id, ::g->data_id.generate(4, { "data" }));
	GENERATE_VAR(data_size, ::g->data_size.generate());
	GENERATE_VAR(audio_data, ::g->audio_data.generate(data_size()));

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

