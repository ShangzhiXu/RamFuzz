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



class FLV_TAG_SCRIPT {
	std::vector<FLV_TAG_SCRIPT*>& instances;

	ubyte tag_type_var;
	ubyte ds_hi_var;
	ubyte ds_mid_var;
	ubyte ds_lo_var;
	ubyte ts_hi_var;
	ubyte ts_mid_var;
	ubyte ts_lo_var;
	ubyte ts_ext_var;
	ubyte sid_hi_var;
	ubyte sid_mid_var;
	ubyte sid_lo_var;
	std::vector<ubyte> script_data_var;

public:
	bool tag_type_exists = false;
	bool ds_hi_exists = false;
	bool ds_mid_exists = false;
	bool ds_lo_exists = false;
	bool ts_hi_exists = false;
	bool ts_mid_exists = false;
	bool ts_lo_exists = false;
	bool ts_ext_exists = false;
	bool sid_hi_exists = false;
	bool sid_mid_exists = false;
	bool sid_lo_exists = false;
	bool script_data_exists = false;

	ubyte& tag_type() {
		assert_cond(tag_type_exists, "struct field tag_type does not exist");
		return tag_type_var;
	}
	ubyte& ds_hi() {
		assert_cond(ds_hi_exists, "struct field ds_hi does not exist");
		return ds_hi_var;
	}
	ubyte& ds_mid() {
		assert_cond(ds_mid_exists, "struct field ds_mid does not exist");
		return ds_mid_var;
	}
	ubyte& ds_lo() {
		assert_cond(ds_lo_exists, "struct field ds_lo does not exist");
		return ds_lo_var;
	}
	ubyte& ts_hi() {
		assert_cond(ts_hi_exists, "struct field ts_hi does not exist");
		return ts_hi_var;
	}
	ubyte& ts_mid() {
		assert_cond(ts_mid_exists, "struct field ts_mid does not exist");
		return ts_mid_var;
	}
	ubyte& ts_lo() {
		assert_cond(ts_lo_exists, "struct field ts_lo does not exist");
		return ts_lo_var;
	}
	ubyte& ts_ext() {
		assert_cond(ts_ext_exists, "struct field ts_ext does not exist");
		return ts_ext_var;
	}
	ubyte& sid_hi() {
		assert_cond(sid_hi_exists, "struct field sid_hi does not exist");
		return sid_hi_var;
	}
	ubyte& sid_mid() {
		assert_cond(sid_mid_exists, "struct field sid_mid does not exist");
		return sid_mid_var;
	}
	ubyte& sid_lo() {
		assert_cond(sid_lo_exists, "struct field sid_lo does not exist");
		return sid_lo_var;
	}
	std::vector<ubyte>& script_data() {
		assert_cond(script_data_exists, "struct field script_data does not exist");
		return script_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	FLV_TAG_SCRIPT& operator () () { return *instances.back(); }
	FLV_TAG_SCRIPT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	FLV_TAG_SCRIPT(std::vector<FLV_TAG_SCRIPT*>& instances) : instances(instances) { instances.push_back(this); }
	~FLV_TAG_SCRIPT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			FLV_TAG_SCRIPT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	FLV_TAG_SCRIPT* generate();
};

int FLV_TAG_SCRIPT::_parent_id = 0;
int FLV_TAG_SCRIPT::_index_start = 0;



class FLV_TAG_VIDEO {
	std::vector<FLV_TAG_VIDEO*>& instances;

	ubyte tag_type_var;
	ubyte ds_hi_var;
	ubyte ds_mid_var;
	ubyte ds_lo_var;
	ubyte ts_hi_var;
	ubyte ts_mid_var;
	ubyte ts_lo_var;
	ubyte ts_ext_var;
	ubyte sid_hi_var;
	ubyte sid_mid_var;
	ubyte sid_lo_var;
	ubyte video_header_var;
	std::vector<ubyte> video_data_var;

public:
	bool tag_type_exists = false;
	bool ds_hi_exists = false;
	bool ds_mid_exists = false;
	bool ds_lo_exists = false;
	bool ts_hi_exists = false;
	bool ts_mid_exists = false;
	bool ts_lo_exists = false;
	bool ts_ext_exists = false;
	bool sid_hi_exists = false;
	bool sid_mid_exists = false;
	bool sid_lo_exists = false;
	bool video_header_exists = false;
	bool video_data_exists = false;

	ubyte& tag_type() {
		assert_cond(tag_type_exists, "struct field tag_type does not exist");
		return tag_type_var;
	}
	ubyte& ds_hi() {
		assert_cond(ds_hi_exists, "struct field ds_hi does not exist");
		return ds_hi_var;
	}
	ubyte& ds_mid() {
		assert_cond(ds_mid_exists, "struct field ds_mid does not exist");
		return ds_mid_var;
	}
	ubyte& ds_lo() {
		assert_cond(ds_lo_exists, "struct field ds_lo does not exist");
		return ds_lo_var;
	}
	ubyte& ts_hi() {
		assert_cond(ts_hi_exists, "struct field ts_hi does not exist");
		return ts_hi_var;
	}
	ubyte& ts_mid() {
		assert_cond(ts_mid_exists, "struct field ts_mid does not exist");
		return ts_mid_var;
	}
	ubyte& ts_lo() {
		assert_cond(ts_lo_exists, "struct field ts_lo does not exist");
		return ts_lo_var;
	}
	ubyte& ts_ext() {
		assert_cond(ts_ext_exists, "struct field ts_ext does not exist");
		return ts_ext_var;
	}
	ubyte& sid_hi() {
		assert_cond(sid_hi_exists, "struct field sid_hi does not exist");
		return sid_hi_var;
	}
	ubyte& sid_mid() {
		assert_cond(sid_mid_exists, "struct field sid_mid does not exist");
		return sid_mid_var;
	}
	ubyte& sid_lo() {
		assert_cond(sid_lo_exists, "struct field sid_lo does not exist");
		return sid_lo_var;
	}
	ubyte& video_header() {
		assert_cond(video_header_exists, "struct field video_header does not exist");
		return video_header_var;
	}
	std::vector<ubyte>& video_data() {
		assert_cond(video_data_exists, "struct field video_data does not exist");
		return video_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	FLV_TAG_VIDEO& operator () () { return *instances.back(); }
	FLV_TAG_VIDEO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	FLV_TAG_VIDEO(std::vector<FLV_TAG_VIDEO*>& instances) : instances(instances) { instances.push_back(this); }
	~FLV_TAG_VIDEO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			FLV_TAG_VIDEO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	FLV_TAG_VIDEO* generate();
};

int FLV_TAG_VIDEO::_parent_id = 0;
int FLV_TAG_VIDEO::_index_start = 0;



class FLV_TAG_AUDIO {
	std::vector<FLV_TAG_AUDIO*>& instances;

	ubyte tag_type_var;
	ubyte ds_hi_var;
	ubyte ds_mid_var;
	ubyte ds_lo_var;
	ubyte ts_hi_var;
	ubyte ts_mid_var;
	ubyte ts_lo_var;
	ubyte ts_ext_var;
	ubyte sid_hi_var;
	ubyte sid_mid_var;
	ubyte sid_lo_var;
	ubyte audio_header_var;
	std::vector<ubyte> audio_data_var;

public:
	bool tag_type_exists = false;
	bool ds_hi_exists = false;
	bool ds_mid_exists = false;
	bool ds_lo_exists = false;
	bool ts_hi_exists = false;
	bool ts_mid_exists = false;
	bool ts_lo_exists = false;
	bool ts_ext_exists = false;
	bool sid_hi_exists = false;
	bool sid_mid_exists = false;
	bool sid_lo_exists = false;
	bool audio_header_exists = false;
	bool audio_data_exists = false;

	ubyte& tag_type() {
		assert_cond(tag_type_exists, "struct field tag_type does not exist");
		return tag_type_var;
	}
	ubyte& ds_hi() {
		assert_cond(ds_hi_exists, "struct field ds_hi does not exist");
		return ds_hi_var;
	}
	ubyte& ds_mid() {
		assert_cond(ds_mid_exists, "struct field ds_mid does not exist");
		return ds_mid_var;
	}
	ubyte& ds_lo() {
		assert_cond(ds_lo_exists, "struct field ds_lo does not exist");
		return ds_lo_var;
	}
	ubyte& ts_hi() {
		assert_cond(ts_hi_exists, "struct field ts_hi does not exist");
		return ts_hi_var;
	}
	ubyte& ts_mid() {
		assert_cond(ts_mid_exists, "struct field ts_mid does not exist");
		return ts_mid_var;
	}
	ubyte& ts_lo() {
		assert_cond(ts_lo_exists, "struct field ts_lo does not exist");
		return ts_lo_var;
	}
	ubyte& ts_ext() {
		assert_cond(ts_ext_exists, "struct field ts_ext does not exist");
		return ts_ext_var;
	}
	ubyte& sid_hi() {
		assert_cond(sid_hi_exists, "struct field sid_hi does not exist");
		return sid_hi_var;
	}
	ubyte& sid_mid() {
		assert_cond(sid_mid_exists, "struct field sid_mid does not exist");
		return sid_mid_var;
	}
	ubyte& sid_lo() {
		assert_cond(sid_lo_exists, "struct field sid_lo does not exist");
		return sid_lo_var;
	}
	ubyte& audio_header() {
		assert_cond(audio_header_exists, "struct field audio_header does not exist");
		return audio_header_var;
	}
	std::vector<ubyte>& audio_data() {
		assert_cond(audio_data_exists, "struct field audio_data does not exist");
		return audio_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	FLV_TAG_AUDIO& operator () () { return *instances.back(); }
	FLV_TAG_AUDIO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	FLV_TAG_AUDIO(std::vector<FLV_TAG_AUDIO*>& instances) : instances(instances) { instances.push_back(this); }
	~FLV_TAG_AUDIO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			FLV_TAG_AUDIO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	FLV_TAG_AUDIO* generate();
};

int FLV_TAG_AUDIO::_parent_id = 0;
int FLV_TAG_AUDIO::_index_start = 0;



class flv_file {
	std::vector<flv_file*>& instances;

	ubyte sig1_var;
	ubyte sig2_var;
	ubyte sig3_var;
	ubyte version_var;
	ubyte flags_var;
	uint32 header_size_var;
	uint32 prev_tag_size0_var;
	FLV_TAG_SCRIPT* script_tag_var;
	uint32 pts1_var;
	FLV_TAG_VIDEO* video_tag_var;
	uint32 pts2_var;
	FLV_TAG_AUDIO* audio_tag_var;
	uint32 pts3_var;

public:
	bool sig1_exists = false;
	bool sig2_exists = false;
	bool sig3_exists = false;
	bool version_exists = false;
	bool flags_exists = false;
	bool header_size_exists = false;
	bool prev_tag_size0_exists = false;
	bool script_tag_exists = false;
	bool pts1_exists = false;
	bool video_tag_exists = false;
	bool pts2_exists = false;
	bool audio_tag_exists = false;
	bool pts3_exists = false;

	ubyte& sig1() {
		assert_cond(sig1_exists, "struct field sig1 does not exist");
		return sig1_var;
	}
	ubyte& sig2() {
		assert_cond(sig2_exists, "struct field sig2 does not exist");
		return sig2_var;
	}
	ubyte& sig3() {
		assert_cond(sig3_exists, "struct field sig3 does not exist");
		return sig3_var;
	}
	ubyte& version() {
		assert_cond(version_exists, "struct field version does not exist");
		return version_var;
	}
	ubyte& flags() {
		assert_cond(flags_exists, "struct field flags does not exist");
		return flags_var;
	}
	uint32& header_size() {
		assert_cond(header_size_exists, "struct field header_size does not exist");
		return header_size_var;
	}
	uint32& prev_tag_size0() {
		assert_cond(prev_tag_size0_exists, "struct field prev_tag_size0 does not exist");
		return prev_tag_size0_var;
	}
	FLV_TAG_SCRIPT& script_tag() {
		assert_cond(script_tag_exists, "struct field script_tag does not exist");
		return *script_tag_var;
	}
	uint32& pts1() {
		assert_cond(pts1_exists, "struct field pts1 does not exist");
		return pts1_var;
	}
	FLV_TAG_VIDEO& video_tag() {
		assert_cond(video_tag_exists, "struct field video_tag does not exist");
		return *video_tag_var;
	}
	uint32& pts2() {
		assert_cond(pts2_exists, "struct field pts2 does not exist");
		return pts2_var;
	}
	FLV_TAG_AUDIO& audio_tag() {
		assert_cond(audio_tag_exists, "struct field audio_tag does not exist");
		return *audio_tag_var;
	}
	uint32& pts3() {
		assert_cond(pts3_exists, "struct field pts3 does not exist");
		return pts3_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	flv_file& operator () () { return *instances.back(); }
	flv_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	flv_file(std::vector<flv_file*>& instances) : instances(instances) { instances.push_back(this); }
	~flv_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			flv_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	flv_file* generate();
};

int flv_file::_parent_id = 0;
int flv_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "FLV" };


std::vector<FLV_TAG_SCRIPT*> FLV_TAG_SCRIPT_script_tag_instances;
std::vector<FLV_TAG_VIDEO*> FLV_TAG_VIDEO_video_tag_instances;
std::vector<FLV_TAG_AUDIO*> FLV_TAG_AUDIO_audio_tag_instances;
std::vector<flv_file*> flv_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "sig1", "ubyte_class" }, { "sig2", "ubyte_class" }, { "sig3", "ubyte_class" }, { "version", "ubyte_class" }, { "flags", "ubyte_class" }, { "header_size", "uint32_class" }, { "prev_tag_size0", "uint32_class" }, { "tag_type", "ubyte_class" }, { "ds_hi", "ubyte_class" }, { "ds_mid", "ubyte_class" }, { "ds_lo", "ubyte_class" }, { "ts_hi", "ubyte_class" }, { "ts_mid", "ubyte_class" }, { "ts_lo", "ubyte_class" }, { "ts_ext", "ubyte_class" }, { "sid_hi", "ubyte_class" }, { "sid_mid", "ubyte_class" }, { "sid_lo", "ubyte_class" }, { "script_data", "ubyte_array_class" }, { "script_tag", "FLV_TAG_SCRIPT" }, { "pts1", "uint32_class" }, { "video_header", "ubyte_class" }, { "video_data", "ubyte_array_class" }, { "video_tag", "FLV_TAG_VIDEO" }, { "pts2", "uint32_class" }, { "audio_header", "ubyte_class" }, { "audio_data", "ubyte_array_class" }, { "audio_tag", "FLV_TAG_AUDIO" }, { "pts3", "uint32_class" }, { "file", "flv_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	ubyte_class sig1;
	ubyte_class sig2;
	ubyte_class sig3;
	ubyte_class version;
	ubyte_class flags;
	uint32_class header_size;
	uint32_class prev_tag_size0;
	ubyte_class tag_type;
	ubyte_class ds_hi;
	ubyte_class ds_mid;
	ubyte_class ds_lo;
	ubyte_class ts_hi;
	ubyte_class ts_mid;
	ubyte_class ts_lo;
	ubyte_class ts_ext;
	ubyte_class sid_hi;
	ubyte_class sid_mid;
	ubyte_class sid_lo;
	ubyte_class script_data_element;
	ubyte_array_class script_data;
	FLV_TAG_SCRIPT script_tag;
	uint32_class pts1;
	ubyte_class video_header;
	ubyte_class video_data_element;
	ubyte_array_class video_data;
	FLV_TAG_VIDEO video_tag;
	uint32_class pts2;
	ubyte_class audio_header;
	ubyte_class audio_data_element;
	ubyte_array_class audio_data;
	FLV_TAG_AUDIO audio_tag;
	uint32_class pts3;
	flv_file file;


	globals_class() :
		sig1(1),
		sig2(1),
		sig3(1),
		version(1),
		flags(1),
		header_size(1),
		prev_tag_size0(1),
		tag_type(1),
		ds_hi(1),
		ds_mid(1),
		ds_lo(1),
		ts_hi(1),
		ts_mid(1),
		ts_lo(1),
		ts_ext(1),
		sid_hi(1),
		sid_mid(1),
		sid_lo(1),
		script_data_element(false),
		script_data(script_data_element),
		script_tag(FLV_TAG_SCRIPT_script_tag_instances),
		pts1(1),
		video_header(1),
		video_data_element(false),
		video_data(video_data_element),
		video_tag(FLV_TAG_VIDEO_video_tag_instances),
		pts2(1),
		audio_header(1),
		audio_data_element(false),
		audio_data(audio_data_element),
		audio_tag(FLV_TAG_AUDIO_audio_tag_instances),
		pts3(1),
		file(flv_file_file_instances)
	{}
};

globals_class* g;


FLV_TAG_SCRIPT* FLV_TAG_SCRIPT::generate() {
	if (generated == 1) {
		FLV_TAG_SCRIPT* new_instance = new FLV_TAG_SCRIPT(instances);
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

	GENERATE_VAR(tag_type, ::g->tag_type.generate({ 18 }));
	GENERATE_VAR(ds_hi, ::g->ds_hi.generate({ 0 }));
	GENERATE_VAR(ds_mid, ::g->ds_mid.generate({ 0 }));
	GENERATE_VAR(ds_lo, ::g->ds_lo.generate({ 16, 32, 48, 64 }));
	GENERATE_VAR(ts_hi, ::g->ts_hi.generate({ 0 }));
	GENERATE_VAR(ts_mid, ::g->ts_mid.generate({ 0 }));
	GENERATE_VAR(ts_lo, ::g->ts_lo.generate({ 0 }));
	GENERATE_VAR(ts_ext, ::g->ts_ext.generate({ 0 }));
	GENERATE_VAR(sid_hi, ::g->sid_hi.generate({ 0 }));
	GENERATE_VAR(sid_mid, ::g->sid_mid.generate({ 0 }));
	GENERATE_VAR(sid_lo, ::g->sid_lo.generate({ 0 }));
	GENERATE_VAR(script_data, ::g->script_data.generate(ds_lo()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


FLV_TAG_VIDEO* FLV_TAG_VIDEO::generate() {
	if (generated == 1) {
		FLV_TAG_VIDEO* new_instance = new FLV_TAG_VIDEO(instances);
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

	GENERATE_VAR(tag_type, ::g->tag_type.generate({ 9 }));
	GENERATE_VAR(ds_hi, ::g->ds_hi.generate({ 0 }));
	GENERATE_VAR(ds_mid, ::g->ds_mid.generate({ 0 }));
	GENERATE_VAR(ds_lo, ::g->ds_lo.generate({ 16, 32, 48, 64 }));
	GENERATE_VAR(ts_hi, ::g->ts_hi.generate({ 0 }));
	GENERATE_VAR(ts_mid, ::g->ts_mid.generate({ 0 }));
	GENERATE_VAR(ts_lo, ::g->ts_lo.generate());
	GENERATE_VAR(ts_ext, ::g->ts_ext.generate({ 0 }));
	GENERATE_VAR(sid_hi, ::g->sid_hi.generate({ 0 }));
	GENERATE_VAR(sid_mid, ::g->sid_mid.generate({ 0 }));
	GENERATE_VAR(sid_lo, ::g->sid_lo.generate({ 0 }));
	GENERATE_VAR(video_header, ::g->video_header.generate());
	GENERATE_VAR(video_data, ::g->video_data.generate((ds_lo() - 1)));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


FLV_TAG_AUDIO* FLV_TAG_AUDIO::generate() {
	if (generated == 1) {
		FLV_TAG_AUDIO* new_instance = new FLV_TAG_AUDIO(instances);
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

	GENERATE_VAR(tag_type, ::g->tag_type.generate({ 8 }));
	GENERATE_VAR(ds_hi, ::g->ds_hi.generate({ 0 }));
	GENERATE_VAR(ds_mid, ::g->ds_mid.generate({ 0 }));
	GENERATE_VAR(ds_lo, ::g->ds_lo.generate({ 16, 32, 48, 64 }));
	GENERATE_VAR(ts_hi, ::g->ts_hi.generate({ 0 }));
	GENERATE_VAR(ts_mid, ::g->ts_mid.generate({ 0 }));
	GENERATE_VAR(ts_lo, ::g->ts_lo.generate());
	GENERATE_VAR(ts_ext, ::g->ts_ext.generate({ 0 }));
	GENERATE_VAR(sid_hi, ::g->sid_hi.generate({ 0 }));
	GENERATE_VAR(sid_mid, ::g->sid_mid.generate({ 0 }));
	GENERATE_VAR(sid_lo, ::g->sid_lo.generate({ 0 }));
	GENERATE_VAR(audio_header, ::g->audio_header.generate());
	GENERATE_VAR(audio_data, ::g->audio_data.generate((ds_lo() - 1)));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


flv_file* flv_file::generate() {
	if (generated == 1) {
		flv_file* new_instance = new flv_file(instances);
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

	GENERATE_VAR(sig1, ::g->sig1.generate({ 0x46 }));
	GENERATE_VAR(sig2, ::g->sig2.generate({ 0x4C }));
	GENERATE_VAR(sig3, ::g->sig3.generate({ 0x56 }));
	GENERATE_VAR(version, ::g->version.generate({ 1 }));
	GENERATE_VAR(flags, ::g->flags.generate({ 5 }));
	GENERATE_VAR(header_size, ::g->header_size.generate({ 9 }));
	GENERATE_VAR(prev_tag_size0, ::g->prev_tag_size0.generate({ 0 }));
	GENERATE_VAR(script_tag, ::g->script_tag.generate());
	GENERATE_VAR(pts1, ::g->pts1.generate());
	GENERATE_VAR(video_tag, ::g->video_tag.generate());
	GENERATE_VAR(pts2, ::g->pts2.generate());
	GENERATE_VAR(audio_tag, ::g->audio_tag.generate());
	GENERATE_VAR(pts3, ::g->pts3.generate());

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

