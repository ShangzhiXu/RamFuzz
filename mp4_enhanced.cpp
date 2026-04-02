#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"

enum qtlang {
	qtlEnglish = 0,
	qtlFrench = 1,
	qtlGerman = 2,
	qtlItalian = 3,
	qtlDutch = 4,
	qtlSwedish = 5,
	qtlSpanish = 6,
	qtlDanish = 7,
	qtlPortuguese = 8,
	qtlNorwegian = 9,
	qtlHebrew = 10,
	qtlJapanese = 11,
	qtlArabic = 12,
	qtlFinnish = 13,
	qtlGreek = 14,
	qtlIcelandic = 15,
	qtlMaltese = 16,
	qtlTurkish = 17,
	qtlCroatian = 18,
	qtlChineseTraditional = 19,
	qtlUrdu = 20,
	qtlHindi = 21,
	qtlThai = 22,
	qtlKorean = 23,
	qtlLithuanian = 24,
	qtlPolish = 25,
	qtlHungarian = 26,
	qtlEstonian = 27,
	qtlLettish = 28,
	qtlLatvian = 28,
	qtlSaami = 29,
	qtlSami = 29,
	qtlFaroese = 30,
	qtlFarsi = 31,
	qtlRussian = 32,
	qtlChineseSimplified = 33,
	qtlFlemish = 34,
	qtlIrish = 35,
	qtlAlbanian = 36,
	qtlRomanian = 37,
	qtlCzech = 38,
	qtlSlovak = 39,
	qtlSlovenian = 40,
	qtlYiddish = 41,
	qtlSerbian = 42,
	qtlMacedonian = 43,
	qtlBulgarian = 44,
	qtlUkrainian = 45,
	qtlBelarusian = 46,
	qtlUzbek = 47,
	qtlKazakh = 48,
	qtlAzerbaijani = 49,
	qtlAzerbaijanAr = 50,
	qtlArmenian = 51,
	qtlGeorgian = 52,
	qtlMoldavian = 53,
	qtlKirghiz = 54,
	qtlTajiki = 55,
	qtlTurkmen = 56,
	qtlMongolian = 57,
	qtlMongolianCyr = 58,
	qtlPashto = 59,
	qtlKurdish = 60,
	qtlKashmiri = 61,
	qtlSindhi = 62,
	qtlTibetan = 63,
	qtlNepali = 64,
	qtlSanskrit = 65,
	qtlMarathi = 66,
	qtlBengali = 67,
	qtlAssamese = 68,
	qtlGujarati = 69,
	qtlPunjabi = 70,
	qtlOriya = 71,
	qtlMalayalam = 72,
	qtlKannada = 73,
	qtlTamil = 74,
	qtlTelugu = 75,
	qtlSinhala = 76,
	qtlBurmese = 77,
	qtlKhmer = 78,
	qtlLao = 79,
	qtlVietnamese = 80,
	qtlIndonesian = 81,
	qtlTagalog = 82,
	qtlMalayRoman = 83,
	qtlMalayArabic = 84,
	qtlAmharic = 85,
	qtlGalla = 87,
	qtlOromo = 87,
	qtlSomali = 88,
	qtlSwahili = 89,
	qtlKinyarwanda = 90,
	qtlRundi = 91,
	qtlNyanja = 92,
	qtlMalagasy = 93,
	qtlEsperanto = 94,
	qtlWelsh = 128,
	qtlBasque = 129,
	qtlCatalan = 130,
	qtlLatin = 131,
	qtlQuechua = 132,
	qtlGuarani = 133,
	qtlAymara = 134,
	qtlTatar = 135,
	qtlUighur = 136,
	qtlDzongkha = 137,
	qtlJavaneseRom = 138,
	qtlUnspecified = 32767,
};

enum qtgfxmode : uint16 {
	qtgCopy = (uint16) 0x000,
	qtgDitherCopy = (uint16) 0x040,
	qtgBlend = (uint16) 0x020,
	qtgTransparent = (uint16) 0x024,
	qtgStraightAlpha = (uint16) 0x100,
	qtgPremulWhiteAlpha = (uint16) 0x101,
	qtgPremulBlackAlpha = (uint16) 0x102,
	qtgStraightAlphaBlend = (uint16) 0x104,
	qtgComposition = (uint16) 0x103,
};
std::vector<uint16> qtgfxmode_values = { qtgCopy, qtgDitherCopy, qtgBlend, qtgTransparent, qtgStraightAlpha, qtgPremulWhiteAlpha, qtgPremulBlackAlpha, qtgStraightAlphaBlend, qtgComposition };


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



class fourcc {
	std::vector<fourcc*>& instances;

	std::string value_var;

public:
	bool value_exists = false;

	std::string& value() {
		assert_cond(value_exists, "struct field value does not exist");
		return value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	fourcc& operator () () { return *instances.back(); }
	fourcc& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	fourcc(std::vector<fourcc*>& instances) : instances(instances) { instances.push_back(this); }
	~fourcc() {
		if (generated == 2)
			return;
		while (instances.size()) {
			fourcc* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	fourcc* generate();
};

int fourcc::_parent_id = 0;
int fourcc::_index_start = 0;


class mp4box;



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



class byte_array_class {
	byte_class& element;
	std::unordered_map<int, std::vector<byte>> element_known_values;
	std::vector<byte> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<byte>& operator () () { return value; }
	byte operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	byte_array_class(byte_class& element, std::unordered_map<int, std::vector<byte>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<byte> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(byte), 0, known->second));
				_sizeof += sizeof(byte);
			}
		}
		return value;
	}
};



class uint64_class {
	int small;
	std::vector<uint64> known_values;
	uint64 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(uint64);
	uint64 operator () () { return value; }
	uint64_class(int small, std::vector<uint64> known_values = {}) : small(small), known_values(known_values) {}

	uint64 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(uint64), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(uint64), 0, known_values);
		}
		return value;
	}

	uint64 generate(std::vector<uint64> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(uint64), 0, possible_values);
		return value;
	}
};



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



class fp32 {
	std::vector<fp32*>& instances;

	int32 value_var;

public:
	bool value_exists = false;

	int32& value() {
		assert_cond(value_exists, "struct field value does not exist");
		return value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	fp32& operator () () { return *instances.back(); }
	fp32& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	fp32(std::vector<fp32*>& instances) : instances(instances) { instances.push_back(this); }
	~fp32() {
		if (generated == 2)
			return;
		while (instances.size()) {
			fp32* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	fp32* generate();
};

int fp32::_parent_id = 0;
int fp32::_index_start = 0;



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



class fp16 {
	std::vector<fp16*>& instances;

	int16 value_var;

public:
	bool value_exists = false;

	int16& value() {
		assert_cond(value_exists, "struct field value does not exist");
		return value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	fp16& operator () () { return *instances.back(); }
	fp16& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	fp16(std::vector<fp16*>& instances) : instances(instances) { instances.push_back(this); }
	~fp16() {
		if (generated == 2)
			return;
		while (instances.size()) {
			fp16* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	fp16* generate();
};

int fp16::_parent_id = 0;
int fp16::_index_start = 0;



class fp32uvw {
	std::vector<fp32uvw*>& instances;

	int32 value_var;

public:
	bool value_exists = false;

	int32& value() {
		assert_cond(value_exists, "struct field value does not exist");
		return value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	fp32uvw& operator () () { return *instances.back(); }
	fp32uvw& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	fp32uvw(std::vector<fp32uvw*>& instances) : instances(instances) { instances.push_back(this); }
	~fp32uvw() {
		if (generated == 2)
			return;
		while (instances.size()) {
			fp32uvw* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	fp32uvw* generate();
};

int fp32uvw::_parent_id = 0;
int fp32uvw::_index_start = 0;



class matrix {
	std::vector<matrix*>& instances;

	fp32* a_var;
	fp32* b_var;
	fp32uvw* u_var;
	fp32* c_var;
	fp32* d_var;
	fp32uvw* v_var;
	fp32* x_var;
	fp32* y_var;
	fp32uvw* w_var;

public:
	bool a_exists = false;
	bool b_exists = false;
	bool u_exists = false;
	bool c_exists = false;
	bool d_exists = false;
	bool v_exists = false;
	bool x_exists = false;
	bool y_exists = false;
	bool w_exists = false;

	fp32& a() {
		assert_cond(a_exists, "struct field a does not exist");
		return *a_var;
	}
	fp32& b() {
		assert_cond(b_exists, "struct field b does not exist");
		return *b_var;
	}
	fp32uvw& u() {
		assert_cond(u_exists, "struct field u does not exist");
		return *u_var;
	}
	fp32& c() {
		assert_cond(c_exists, "struct field c does not exist");
		return *c_var;
	}
	fp32& d() {
		assert_cond(d_exists, "struct field d does not exist");
		return *d_var;
	}
	fp32uvw& v() {
		assert_cond(v_exists, "struct field v does not exist");
		return *v_var;
	}
	fp32& x() {
		assert_cond(x_exists, "struct field x does not exist");
		return *x_var;
	}
	fp32& y() {
		assert_cond(y_exists, "struct field y does not exist");
		return *y_var;
	}
	fp32uvw& w() {
		assert_cond(w_exists, "struct field w does not exist");
		return *w_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	matrix& operator () () { return *instances.back(); }
	matrix& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	matrix(std::vector<matrix*>& instances) : instances(instances) { instances.push_back(this); }
	~matrix() {
		if (generated == 2)
			return;
		while (instances.size()) {
			matrix* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	matrix* generate();
};

int matrix::_parent_id = 0;
int matrix::_index_start = 0;



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



class byte_bitfield {
	int small;
	std::vector<byte> known_values;
	byte value;
public:
	byte operator () () { return value; }
	byte_bitfield(int small, std::vector<byte> known_values = {}) : small(small), known_values(known_values) {}

	byte generate(unsigned bits) {
		if (!bits)
			return 0;
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(byte), bits, small);
		} else {
			value = file_acc.file_integer(sizeof(byte), bits, known_values);
		}
		return value;
	}

	byte generate(unsigned bits, std::vector<byte> possible_values) {
		if (!bits)
			return 0;
		value = file_acc.file_integer(sizeof(byte), bits, possible_values);
		return value;
	}
};



class tkhd_flags {
	std::vector<tkhd_flags*>& instances;

	std::vector<byte> dummy_var;
	byte dummy2_var : 4;
	byte track_in_poster_var : 1;
	byte track_in_preview_var : 1;
	byte track_in_movie_var : 1;
	byte track_enabled_var : 1;

public:
	bool dummy_exists = false;
	bool dummy2_exists = false;
	bool track_in_poster_exists = false;
	bool track_in_preview_exists = false;
	bool track_in_movie_exists = false;
	bool track_enabled_exists = false;

	std::vector<byte>& dummy() {
		assert_cond(dummy_exists, "struct field dummy does not exist");
		return dummy_var;
	}
	byte dummy2() {
		assert_cond(dummy2_exists, "struct field dummy2 does not exist");
		return dummy2_var;
	}
	byte track_in_poster() {
		assert_cond(track_in_poster_exists, "struct field track_in_poster does not exist");
		return track_in_poster_var;
	}
	byte track_in_preview() {
		assert_cond(track_in_preview_exists, "struct field track_in_preview does not exist");
		return track_in_preview_var;
	}
	byte track_in_movie() {
		assert_cond(track_in_movie_exists, "struct field track_in_movie does not exist");
		return track_in_movie_var;
	}
	byte track_enabled() {
		assert_cond(track_enabled_exists, "struct field track_enabled does not exist");
		return track_enabled_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	tkhd_flags& operator () () { return *instances.back(); }
	tkhd_flags& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	tkhd_flags(std::vector<tkhd_flags*>& instances) : instances(instances) { instances.push_back(this); }
	~tkhd_flags() {
		if (generated == 2)
			return;
		while (instances.size()) {
			tkhd_flags* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	tkhd_flags* generate();
};

int tkhd_flags::_parent_id = 0;
int tkhd_flags::_index_start = 0;



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



class mp4lang {
	std::vector<mp4lang*>& instances;

	uint16 value_var;

public:
	bool value_exists = false;

	uint16& value() {
		assert_cond(value_exists, "struct field value does not exist");
		return value_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp4lang& operator () () { return *instances.back(); }
	mp4lang& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp4lang(std::vector<mp4lang*>& instances) : instances(instances) { instances.push_back(this); }
	~mp4lang() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp4lang* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp4lang* generate();
};

int mp4lang::_parent_id = 0;
int mp4lang::_index_start = 0;



class elst_entry {
	std::vector<elst_entry*>& instances;

	uint32 duration_var;
	uint32 media_time_var;
	fp32* media_rate_var;

public:
	bool duration_exists = false;
	bool media_time_exists = false;
	bool media_rate_exists = false;

	uint32& duration() {
		assert_cond(duration_exists, "struct field duration does not exist");
		return duration_var;
	}
	uint32& media_time() {
		assert_cond(media_time_exists, "struct field media_time does not exist");
		return media_time_var;
	}
	fp32& media_rate() {
		assert_cond(media_rate_exists, "struct field media_rate does not exist");
		return *media_rate_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	elst_entry& operator () () { return *instances.back(); }
	elst_entry& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	elst_entry(std::vector<elst_entry*>& instances) : instances(instances) { instances.push_back(this); }
	~elst_entry() {
		if (generated == 2)
			return;
		while (instances.size()) {
			elst_entry* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	elst_entry* generate();
};

int elst_entry::_parent_id = 0;
int elst_entry::_index_start = 0;



class int64_class {
	int small;
	std::vector<int64> known_values;
	int64 value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(int64);
	int64 operator () () { return value; }
	int64_class(int small, std::vector<int64> known_values = {}) : small(small), known_values(known_values) {}

	int64 generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(int64), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(int64), 0, known_values);
		}
		return value;
	}

	int64 generate(std::vector<int64> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(int64), 0, possible_values);
		return value;
	}
};



class elst_entry_v1 {
	std::vector<elst_entry_v1*>& instances;

	uint64 segment_duration_var;
	int64 media_time_var;
	int16 media_rate_integer_var;
	int16 media_rate_fraction_var;

public:
	bool segment_duration_exists = false;
	bool media_time_exists = false;
	bool media_rate_integer_exists = false;
	bool media_rate_fraction_exists = false;

	uint64& segment_duration() {
		assert_cond(segment_duration_exists, "struct field segment_duration does not exist");
		return segment_duration_var;
	}
	int64& media_time() {
		assert_cond(media_time_exists, "struct field media_time does not exist");
		return media_time_var;
	}
	int16& media_rate_integer() {
		assert_cond(media_rate_integer_exists, "struct field media_rate_integer does not exist");
		return media_rate_integer_var;
	}
	int16& media_rate_fraction() {
		assert_cond(media_rate_fraction_exists, "struct field media_rate_fraction does not exist");
		return media_rate_fraction_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	elst_entry_v1& operator () () { return *instances.back(); }
	elst_entry_v1& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	elst_entry_v1(std::vector<elst_entry_v1*>& instances) : instances(instances) { instances.push_back(this); }
	~elst_entry_v1() {
		if (generated == 2)
			return;
		while (instances.size()) {
			elst_entry_v1* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	elst_entry_v1* generate();
};

int elst_entry_v1::_parent_id = 0;
int elst_entry_v1::_index_start = 0;



class vmhd_flags {
	std::vector<vmhd_flags*>& instances;

	std::vector<byte> dummy_var;
	byte dummy2_var;

public:
	bool dummy_exists = false;
	bool dummy2_exists = false;

	std::vector<byte>& dummy() {
		assert_cond(dummy_exists, "struct field dummy does not exist");
		return dummy_var;
	}
	byte& dummy2() {
		assert_cond(dummy2_exists, "struct field dummy2 does not exist");
		return dummy2_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	vmhd_flags& operator () () { return *instances.back(); }
	vmhd_flags& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	vmhd_flags(std::vector<vmhd_flags*>& instances) : instances(instances) { instances.push_back(this); }
	~vmhd_flags() {
		if (generated == 2)
			return;
		while (instances.size()) {
			vmhd_flags* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	vmhd_flags* generate();
};

int vmhd_flags::_parent_id = 0;
int vmhd_flags::_index_start = 0;


qtgfxmode qtgfxmode_generate() {
	return (qtgfxmode) file_acc.file_integer(sizeof(uint16), 0, qtgfxmode_values);
}

qtgfxmode qtgfxmode_generate(std::vector<uint16> known_values) {
	return (qtgfxmode) file_acc.file_integer(sizeof(uint16), 0, known_values);
}


class qtopcolor {
	std::vector<qtopcolor*>& instances;

	uint16 red_var;
	uint16 green_var;
	uint16 blue_var;

public:
	bool red_exists = false;
	bool green_exists = false;
	bool blue_exists = false;

	uint16& red() {
		assert_cond(red_exists, "struct field red does not exist");
		return red_var;
	}
	uint16& green() {
		assert_cond(green_exists, "struct field green does not exist");
		return green_var;
	}
	uint16& blue() {
		assert_cond(blue_exists, "struct field blue does not exist");
		return blue_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	qtopcolor& operator () () { return *instances.back(); }
	qtopcolor& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	qtopcolor(std::vector<qtopcolor*>& instances) : instances(instances) { instances.push_back(this); }
	~qtopcolor() {
		if (generated == 2)
			return;
		while (instances.size()) {
			qtopcolor* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	qtopcolor* generate();
};

int qtopcolor::_parent_id = 0;
int qtopcolor::_index_start = 0;



class string_class {
	std::vector<std::string> known_values;
	std::string value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::string operator () () { return value; }
	string_class(std::vector<std::string> known_values = {}) : known_values(known_values) {}

	std::string generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_string();
		} else {
			value = file_acc.file_string(known_values);
		}
		_sizeof = value.length() + 1;
		return value;
	}
};



class str_stts {
	std::vector<str_stts*>& instances;

	uint32 sample_count_var;
	uint32 sample_delta_var;

public:
	bool sample_count_exists = false;
	bool sample_delta_exists = false;

	uint32& sample_count() {
		assert_cond(sample_count_exists, "struct field sample_count does not exist");
		return sample_count_var;
	}
	uint32& sample_delta() {
		assert_cond(sample_delta_exists, "struct field sample_delta does not exist");
		return sample_delta_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	str_stts& operator () () { return *instances.back(); }
	str_stts& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_stts(std::vector<str_stts*>& instances) : instances(instances) { instances.push_back(this); }
	~str_stts() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_stts* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_stts* generate();
};

int str_stts::_parent_id = 0;
int str_stts::_index_start = 0;



class str_stts_array_class {
	str_stts& element;
	std::vector<str_stts*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_stts*>& operator () () { return value; }
	str_stts operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_stts_array_class(str_stts& element) : element(element) {}

	std::vector<str_stts*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class str_ctts_v0 {
	std::vector<str_ctts_v0*>& instances;

	uint32 sample_count_var;
	uint32 sample_offset_var;

public:
	bool sample_count_exists = false;
	bool sample_offset_exists = false;

	uint32& sample_count() {
		assert_cond(sample_count_exists, "struct field sample_count does not exist");
		return sample_count_var;
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
	str_ctts_v0& operator () () { return *instances.back(); }
	str_ctts_v0& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_ctts_v0(std::vector<str_ctts_v0*>& instances) : instances(instances) { instances.push_back(this); }
	~str_ctts_v0() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_ctts_v0* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_ctts_v0* generate();
};

int str_ctts_v0::_parent_id = 0;
int str_ctts_v0::_index_start = 0;



class str_ctts_v0_array_class {
	str_ctts_v0& element;
	std::vector<str_ctts_v0*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_ctts_v0*>& operator () () { return value; }
	str_ctts_v0 operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_ctts_v0_array_class(str_ctts_v0& element) : element(element) {}

	std::vector<str_ctts_v0*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class str_ctts_v1 {
	std::vector<str_ctts_v1*>& instances;

	uint32 sample_count_var;
	int32 sample_offset_var;

public:
	bool sample_count_exists = false;
	bool sample_offset_exists = false;

	uint32& sample_count() {
		assert_cond(sample_count_exists, "struct field sample_count does not exist");
		return sample_count_var;
	}
	int32& sample_offset() {
		assert_cond(sample_offset_exists, "struct field sample_offset does not exist");
		return sample_offset_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	str_ctts_v1& operator () () { return *instances.back(); }
	str_ctts_v1& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_ctts_v1(std::vector<str_ctts_v1*>& instances) : instances(instances) { instances.push_back(this); }
	~str_ctts_v1() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_ctts_v1* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_ctts_v1* generate();
};

int str_ctts_v1::_parent_id = 0;
int str_ctts_v1::_index_start = 0;



class str_ctts_v1_array_class {
	str_ctts_v1& element;
	std::vector<str_ctts_v1*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_ctts_v1*>& operator () () { return value; }
	str_ctts_v1 operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_ctts_v1_array_class(str_ctts_v1& element) : element(element) {}

	std::vector<str_ctts_v1*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class str_stsc {
	std::vector<str_stsc*>& instances;

	uint32 first_chunk_var;
	uint32 samples_per_chunk_var;
	uint32 sample_description_index_var;

public:
	bool first_chunk_exists = false;
	bool samples_per_chunk_exists = false;
	bool sample_description_index_exists = false;

	uint32& first_chunk() {
		assert_cond(first_chunk_exists, "struct field first_chunk does not exist");
		return first_chunk_var;
	}
	uint32& samples_per_chunk() {
		assert_cond(samples_per_chunk_exists, "struct field samples_per_chunk does not exist");
		return samples_per_chunk_var;
	}
	uint32& sample_description_index() {
		assert_cond(sample_description_index_exists, "struct field sample_description_index does not exist");
		return sample_description_index_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	str_stsc& operator () () { return *instances.back(); }
	str_stsc& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_stsc(std::vector<str_stsc*>& instances) : instances(instances) { instances.push_back(this); }
	~str_stsc() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_stsc* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_stsc* generate();
};

int str_stsc::_parent_id = 0;
int str_stsc::_index_start = 0;



class str_stsc_array_class {
	str_stsc& element;
	std::vector<str_stsc*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_stsc*>& operator () () { return value; }
	str_stsc operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_stsc_array_class(str_stsc& element) : element(element) {}

	std::vector<str_stsc*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class uint16_array_class {
	uint16_class& element;
	std::unordered_map<int, std::vector<uint16>> element_known_values;
	std::vector<uint16> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<uint16>& operator () () { return value; }
	uint16 operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	uint16_array_class(uint16_class& element, std::unordered_map<int, std::vector<uint16>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<uint16> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(uint16), 0, known->second));
				_sizeof += sizeof(uint16);
			}
		}
		return value;
	}
};



class uint64_array_class {
	uint64_class& element;
	std::unordered_map<int, std::vector<uint64>> element_known_values;
	std::vector<uint64> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<uint64>& operator () () { return value; }
	uint64 operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	uint64_array_class(uint64_class& element, std::unordered_map<int, std::vector<uint64>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<uint64> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(uint64), 0, known->second));
				_sizeof += sizeof(uint64);
			}
		}
		return value;
	}
};



class str_stsh {
	std::vector<str_stsh*>& instances;

	uint32 shadowed_sample_number_var;
	uint32 sync_sample_number_var;

public:
	bool shadowed_sample_number_exists = false;
	bool sync_sample_number_exists = false;

	uint32& shadowed_sample_number() {
		assert_cond(shadowed_sample_number_exists, "struct field shadowed_sample_number does not exist");
		return shadowed_sample_number_var;
	}
	uint32& sync_sample_number() {
		assert_cond(sync_sample_number_exists, "struct field sync_sample_number does not exist");
		return sync_sample_number_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	str_stsh& operator () () { return *instances.back(); }
	str_stsh& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_stsh(std::vector<str_stsh*>& instances) : instances(instances) { instances.push_back(this); }
	~str_stsh() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_stsh* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_stsh* generate();
};

int str_stsh::_parent_id = 0;
int str_stsh::_index_start = 0;



class str_stsh_array_class {
	str_stsh& element;
	std::vector<str_stsh*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_stsh*>& operator () () { return value; }
	str_stsh operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_stsh_array_class(str_stsh& element) : element(element) {}

	std::vector<str_stsh*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class entry_struct {
	std::vector<entry_struct*>& instances;

	uint32 sample_count_var;
	uint32 group_description_index_var;

public:
	bool sample_count_exists = false;
	bool group_description_index_exists = false;

	uint32& sample_count() {
		assert_cond(sample_count_exists, "struct field sample_count does not exist");
		return sample_count_var;
	}
	uint32& group_description_index() {
		assert_cond(group_description_index_exists, "struct field group_description_index does not exist");
		return group_description_index_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	entry_struct& operator () () { return *instances.back(); }
	entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	entry_struct(std::vector<entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	entry_struct* generate();
};

int entry_struct::_parent_id = 0;
int entry_struct::_index_start = 0;



class hevc_array_struct {
	std::vector<hevc_array_struct*>& instances;

	byte array_completeness_and_NAL_unit_type_var;
	uint16 numNalus_var;
	uint16 nalUnitLength_var;
	std::vector<byte> nalUnit_var;

public:
	bool array_completeness_and_NAL_unit_type_exists = false;
	bool numNalus_exists = false;
	bool nalUnitLength_exists = false;
	bool nalUnit_exists = false;

	byte& array_completeness_and_NAL_unit_type() {
		assert_cond(array_completeness_and_NAL_unit_type_exists, "struct field array_completeness_and_NAL_unit_type does not exist");
		return array_completeness_and_NAL_unit_type_var;
	}
	uint16& numNalus() {
		assert_cond(numNalus_exists, "struct field numNalus does not exist");
		return numNalus_var;
	}
	uint16& nalUnitLength() {
		assert_cond(nalUnitLength_exists, "struct field nalUnitLength does not exist");
		return nalUnitLength_var;
	}
	std::vector<byte>& nalUnit() {
		assert_cond(nalUnit_exists, "struct field nalUnit does not exist");
		return nalUnit_var;
	}

	/* locals */
	uint16 n;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	hevc_array_struct& operator () () { return *instances.back(); }
	hevc_array_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	hevc_array_struct(std::vector<hevc_array_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~hevc_array_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			hevc_array_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	hevc_array_struct* generate();
};

int hevc_array_struct::_parent_id = 0;
int hevc_array_struct::_index_start = 0;



class font_entry_struct {
	std::vector<font_entry_struct*>& instances;

	uint16 font_ID_var;
	byte font_name_length_var;
	std::string font_name_var;

public:
	bool font_ID_exists = false;
	bool font_name_length_exists = false;
	bool font_name_exists = false;

	uint16& font_ID() {
		assert_cond(font_ID_exists, "struct field font_ID does not exist");
		return font_ID_var;
	}
	byte& font_name_length() {
		assert_cond(font_name_length_exists, "struct field font_name_length does not exist");
		return font_name_length_var;
	}
	std::string& font_name() {
		assert_cond(font_name_exists, "struct field font_name does not exist");
		return font_name_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	font_entry_struct& operator () () { return *instances.back(); }
	font_entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	font_entry_struct(std::vector<font_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~font_entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			font_entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	font_entry_struct* generate();
};

int font_entry_struct::_parent_id = 0;
int font_entry_struct::_index_start = 0;



class senc_entry_struct_subsample_struct {
	std::vector<senc_entry_struct_subsample_struct*>& instances;

	uint16 bytes_of_clear_data_var;
	uint32 bytes_of_protected_data_var;

public:
	bool bytes_of_clear_data_exists = false;
	bool bytes_of_protected_data_exists = false;

	uint16& bytes_of_clear_data() {
		assert_cond(bytes_of_clear_data_exists, "struct field bytes_of_clear_data does not exist");
		return bytes_of_clear_data_var;
	}
	uint32& bytes_of_protected_data() {
		assert_cond(bytes_of_protected_data_exists, "struct field bytes_of_protected_data does not exist");
		return bytes_of_protected_data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	senc_entry_struct_subsample_struct& operator () () { return *instances.back(); }
	senc_entry_struct_subsample_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	senc_entry_struct_subsample_struct(std::vector<senc_entry_struct_subsample_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~senc_entry_struct_subsample_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			senc_entry_struct_subsample_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	senc_entry_struct_subsample_struct* generate();
};

int senc_entry_struct_subsample_struct::_parent_id = 0;
int senc_entry_struct_subsample_struct::_index_start = 0;



class senc_entry_struct_subsample_struct_array_class {
	senc_entry_struct_subsample_struct& element;
	std::vector<senc_entry_struct_subsample_struct*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<senc_entry_struct_subsample_struct*>& operator () () { return value; }
	senc_entry_struct_subsample_struct operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	senc_entry_struct_subsample_struct_array_class(senc_entry_struct_subsample_struct& element) : element(element) {}

	std::vector<senc_entry_struct_subsample_struct*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class senc_entry_struct {
	std::vector<senc_entry_struct*>& instances;

	std::vector<byte> per_sample_IV_var;
	uint16 subsample_count_var;
	std::vector<senc_entry_struct_subsample_struct*> subsample_var;

public:
	bool per_sample_IV_exists = false;
	bool subsample_count_exists = false;
	bool subsample_exists = false;

	std::vector<byte>& per_sample_IV() {
		assert_cond(per_sample_IV_exists, "struct field per_sample_IV does not exist");
		return per_sample_IV_var;
	}
	uint16& subsample_count() {
		assert_cond(subsample_count_exists, "struct field subsample_count does not exist");
		return subsample_count_var;
	}
	std::vector<senc_entry_struct_subsample_struct*>& subsample() {
		assert_cond(subsample_exists, "struct field subsample does not exist");
		return subsample_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	senc_entry_struct& operator () () { return *instances.back(); }
	senc_entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	senc_entry_struct(std::vector<senc_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~senc_entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			senc_entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	senc_entry_struct* generate();
};

int senc_entry_struct::_parent_id = 0;
int senc_entry_struct::_index_start = 0;



class trun_entry_struct {
	std::vector<trun_entry_struct*>& instances;

	uint32 sample_duration_var;
	uint32 sample_size_var;
	uint32 sample_flags_var;

public:
	bool sample_duration_exists = false;
	bool sample_size_exists = false;
	bool sample_flags_exists = false;

	uint32& sample_duration() {
		assert_cond(sample_duration_exists, "struct field sample_duration does not exist");
		return sample_duration_var;
	}
	uint32& sample_size() {
		assert_cond(sample_size_exists, "struct field sample_size does not exist");
		return sample_size_var;
	}
	uint32& sample_flags() {
		assert_cond(sample_flags_exists, "struct field sample_flags does not exist");
		return sample_flags_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	trun_entry_struct& operator () () { return *instances.back(); }
	trun_entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	trun_entry_struct(std::vector<trun_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~trun_entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			trun_entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	trun_entry_struct* generate();
};

int trun_entry_struct::_parent_id = 0;
int trun_entry_struct::_index_start = 0;



class str_sidx {
	std::vector<str_sidx*>& instances;

	uint32 reference_size31_type1_var;
	uint32 subsegment_duration_var;
	uint32 SAP_delta_time28_type3_starts_with1_var;

public:
	bool reference_size31_type1_exists = false;
	bool subsegment_duration_exists = false;
	bool SAP_delta_time28_type3_starts_with1_exists = false;

	uint32& reference_size31_type1() {
		assert_cond(reference_size31_type1_exists, "struct field reference_size31_type1 does not exist");
		return reference_size31_type1_var;
	}
	uint32& subsegment_duration() {
		assert_cond(subsegment_duration_exists, "struct field subsegment_duration does not exist");
		return subsegment_duration_var;
	}
	uint32& SAP_delta_time28_type3_starts_with1() {
		assert_cond(SAP_delta_time28_type3_starts_with1_exists, "struct field SAP_delta_time28_type3_starts_with1 does not exist");
		return SAP_delta_time28_type3_starts_with1_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	str_sidx& operator () () { return *instances.back(); }
	str_sidx& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	str_sidx(std::vector<str_sidx*>& instances) : instances(instances) { instances.push_back(this); }
	~str_sidx() {
		if (generated == 2)
			return;
		while (instances.size()) {
			str_sidx* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	str_sidx* generate();
};

int str_sidx::_parent_id = 0;
int str_sidx::_index_start = 0;



class str_sidx_array_class {
	str_sidx& element;
	std::vector<str_sidx*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<str_sidx*>& operator () () { return value; }
	str_sidx operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	str_sidx_array_class(str_sidx& element) : element(element) {}

	std::vector<str_sidx*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class subsegment_struct_range_struct {
	std::vector<subsegment_struct_range_struct*>& instances;

	byte level_var;
	std::vector<byte> range_size_var;

public:
	bool level_exists = false;
	bool range_size_exists = false;

	byte& level() {
		assert_cond(level_exists, "struct field level does not exist");
		return level_var;
	}
	std::vector<byte>& range_size() {
		assert_cond(range_size_exists, "struct field range_size does not exist");
		return range_size_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	subsegment_struct_range_struct& operator () () { return *instances.back(); }
	subsegment_struct_range_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	subsegment_struct_range_struct(std::vector<subsegment_struct_range_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~subsegment_struct_range_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			subsegment_struct_range_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	subsegment_struct_range_struct* generate();
};

int subsegment_struct_range_struct::_parent_id = 0;
int subsegment_struct_range_struct::_index_start = 0;



class subsegment_struct_range_struct_array_class {
	subsegment_struct_range_struct& element;
	std::vector<subsegment_struct_range_struct*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<subsegment_struct_range_struct*>& operator () () { return value; }
	subsegment_struct_range_struct operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	subsegment_struct_range_struct_array_class(subsegment_struct_range_struct& element) : element(element) {}

	std::vector<subsegment_struct_range_struct*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class subsegment_struct {
	std::vector<subsegment_struct*>& instances;

	uint32 ranges_count_var;
	std::vector<subsegment_struct_range_struct*> range_var;

public:
	bool ranges_count_exists = false;
	bool range_exists = false;

	uint32& ranges_count() {
		assert_cond(ranges_count_exists, "struct field ranges_count does not exist");
		return ranges_count_var;
	}
	std::vector<subsegment_struct_range_struct*>& range() {
		assert_cond(range_exists, "struct field range does not exist");
		return range_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	subsegment_struct& operator () () { return *instances.back(); }
	subsegment_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	subsegment_struct(std::vector<subsegment_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~subsegment_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			subsegment_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	subsegment_struct* generate();
};

int subsegment_struct::_parent_id = 0;
int subsegment_struct::_index_start = 0;



class ipma_entry_struct {
	std::vector<ipma_entry_struct*>& instances;

	byte association_count_var;

public:
	bool association_count_exists = false;

	byte& association_count() {
		assert_cond(association_count_exists, "struct field association_count does not exist");
		return association_count_var;
	}

	/* locals */
	byte j;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ipma_entry_struct& operator () () { return *instances.back(); }
	ipma_entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ipma_entry_struct(std::vector<ipma_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~ipma_entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ipma_entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ipma_entry_struct* generate(int64& endOffset);
};

int ipma_entry_struct::_parent_id = 0;
int ipma_entry_struct::_index_start = 0;



class pdin_entry_struct {
	std::vector<pdin_entry_struct*>& instances;

	uint32 rate_var;
	uint32 initial_delay_var;

public:
	bool rate_exists = false;
	bool initial_delay_exists = false;

	uint32& rate() {
		assert_cond(rate_exists, "struct field rate does not exist");
		return rate_var;
	}
	uint32& initial_delay() {
		assert_cond(initial_delay_exists, "struct field initial_delay does not exist");
		return initial_delay_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	pdin_entry_struct& operator () () { return *instances.back(); }
	pdin_entry_struct& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	pdin_entry_struct(std::vector<pdin_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
	~pdin_entry_struct() {
		if (generated == 2)
			return;
		while (instances.size()) {
			pdin_entry_struct* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	pdin_entry_struct* generate();
};

int pdin_entry_struct::_parent_id = 0;
int pdin_entry_struct::_index_start = 0;



class mp4box {
	std::vector<mp4box*>& instances;

	uint32 size_var;
	fourcc* type_var;
	mp4box* box_var;
	mp4box* mvhd_block_var;
	mp4box* trak_block_var;
	mp4box* iods_block_var;
	mp4box* udta_block_var;
	mp4box* meta_block_var;
	mp4box* mvex_block_var;
	mp4box* unknown_block_var;
	std::string major_brand_var;
	uint32 minor_version_var;
	std::string compatible_brand_var;
	byte version_var;
	std::vector<byte> flag_var;
	uint32 timescale_var;
	fp32* rate_var;
	fp16* volume_var;
	matrix* matrix_structure_var;
	uint32 next_track_ID_var;
	std::vector<byte> data_var;
	std::vector<byte> OD_data_var;
	mp4box* tkhd_block_var;
	mp4box* mdia_block_var;
	mp4box* edts_block_var;
	mp4box* tref_block_var;
	tkhd_flags* tkhd_fl_var;
	uint32 track_ID_var;
	int16 layer_var;
	int16 alternate_group_var;
	mp4box* mdhd_block_var;
	mp4box* hdlr_block_var;
	mp4box* minf_block_var;
	mp4box* elng_block_var;
	mp4lang* language_var;
	uint32 handler_type_var;
	mp4box* child_block_var;
	uint32 elst_count_var;
	std::string notice_var;
	mp4box* child_box_var;
	mp4box* header_block_var;
	mp4box* stbl_block_var;
	mp4box* dinf_block_var;
	vmhd_flags* vmhd_fl_var;
	uint16 graphics_mode_var;
	qtopcolor* opcolor_var;
	fp16* balance_var;
	uint32 dref_count_var;
	mp4box* entry_box_var;
	std::string location_var;
	uint32 stsd_count_var;
	mp4box* sample_entry_var;
	uint32 stts_count_var;
	uint32 ctts_count_var;
	uint32 stsc_count_var;
	uint32 sample_size_var;
	uint32 sample_count_var;
	std::vector<byte> reserved_stz2_var;
	byte field_size_var;
	uint32 stco_count_var;
	uint32 co64_count_var;
	uint32 stss_count_var;
	std::vector<uint32> sample_number_var;
	uint32 stsh_count_var;
	std::vector<byte> sample_dependency_table_var;
	uint32 grouping_type_var;
	uint32 grouping_type_parameter_var;
	uint32 sbgp_count_var;
	entry_struct* entry_var;
	uint32 default_length_var;
	uint32 default_sample_description_index_var;
	uint32 sgpd_count_var;
	uint32 description_length_var;
	std::vector<byte> description_var;
	uint16 data_reference_index_var;
	uint16 pre_defined1_var;
	std::vector<uint32> pre_defined2_var;
	uint32 horizresolution_var;
	uint32 vertresolution_var;
	uint16 frame_count_var;
	std::vector<byte> compressorname_var;
	uint16 depth_var;
	int16 pre_defined3_var;
	byte configurationVersion_var;
	byte AVCProfileIndication_var;
	byte profile_compatibility_var;
	byte AVCLevelIndication_var;
	byte lengthSizeMinusOne_var;
	byte numOfSequenceParameterSets_var;
	uint16 sequenceParameterSetLength_var;
	std::vector<byte> sequenceParameterSetNALUnit_var;
	byte numOfPictureParameterSets_var;
	uint16 pictureParameterSetLength_var;
	std::vector<byte> pictureParameterSetNALUnit_var;
	std::vector<byte> extra_data_var;
	byte general_profile_space_tier_idc_var;
	uint32 general_profile_compatibility_flags_var;
	std::vector<byte> general_constraint_indicator_flag_var;
	byte general_level_idc_var;
	uint16 min_spatial_segmentation_idc_var;
	byte parallelismType_var;
	byte chromaFormat_var;
	byte bitDepthLumaMinus8_var;
	byte bitDepthChromaMinus8_var;
	uint16 avgFrameRate_var;
	byte constFR_numTempLayers_tidNested_lenSize_var;
	byte numOfArrays_var;
	hevc_array_struct* hevc_array_var;
	byte marker_version_var;
	byte seq_profile_level_var;
	byte chroma_flags_var;
	byte delay_flags_var;
	std::vector<byte> configOBUs_var;
	byte dv_version_major_var;
	byte dv_version_minor_var;
	uint16 profile_level_flags_var;
	uint32 bl_compat_and_reserved__var;
	std::vector<byte> reserved__data_var;
	uint32 bufferSizeDB_var;
	uint32 maxBitrate_var;
	uint32 avgBitrate_var;
	uint32 hSpacing_var;
	uint32 vSpacing_var;
	uint32 cleanApertureWidthN_var;
	uint32 cleanApertureWidthD_var;
	uint32 cleanApertureHeightN_var;
	uint32 cleanApertureHeightD_var;
	int32 horizOffN_var;
	uint32 horizOffD_var;
	int32 vertOffN_var;
	uint32 vertOffD_var;
	std::string colourType_var;
	uint16 colour_primaries_var;
	uint16 transfer_characteristics_var;
	uint16 matrix_coefficients_var;
	byte full_range_flag_var;
	std::vector<byte> icc_profile_var;
	uint16 channelcount_var;
	uint16 samplesize_var;
	uint32 samplerate_var;
	std::vector<byte> ES_Descriptor_var;
	uint16 compression_id_var;
	uint16 packet_size_var;
	byte outputChannelCount_var;
	uint16 preSkip_var;
	uint32 inputSampleRate_var;
	int16 outputGain_var;
	byte channelMappingFamily_var;
	byte streamCount_var;
	byte coupledCount_var;
	std::vector<byte> channelMapping_var;
	std::vector<byte> flac_metadata_var;
	std::vector<byte> alac_specific_config_var;
	std::string namespace_uri_var;
	std::string schema_location_var;
	std::string auxiliary_mime_types_var;
	uint32 display_flags_var;
	byte horizontal_justification_var;
	byte vertical_justification_var;
	std::vector<byte> background_color_rgba_var;
	int16 box_top_var;
	int16 box_left_var;
	int16 box_bottom_var;
	int16 box_right_var;
	uint16 startChar_var;
	uint16 endChar_var;
	uint16 font_ID_var;
	byte face_style_flags_var;
	byte font_size_var;
	std::vector<byte> text_color_rgba_var;
	uint16 ftab_count_var;
	font_entry_struct* font_entry_var;
	std::string content_encoding_var;
	std::string mime_format_var;
	std::string xml_data_var;
	std::string data_format_var;
	std::string scheme_type_var;
	uint32 scheme_version_var;
	std::string scheme_uri_var;
	byte default_crypt_skip_byte_block_var;
	byte default_isProtected_var;
	byte default_Per_Sample_IV_Size_var;
	std::vector<byte> default_KID_var;
	byte default_constant_IV_size_var;
	std::vector<byte> default_constant_IV_var;
	std::vector<byte> systemID_var;
	uint32 KID_count_var;
	std::vector<byte> KID_var;
	uint32 DataSize_var;
	std::vector<byte> Data_var;
	senc_entry_struct* senc_entry_var;
	uint32 sequence_number_var;
	uint64 base_data_offset_var;
	uint32 sample_description_index_var;
	uint32 default_sample_duration_var;
	uint32 default_sample_size_var;
	uint32 default_sample_flags_var;
	int32 data_offset_var;
	uint32 first_sample_flags_var;
	trun_entry_struct* trun_entry_var;
	uint32 aux_info_type_var;
	uint32 aux_info_type_parameter_var;
	byte default_sample_info_size_var;
	std::vector<byte> sample_info_size_var;
	uint32 saio_count_var;
	uint32 reference_ID_var;
	uint16 reference_count_var;
	std::vector<str_sidx*> references_var;
	uint32 subsegment_count_var;
	subsegment_struct* subsegment_var;
	uint32 reserved__and_lengths_var;
	uint32 number_of_entry_var;
	std::vector<byte> entry_data_var;
	uint32 mfra_size_var;
	uint32 iinf_count_var;
	mp4box* infe_box_var;
	uint16 item_protection_index_var;
	std::string item_name_var;
	std::string content_type_var;
	std::vector<byte> item_type_bytes_var;
	std::string item_uri_type_var;
	byte offset_length_sizes_var;
	byte baseoffset_index_sizes_var;
	uint32 iloc_item_count_var;
	std::vector<byte> item_data_var;
	mp4box* ref_box_var;
	uint32 ipma_count_var;
	ipma_entry_struct* ipma_entry_var;
	uint16 protection_count_var;
	mp4box* sinf_box_var;
	uint16 num_components_var;
	byte bits_per_component_var;
	byte compression_type_var;
	byte unknownColorspace_var;
	byte intellectual_property_var;
	std::string scheme_id_uri_var;
	uint32 presentation_time_delta_var;
	uint32 event_duration_var;
	uint32 id_var;
	uint64 presentation_time_var;
	std::vector<byte> message_data_var;
	uint32 reference_track_ID_var;
	uint64 ntp_timestamp_var;
	pdin_entry_struct* pdin_entry_var;
	std::string extended_language_var;
	std::string schemeURI_var;
	std::vector<byte> usertype_var;
	uint32 type_indicator_var;
	uint32 locale_var;
	std::vector<byte> aliasInfo_var;
	std::vector<byte> parameterSets_var;
	std::vector<byte> subSampleInformation_var;
	std::vector<byte> unknown_var;

public:
	bool size_exists = false;
	bool type_exists = false;
	bool box_exists = false;
	bool mvhd_block_exists = false;
	bool trak_block_exists = false;
	bool iods_block_exists = false;
	bool udta_block_exists = false;
	bool meta_block_exists = false;
	bool mvex_block_exists = false;
	bool unknown_block_exists = false;
	bool major_brand_exists = false;
	bool minor_version_exists = false;
	bool compatible_brand_exists = false;
	bool version_exists = false;
	bool flag_exists = false;
	bool timescale_exists = false;
	bool rate_exists = false;
	bool volume_exists = false;
	bool matrix_structure_exists = false;
	bool next_track_ID_exists = false;
	bool data_exists = false;
	bool OD_data_exists = false;
	bool tkhd_block_exists = false;
	bool mdia_block_exists = false;
	bool edts_block_exists = false;
	bool tref_block_exists = false;
	bool tkhd_fl_exists = false;
	bool track_ID_exists = false;
	bool layer_exists = false;
	bool alternate_group_exists = false;
	bool mdhd_block_exists = false;
	bool hdlr_block_exists = false;
	bool minf_block_exists = false;
	bool elng_block_exists = false;
	bool language_exists = false;
	bool handler_type_exists = false;
	bool child_block_exists = false;
	bool elst_count_exists = false;
	bool notice_exists = false;
	bool child_box_exists = false;
	bool header_block_exists = false;
	bool stbl_block_exists = false;
	bool dinf_block_exists = false;
	bool vmhd_fl_exists = false;
	bool graphics_mode_exists = false;
	bool opcolor_exists = false;
	bool balance_exists = false;
	bool dref_count_exists = false;
	bool entry_box_exists = false;
	bool location_exists = false;
	bool stsd_count_exists = false;
	bool sample_entry_exists = false;
	bool stts_count_exists = false;
	bool ctts_count_exists = false;
	bool stsc_count_exists = false;
	bool sample_size_exists = false;
	bool sample_count_exists = false;
	bool reserved_stz2_exists = false;
	bool field_size_exists = false;
	bool stco_count_exists = false;
	bool co64_count_exists = false;
	bool stss_count_exists = false;
	bool sample_number_exists = false;
	bool stsh_count_exists = false;
	bool sample_dependency_table_exists = false;
	bool grouping_type_exists = false;
	bool grouping_type_parameter_exists = false;
	bool sbgp_count_exists = false;
	bool entry_exists = false;
	bool default_length_exists = false;
	bool default_sample_description_index_exists = false;
	bool sgpd_count_exists = false;
	bool description_length_exists = false;
	bool description_exists = false;
	bool data_reference_index_exists = false;
	bool pre_defined1_exists = false;
	bool pre_defined2_exists = false;
	bool horizresolution_exists = false;
	bool vertresolution_exists = false;
	bool frame_count_exists = false;
	bool compressorname_exists = false;
	bool depth_exists = false;
	bool pre_defined3_exists = false;
	bool configurationVersion_exists = false;
	bool AVCProfileIndication_exists = false;
	bool profile_compatibility_exists = false;
	bool AVCLevelIndication_exists = false;
	bool lengthSizeMinusOne_exists = false;
	bool numOfSequenceParameterSets_exists = false;
	bool sequenceParameterSetLength_exists = false;
	bool sequenceParameterSetNALUnit_exists = false;
	bool numOfPictureParameterSets_exists = false;
	bool pictureParameterSetLength_exists = false;
	bool pictureParameterSetNALUnit_exists = false;
	bool extra_data_exists = false;
	bool general_profile_space_tier_idc_exists = false;
	bool general_profile_compatibility_flags_exists = false;
	bool general_constraint_indicator_flag_exists = false;
	bool general_level_idc_exists = false;
	bool min_spatial_segmentation_idc_exists = false;
	bool parallelismType_exists = false;
	bool chromaFormat_exists = false;
	bool bitDepthLumaMinus8_exists = false;
	bool bitDepthChromaMinus8_exists = false;
	bool avgFrameRate_exists = false;
	bool constFR_numTempLayers_tidNested_lenSize_exists = false;
	bool numOfArrays_exists = false;
	bool hevc_array_exists = false;
	bool marker_version_exists = false;
	bool seq_profile_level_exists = false;
	bool chroma_flags_exists = false;
	bool delay_flags_exists = false;
	bool configOBUs_exists = false;
	bool dv_version_major_exists = false;
	bool dv_version_minor_exists = false;
	bool profile_level_flags_exists = false;
	bool bl_compat_and_reserved__exists = false;
	bool reserved__data_exists = false;
	bool bufferSizeDB_exists = false;
	bool maxBitrate_exists = false;
	bool avgBitrate_exists = false;
	bool hSpacing_exists = false;
	bool vSpacing_exists = false;
	bool cleanApertureWidthN_exists = false;
	bool cleanApertureWidthD_exists = false;
	bool cleanApertureHeightN_exists = false;
	bool cleanApertureHeightD_exists = false;
	bool horizOffN_exists = false;
	bool horizOffD_exists = false;
	bool vertOffN_exists = false;
	bool vertOffD_exists = false;
	bool colourType_exists = false;
	bool colour_primaries_exists = false;
	bool transfer_characteristics_exists = false;
	bool matrix_coefficients_exists = false;
	bool full_range_flag_exists = false;
	bool icc_profile_exists = false;
	bool channelcount_exists = false;
	bool samplesize_exists = false;
	bool samplerate_exists = false;
	bool ES_Descriptor_exists = false;
	bool compression_id_exists = false;
	bool packet_size_exists = false;
	bool outputChannelCount_exists = false;
	bool preSkip_exists = false;
	bool inputSampleRate_exists = false;
	bool outputGain_exists = false;
	bool channelMappingFamily_exists = false;
	bool streamCount_exists = false;
	bool coupledCount_exists = false;
	bool channelMapping_exists = false;
	bool flac_metadata_exists = false;
	bool alac_specific_config_exists = false;
	bool namespace_uri_exists = false;
	bool schema_location_exists = false;
	bool auxiliary_mime_types_exists = false;
	bool display_flags_exists = false;
	bool horizontal_justification_exists = false;
	bool vertical_justification_exists = false;
	bool background_color_rgba_exists = false;
	bool box_top_exists = false;
	bool box_left_exists = false;
	bool box_bottom_exists = false;
	bool box_right_exists = false;
	bool startChar_exists = false;
	bool endChar_exists = false;
	bool font_ID_exists = false;
	bool face_style_flags_exists = false;
	bool font_size_exists = false;
	bool text_color_rgba_exists = false;
	bool ftab_count_exists = false;
	bool font_entry_exists = false;
	bool content_encoding_exists = false;
	bool mime_format_exists = false;
	bool xml_data_exists = false;
	bool data_format_exists = false;
	bool scheme_type_exists = false;
	bool scheme_version_exists = false;
	bool scheme_uri_exists = false;
	bool default_crypt_skip_byte_block_exists = false;
	bool default_isProtected_exists = false;
	bool default_Per_Sample_IV_Size_exists = false;
	bool default_KID_exists = false;
	bool default_constant_IV_size_exists = false;
	bool default_constant_IV_exists = false;
	bool systemID_exists = false;
	bool KID_count_exists = false;
	bool KID_exists = false;
	bool DataSize_exists = false;
	bool Data_exists = false;
	bool senc_entry_exists = false;
	bool sequence_number_exists = false;
	bool base_data_offset_exists = false;
	bool sample_description_index_exists = false;
	bool default_sample_duration_exists = false;
	bool default_sample_size_exists = false;
	bool default_sample_flags_exists = false;
	bool data_offset_exists = false;
	bool first_sample_flags_exists = false;
	bool trun_entry_exists = false;
	bool aux_info_type_exists = false;
	bool aux_info_type_parameter_exists = false;
	bool default_sample_info_size_exists = false;
	bool sample_info_size_exists = false;
	bool saio_count_exists = false;
	bool reference_ID_exists = false;
	bool reference_count_exists = false;
	bool references_exists = false;
	bool subsegment_count_exists = false;
	bool subsegment_exists = false;
	bool reserved__and_lengths_exists = false;
	bool number_of_entry_exists = false;
	bool entry_data_exists = false;
	bool mfra_size_exists = false;
	bool iinf_count_exists = false;
	bool infe_box_exists = false;
	bool item_protection_index_exists = false;
	bool item_name_exists = false;
	bool content_type_exists = false;
	bool item_type_bytes_exists = false;
	bool item_uri_type_exists = false;
	bool offset_length_sizes_exists = false;
	bool baseoffset_index_sizes_exists = false;
	bool iloc_item_count_exists = false;
	bool item_data_exists = false;
	bool ref_box_exists = false;
	bool ipma_count_exists = false;
	bool ipma_entry_exists = false;
	bool protection_count_exists = false;
	bool sinf_box_exists = false;
	bool num_components_exists = false;
	bool bits_per_component_exists = false;
	bool compression_type_exists = false;
	bool unknownColorspace_exists = false;
	bool intellectual_property_exists = false;
	bool scheme_id_uri_exists = false;
	bool presentation_time_delta_exists = false;
	bool event_duration_exists = false;
	bool id_exists = false;
	bool presentation_time_exists = false;
	bool message_data_exists = false;
	bool reference_track_ID_exists = false;
	bool ntp_timestamp_exists = false;
	bool pdin_entry_exists = false;
	bool extended_language_exists = false;
	bool schemeURI_exists = false;
	bool usertype_exists = false;
	bool type_indicator_exists = false;
	bool locale_exists = false;
	bool aliasInfo_exists = false;
	bool parameterSets_exists = false;
	bool subSampleInformation_exists = false;
	bool unknown_exists = false;

	uint32& size() {
		assert_cond(size_exists, "struct field size does not exist");
		return size_var;
	}
	fourcc& type() {
		assert_cond(type_exists, "struct field type does not exist");
		return *type_var;
	}
	mp4box& box() {
		assert_cond(box_exists, "struct field box does not exist");
		return *box_var;
	}
	mp4box& mvhd_block() {
		assert_cond(mvhd_block_exists, "struct field mvhd_block does not exist");
		return *mvhd_block_var;
	}
	mp4box& trak_block() {
		assert_cond(trak_block_exists, "struct field trak_block does not exist");
		return *trak_block_var;
	}
	mp4box& iods_block() {
		assert_cond(iods_block_exists, "struct field iods_block does not exist");
		return *iods_block_var;
	}
	mp4box& udta_block() {
		assert_cond(udta_block_exists, "struct field udta_block does not exist");
		return *udta_block_var;
	}
	mp4box& meta_block() {
		assert_cond(meta_block_exists, "struct field meta_block does not exist");
		return *meta_block_var;
	}
	mp4box& mvex_block() {
		assert_cond(mvex_block_exists, "struct field mvex_block does not exist");
		return *mvex_block_var;
	}
	mp4box& unknown_block() {
		assert_cond(unknown_block_exists, "struct field unknown_block does not exist");
		return *unknown_block_var;
	}
	std::string& major_brand() {
		assert_cond(major_brand_exists, "struct field major_brand does not exist");
		return major_brand_var;
	}
	uint32& minor_version() {
		assert_cond(minor_version_exists, "struct field minor_version does not exist");
		return minor_version_var;
	}
	std::string& compatible_brand() {
		assert_cond(compatible_brand_exists, "struct field compatible_brand does not exist");
		return compatible_brand_var;
	}
	byte& version() {
		assert_cond(version_exists, "struct field version does not exist");
		return version_var;
	}
	std::vector<byte>& flag() {
		assert_cond(flag_exists, "struct field flag does not exist");
		return flag_var;
	}
	uint32& timescale() {
		assert_cond(timescale_exists, "struct field timescale does not exist");
		return timescale_var;
	}
	fp32& rate() {
		assert_cond(rate_exists, "struct field rate does not exist");
		return *rate_var;
	}
	fp16& volume() {
		assert_cond(volume_exists, "struct field volume does not exist");
		return *volume_var;
	}
	matrix& matrix_structure() {
		assert_cond(matrix_structure_exists, "struct field matrix_structure does not exist");
		return *matrix_structure_var;
	}
	uint32& next_track_ID() {
		assert_cond(next_track_ID_exists, "struct field next_track_ID does not exist");
		return next_track_ID_var;
	}
	std::vector<byte>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}
	std::vector<byte>& OD_data() {
		assert_cond(OD_data_exists, "struct field OD_data does not exist");
		return OD_data_var;
	}
	mp4box& tkhd_block() {
		assert_cond(tkhd_block_exists, "struct field tkhd_block does not exist");
		return *tkhd_block_var;
	}
	mp4box& mdia_block() {
		assert_cond(mdia_block_exists, "struct field mdia_block does not exist");
		return *mdia_block_var;
	}
	mp4box& edts_block() {
		assert_cond(edts_block_exists, "struct field edts_block does not exist");
		return *edts_block_var;
	}
	mp4box& tref_block() {
		assert_cond(tref_block_exists, "struct field tref_block does not exist");
		return *tref_block_var;
	}
	tkhd_flags& tkhd_fl() {
		assert_cond(tkhd_fl_exists, "struct field tkhd_fl does not exist");
		return *tkhd_fl_var;
	}
	uint32& track_ID() {
		assert_cond(track_ID_exists, "struct field track_ID does not exist");
		return track_ID_var;
	}
	int16& layer() {
		assert_cond(layer_exists, "struct field layer does not exist");
		return layer_var;
	}
	int16& alternate_group() {
		assert_cond(alternate_group_exists, "struct field alternate_group does not exist");
		return alternate_group_var;
	}
	mp4box& mdhd_block() {
		assert_cond(mdhd_block_exists, "struct field mdhd_block does not exist");
		return *mdhd_block_var;
	}
	mp4box& hdlr_block() {
		assert_cond(hdlr_block_exists, "struct field hdlr_block does not exist");
		return *hdlr_block_var;
	}
	mp4box& minf_block() {
		assert_cond(minf_block_exists, "struct field minf_block does not exist");
		return *minf_block_var;
	}
	mp4box& elng_block() {
		assert_cond(elng_block_exists, "struct field elng_block does not exist");
		return *elng_block_var;
	}
	mp4lang& language() {
		assert_cond(language_exists, "struct field language does not exist");
		return *language_var;
	}
	uint32& handler_type() {
		assert_cond(handler_type_exists, "struct field handler_type does not exist");
		return handler_type_var;
	}
	mp4box& child_block() {
		assert_cond(child_block_exists, "struct field child_block does not exist");
		return *child_block_var;
	}
	uint32& elst_count() {
		assert_cond(elst_count_exists, "struct field elst_count does not exist");
		return elst_count_var;
	}
	std::string& notice() {
		assert_cond(notice_exists, "struct field notice does not exist");
		return notice_var;
	}
	mp4box& child_box() {
		assert_cond(child_box_exists, "struct field child_box does not exist");
		return *child_box_var;
	}
	mp4box& header_block() {
		assert_cond(header_block_exists, "struct field header_block does not exist");
		return *header_block_var;
	}
	mp4box& stbl_block() {
		assert_cond(stbl_block_exists, "struct field stbl_block does not exist");
		return *stbl_block_var;
	}
	mp4box& dinf_block() {
		assert_cond(dinf_block_exists, "struct field dinf_block does not exist");
		return *dinf_block_var;
	}
	vmhd_flags& vmhd_fl() {
		assert_cond(vmhd_fl_exists, "struct field vmhd_fl does not exist");
		return *vmhd_fl_var;
	}
	uint16& graphics_mode() {
		assert_cond(graphics_mode_exists, "struct field graphics_mode does not exist");
		return graphics_mode_var;
	}
	qtopcolor& opcolor() {
		assert_cond(opcolor_exists, "struct field opcolor does not exist");
		return *opcolor_var;
	}
	fp16& balance() {
		assert_cond(balance_exists, "struct field balance does not exist");
		return *balance_var;
	}
	uint32& dref_count() {
		assert_cond(dref_count_exists, "struct field dref_count does not exist");
		return dref_count_var;
	}
	mp4box& entry_box() {
		assert_cond(entry_box_exists, "struct field entry_box does not exist");
		return *entry_box_var;
	}
	std::string& location() {
		assert_cond(location_exists, "struct field location does not exist");
		return location_var;
	}
	uint32& stsd_count() {
		assert_cond(stsd_count_exists, "struct field stsd_count does not exist");
		return stsd_count_var;
	}
	mp4box& sample_entry() {
		assert_cond(sample_entry_exists, "struct field sample_entry does not exist");
		return *sample_entry_var;
	}
	uint32& stts_count() {
		assert_cond(stts_count_exists, "struct field stts_count does not exist");
		return stts_count_var;
	}
	uint32& ctts_count() {
		assert_cond(ctts_count_exists, "struct field ctts_count does not exist");
		return ctts_count_var;
	}
	uint32& stsc_count() {
		assert_cond(stsc_count_exists, "struct field stsc_count does not exist");
		return stsc_count_var;
	}
	uint32& sample_size() {
		assert_cond(sample_size_exists, "struct field sample_size does not exist");
		return sample_size_var;
	}
	uint32& sample_count() {
		assert_cond(sample_count_exists, "struct field sample_count does not exist");
		return sample_count_var;
	}
	std::vector<byte>& reserved_stz2() {
		assert_cond(reserved_stz2_exists, "struct field reserved_stz2 does not exist");
		return reserved_stz2_var;
	}
	byte& field_size() {
		assert_cond(field_size_exists, "struct field field_size does not exist");
		return field_size_var;
	}
	uint32& stco_count() {
		assert_cond(stco_count_exists, "struct field stco_count does not exist");
		return stco_count_var;
	}
	uint32& co64_count() {
		assert_cond(co64_count_exists, "struct field co64_count does not exist");
		return co64_count_var;
	}
	uint32& stss_count() {
		assert_cond(stss_count_exists, "struct field stss_count does not exist");
		return stss_count_var;
	}
	std::vector<uint32>& sample_number() {
		assert_cond(sample_number_exists, "struct field sample_number does not exist");
		return sample_number_var;
	}
	uint32& stsh_count() {
		assert_cond(stsh_count_exists, "struct field stsh_count does not exist");
		return stsh_count_var;
	}
	std::vector<byte>& sample_dependency_table() {
		assert_cond(sample_dependency_table_exists, "struct field sample_dependency_table does not exist");
		return sample_dependency_table_var;
	}
	uint32& grouping_type() {
		assert_cond(grouping_type_exists, "struct field grouping_type does not exist");
		return grouping_type_var;
	}
	uint32& grouping_type_parameter() {
		assert_cond(grouping_type_parameter_exists, "struct field grouping_type_parameter does not exist");
		return grouping_type_parameter_var;
	}
	uint32& sbgp_count() {
		assert_cond(sbgp_count_exists, "struct field sbgp_count does not exist");
		return sbgp_count_var;
	}
	entry_struct& entry() {
		assert_cond(entry_exists, "struct field entry does not exist");
		return *entry_var;
	}
	uint32& default_length() {
		assert_cond(default_length_exists, "struct field default_length does not exist");
		return default_length_var;
	}
	uint32& default_sample_description_index() {
		assert_cond(default_sample_description_index_exists, "struct field default_sample_description_index does not exist");
		return default_sample_description_index_var;
	}
	uint32& sgpd_count() {
		assert_cond(sgpd_count_exists, "struct field sgpd_count does not exist");
		return sgpd_count_var;
	}
	uint32& description_length() {
		assert_cond(description_length_exists, "struct field description_length does not exist");
		return description_length_var;
	}
	std::vector<byte>& description() {
		assert_cond(description_exists, "struct field description does not exist");
		return description_var;
	}
	uint16& data_reference_index() {
		assert_cond(data_reference_index_exists, "struct field data_reference_index does not exist");
		return data_reference_index_var;
	}
	uint16& pre_defined1() {
		assert_cond(pre_defined1_exists, "struct field pre_defined1 does not exist");
		return pre_defined1_var;
	}
	std::vector<uint32>& pre_defined2() {
		assert_cond(pre_defined2_exists, "struct field pre_defined2 does not exist");
		return pre_defined2_var;
	}
	uint32& horizresolution() {
		assert_cond(horizresolution_exists, "struct field horizresolution does not exist");
		return horizresolution_var;
	}
	uint32& vertresolution() {
		assert_cond(vertresolution_exists, "struct field vertresolution does not exist");
		return vertresolution_var;
	}
	uint16& frame_count() {
		assert_cond(frame_count_exists, "struct field frame_count does not exist");
		return frame_count_var;
	}
	std::vector<byte>& compressorname() {
		assert_cond(compressorname_exists, "struct field compressorname does not exist");
		return compressorname_var;
	}
	uint16& depth() {
		assert_cond(depth_exists, "struct field depth does not exist");
		return depth_var;
	}
	int16& pre_defined3() {
		assert_cond(pre_defined3_exists, "struct field pre_defined3 does not exist");
		return pre_defined3_var;
	}
	byte& configurationVersion() {
		assert_cond(configurationVersion_exists, "struct field configurationVersion does not exist");
		return configurationVersion_var;
	}
	byte& AVCProfileIndication() {
		assert_cond(AVCProfileIndication_exists, "struct field AVCProfileIndication does not exist");
		return AVCProfileIndication_var;
	}
	byte& profile_compatibility() {
		assert_cond(profile_compatibility_exists, "struct field profile_compatibility does not exist");
		return profile_compatibility_var;
	}
	byte& AVCLevelIndication() {
		assert_cond(AVCLevelIndication_exists, "struct field AVCLevelIndication does not exist");
		return AVCLevelIndication_var;
	}
	byte& lengthSizeMinusOne() {
		assert_cond(lengthSizeMinusOne_exists, "struct field lengthSizeMinusOne does not exist");
		return lengthSizeMinusOne_var;
	}
	byte& numOfSequenceParameterSets() {
		assert_cond(numOfSequenceParameterSets_exists, "struct field numOfSequenceParameterSets does not exist");
		return numOfSequenceParameterSets_var;
	}
	uint16& sequenceParameterSetLength() {
		assert_cond(sequenceParameterSetLength_exists, "struct field sequenceParameterSetLength does not exist");
		return sequenceParameterSetLength_var;
	}
	std::vector<byte>& sequenceParameterSetNALUnit() {
		assert_cond(sequenceParameterSetNALUnit_exists, "struct field sequenceParameterSetNALUnit does not exist");
		return sequenceParameterSetNALUnit_var;
	}
	byte& numOfPictureParameterSets() {
		assert_cond(numOfPictureParameterSets_exists, "struct field numOfPictureParameterSets does not exist");
		return numOfPictureParameterSets_var;
	}
	uint16& pictureParameterSetLength() {
		assert_cond(pictureParameterSetLength_exists, "struct field pictureParameterSetLength does not exist");
		return pictureParameterSetLength_var;
	}
	std::vector<byte>& pictureParameterSetNALUnit() {
		assert_cond(pictureParameterSetNALUnit_exists, "struct field pictureParameterSetNALUnit does not exist");
		return pictureParameterSetNALUnit_var;
	}
	std::vector<byte>& extra_data() {
		assert_cond(extra_data_exists, "struct field extra_data does not exist");
		return extra_data_var;
	}
	byte& general_profile_space_tier_idc() {
		assert_cond(general_profile_space_tier_idc_exists, "struct field general_profile_space_tier_idc does not exist");
		return general_profile_space_tier_idc_var;
	}
	uint32& general_profile_compatibility_flags() {
		assert_cond(general_profile_compatibility_flags_exists, "struct field general_profile_compatibility_flags does not exist");
		return general_profile_compatibility_flags_var;
	}
	std::vector<byte>& general_constraint_indicator_flag() {
		assert_cond(general_constraint_indicator_flag_exists, "struct field general_constraint_indicator_flag does not exist");
		return general_constraint_indicator_flag_var;
	}
	byte& general_level_idc() {
		assert_cond(general_level_idc_exists, "struct field general_level_idc does not exist");
		return general_level_idc_var;
	}
	uint16& min_spatial_segmentation_idc() {
		assert_cond(min_spatial_segmentation_idc_exists, "struct field min_spatial_segmentation_idc does not exist");
		return min_spatial_segmentation_idc_var;
	}
	byte& parallelismType() {
		assert_cond(parallelismType_exists, "struct field parallelismType does not exist");
		return parallelismType_var;
	}
	byte& chromaFormat() {
		assert_cond(chromaFormat_exists, "struct field chromaFormat does not exist");
		return chromaFormat_var;
	}
	byte& bitDepthLumaMinus8() {
		assert_cond(bitDepthLumaMinus8_exists, "struct field bitDepthLumaMinus8 does not exist");
		return bitDepthLumaMinus8_var;
	}
	byte& bitDepthChromaMinus8() {
		assert_cond(bitDepthChromaMinus8_exists, "struct field bitDepthChromaMinus8 does not exist");
		return bitDepthChromaMinus8_var;
	}
	uint16& avgFrameRate() {
		assert_cond(avgFrameRate_exists, "struct field avgFrameRate does not exist");
		return avgFrameRate_var;
	}
	byte& constFR_numTempLayers_tidNested_lenSize() {
		assert_cond(constFR_numTempLayers_tidNested_lenSize_exists, "struct field constFR_numTempLayers_tidNested_lenSize does not exist");
		return constFR_numTempLayers_tidNested_lenSize_var;
	}
	byte& numOfArrays() {
		assert_cond(numOfArrays_exists, "struct field numOfArrays does not exist");
		return numOfArrays_var;
	}
	hevc_array_struct& hevc_array() {
		assert_cond(hevc_array_exists, "struct field hevc_array does not exist");
		return *hevc_array_var;
	}
	byte& marker_version() {
		assert_cond(marker_version_exists, "struct field marker_version does not exist");
		return marker_version_var;
	}
	byte& seq_profile_level() {
		assert_cond(seq_profile_level_exists, "struct field seq_profile_level does not exist");
		return seq_profile_level_var;
	}
	byte& chroma_flags() {
		assert_cond(chroma_flags_exists, "struct field chroma_flags does not exist");
		return chroma_flags_var;
	}
	byte& delay_flags() {
		assert_cond(delay_flags_exists, "struct field delay_flags does not exist");
		return delay_flags_var;
	}
	std::vector<byte>& configOBUs() {
		assert_cond(configOBUs_exists, "struct field configOBUs does not exist");
		return configOBUs_var;
	}
	byte& dv_version_major() {
		assert_cond(dv_version_major_exists, "struct field dv_version_major does not exist");
		return dv_version_major_var;
	}
	byte& dv_version_minor() {
		assert_cond(dv_version_minor_exists, "struct field dv_version_minor does not exist");
		return dv_version_minor_var;
	}
	uint16& profile_level_flags() {
		assert_cond(profile_level_flags_exists, "struct field profile_level_flags does not exist");
		return profile_level_flags_var;
	}
	uint32& bl_compat_and_reserved_() {
		assert_cond(bl_compat_and_reserved__exists, "struct field bl_compat_and_reserved_ does not exist");
		return bl_compat_and_reserved__var;
	}
	std::vector<byte>& reserved__data() {
		assert_cond(reserved__data_exists, "struct field reserved__data does not exist");
		return reserved__data_var;
	}
	uint32& bufferSizeDB() {
		assert_cond(bufferSizeDB_exists, "struct field bufferSizeDB does not exist");
		return bufferSizeDB_var;
	}
	uint32& maxBitrate() {
		assert_cond(maxBitrate_exists, "struct field maxBitrate does not exist");
		return maxBitrate_var;
	}
	uint32& avgBitrate() {
		assert_cond(avgBitrate_exists, "struct field avgBitrate does not exist");
		return avgBitrate_var;
	}
	uint32& hSpacing() {
		assert_cond(hSpacing_exists, "struct field hSpacing does not exist");
		return hSpacing_var;
	}
	uint32& vSpacing() {
		assert_cond(vSpacing_exists, "struct field vSpacing does not exist");
		return vSpacing_var;
	}
	uint32& cleanApertureWidthN() {
		assert_cond(cleanApertureWidthN_exists, "struct field cleanApertureWidthN does not exist");
		return cleanApertureWidthN_var;
	}
	uint32& cleanApertureWidthD() {
		assert_cond(cleanApertureWidthD_exists, "struct field cleanApertureWidthD does not exist");
		return cleanApertureWidthD_var;
	}
	uint32& cleanApertureHeightN() {
		assert_cond(cleanApertureHeightN_exists, "struct field cleanApertureHeightN does not exist");
		return cleanApertureHeightN_var;
	}
	uint32& cleanApertureHeightD() {
		assert_cond(cleanApertureHeightD_exists, "struct field cleanApertureHeightD does not exist");
		return cleanApertureHeightD_var;
	}
	int32& horizOffN() {
		assert_cond(horizOffN_exists, "struct field horizOffN does not exist");
		return horizOffN_var;
	}
	uint32& horizOffD() {
		assert_cond(horizOffD_exists, "struct field horizOffD does not exist");
		return horizOffD_var;
	}
	int32& vertOffN() {
		assert_cond(vertOffN_exists, "struct field vertOffN does not exist");
		return vertOffN_var;
	}
	uint32& vertOffD() {
		assert_cond(vertOffD_exists, "struct field vertOffD does not exist");
		return vertOffD_var;
	}
	std::string& colourType() {
		assert_cond(colourType_exists, "struct field colourType does not exist");
		return colourType_var;
	}
	uint16& colour_primaries() {
		assert_cond(colour_primaries_exists, "struct field colour_primaries does not exist");
		return colour_primaries_var;
	}
	uint16& transfer_characteristics() {
		assert_cond(transfer_characteristics_exists, "struct field transfer_characteristics does not exist");
		return transfer_characteristics_var;
	}
	uint16& matrix_coefficients() {
		assert_cond(matrix_coefficients_exists, "struct field matrix_coefficients does not exist");
		return matrix_coefficients_var;
	}
	byte& full_range_flag() {
		assert_cond(full_range_flag_exists, "struct field full_range_flag does not exist");
		return full_range_flag_var;
	}
	std::vector<byte>& icc_profile() {
		assert_cond(icc_profile_exists, "struct field icc_profile does not exist");
		return icc_profile_var;
	}
	uint16& channelcount() {
		assert_cond(channelcount_exists, "struct field channelcount does not exist");
		return channelcount_var;
	}
	uint16& samplesize() {
		assert_cond(samplesize_exists, "struct field samplesize does not exist");
		return samplesize_var;
	}
	uint32& samplerate() {
		assert_cond(samplerate_exists, "struct field samplerate does not exist");
		return samplerate_var;
	}
	std::vector<byte>& ES_Descriptor() {
		assert_cond(ES_Descriptor_exists, "struct field ES_Descriptor does not exist");
		return ES_Descriptor_var;
	}
	uint16& compression_id() {
		assert_cond(compression_id_exists, "struct field compression_id does not exist");
		return compression_id_var;
	}
	uint16& packet_size() {
		assert_cond(packet_size_exists, "struct field packet_size does not exist");
		return packet_size_var;
	}
	byte& outputChannelCount() {
		assert_cond(outputChannelCount_exists, "struct field outputChannelCount does not exist");
		return outputChannelCount_var;
	}
	uint16& preSkip() {
		assert_cond(preSkip_exists, "struct field preSkip does not exist");
		return preSkip_var;
	}
	uint32& inputSampleRate() {
		assert_cond(inputSampleRate_exists, "struct field inputSampleRate does not exist");
		return inputSampleRate_var;
	}
	int16& outputGain() {
		assert_cond(outputGain_exists, "struct field outputGain does not exist");
		return outputGain_var;
	}
	byte& channelMappingFamily() {
		assert_cond(channelMappingFamily_exists, "struct field channelMappingFamily does not exist");
		return channelMappingFamily_var;
	}
	byte& streamCount() {
		assert_cond(streamCount_exists, "struct field streamCount does not exist");
		return streamCount_var;
	}
	byte& coupledCount() {
		assert_cond(coupledCount_exists, "struct field coupledCount does not exist");
		return coupledCount_var;
	}
	std::vector<byte>& channelMapping() {
		assert_cond(channelMapping_exists, "struct field channelMapping does not exist");
		return channelMapping_var;
	}
	std::vector<byte>& flac_metadata() {
		assert_cond(flac_metadata_exists, "struct field flac_metadata does not exist");
		return flac_metadata_var;
	}
	std::vector<byte>& alac_specific_config() {
		assert_cond(alac_specific_config_exists, "struct field alac_specific_config does not exist");
		return alac_specific_config_var;
	}
	std::string& namespace_uri() {
		assert_cond(namespace_uri_exists, "struct field namespace_uri does not exist");
		return namespace_uri_var;
	}
	std::string& schema_location() {
		assert_cond(schema_location_exists, "struct field schema_location does not exist");
		return schema_location_var;
	}
	std::string& auxiliary_mime_types() {
		assert_cond(auxiliary_mime_types_exists, "struct field auxiliary_mime_types does not exist");
		return auxiliary_mime_types_var;
	}
	uint32& display_flags() {
		assert_cond(display_flags_exists, "struct field display_flags does not exist");
		return display_flags_var;
	}
	byte& horizontal_justification() {
		assert_cond(horizontal_justification_exists, "struct field horizontal_justification does not exist");
		return horizontal_justification_var;
	}
	byte& vertical_justification() {
		assert_cond(vertical_justification_exists, "struct field vertical_justification does not exist");
		return vertical_justification_var;
	}
	std::vector<byte>& background_color_rgba() {
		assert_cond(background_color_rgba_exists, "struct field background_color_rgba does not exist");
		return background_color_rgba_var;
	}
	int16& box_top() {
		assert_cond(box_top_exists, "struct field box_top does not exist");
		return box_top_var;
	}
	int16& box_left() {
		assert_cond(box_left_exists, "struct field box_left does not exist");
		return box_left_var;
	}
	int16& box_bottom() {
		assert_cond(box_bottom_exists, "struct field box_bottom does not exist");
		return box_bottom_var;
	}
	int16& box_right() {
		assert_cond(box_right_exists, "struct field box_right does not exist");
		return box_right_var;
	}
	uint16& startChar() {
		assert_cond(startChar_exists, "struct field startChar does not exist");
		return startChar_var;
	}
	uint16& endChar() {
		assert_cond(endChar_exists, "struct field endChar does not exist");
		return endChar_var;
	}
	uint16& font_ID() {
		assert_cond(font_ID_exists, "struct field font_ID does not exist");
		return font_ID_var;
	}
	byte& face_style_flags() {
		assert_cond(face_style_flags_exists, "struct field face_style_flags does not exist");
		return face_style_flags_var;
	}
	byte& font_size() {
		assert_cond(font_size_exists, "struct field font_size does not exist");
		return font_size_var;
	}
	std::vector<byte>& text_color_rgba() {
		assert_cond(text_color_rgba_exists, "struct field text_color_rgba does not exist");
		return text_color_rgba_var;
	}
	uint16& ftab_count() {
		assert_cond(ftab_count_exists, "struct field ftab_count does not exist");
		return ftab_count_var;
	}
	font_entry_struct& font_entry() {
		assert_cond(font_entry_exists, "struct field font_entry does not exist");
		return *font_entry_var;
	}
	std::string& content_encoding() {
		assert_cond(content_encoding_exists, "struct field content_encoding does not exist");
		return content_encoding_var;
	}
	std::string& mime_format() {
		assert_cond(mime_format_exists, "struct field mime_format does not exist");
		return mime_format_var;
	}
	std::string& xml_data() {
		assert_cond(xml_data_exists, "struct field xml_data does not exist");
		return xml_data_var;
	}
	std::string& data_format() {
		assert_cond(data_format_exists, "struct field data_format does not exist");
		return data_format_var;
	}
	std::string& scheme_type() {
		assert_cond(scheme_type_exists, "struct field scheme_type does not exist");
		return scheme_type_var;
	}
	uint32& scheme_version() {
		assert_cond(scheme_version_exists, "struct field scheme_version does not exist");
		return scheme_version_var;
	}
	std::string& scheme_uri() {
		assert_cond(scheme_uri_exists, "struct field scheme_uri does not exist");
		return scheme_uri_var;
	}
	byte& default_crypt_skip_byte_block() {
		assert_cond(default_crypt_skip_byte_block_exists, "struct field default_crypt_skip_byte_block does not exist");
		return default_crypt_skip_byte_block_var;
	}
	byte& default_isProtected() {
		assert_cond(default_isProtected_exists, "struct field default_isProtected does not exist");
		return default_isProtected_var;
	}
	byte& default_Per_Sample_IV_Size() {
		assert_cond(default_Per_Sample_IV_Size_exists, "struct field default_Per_Sample_IV_Size does not exist");
		return default_Per_Sample_IV_Size_var;
	}
	std::vector<byte>& default_KID() {
		assert_cond(default_KID_exists, "struct field default_KID does not exist");
		return default_KID_var;
	}
	byte& default_constant_IV_size() {
		assert_cond(default_constant_IV_size_exists, "struct field default_constant_IV_size does not exist");
		return default_constant_IV_size_var;
	}
	std::vector<byte>& default_constant_IV() {
		assert_cond(default_constant_IV_exists, "struct field default_constant_IV does not exist");
		return default_constant_IV_var;
	}
	std::vector<byte>& systemID() {
		assert_cond(systemID_exists, "struct field systemID does not exist");
		return systemID_var;
	}
	uint32& KID_count() {
		assert_cond(KID_count_exists, "struct field KID_count does not exist");
		return KID_count_var;
	}
	std::vector<byte>& KID() {
		assert_cond(KID_exists, "struct field KID does not exist");
		return KID_var;
	}
	uint32& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	std::vector<byte>& Data() {
		assert_cond(Data_exists, "struct field Data does not exist");
		return Data_var;
	}
	senc_entry_struct& senc_entry() {
		assert_cond(senc_entry_exists, "struct field senc_entry does not exist");
		return *senc_entry_var;
	}
	uint32& sequence_number() {
		assert_cond(sequence_number_exists, "struct field sequence_number does not exist");
		return sequence_number_var;
	}
	uint64& base_data_offset() {
		assert_cond(base_data_offset_exists, "struct field base_data_offset does not exist");
		return base_data_offset_var;
	}
	uint32& sample_description_index() {
		assert_cond(sample_description_index_exists, "struct field sample_description_index does not exist");
		return sample_description_index_var;
	}
	uint32& default_sample_duration() {
		assert_cond(default_sample_duration_exists, "struct field default_sample_duration does not exist");
		return default_sample_duration_var;
	}
	uint32& default_sample_size() {
		assert_cond(default_sample_size_exists, "struct field default_sample_size does not exist");
		return default_sample_size_var;
	}
	uint32& default_sample_flags() {
		assert_cond(default_sample_flags_exists, "struct field default_sample_flags does not exist");
		return default_sample_flags_var;
	}
	int32& data_offset() {
		assert_cond(data_offset_exists, "struct field data_offset does not exist");
		return data_offset_var;
	}
	uint32& first_sample_flags() {
		assert_cond(first_sample_flags_exists, "struct field first_sample_flags does not exist");
		return first_sample_flags_var;
	}
	trun_entry_struct& trun_entry() {
		assert_cond(trun_entry_exists, "struct field trun_entry does not exist");
		return *trun_entry_var;
	}
	uint32& aux_info_type() {
		assert_cond(aux_info_type_exists, "struct field aux_info_type does not exist");
		return aux_info_type_var;
	}
	uint32& aux_info_type_parameter() {
		assert_cond(aux_info_type_parameter_exists, "struct field aux_info_type_parameter does not exist");
		return aux_info_type_parameter_var;
	}
	byte& default_sample_info_size() {
		assert_cond(default_sample_info_size_exists, "struct field default_sample_info_size does not exist");
		return default_sample_info_size_var;
	}
	std::vector<byte>& sample_info_size() {
		assert_cond(sample_info_size_exists, "struct field sample_info_size does not exist");
		return sample_info_size_var;
	}
	uint32& saio_count() {
		assert_cond(saio_count_exists, "struct field saio_count does not exist");
		return saio_count_var;
	}
	uint32& reference_ID() {
		assert_cond(reference_ID_exists, "struct field reference_ID does not exist");
		return reference_ID_var;
	}
	uint16& reference_count() {
		assert_cond(reference_count_exists, "struct field reference_count does not exist");
		return reference_count_var;
	}
	std::vector<str_sidx*>& references() {
		assert_cond(references_exists, "struct field references does not exist");
		return references_var;
	}
	uint32& subsegment_count() {
		assert_cond(subsegment_count_exists, "struct field subsegment_count does not exist");
		return subsegment_count_var;
	}
	subsegment_struct& subsegment() {
		assert_cond(subsegment_exists, "struct field subsegment does not exist");
		return *subsegment_var;
	}
	uint32& reserved__and_lengths() {
		assert_cond(reserved__and_lengths_exists, "struct field reserved__and_lengths does not exist");
		return reserved__and_lengths_var;
	}
	uint32& number_of_entry() {
		assert_cond(number_of_entry_exists, "struct field number_of_entry does not exist");
		return number_of_entry_var;
	}
	std::vector<byte>& entry_data() {
		assert_cond(entry_data_exists, "struct field entry_data does not exist");
		return entry_data_var;
	}
	uint32& mfra_size() {
		assert_cond(mfra_size_exists, "struct field mfra_size does not exist");
		return mfra_size_var;
	}
	uint32& iinf_count() {
		assert_cond(iinf_count_exists, "struct field iinf_count does not exist");
		return iinf_count_var;
	}
	mp4box& infe_box() {
		assert_cond(infe_box_exists, "struct field infe_box does not exist");
		return *infe_box_var;
	}
	uint16& item_protection_index() {
		assert_cond(item_protection_index_exists, "struct field item_protection_index does not exist");
		return item_protection_index_var;
	}
	std::string& item_name() {
		assert_cond(item_name_exists, "struct field item_name does not exist");
		return item_name_var;
	}
	std::string& content_type() {
		assert_cond(content_type_exists, "struct field content_type does not exist");
		return content_type_var;
	}
	std::vector<byte>& item_type_bytes() {
		assert_cond(item_type_bytes_exists, "struct field item_type_bytes does not exist");
		return item_type_bytes_var;
	}
	std::string& item_uri_type() {
		assert_cond(item_uri_type_exists, "struct field item_uri_type does not exist");
		return item_uri_type_var;
	}
	byte& offset_length_sizes() {
		assert_cond(offset_length_sizes_exists, "struct field offset_length_sizes does not exist");
		return offset_length_sizes_var;
	}
	byte& baseoffset_index_sizes() {
		assert_cond(baseoffset_index_sizes_exists, "struct field baseoffset_index_sizes does not exist");
		return baseoffset_index_sizes_var;
	}
	uint32& iloc_item_count() {
		assert_cond(iloc_item_count_exists, "struct field iloc_item_count does not exist");
		return iloc_item_count_var;
	}
	std::vector<byte>& item_data() {
		assert_cond(item_data_exists, "struct field item_data does not exist");
		return item_data_var;
	}
	mp4box& ref_box() {
		assert_cond(ref_box_exists, "struct field ref_box does not exist");
		return *ref_box_var;
	}
	uint32& ipma_count() {
		assert_cond(ipma_count_exists, "struct field ipma_count does not exist");
		return ipma_count_var;
	}
	ipma_entry_struct& ipma_entry() {
		assert_cond(ipma_entry_exists, "struct field ipma_entry does not exist");
		return *ipma_entry_var;
	}
	uint16& protection_count() {
		assert_cond(protection_count_exists, "struct field protection_count does not exist");
		return protection_count_var;
	}
	mp4box& sinf_box() {
		assert_cond(sinf_box_exists, "struct field sinf_box does not exist");
		return *sinf_box_var;
	}
	uint16& num_components() {
		assert_cond(num_components_exists, "struct field num_components does not exist");
		return num_components_var;
	}
	byte& bits_per_component() {
		assert_cond(bits_per_component_exists, "struct field bits_per_component does not exist");
		return bits_per_component_var;
	}
	byte& compression_type() {
		assert_cond(compression_type_exists, "struct field compression_type does not exist");
		return compression_type_var;
	}
	byte& unknownColorspace() {
		assert_cond(unknownColorspace_exists, "struct field unknownColorspace does not exist");
		return unknownColorspace_var;
	}
	byte& intellectual_property() {
		assert_cond(intellectual_property_exists, "struct field intellectual_property does not exist");
		return intellectual_property_var;
	}
	std::string& scheme_id_uri() {
		assert_cond(scheme_id_uri_exists, "struct field scheme_id_uri does not exist");
		return scheme_id_uri_var;
	}
	uint32& presentation_time_delta() {
		assert_cond(presentation_time_delta_exists, "struct field presentation_time_delta does not exist");
		return presentation_time_delta_var;
	}
	uint32& event_duration() {
		assert_cond(event_duration_exists, "struct field event_duration does not exist");
		return event_duration_var;
	}
	uint32& id() {
		assert_cond(id_exists, "struct field id does not exist");
		return id_var;
	}
	uint64& presentation_time() {
		assert_cond(presentation_time_exists, "struct field presentation_time does not exist");
		return presentation_time_var;
	}
	std::vector<byte>& message_data() {
		assert_cond(message_data_exists, "struct field message_data does not exist");
		return message_data_var;
	}
	uint32& reference_track_ID() {
		assert_cond(reference_track_ID_exists, "struct field reference_track_ID does not exist");
		return reference_track_ID_var;
	}
	uint64& ntp_timestamp() {
		assert_cond(ntp_timestamp_exists, "struct field ntp_timestamp does not exist");
		return ntp_timestamp_var;
	}
	pdin_entry_struct& pdin_entry() {
		assert_cond(pdin_entry_exists, "struct field pdin_entry does not exist");
		return *pdin_entry_var;
	}
	std::string& extended_language() {
		assert_cond(extended_language_exists, "struct field extended_language does not exist");
		return extended_language_var;
	}
	std::string& schemeURI() {
		assert_cond(schemeURI_exists, "struct field schemeURI does not exist");
		return schemeURI_var;
	}
	std::vector<byte>& usertype() {
		assert_cond(usertype_exists, "struct field usertype does not exist");
		return usertype_var;
	}
	uint32& type_indicator() {
		assert_cond(type_indicator_exists, "struct field type_indicator does not exist");
		return type_indicator_var;
	}
	uint32& locale() {
		assert_cond(locale_exists, "struct field locale does not exist");
		return locale_var;
	}
	std::vector<byte>& aliasInfo() {
		assert_cond(aliasInfo_exists, "struct field aliasInfo does not exist");
		return aliasInfo_var;
	}
	std::vector<byte>& parameterSets() {
		assert_cond(parameterSets_exists, "struct field parameterSets does not exist");
		return parameterSets_var;
	}
	std::vector<byte>& subSampleInformation() {
		assert_cond(subSampleInformation_exists, "struct field subSampleInformation does not exist");
		return subSampleInformation_var;
	}
	std::vector<byte>& unknown() {
		assert_cond(unknown_exists, "struct field unknown does not exist");
		return unknown_var;
	}

	/* locals */
	uint64 startOffset;
	int tries;
	int64 endOffset;
	uint64 contentsize;
	int _clim1;
	std::string chunk_type;
	std::vector<std::string> preferred_blocks;
	std::vector<std::string> possible_blocks;
	int _blim_moov;
	std::vector<std::string> available_major_brands;
	std::string selected_major_brand;
	std::vector<std::string> compatiple_brands;
	std::vector<std::string> available_brands;
	std::string selected_brand;
	std::vector<std::string> compat_brands;
	int _blim_trak;
	int _blim_mdia;
	int _blim_edts;
	uint32 i;
	int _clim2;
	int _blim_meta;
	int _blim_minf;
	int _blim_dinf;
	int _blim_stbl;
	uint32 bytes_left;
	uint32 per_entry;
	int _clim3;
	byte numSPS;
	byte j;
	int _clim4;
	byte k;
	int _clim5;
	int _clim6;
	int _clim7;
	int _clim8;
	int _clim9;
	int _clim10;
	int _clim11;
	int _clim12;
	int _clim13;
	int _clim14;
	int _clim15;
	int _clim16;
	int _clim17;
	int _clim18;
	int _clim19;
	int _clim20;
	int _clim21;
	int _clim22;
	int _clim23;
	std::string it_str;
	int _clim24;
	int _clim25;
	int _clim26;
	int _clim27;
	uint32 parsedSize;
	uint64 writePosition;
	uint32 newSize;
	int evil;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp4box& operator () () { return *instances.back(); }
	mp4box& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp4box(std::vector<mp4box*>& instances) : instances(instances) { instances.push_back(this); }
	~mp4box() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp4box* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp4box* generate();
};

int mp4box::_parent_id = 0;
int mp4box::_index_start = 0;



class mp4file {
	std::vector<mp4file*>& instances;

	mp4box* ftyp_block_var;
	mp4box* mdat_block_var;
	mp4box* moov_block_var;
	mp4box* moof_block_var;
	mp4box* sidx_block_var;
	mp4box* ssix_block_var;
	mp4box* emsg_block_var;
	mp4box* pdin_block_var;
	mp4box* meta_block_var;
	mp4box* mfra_block_var;
	mp4box* prft_block_var;
	mp4box* uuid_block_var;
	mp4box* free_block_var;
	mp4box* unknown_block_var;

public:
	bool ftyp_block_exists = false;
	bool mdat_block_exists = false;
	bool moov_block_exists = false;
	bool moof_block_exists = false;
	bool sidx_block_exists = false;
	bool ssix_block_exists = false;
	bool emsg_block_exists = false;
	bool pdin_block_exists = false;
	bool meta_block_exists = false;
	bool mfra_block_exists = false;
	bool prft_block_exists = false;
	bool uuid_block_exists = false;
	bool free_block_exists = false;
	bool unknown_block_exists = false;

	mp4box& ftyp_block() {
		assert_cond(ftyp_block_exists, "struct field ftyp_block does not exist");
		return *ftyp_block_var;
	}
	mp4box& mdat_block() {
		assert_cond(mdat_block_exists, "struct field mdat_block does not exist");
		return *mdat_block_var;
	}
	mp4box& moov_block() {
		assert_cond(moov_block_exists, "struct field moov_block does not exist");
		return *moov_block_var;
	}
	mp4box& moof_block() {
		assert_cond(moof_block_exists, "struct field moof_block does not exist");
		return *moof_block_var;
	}
	mp4box& sidx_block() {
		assert_cond(sidx_block_exists, "struct field sidx_block does not exist");
		return *sidx_block_var;
	}
	mp4box& ssix_block() {
		assert_cond(ssix_block_exists, "struct field ssix_block does not exist");
		return *ssix_block_var;
	}
	mp4box& emsg_block() {
		assert_cond(emsg_block_exists, "struct field emsg_block does not exist");
		return *emsg_block_var;
	}
	mp4box& pdin_block() {
		assert_cond(pdin_block_exists, "struct field pdin_block does not exist");
		return *pdin_block_var;
	}
	mp4box& meta_block() {
		assert_cond(meta_block_exists, "struct field meta_block does not exist");
		return *meta_block_var;
	}
	mp4box& mfra_block() {
		assert_cond(mfra_block_exists, "struct field mfra_block does not exist");
		return *mfra_block_var;
	}
	mp4box& prft_block() {
		assert_cond(prft_block_exists, "struct field prft_block does not exist");
		return *prft_block_var;
	}
	mp4box& uuid_block() {
		assert_cond(uuid_block_exists, "struct field uuid_block does not exist");
		return *uuid_block_var;
	}
	mp4box& free_block() {
		assert_cond(free_block_exists, "struct field free_block does not exist");
		return *free_block_var;
	}
	mp4box& unknown_block() {
		assert_cond(unknown_block_exists, "struct field unknown_block does not exist");
		return *unknown_block_var;
	}

	/* locals */
	std::string chunk_type;
	std::vector<std::string> preferred_blocks;
	std::vector<std::string> possible_blocks;
	int _blim_file;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	mp4file& operator () () { return *instances.back(); }
	mp4file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	mp4file(std::vector<mp4file*>& instances) : instances(instances) { instances.push_back(this); }
	~mp4file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			mp4file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	mp4file* generate();
};

int mp4file::_parent_id = 0;
int mp4file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "ac-3", "ac-4", "alac", "alaw", "alst", "afra", "av01", "av1C", "avc1", "avc3", "avc4", "avcC", "bxml", "btrt", "cdsc", "clap", "co64", "colr", "cprt", "cslg", "ctts", "dac3", "data", "dec3", "dfLa", "dinf", "dnld", "dOps", "dref", "drms", "dtsc", "dtse", "dtsh", "dtsl", "dvcC", "dvav", "dvh1", "dvhe", "dvvc", "ec-3", "edts", "elng", "elst", "emsg", "enca", "encv", "eqiv", "esds", "fiin", "fire", "flac", "fLaC", "fpat", "fpar", "fprt", "free", "frma", "ftab", "ftap", "ftyp", "hdlr", "hev1", "hint", "hmhd", "hvc1", "hvcC", "idat", "ihdr", "iinf", "iloc", "ilst", "infe", "iods", "ipco", "ipma", "ipmc", "ipro", "iprp", "iref", "iso2", "isom", "jp2c", "kind", "lhdr", "mdat", "mdhd", "mdia", "meco", "mehd", "mere", "meta", "mfhd", "mfra", "mfro", "minf", "mmpu", "moof", "moov", "mp41", "mp42", "mp4a", "mp4s", "mp4v", "mp71", "msnv", "mvex", "mvhd", "nmhd", "Opus", "paen", "pasp", "pdam", "pdin", "pitm", "prft", "pssh", "pvc1", "saio", "saiz", "sbgp", "sbtl", "schi", "schm", "sdtp", "senc", "sgpd", "sidx", "sinf", "skip", "smhd", "soun", "ssix", "stbl", "stco", "stpp", "stsc", "stsd", "stsh", "stss", "stsz", "stts", "stxt", "stz2", "styp", "tenc", "tfdt", "tfhd", "tfra", "tkhd", "traf", "trak", "tref", "trep", "trex", "trun", "ttml", "tx3g", "udta", "ulaw", "url ", "urn ", "uuid", "vide", "vmhd", "wave", "wide", "wvtt", "xml " };


std::vector<fourcc*> fourcc_type_instances;
std::vector<mp4box*> mp4box_box_instances;
std::vector<mp4box*> mp4box_mvhd_block_instances;
std::vector<mp4box*> mp4box_trak_block_instances;
std::vector<mp4box*> mp4box_iods_block_instances;
std::vector<mp4box*> mp4box_udta_block_instances;
std::vector<mp4box*> mp4box_meta_block_instances;
std::vector<mp4box*> mp4box_mvex_block_instances;
std::vector<mp4box*> mp4box_unknown_block_instances;
std::vector<fp32*> fp32_rate_instances;
std::vector<fp16*> fp16_volume_instances;
std::vector<fp32*> fp32_a_instances;
std::vector<fp32*> fp32_b_instances;
std::vector<fp32uvw*> fp32uvw_u_instances;
std::vector<fp32*> fp32_c_instances;
std::vector<fp32*> fp32_d_instances;
std::vector<fp32uvw*> fp32uvw_v_instances;
std::vector<fp32*> fp32_x_instances;
std::vector<fp32*> fp32_y_instances;
std::vector<fp32uvw*> fp32uvw_w_instances;
std::vector<matrix*> matrix_matrix_structure_instances;
std::vector<mp4box*> mp4box_tkhd_block_instances;
std::vector<mp4box*> mp4box_mdia_block_instances;
std::vector<mp4box*> mp4box_edts_block_instances;
std::vector<mp4box*> mp4box_tref_block_instances;
std::vector<tkhd_flags*> tkhd_flags_tkhd_fl_instances;
std::vector<fp32*> fp32_width_instances;
std::vector<fp32*> fp32_height_instances;
std::vector<mp4box*> mp4box_mdhd_block_instances;
std::vector<mp4box*> mp4box_hdlr_block_instances;
std::vector<mp4box*> mp4box_minf_block_instances;
std::vector<mp4box*> mp4box_elng_block_instances;
std::vector<mp4lang*> mp4lang_language_instances;
std::vector<mp4box*> mp4box_child_block_instances;
std::vector<fp32*> fp32_media_rate_instances;
std::vector<elst_entry*> elst_entry_entries_instances;
std::vector<elst_entry_v1*> elst_entry_v1_entries__instances;
std::vector<mp4box*> mp4box_child_box_instances;
std::vector<mp4box*> mp4box_header_block_instances;
std::vector<mp4box*> mp4box_stbl_block_instances;
std::vector<mp4box*> mp4box_dinf_block_instances;
std::vector<vmhd_flags*> vmhd_flags_vmhd_fl_instances;
std::vector<qtopcolor*> qtopcolor_opcolor_instances;
std::vector<fp16*> fp16_balance_instances;
std::vector<mp4box*> mp4box_entry_box_instances;
std::vector<mp4box*> mp4box_sample_entry_instances;
std::vector<str_stts*> str_stts_entries___element_instances;
std::vector<str_ctts_v0*> str_ctts_v0_entries____element_instances;
std::vector<str_ctts_v1*> str_ctts_v1_entries_____element_instances;
std::vector<str_stsc*> str_stsc_entries______element_instances;
std::vector<str_stsh*> str_stsh_entries_______element_instances;
std::vector<entry_struct*> entry_struct_entry_instances;
std::vector<hevc_array_struct*> hevc_array_struct_hevc_array_instances;
std::vector<font_entry_struct*> font_entry_struct_font_entry_instances;
std::vector<senc_entry_struct_subsample_struct*> senc_entry_struct_subsample_struct_subsample_element_instances;
std::vector<senc_entry_struct*> senc_entry_struct_senc_entry_instances;
std::vector<trun_entry_struct*> trun_entry_struct_trun_entry_instances;
std::vector<str_sidx*> str_sidx_references_element_instances;
std::vector<subsegment_struct_range_struct*> subsegment_struct_range_struct_range_element_instances;
std::vector<subsegment_struct*> subsegment_struct_subsegment_instances;
std::vector<mp4box*> mp4box_infe_box_instances;
std::vector<mp4box*> mp4box_ref_box_instances;
std::vector<ipma_entry_struct*> ipma_entry_struct_ipma_entry_instances;
std::vector<mp4box*> mp4box_sinf_box_instances;
std::vector<pdin_entry_struct*> pdin_entry_struct_pdin_entry_instances;
std::vector<mp4box*> mp4box_ftyp_block_instances;
std::vector<mp4box*> mp4box_mdat_block_instances;
std::vector<mp4box*> mp4box_moov_block_instances;
std::vector<mp4box*> mp4box_moof_block_instances;
std::vector<mp4box*> mp4box_sidx_block_instances;
std::vector<mp4box*> mp4box_ssix_block_instances;
std::vector<mp4box*> mp4box_emsg_block_instances;
std::vector<mp4box*> mp4box_pdin_block_instances;
std::vector<mp4box*> mp4box_mfra_block_instances;
std::vector<mp4box*> mp4box_prft_block_instances;
std::vector<mp4box*> mp4box_uuid_block_instances;
std::vector<mp4box*> mp4box_free_block_instances;
std::vector<mp4file*> mp4file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "size", "uint32_class" }, { "value", "char_array_class" }, { "type", "fourcc" }, { "box", "mp4box" }, { "mvhd_block", "mp4box" }, { "trak_block", "mp4box" }, { "iods_block", "mp4box" }, { "udta_block", "mp4box" }, { "meta_block", "mp4box" }, { "mvex_block", "mp4box" }, { "unknown_block", "mp4box" }, { "major_brand", "char_array_class" }, { "minor_version", "uint32_class" }, { "compatible_brand", "char_array_class" }, { "version", "byte_class" }, { "flag", "byte_array_class" }, { "creation_time", "uint32_class" }, { "modification_time", "uint32_class" }, { "timescale", "uint32_class" }, { "duration", "uint32_class" }, { "creation_time_", "uint64_class" }, { "modification_time_", "uint64_class" }, { "duration_", "uint64_class" }, { "value_", "int32_class" }, { "rate", "fp32" }, { "value__", "int16_class" }, { "volume", "fp16" }, { "reserved_", "byte_array_class" }, { "a", "fp32" }, { "b", "fp32" }, { "u", "fp32uvw" }, { "c", "fp32" }, { "d", "fp32" }, { "v", "fp32uvw" }, { "x", "fp32" }, { "y", "fp32" }, { "w", "fp32uvw" }, { "matrix_structure", "matrix" }, { "pre_defined", "uint32_array_class" }, { "next_track_ID", "uint32_class" }, { "data", "byte_array_class" }, { "OD_data", "byte_array_class" }, { "tkhd_block", "mp4box" }, { "mdia_block", "mp4box" }, { "edts_block", "mp4box" }, { "tref_block", "mp4box" }, { "dummy", "byte_array_class" }, { "dummy2", "byte_bitfield" }, { "track_in_poster", "byte_bitfield" }, { "track_in_preview", "byte_bitfield" }, { "track_in_movie", "byte_bitfield" }, { "track_enabled", "byte_bitfield" }, { "tkhd_fl", "tkhd_flags" }, { "track_ID", "uint32_class" }, { "reserved__", "uint32_class" }, { "reserved_2", "uint64_class" }, { "layer", "int16_class" }, { "alternate_group", "int16_class" }, { "reserved_3", "uint16_class" }, { "width", "fp32" }, { "height", "fp32" }, { "mdhd_block", "mp4box" }, { "hdlr_block", "mp4box" }, { "minf_block", "mp4box" }, { "elng_block", "mp4box" }, { "value___", "uint16_class" }, { "language", "mp4lang" }, { "pre_defined_", "uint16_class" }, { "pre_defined__", "uint32_class" }, { "handler_type", "uint32_class" }, { "name", "byte_array_class" }, { "child_block", "mp4box" }, { "elst_count", "uint32_class" }, { "media_time", "uint32_class" }, { "media_rate", "fp32" }, { "entries", "elst_entry" }, { "segment_duration", "uint64_class" }, { "media_time_", "int64_class" }, { "media_rate_integer", "int16_class" }, { "media_rate_fraction", "int16_class" }, { "entries_", "elst_entry_v1" }, { "notice", "char_array_class" }, { "child_box", "mp4box" }, { "header_block", "mp4box" }, { "stbl_block", "mp4box" }, { "dinf_block", "mp4box" }, { "dummy2_", "byte_class" }, { "vmhd_fl", "vmhd_flags" }, { "graphics_mode", "qtgfxmode" }, { "red", "uint16_class" }, { "green", "uint16_class" }, { "blue", "uint16_class" }, { "opcolor", "qtopcolor" }, { "balance", "fp16" }, { "reserved___", "uint16_class" }, { "dref_count", "uint32_class" }, { "entry_box", "mp4box" }, { "location", "string_class" }, { "name_", "string_class" }, { "stsd_count", "uint32_class" }, { "sample_entry", "mp4box" }, { "stts_count", "uint32_class" }, { "sample_count", "uint32_class" }, { "sample_delta", "uint32_class" }, { "entries__", "str_stts_array_class" }, { "ctts_count", "uint32_class" }, { "sample_offset", "uint32_class" }, { "entries___", "str_ctts_v0_array_class" }, { "sample_offset_", "int32_class" }, { "entries____", "str_ctts_v1_array_class" }, { "stsc_count", "uint32_class" }, { "first_chunk", "uint32_class" }, { "samples_per_chunk", "uint32_class" }, { "sample_description_index", "uint32_class" }, { "entries_____", "str_stsc_array_class" }, { "sample_size", "uint32_class" }, { "entry_size", "uint32_array_class" }, { "reserved_stz2", "byte_array_class" }, { "field_size", "byte_class" }, { "entry_size_", "uint16_array_class" }, { "entry_size__", "byte_array_class" }, { "stco_count", "uint32_class" }, { "chunk_offset", "uint32_array_class" }, { "co64_count", "uint32_class" }, { "chunk_offset_", "uint64_array_class" }, { "stss_count", "uint32_class" }, { "sample_number", "uint32_array_class" }, { "stsh_count", "uint32_class" }, { "shadowed_sample_number", "uint32_class" }, { "sync_sample_number", "uint32_class" }, { "entries______", "str_stsh_array_class" }, { "sample_dependency_table", "byte_array_class" }, { "grouping_type", "uint32_class" }, { "grouping_type_parameter", "uint32_class" }, { "sbgp_count", "uint32_class" }, { "group_description_index", "uint32_class" }, { "entry", "entry_struct" }, { "default_length", "uint32_class" }, { "default_sample_description_index", "uint32_class" }, { "sgpd_count", "uint32_class" }, { "description_length", "uint32_class" }, { "description", "byte_array_class" }, { "compositionToDTSShift", "int32_class" }, { "leastDecodeToDisplayDelta", "int32_class" }, { "greatestDecodeToDisplayDelta", "int32_class" }, { "compositionStartTime", "int32_class" }, { "compositionEndTime", "int32_class" }, { "compositionToDTSShift_", "int64_class" }, { "leastDecodeToDisplayDelta_", "int64_class" }, { "greatestDecodeToDisplayDelta_", "int64_class" }, { "compositionStartTime_", "int64_class" }, { "compositionEndTime_", "int64_class" }, { "reserved_1", "byte_array_class" }, { "data_reference_index", "uint16_class" }, { "pre_defined1", "uint16_class" }, { "reserved_2_", "uint16_class" }, { "pre_defined2", "uint32_array_class" }, { "width_", "uint16_class" }, { "height_", "uint16_class" }, { "horizresolution", "uint32_class" }, { "vertresolution", "uint32_class" }, { "reserved_3_", "uint32_class" }, { "frame_count", "uint16_class" }, { "compressorname", "byte_array_class" }, { "depth", "uint16_class" }, { "pre_defined3", "int16_class" }, { "configurationVersion", "byte_class" }, { "AVCProfileIndication", "byte_class" }, { "profile_compatibility", "byte_class" }, { "AVCLevelIndication", "byte_class" }, { "lengthSizeMinusOne", "byte_class" }, { "numOfSequenceParameterSets", "byte_class" }, { "sequenceParameterSetLength", "uint16_class" }, { "sequenceParameterSetNALUnit", "byte_array_class" }, { "numOfPictureParameterSets", "byte_class" }, { "pictureParameterSetLength", "uint16_class" }, { "pictureParameterSetNALUnit", "byte_array_class" }, { "extra_data", "byte_array_class" }, { "general_profile_space_tier_idc", "byte_class" }, { "general_profile_compatibility_flags", "uint32_class" }, { "general_constraint_indicator_flag", "byte_array_class" }, { "general_level_idc", "byte_class" }, { "min_spatial_segmentation_idc", "uint16_class" }, { "parallelismType", "byte_class" }, { "chromaFormat", "byte_class" }, { "bitDepthLumaMinus8", "byte_class" }, { "bitDepthChromaMinus8", "byte_class" }, { "avgFrameRate", "uint16_class" }, { "constFR_numTempLayers_tidNested_lenSize", "byte_class" }, { "numOfArrays", "byte_class" }, { "array_completeness_and_NAL_unit_type", "byte_class" }, { "numNalus", "uint16_class" }, { "nalUnitLength", "uint16_class" }, { "nalUnit", "byte_array_class" }, { "hevc_array", "hevc_array_struct" }, { "marker_version", "byte_class" }, { "seq_profile_level", "byte_class" }, { "chroma_flags", "byte_class" }, { "delay_flags", "byte_class" }, { "configOBUs", "byte_array_class" }, { "dv_version_major", "byte_class" }, { "dv_version_minor", "byte_class" }, { "profile_level_flags", "uint16_class" }, { "bl_compat_and_reserved_", "uint32_class" }, { "reserved__data", "byte_array_class" }, { "bufferSizeDB", "uint32_class" }, { "maxBitrate", "uint32_class" }, { "avgBitrate", "uint32_class" }, { "hSpacing", "uint32_class" }, { "vSpacing", "uint32_class" }, { "cleanApertureWidthN", "uint32_class" }, { "cleanApertureWidthD", "uint32_class" }, { "cleanApertureHeightN", "uint32_class" }, { "cleanApertureHeightD", "uint32_class" }, { "horizOffN", "int32_class" }, { "horizOffD", "uint32_class" }, { "vertOffN", "int32_class" }, { "vertOffD", "uint32_class" }, { "colourType", "char_array_class" }, { "colour_primaries", "uint16_class" }, { "transfer_characteristics", "uint16_class" }, { "matrix_coefficients", "uint16_class" }, { "full_range_flag", "byte_class" }, { "icc_profile", "byte_array_class" }, { "reserved_2__", "byte_array_class" }, { "channelcount", "uint16_class" }, { "samplesize", "uint16_class" }, { "samplerate", "uint32_class" }, { "ES_Descriptor", "byte_array_class" }, { "compression_id", "uint16_class" }, { "packet_size", "uint16_class" }, { "outputChannelCount", "byte_class" }, { "preSkip", "uint16_class" }, { "inputSampleRate", "uint32_class" }, { "outputGain", "int16_class" }, { "channelMappingFamily", "byte_class" }, { "streamCount", "byte_class" }, { "coupledCount", "byte_class" }, { "channelMapping", "byte_array_class" }, { "flac_metadata", "byte_array_class" }, { "alac_specific_config", "byte_array_class" }, { "namespace_uri", "string_class" }, { "schema_location", "string_class" }, { "auxiliary_mime_types", "string_class" }, { "display_flags", "uint32_class" }, { "horizontal_justification", "byte_class" }, { "vertical_justification", "byte_class" }, { "background_color_rgba", "byte_array_class" }, { "box_top", "int16_class" }, { "box_left", "int16_class" }, { "box_bottom", "int16_class" }, { "box_right", "int16_class" }, { "startChar", "uint16_class" }, { "endChar", "uint16_class" }, { "font_ID", "uint16_class" }, { "face_style_flags", "byte_class" }, { "font_size", "byte_class" }, { "text_color_rgba", "byte_array_class" }, { "ftab_count", "uint16_class" }, { "font_name_length", "byte_class" }, { "font_name", "char_array_class" }, { "font_entry", "font_entry_struct" }, { "content_encoding", "string_class" }, { "mime_format", "string_class" }, { "xml_data", "char_array_class" }, { "data_format", "char_array_class" }, { "scheme_type", "char_array_class" }, { "scheme_version", "uint32_class" }, { "scheme_uri", "char_array_class" }, { "reserved_1_", "byte_class" }, { "reserved_2___", "byte_class" }, { "default_crypt_skip_byte_block", "byte_class" }, { "default_isProtected", "byte_class" }, { "default_Per_Sample_IV_Size", "byte_class" }, { "default_KID", "byte_array_class" }, { "default_constant_IV_size", "byte_class" }, { "default_constant_IV", "byte_array_class" }, { "systemID", "byte_array_class" }, { "KID_count", "uint32_class" }, { "KID", "byte_array_class" }, { "DataSize", "uint32_class" }, { "Data", "byte_array_class" }, { "per_sample_IV", "byte_array_class" }, { "subsample_count", "uint16_class" }, { "bytes_of_clear_data", "uint16_class" }, { "bytes_of_protected_data", "uint32_class" }, { "subsample", "senc_entry_struct_subsample_struct_array_class" }, { "senc_entry", "senc_entry_struct" }, { "sequence_number", "uint32_class" }, { "base_data_offset", "uint64_class" }, { "default_sample_duration", "uint32_class" }, { "default_sample_size", "uint32_class" }, { "default_sample_flags", "uint32_class" }, { "baseMediaDecodeTime", "uint32_class" }, { "baseMediaDecodeTime_", "uint64_class" }, { "data_offset", "int32_class" }, { "first_sample_flags", "uint32_class" }, { "sample_duration", "uint32_class" }, { "sample_flags", "uint32_class" }, { "sample_composition_time_offset", "uint32_class" }, { "sample_composition_time_offset_", "int32_class" }, { "trun_entry", "trun_entry_struct" }, { "fragment_duration", "uint32_class" }, { "fragment_duration_", "uint64_class" }, { "aux_info_type", "uint32_class" }, { "aux_info_type_parameter", "uint32_class" }, { "default_sample_info_size", "byte_class" }, { "sample_info_size", "byte_array_class" }, { "saio_count", "uint32_class" }, { "offset", "uint32_array_class" }, { "offset_", "uint64_array_class" }, { "reference_ID", "uint32_class" }, { "earliest_presentation_time", "uint32_class" }, { "first_offset", "uint32_class" }, { "earliest_presentation_time_", "uint64_class" }, { "first_offset_", "uint64_class" }, { "reference_count", "uint16_class" }, { "reference_size31_type1", "uint32_class" }, { "subsegment_duration", "uint32_class" }, { "SAP_delta_time28_type3_starts_with1", "uint32_class" }, { "references", "str_sidx_array_class" }, { "subsegment_count", "uint32_class" }, { "ranges_count", "uint32_class" }, { "level", "byte_class" }, { "range_size", "byte_array_class" }, { "range", "subsegment_struct_range_struct_array_class" }, { "subsegment", "subsegment_struct" }, { "reserved__and_lengths", "uint32_class" }, { "number_of_entry", "uint32_class" }, { "entry_data", "byte_array_class" }, { "mfra_size", "uint32_class" }, { "item_ID", "uint16_class" }, { "item_ID_", "uint32_class" }, { "iinf_count", "uint32_class" }, { "infe_box", "mp4box" }, { "item_protection_index", "uint16_class" }, { "item_name", "string_class" }, { "content_type", "string_class" }, { "item_type_bytes", "byte_array_class" }, { "item_uri_type", "string_class" }, { "offset_length_sizes", "byte_class" }, { "baseoffset_index_sizes", "byte_class" }, { "iloc_item_count", "uint32_class" }, { "item_data", "byte_array_class" }, { "ref_box", "mp4box" }, { "ipma_count", "uint32_class" }, { "association_count", "byte_class" }, { "property_index", "uint16_class" }, { "property_index_", "byte_class" }, { "ipma_entry", "ipma_entry_struct" }, { "protection_count", "uint16_class" }, { "sinf_box", "mp4box" }, { "height__", "uint32_class" }, { "width__", "uint32_class" }, { "num_components", "uint16_class" }, { "bits_per_component", "byte_class" }, { "compression_type", "byte_class" }, { "unknownColorspace", "byte_class" }, { "intellectual_property", "byte_class" }, { "scheme_id_uri", "string_class" }, { "value____", "string_class" }, { "presentation_time_delta", "uint32_class" }, { "event_duration", "uint32_class" }, { "id", "uint32_class" }, { "presentation_time", "uint64_class" }, { "message_data", "byte_array_class" }, { "reference_track_ID", "uint32_class" }, { "ntp_timestamp", "uint64_class" }, { "media_time__", "uint64_class" }, { "rate_", "uint32_class" }, { "initial_delay", "uint32_class" }, { "pdin_entry", "pdin_entry_struct" }, { "extended_language", "string_class" }, { "schemeURI", "string_class" }, { "usertype", "byte_array_class" }, { "type_indicator", "uint32_class" }, { "locale", "uint32_class" }, { "value_____", "byte_array_class" }, { "aliasInfo", "byte_array_class" }, { "parameterSets", "byte_array_class" }, { "subSampleInformation", "byte_array_class" }, { "unknown", "byte_array_class" }, { "ftyp_block", "mp4box" }, { "mdat_block", "mp4box" }, { "moov_block", "mp4box" }, { "moof_block", "mp4box" }, { "sidx_block", "mp4box" }, { "ssix_block", "mp4box" }, { "emsg_block", "mp4box" }, { "pdin_block", "mp4box" }, { "mfra_block", "mp4box" }, { "prft_block", "mp4box" }, { "uuid_block", "mp4box" }, { "free_block", "mp4box" }, { "file", "mp4file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	/*local*/ uint32 sharedSamplecountVar;
	/*local*/ uint32 mdatPosition;
	/*local*/ byte isVideo;
	uint32_class size;
	char_class value_element;
	char_array_class value;
	fourcc type;
	mp4box box;
	mp4box mvhd_block;
	mp4box trak_block;
	mp4box iods_block;
	mp4box udta_block;
	mp4box meta_block;
	mp4box mvex_block;
	mp4box unknown_block;
	char_class major_brand_element;
	char_array_class major_brand;
	uint32_class minor_version;
	char_class compatible_brand_element;
	char_array_class compatible_brand;
	byte_class version;
	byte_class flag_element;
	byte_array_class flag;
	uint32_class creation_time;
	uint32_class modification_time;
	uint32_class timescale;
	uint32_class duration;
	uint64_class creation_time_;
	uint64_class modification_time_;
	uint64_class duration_;
	int32_class value_;
	fp32 rate;
	int16_class value__;
	fp16 volume;
	byte_class reserved__element;
	byte_array_class reserved_;
	fp32 a;
	fp32 b;
	fp32uvw u;
	fp32 c;
	fp32 d;
	fp32uvw v;
	fp32 x;
	fp32 y;
	fp32uvw w;
	matrix matrix_structure;
	uint32_class pre_defined_element;
	uint32_array_class pre_defined;
	uint32_class next_track_ID;
	byte_class data_element;
	byte_array_class data;
	byte_class OD_data_element;
	byte_array_class OD_data;
	mp4box tkhd_block;
	mp4box mdia_block;
	mp4box edts_block;
	mp4box tref_block;
	byte_class dummy_element;
	byte_array_class dummy;
	byte_bitfield dummy2;
	byte_bitfield track_in_poster;
	byte_bitfield track_in_preview;
	byte_bitfield track_in_movie;
	byte_bitfield track_enabled;
	tkhd_flags tkhd_fl;
	uint32_class track_ID;
	uint32_class reserved__;
	uint64_class reserved_2;
	int16_class layer;
	int16_class alternate_group;
	uint16_class reserved_3;
	fp32 width;
	fp32 height;
	mp4box mdhd_block;
	mp4box hdlr_block;
	mp4box minf_block;
	mp4box elng_block;
	uint16_class value___;
	mp4lang language;
	uint16_class pre_defined_;
	uint32_class pre_defined__;
	uint32_class handler_type;
	byte_class name_element;
	byte_array_class name;
	mp4box child_block;
	uint32_class elst_count;
	uint32_class media_time;
	fp32 media_rate;
	elst_entry entries;
	uint64_class segment_duration;
	int64_class media_time_;
	int16_class media_rate_integer;
	int16_class media_rate_fraction;
	elst_entry_v1 entries_;
	char_class notice_element;
	char_array_class notice;
	mp4box child_box;
	mp4box header_block;
	mp4box stbl_block;
	mp4box dinf_block;
	byte_class dummy2_;
	vmhd_flags vmhd_fl;
	uint16_class red;
	uint16_class green;
	uint16_class blue;
	qtopcolor opcolor;
	fp16 balance;
	uint16_class reserved___;
	uint32_class dref_count;
	mp4box entry_box;
	string_class location;
	string_class name_;
	uint32_class stsd_count;
	mp4box sample_entry;
	uint32_class stts_count;
	uint32_class sample_count;
	uint32_class sample_delta;
	str_stts entries___element;
	str_stts_array_class entries__;
	uint32_class ctts_count;
	uint32_class sample_offset;
	str_ctts_v0 entries____element;
	str_ctts_v0_array_class entries___;
	int32_class sample_offset_;
	str_ctts_v1 entries_____element;
	str_ctts_v1_array_class entries____;
	uint32_class stsc_count;
	uint32_class first_chunk;
	uint32_class samples_per_chunk;
	uint32_class sample_description_index;
	str_stsc entries______element;
	str_stsc_array_class entries_____;
	uint32_class sample_size;
	uint32_class entry_size_element;
	uint32_array_class entry_size;
	byte_class reserved_stz2_element;
	byte_array_class reserved_stz2;
	byte_class field_size;
	uint16_class entry_size__element;
	uint16_array_class entry_size_;
	byte_class entry_size___element;
	byte_array_class entry_size__;
	uint32_class stco_count;
	uint32_class chunk_offset_element;
	uint32_array_class chunk_offset;
	uint32_class co64_count;
	uint64_class chunk_offset__element;
	uint64_array_class chunk_offset_;
	uint32_class stss_count;
	uint32_class sample_number_element;
	uint32_array_class sample_number;
	uint32_class stsh_count;
	uint32_class shadowed_sample_number;
	uint32_class sync_sample_number;
	str_stsh entries_______element;
	str_stsh_array_class entries______;
	byte_class sample_dependency_table_element;
	byte_array_class sample_dependency_table;
	uint32_class grouping_type;
	uint32_class grouping_type_parameter;
	uint32_class sbgp_count;
	uint32_class group_description_index;
	entry_struct entry;
	uint32_class default_length;
	uint32_class default_sample_description_index;
	uint32_class sgpd_count;
	uint32_class description_length;
	byte_class description_element;
	byte_array_class description;
	int32_class compositionToDTSShift;
	int32_class leastDecodeToDisplayDelta;
	int32_class greatestDecodeToDisplayDelta;
	int32_class compositionStartTime;
	int32_class compositionEndTime;
	int64_class compositionToDTSShift_;
	int64_class leastDecodeToDisplayDelta_;
	int64_class greatestDecodeToDisplayDelta_;
	int64_class compositionStartTime_;
	int64_class compositionEndTime_;
	byte_class reserved_1_element;
	byte_array_class reserved_1;
	uint16_class data_reference_index;
	uint16_class pre_defined1;
	uint16_class reserved_2_;
	uint32_class pre_defined2_element;
	uint32_array_class pre_defined2;
	uint16_class width_;
	uint16_class height_;
	uint32_class horizresolution;
	uint32_class vertresolution;
	uint32_class reserved_3_;
	uint16_class frame_count;
	byte_class compressorname_element;
	byte_array_class compressorname;
	uint16_class depth;
	int16_class pre_defined3;
	byte_class configurationVersion;
	byte_class AVCProfileIndication;
	byte_class profile_compatibility;
	byte_class AVCLevelIndication;
	byte_class lengthSizeMinusOne;
	byte_class numOfSequenceParameterSets;
	uint16_class sequenceParameterSetLength;
	byte_class sequenceParameterSetNALUnit_element;
	byte_array_class sequenceParameterSetNALUnit;
	byte_class numOfPictureParameterSets;
	uint16_class pictureParameterSetLength;
	byte_class pictureParameterSetNALUnit_element;
	byte_array_class pictureParameterSetNALUnit;
	byte_class extra_data_element;
	byte_array_class extra_data;
	byte_class general_profile_space_tier_idc;
	uint32_class general_profile_compatibility_flags;
	byte_class general_constraint_indicator_flag_element;
	byte_array_class general_constraint_indicator_flag;
	byte_class general_level_idc;
	uint16_class min_spatial_segmentation_idc;
	byte_class parallelismType;
	byte_class chromaFormat;
	byte_class bitDepthLumaMinus8;
	byte_class bitDepthChromaMinus8;
	uint16_class avgFrameRate;
	byte_class constFR_numTempLayers_tidNested_lenSize;
	byte_class numOfArrays;
	byte_class array_completeness_and_NAL_unit_type;
	uint16_class numNalus;
	uint16_class nalUnitLength;
	byte_class nalUnit_element;
	byte_array_class nalUnit;
	hevc_array_struct hevc_array;
	byte_class marker_version;
	byte_class seq_profile_level;
	byte_class chroma_flags;
	byte_class delay_flags;
	byte_class configOBUs_element;
	byte_array_class configOBUs;
	byte_class dv_version_major;
	byte_class dv_version_minor;
	uint16_class profile_level_flags;
	uint32_class bl_compat_and_reserved_;
	byte_class reserved__data_element;
	byte_array_class reserved__data;
	uint32_class bufferSizeDB;
	uint32_class maxBitrate;
	uint32_class avgBitrate;
	uint32_class hSpacing;
	uint32_class vSpacing;
	uint32_class cleanApertureWidthN;
	uint32_class cleanApertureWidthD;
	uint32_class cleanApertureHeightN;
	uint32_class cleanApertureHeightD;
	int32_class horizOffN;
	uint32_class horizOffD;
	int32_class vertOffN;
	uint32_class vertOffD;
	char_class colourType_element;
	char_array_class colourType;
	uint16_class colour_primaries;
	uint16_class transfer_characteristics;
	uint16_class matrix_coefficients;
	byte_class full_range_flag;
	byte_class icc_profile_element;
	byte_array_class icc_profile;
	byte_class reserved_2___element;
	byte_array_class reserved_2__;
	uint16_class channelcount;
	uint16_class samplesize;
	uint32_class samplerate;
	byte_class ES_Descriptor_element;
	byte_array_class ES_Descriptor;
	uint16_class compression_id;
	uint16_class packet_size;
	byte_class outputChannelCount;
	uint16_class preSkip;
	uint32_class inputSampleRate;
	int16_class outputGain;
	byte_class channelMappingFamily;
	byte_class streamCount;
	byte_class coupledCount;
	byte_class channelMapping_element;
	byte_array_class channelMapping;
	byte_class flac_metadata_element;
	byte_array_class flac_metadata;
	byte_class alac_specific_config_element;
	byte_array_class alac_specific_config;
	string_class namespace_uri;
	string_class schema_location;
	string_class auxiliary_mime_types;
	uint32_class display_flags;
	byte_class horizontal_justification;
	byte_class vertical_justification;
	byte_class background_color_rgba_element;
	byte_array_class background_color_rgba;
	int16_class box_top;
	int16_class box_left;
	int16_class box_bottom;
	int16_class box_right;
	uint16_class startChar;
	uint16_class endChar;
	uint16_class font_ID;
	byte_class face_style_flags;
	byte_class font_size;
	byte_class text_color_rgba_element;
	byte_array_class text_color_rgba;
	uint16_class ftab_count;
	byte_class font_name_length;
	char_class font_name_element;
	char_array_class font_name;
	font_entry_struct font_entry;
	string_class content_encoding;
	string_class mime_format;
	char_class xml_data_element;
	char_array_class xml_data;
	char_class data_format_element;
	char_array_class data_format;
	char_class scheme_type_element;
	char_array_class scheme_type;
	uint32_class scheme_version;
	char_class scheme_uri_element;
	char_array_class scheme_uri;
	byte_class reserved_1_;
	byte_class reserved_2___;
	byte_class default_crypt_skip_byte_block;
	byte_class default_isProtected;
	byte_class default_Per_Sample_IV_Size;
	byte_class default_KID_element;
	byte_array_class default_KID;
	byte_class default_constant_IV_size;
	byte_class default_constant_IV_element;
	byte_array_class default_constant_IV;
	byte_class systemID_element;
	byte_array_class systemID;
	uint32_class KID_count;
	byte_class KID_element;
	byte_array_class KID;
	uint32_class DataSize;
	byte_class Data_element;
	byte_array_class Data;
	byte_class per_sample_IV_element;
	byte_array_class per_sample_IV;
	uint16_class subsample_count;
	uint16_class bytes_of_clear_data;
	uint32_class bytes_of_protected_data;
	senc_entry_struct_subsample_struct subsample_element;
	senc_entry_struct_subsample_struct_array_class subsample;
	senc_entry_struct senc_entry;
	uint32_class sequence_number;
	uint64_class base_data_offset;
	uint32_class default_sample_duration;
	uint32_class default_sample_size;
	uint32_class default_sample_flags;
	uint32_class baseMediaDecodeTime;
	uint64_class baseMediaDecodeTime_;
	int32_class data_offset;
	uint32_class first_sample_flags;
	uint32_class sample_duration;
	uint32_class sample_flags;
	uint32_class sample_composition_time_offset;
	int32_class sample_composition_time_offset_;
	trun_entry_struct trun_entry;
	uint32_class fragment_duration;
	uint64_class fragment_duration_;
	uint32_class aux_info_type;
	uint32_class aux_info_type_parameter;
	byte_class default_sample_info_size;
	byte_class sample_info_size_element;
	byte_array_class sample_info_size;
	uint32_class saio_count;
	uint32_class offset_element;
	uint32_array_class offset;
	uint64_class offset__element;
	uint64_array_class offset_;
	uint32_class reference_ID;
	uint32_class earliest_presentation_time;
	uint32_class first_offset;
	uint64_class earliest_presentation_time_;
	uint64_class first_offset_;
	uint16_class reference_count;
	uint32_class reference_size31_type1;
	uint32_class subsegment_duration;
	uint32_class SAP_delta_time28_type3_starts_with1;
	str_sidx references_element;
	str_sidx_array_class references;
	uint32_class subsegment_count;
	uint32_class ranges_count;
	byte_class level;
	byte_class range_size_element;
	byte_array_class range_size;
	subsegment_struct_range_struct range_element;
	subsegment_struct_range_struct_array_class range;
	subsegment_struct subsegment;
	uint32_class reserved__and_lengths;
	uint32_class number_of_entry;
	byte_class entry_data_element;
	byte_array_class entry_data;
	uint32_class mfra_size;
	uint16_class item_ID;
	uint32_class item_ID_;
	uint32_class iinf_count;
	mp4box infe_box;
	uint16_class item_protection_index;
	string_class item_name;
	string_class content_type;
	byte_class item_type_bytes_element;
	byte_array_class item_type_bytes;
	string_class item_uri_type;
	byte_class offset_length_sizes;
	byte_class baseoffset_index_sizes;
	uint32_class iloc_item_count;
	byte_class item_data_element;
	byte_array_class item_data;
	mp4box ref_box;
	uint32_class ipma_count;
	byte_class association_count;
	uint16_class property_index;
	byte_class property_index_;
	ipma_entry_struct ipma_entry;
	uint16_class protection_count;
	mp4box sinf_box;
	uint32_class height__;
	uint32_class width__;
	uint16_class num_components;
	byte_class bits_per_component;
	byte_class compression_type;
	byte_class unknownColorspace;
	byte_class intellectual_property;
	string_class scheme_id_uri;
	string_class value____;
	uint32_class presentation_time_delta;
	uint32_class event_duration;
	uint32_class id;
	uint64_class presentation_time;
	byte_class message_data_element;
	byte_array_class message_data;
	uint32_class reference_track_ID;
	uint64_class ntp_timestamp;
	uint64_class media_time__;
	uint32_class rate_;
	uint32_class initial_delay;
	pdin_entry_struct pdin_entry;
	string_class extended_language;
	string_class schemeURI;
	byte_class usertype_element;
	byte_array_class usertype;
	uint32_class type_indicator;
	uint32_class locale;
	byte_class value______element;
	byte_array_class value_____;
	byte_class aliasInfo_element;
	byte_array_class aliasInfo;
	byte_class parameterSets_element;
	byte_array_class parameterSets;
	byte_class subSampleInformation_element;
	byte_array_class subSampleInformation;
	byte_class unknown_element;
	byte_array_class unknown;
	mp4box ftyp_block;
	mp4box mdat_block;
	mp4box moov_block;
	mp4box moof_block;
	mp4box sidx_block;
	mp4box ssix_block;
	mp4box emsg_block;
	mp4box pdin_block;
	mp4box mfra_block;
	mp4box prft_block;
	mp4box uuid_block;
	mp4box free_block;
	mp4file file;


	globals_class() :
		size(1),
		value_element(false),
		value(value_element),
		type(fourcc_type_instances),
		box(mp4box_box_instances),
		mvhd_block(mp4box_mvhd_block_instances),
		trak_block(mp4box_trak_block_instances),
		iods_block(mp4box_iods_block_instances),
		udta_block(mp4box_udta_block_instances),
		meta_block(mp4box_meta_block_instances),
		mvex_block(mp4box_mvex_block_instances),
		unknown_block(mp4box_unknown_block_instances),
		major_brand_element(false),
		major_brand(major_brand_element),
		minor_version(1),
		compatible_brand_element(false),
		compatible_brand(compatible_brand_element),
		version(1, { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0 }),
		flag_element(false),
		flag(flag_element),
		creation_time(1),
		modification_time(1),
		timescale(1),
		duration(1),
		creation_time_(1),
		modification_time_(1),
		duration_(1),
		value_(1),
		rate(fp32_rate_instances),
		value__(1),
		volume(fp16_volume_instances),
		reserved__element(false),
		reserved_(reserved__element),
		a(fp32_a_instances),
		b(fp32_b_instances),
		u(fp32uvw_u_instances),
		c(fp32_c_instances),
		d(fp32_d_instances),
		v(fp32uvw_v_instances),
		x(fp32_x_instances),
		y(fp32_y_instances),
		w(fp32uvw_w_instances),
		matrix_structure(matrix_matrix_structure_instances),
		pre_defined_element(false),
		pre_defined(pre_defined_element),
		next_track_ID(1),
		data_element(false),
		data(data_element),
		OD_data_element(false),
		OD_data(OD_data_element),
		tkhd_block(mp4box_tkhd_block_instances),
		mdia_block(mp4box_mdia_block_instances),
		edts_block(mp4box_edts_block_instances),
		tref_block(mp4box_tref_block_instances),
		dummy_element(false),
		dummy(dummy_element),
		dummy2(1),
		track_in_poster(1),
		track_in_preview(1),
		track_in_movie(1),
		track_enabled(1),
		tkhd_fl(tkhd_flags_tkhd_fl_instances),
		track_ID(1),
		reserved__(1),
		reserved_2(1),
		layer(1),
		alternate_group(1),
		reserved_3(1),
		width(fp32_width_instances),
		height(fp32_height_instances),
		mdhd_block(mp4box_mdhd_block_instances),
		hdlr_block(mp4box_hdlr_block_instances),
		minf_block(mp4box_minf_block_instances),
		elng_block(mp4box_elng_block_instances),
		value___(1),
		language(mp4lang_language_instances),
		pre_defined_(1),
		pre_defined__(1),
		handler_type(1),
		name_element(false),
		name(name_element),
		child_block(mp4box_child_block_instances),
		elst_count(1),
		media_time(1),
		media_rate(fp32_media_rate_instances),
		entries(elst_entry_entries_instances),
		segment_duration(1),
		media_time_(1),
		media_rate_integer(1),
		media_rate_fraction(1),
		entries_(elst_entry_v1_entries__instances),
		notice_element(false),
		notice(notice_element),
		child_box(mp4box_child_box_instances),
		header_block(mp4box_header_block_instances),
		stbl_block(mp4box_stbl_block_instances),
		dinf_block(mp4box_dinf_block_instances),
		dummy2_(1),
		vmhd_fl(vmhd_flags_vmhd_fl_instances),
		red(1),
		green(1),
		blue(1),
		opcolor(qtopcolor_opcolor_instances),
		balance(fp16_balance_instances),
		reserved___(1),
		dref_count(1),
		entry_box(mp4box_entry_box_instances),
		stsd_count(1),
		sample_entry(mp4box_sample_entry_instances),
		stts_count(1),
		sample_count(1),
		sample_delta(1),
		entries___element(str_stts_entries___element_instances),
		entries__(entries___element),
		ctts_count(1),
		sample_offset(1),
		entries____element(str_ctts_v0_entries____element_instances),
		entries___(entries____element),
		sample_offset_(1),
		entries_____element(str_ctts_v1_entries_____element_instances),
		entries____(entries_____element),
		stsc_count(1),
		first_chunk(1),
		samples_per_chunk(1),
		sample_description_index(1),
		entries______element(str_stsc_entries______element_instances),
		entries_____(entries______element),
		sample_size(1, { 0 }),
		entry_size_element(false),
		entry_size(entry_size_element),
		reserved_stz2_element(false),
		reserved_stz2(reserved_stz2_element),
		field_size(1, { 16, 8, 4 }),
		entry_size__element(false),
		entry_size_(entry_size__element),
		entry_size___element(false),
		entry_size__(entry_size___element),
		stco_count(1),
		chunk_offset_element(false),
		chunk_offset(chunk_offset_element),
		co64_count(1),
		chunk_offset__element(false),
		chunk_offset_(chunk_offset__element),
		stss_count(1),
		sample_number_element(false),
		sample_number(sample_number_element),
		stsh_count(1),
		shadowed_sample_number(1),
		sync_sample_number(1),
		entries_______element(str_stsh_entries_______element_instances),
		entries______(entries_______element),
		sample_dependency_table_element(false),
		sample_dependency_table(sample_dependency_table_element),
		grouping_type(1),
		grouping_type_parameter(1),
		sbgp_count(1),
		group_description_index(1),
		entry(entry_struct_entry_instances),
		default_length(1, { 0 }),
		default_sample_description_index(1),
		sgpd_count(1),
		description_length(1),
		description_element(false),
		description(description_element),
		compositionToDTSShift(1),
		leastDecodeToDisplayDelta(1),
		greatestDecodeToDisplayDelta(1),
		compositionStartTime(1),
		compositionEndTime(1),
		compositionToDTSShift_(1),
		leastDecodeToDisplayDelta_(1),
		greatestDecodeToDisplayDelta_(1),
		compositionStartTime_(1),
		compositionEndTime_(1),
		reserved_1_element(false),
		reserved_1(reserved_1_element),
		data_reference_index(1),
		pre_defined1(1),
		reserved_2_(1),
		pre_defined2_element(false),
		pre_defined2(pre_defined2_element),
		width_(1),
		height_(1),
		horizresolution(1),
		vertresolution(1),
		reserved_3_(1),
		frame_count(1),
		compressorname_element(false),
		compressorname(compressorname_element),
		depth(1),
		pre_defined3(1),
		configurationVersion(1),
		AVCProfileIndication(1),
		profile_compatibility(1),
		AVCLevelIndication(1),
		lengthSizeMinusOne(1),
		numOfSequenceParameterSets(1),
		sequenceParameterSetLength(1),
		sequenceParameterSetNALUnit_element(false),
		sequenceParameterSetNALUnit(sequenceParameterSetNALUnit_element),
		numOfPictureParameterSets(1),
		pictureParameterSetLength(1),
		pictureParameterSetNALUnit_element(false),
		pictureParameterSetNALUnit(pictureParameterSetNALUnit_element),
		extra_data_element(false),
		extra_data(extra_data_element),
		general_profile_space_tier_idc(1),
		general_profile_compatibility_flags(1),
		general_constraint_indicator_flag_element(false),
		general_constraint_indicator_flag(general_constraint_indicator_flag_element),
		general_level_idc(1),
		min_spatial_segmentation_idc(1),
		parallelismType(1),
		chromaFormat(1),
		bitDepthLumaMinus8(1),
		bitDepthChromaMinus8(1),
		avgFrameRate(1),
		constFR_numTempLayers_tidNested_lenSize(1),
		numOfArrays(1),
		array_completeness_and_NAL_unit_type(1),
		numNalus(1),
		nalUnitLength(1),
		nalUnit_element(false),
		nalUnit(nalUnit_element),
		hevc_array(hevc_array_struct_hevc_array_instances),
		marker_version(1),
		seq_profile_level(1),
		chroma_flags(1),
		delay_flags(1),
		configOBUs_element(false),
		configOBUs(configOBUs_element),
		dv_version_major(1),
		dv_version_minor(1),
		profile_level_flags(1),
		bl_compat_and_reserved_(1),
		reserved__data_element(false),
		reserved__data(reserved__data_element),
		bufferSizeDB(1),
		maxBitrate(1),
		avgBitrate(1),
		hSpacing(1),
		vSpacing(1),
		cleanApertureWidthN(1),
		cleanApertureWidthD(1),
		cleanApertureHeightN(1),
		cleanApertureHeightD(1),
		horizOffN(1),
		horizOffD(1),
		vertOffN(1),
		vertOffD(1),
		colourType_element(false),
		colourType(colourType_element, { "nclx", "nclc", "nclx" }),
		colour_primaries(1),
		transfer_characteristics(1),
		matrix_coefficients(1),
		full_range_flag(1),
		icc_profile_element(false),
		icc_profile(icc_profile_element),
		reserved_2___element(false),
		reserved_2__(reserved_2___element),
		channelcount(1),
		samplesize(1),
		samplerate(1),
		ES_Descriptor_element(false),
		ES_Descriptor(ES_Descriptor_element),
		compression_id(1),
		packet_size(1),
		outputChannelCount(1),
		preSkip(1),
		inputSampleRate(1),
		outputGain(1),
		channelMappingFamily(1, { 0 }),
		streamCount(1),
		coupledCount(1),
		channelMapping_element(false),
		channelMapping(channelMapping_element),
		flac_metadata_element(false),
		flac_metadata(flac_metadata_element),
		alac_specific_config_element(false),
		alac_specific_config(alac_specific_config_element),
		display_flags(1),
		horizontal_justification(1),
		vertical_justification(1),
		background_color_rgba_element(false),
		background_color_rgba(background_color_rgba_element),
		box_top(1),
		box_left(1),
		box_bottom(1),
		box_right(1),
		startChar(1),
		endChar(1),
		font_ID(1),
		face_style_flags(1),
		font_size(1),
		text_color_rgba_element(false),
		text_color_rgba(text_color_rgba_element),
		ftab_count(1),
		font_name_length(1),
		font_name_element(false),
		font_name(font_name_element),
		font_entry(font_entry_struct_font_entry_instances),
		xml_data_element(false),
		xml_data(xml_data_element),
		data_format_element(false),
		data_format(data_format_element),
		scheme_type_element(false),
		scheme_type(scheme_type_element),
		scheme_version(1),
		scheme_uri_element(false),
		scheme_uri(scheme_uri_element),
		reserved_1_(1),
		reserved_2___(1),
		default_crypt_skip_byte_block(1),
		default_isProtected(1),
		default_Per_Sample_IV_Size(1, { 0 }),
		default_KID_element(false),
		default_KID(default_KID_element),
		default_constant_IV_size(1),
		default_constant_IV_element(false),
		default_constant_IV(default_constant_IV_element),
		systemID_element(false),
		systemID(systemID_element),
		KID_count(1),
		KID_element(false),
		KID(KID_element),
		DataSize(1),
		Data_element(false),
		Data(Data_element),
		per_sample_IV_element(false),
		per_sample_IV(per_sample_IV_element),
		subsample_count(1),
		bytes_of_clear_data(1),
		bytes_of_protected_data(1),
		subsample_element(senc_entry_struct_subsample_struct_subsample_element_instances),
		subsample(subsample_element),
		senc_entry(senc_entry_struct_senc_entry_instances),
		sequence_number(1),
		base_data_offset(1),
		default_sample_duration(1),
		default_sample_size(1),
		default_sample_flags(1),
		baseMediaDecodeTime(1),
		baseMediaDecodeTime_(1),
		data_offset(1),
		first_sample_flags(1),
		sample_duration(1),
		sample_flags(1),
		sample_composition_time_offset(1),
		sample_composition_time_offset_(1),
		trun_entry(trun_entry_struct_trun_entry_instances),
		fragment_duration(1),
		fragment_duration_(1),
		aux_info_type(1),
		aux_info_type_parameter(1),
		default_sample_info_size(1, { 0 }),
		sample_info_size_element(false),
		sample_info_size(sample_info_size_element),
		saio_count(1),
		offset_element(false),
		offset(offset_element),
		offset__element(false),
		offset_(offset__element),
		reference_ID(1),
		earliest_presentation_time(1),
		first_offset(1),
		earliest_presentation_time_(1),
		first_offset_(1),
		reference_count(1),
		reference_size31_type1(1),
		subsegment_duration(1),
		SAP_delta_time28_type3_starts_with1(1),
		references_element(str_sidx_references_element_instances),
		references(references_element),
		subsegment_count(1),
		ranges_count(1),
		level(1),
		range_size_element(false),
		range_size(range_size_element),
		range_element(subsegment_struct_range_struct_range_element_instances),
		range(range_element),
		subsegment(subsegment_struct_subsegment_instances),
		reserved__and_lengths(1),
		number_of_entry(1),
		entry_data_element(false),
		entry_data(entry_data_element),
		mfra_size(1),
		item_ID(1),
		item_ID_(1),
		iinf_count(1),
		infe_box(mp4box_infe_box_instances),
		item_protection_index(1),
		item_type_bytes_element(false),
		item_type_bytes(item_type_bytes_element),
		offset_length_sizes(1),
		baseoffset_index_sizes(1),
		iloc_item_count(1),
		item_data_element(false),
		item_data(item_data_element),
		ref_box(mp4box_ref_box_instances),
		ipma_count(1),
		association_count(1),
		property_index(1),
		property_index_(1),
		ipma_entry(ipma_entry_struct_ipma_entry_instances),
		protection_count(1),
		sinf_box(mp4box_sinf_box_instances),
		height__(1),
		width__(1),
		num_components(1),
		bits_per_component(1),
		compression_type(1),
		unknownColorspace(1),
		intellectual_property(1),
		presentation_time_delta(1),
		event_duration(1),
		id(1),
		presentation_time(1),
		message_data_element(false),
		message_data(message_data_element),
		reference_track_ID(1),
		ntp_timestamp(1),
		media_time__(1),
		rate_(1),
		initial_delay(1),
		pdin_entry(pdin_entry_struct_pdin_entry_instances),
		usertype_element(false),
		usertype(usertype_element),
		type_indicator(1),
		locale(1),
		value______element(false),
		value_____(value______element),
		aliasInfo_element(false),
		aliasInfo(aliasInfo_element),
		parameterSets_element(false),
		parameterSets(parameterSets_element),
		subSampleInformation_element(false),
		subSampleInformation(subSampleInformation_element),
		unknown_element(false),
		unknown(unknown_element),
		ftyp_block(mp4box_ftyp_block_instances),
		mdat_block(mp4box_mdat_block_instances),
		moov_block(mp4box_moov_block_instances),
		moof_block(mp4box_moof_block_instances),
		sidx_block(mp4box_sidx_block_instances),
		ssix_block(mp4box_ssix_block_instances),
		emsg_block(mp4box_emsg_block_instances),
		pdin_block(mp4box_pdin_block_instances),
		mfra_block(mp4box_mfra_block_instances),
		prft_block(mp4box_prft_block_instances),
		uuid_block(mp4box_uuid_block_instances),
		free_block(mp4box_free_block_instances),
		file(mp4file_file_instances)
	{}
};

globals_class* g;


fourcc* fourcc::generate() {
	if (generated == 1) {
		fourcc* new_instance = new fourcc(instances);
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

	GENERATE_VAR(value, ::g->value.generate(4));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


fp32* fp32::generate() {
	if (generated == 1) {
		fp32* new_instance = new fp32(instances);
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

	GENERATE_VAR(value, ::g->value_.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


fp16* fp16::generate() {
	if (generated == 1) {
		fp16* new_instance = new fp16(instances);
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

	GENERATE_VAR(value, ::g->value__.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


fp32uvw* fp32uvw::generate() {
	if (generated == 1) {
		fp32uvw* new_instance = new fp32uvw(instances);
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

	GENERATE_VAR(value, ::g->value_.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


matrix* matrix::generate() {
	if (generated == 1) {
		matrix* new_instance = new matrix(instances);
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

	GENERATE_VAR(a, ::g->a.generate());
	GENERATE_VAR(b, ::g->b.generate());
	GENERATE_VAR(u, ::g->u.generate());
	GENERATE_VAR(c, ::g->c.generate());
	GENERATE_VAR(d, ::g->d.generate());
	GENERATE_VAR(v, ::g->v.generate());
	GENERATE_VAR(x, ::g->x.generate());
	GENERATE_VAR(y, ::g->y.generate());
	GENERATE_VAR(w, ::g->w.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


tkhd_flags* tkhd_flags::generate() {
	if (generated == 1) {
		tkhd_flags* new_instance = new tkhd_flags(instances);
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

	GENERATE_VAR(dummy, ::g->dummy.generate(2));
	GENERATE_VAR(dummy2, ::g->dummy2.generate(4));
	GENERATE_VAR(track_in_poster, ::g->track_in_poster.generate(1));
	GENERATE_VAR(track_in_preview, ::g->track_in_preview.generate(1));
	GENERATE_VAR(track_in_movie, ::g->track_in_movie.generate(1));
	GENERATE_VAR(track_enabled, ::g->track_enabled.generate(1));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp4lang* mp4lang::generate() {
	if (generated == 1) {
		mp4lang* new_instance = new mp4lang(instances);
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

	GENERATE_VAR(value, ::g->value___.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


elst_entry* elst_entry::generate() {
	if (generated == 1) {
		elst_entry* new_instance = new elst_entry(instances);
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

	GENERATE_VAR(duration, ::g->duration.generate());
	GENERATE_VAR(media_time, ::g->media_time.generate());
	GENERATE_VAR(media_rate, ::g->media_rate.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


elst_entry_v1* elst_entry_v1::generate() {
	if (generated == 1) {
		elst_entry_v1* new_instance = new elst_entry_v1(instances);
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

	GENERATE_VAR(segment_duration, ::g->segment_duration.generate());
	GENERATE_VAR(media_time, ::g->media_time_.generate());
	GENERATE_VAR(media_rate_integer, ::g->media_rate_integer.generate());
	GENERATE_VAR(media_rate_fraction, ::g->media_rate_fraction.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


vmhd_flags* vmhd_flags::generate() {
	if (generated == 1) {
		vmhd_flags* new_instance = new vmhd_flags(instances);
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

	GENERATE_VAR(dummy, ::g->dummy.generate(2));
	GENERATE_VAR(dummy2, ::g->dummy2_.generate({ 1 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


qtopcolor* qtopcolor::generate() {
	if (generated == 1) {
		qtopcolor* new_instance = new qtopcolor(instances);
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

	GENERATE_VAR(red, ::g->red.generate());
	GENERATE_VAR(green, ::g->green.generate());
	GENERATE_VAR(blue, ::g->blue.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_stts* str_stts::generate() {
	if (generated == 1) {
		str_stts* new_instance = new str_stts(instances);
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

	GENERATE_VAR(sample_count, ::g->sample_count.generate());
	GENERATE_VAR(sample_delta, ::g->sample_delta.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_ctts_v0* str_ctts_v0::generate() {
	if (generated == 1) {
		str_ctts_v0* new_instance = new str_ctts_v0(instances);
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

	GENERATE_VAR(sample_count, ::g->sample_count.generate());
	GENERATE_VAR(sample_offset, ::g->sample_offset.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_ctts_v1* str_ctts_v1::generate() {
	if (generated == 1) {
		str_ctts_v1* new_instance = new str_ctts_v1(instances);
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

	GENERATE_VAR(sample_count, ::g->sample_count.generate());
	GENERATE_VAR(sample_offset, ::g->sample_offset_.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_stsc* str_stsc::generate() {
	if (generated == 1) {
		str_stsc* new_instance = new str_stsc(instances);
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

	GENERATE_VAR(first_chunk, ::g->first_chunk.generate());
	GENERATE_VAR(samples_per_chunk, ::g->samples_per_chunk.generate());
	GENERATE_VAR(sample_description_index, ::g->sample_description_index.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_stsh* str_stsh::generate() {
	if (generated == 1) {
		str_stsh* new_instance = new str_stsh(instances);
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

	GENERATE_VAR(shadowed_sample_number, ::g->shadowed_sample_number.generate());
	GENERATE_VAR(sync_sample_number, ::g->sync_sample_number.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


entry_struct* entry_struct::generate() {
	if (generated == 1) {
		entry_struct* new_instance = new entry_struct(instances);
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

	GENERATE_VAR(sample_count, ::g->sample_count.generate());
	GENERATE_VAR(group_description_index, ::g->group_description_index.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


hevc_array_struct* hevc_array_struct::generate() {
	if (generated == 1) {
		hevc_array_struct* new_instance = new hevc_array_struct(instances);
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

	GENERATE_VAR(array_completeness_and_NAL_unit_type, ::g->array_completeness_and_NAL_unit_type.generate());
	GENERATE_VAR(numNalus, ::g->numNalus.generate({ 1 }));
	for (n = 0; (n < numNalus()); n++) {
			GENERATE_VAR(nalUnitLength, ::g->nalUnitLength.generate({ 1 }));
		GENERATE_VAR(nalUnit, ::g->nalUnit.generate(nalUnitLength()));
	;
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


font_entry_struct* font_entry_struct::generate() {
	if (generated == 1) {
		font_entry_struct* new_instance = new font_entry_struct(instances);
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

	GENERATE_VAR(font_ID, ::g->font_ID.generate());
	GENERATE_VAR(font_name_length, ::g->font_name_length.generate());
	if ((font_name_length() > 0)) {
		GENERATE_VAR(font_name, ::g->font_name.generate(font_name_length()));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


senc_entry_struct_subsample_struct* senc_entry_struct_subsample_struct::generate() {
	if (generated == 1) {
		senc_entry_struct_subsample_struct* new_instance = new senc_entry_struct_subsample_struct(instances);
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

	GENERATE_VAR(bytes_of_clear_data, ::g->bytes_of_clear_data.generate());
	GENERATE_VAR(bytes_of_protected_data, ::g->bytes_of_protected_data.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


senc_entry_struct* senc_entry_struct::generate() {
	if (generated == 1) {
		senc_entry_struct* new_instance = new senc_entry_struct(instances);
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

	GENERATE_VAR(per_sample_IV, ::g->per_sample_IV.generate(8));
	if (((::g->flag()[2] & 2) != 0)) {
		GENERATE_VAR(subsample_count, ::g->subsample_count.generate({ 1 }));
		GENERATE_VAR(subsample, ::g->subsample.generate(subsample_count()));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


trun_entry_struct* trun_entry_struct::generate() {
	if (generated == 1) {
		trun_entry_struct* new_instance = new trun_entry_struct(instances);
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

	if (((::g->flag()[1] & 0x01) != 0)) {
		GENERATE_VAR(sample_duration, ::g->sample_duration.generate());
	};
	if (((::g->flag()[1] & 0x02) != 0)) {
		GENERATE_VAR(sample_size, ::g->sample_size.generate());
	};
	if (((::g->flag()[1] & 0x04) != 0)) {
		GENERATE_VAR(sample_flags, ::g->sample_flags.generate());
	};
	if (((::g->flag()[1] & 0x08) != 0)) {
		if ((::g->version() < 1)) {
			GENERATE(sample_composition_time_offset, ::g->sample_composition_time_offset.generate());
		} else {
			GENERATE(sample_composition_time_offset, ::g->sample_composition_time_offset_.generate());
		};
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


str_sidx* str_sidx::generate() {
	if (generated == 1) {
		str_sidx* new_instance = new str_sidx(instances);
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

	GENERATE_VAR(reference_size31_type1, ::g->reference_size31_type1.generate());
	GENERATE_VAR(subsegment_duration, ::g->subsegment_duration.generate());
	GENERATE_VAR(SAP_delta_time28_type3_starts_with1, ::g->SAP_delta_time28_type3_starts_with1.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


subsegment_struct_range_struct* subsegment_struct_range_struct::generate() {
	if (generated == 1) {
		subsegment_struct_range_struct* new_instance = new subsegment_struct_range_struct(instances);
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

	GENERATE_VAR(level, ::g->level.generate());
	GENERATE_VAR(range_size, ::g->range_size.generate(3));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


subsegment_struct* subsegment_struct::generate() {
	if (generated == 1) {
		subsegment_struct* new_instance = new subsegment_struct(instances);
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

	GENERATE_VAR(ranges_count, ::g->ranges_count.generate({ 1 }));
	GENERATE_VAR(range, ::g->range.generate(ranges_count()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ipma_entry_struct* ipma_entry_struct::generate(int64& endOffset) {
	if (generated == 1) {
		ipma_entry_struct* new_instance = new ipma_entry_struct(instances);
		new_instance->generated = 2;
		return new_instance->generate(endOffset);
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	if ((::g->version() < 1)) {
		GENERATE(item_ID, ::g->item_ID.generate());
	} else {
		GENERATE(item_ID, ::g->item_ID_.generate());
	};
	GENERATE_VAR(association_count, ::g->association_count.generate());
	for (j = 0; ((j < association_count()) && (FTell() < endOffset)); j++) {
			if (((::g->flag()[2] & 1) != 0)) {
			GENERATE(property_index, ::g->property_index.generate());
		} else {
			GENERATE(property_index, ::g->property_index_.generate());
		};
	;
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


pdin_entry_struct* pdin_entry_struct::generate() {
	if (generated == 1) {
		pdin_entry_struct* new_instance = new pdin_entry_struct(instances);
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

	GENERATE_VAR(rate, ::g->rate_.generate());
	GENERATE_VAR(initial_delay, ::g->initial_delay.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp4box* mp4box::generate() {
	if (generated == 1) {
		mp4box* new_instance = new mp4box(instances);
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

	startOffset = FTell();
	tries = 0;
	for (tries = 0; (tries < 3); ++tries) {
			FSeek(startOffset);
		GENERATE_VAR(size, ::g->size.generate({ 0 }));
		if (!size()) {
		break;
		};
	;
	};
	GENERATE_VAR(type, ::g->type.generate());
	endOffset = (startOffset + size());
	contentsize = ((size() > 8) ? (size() - 8) : 0);
	ChangeArrayLength();
	switch (STR2INT(type().value())) {
	case STR2INT("moof"):
	case STR2INT("traf"):
	case STR2INT("mvex"):
	case STR2INT("sinf"):
	case STR2INT("schi"):
	case STR2INT("iprp"):
	case STR2INT("ipco"):
	case STR2INT("mfra"):
	case STR2INT("meco"):
		_clim1 = 0;
		while (((_clim1++ < 8) && (FTell() < endOffset))) {
			GENERATE_VAR(box, ::g->box.generate());
			FSeek(box().endOffset);
		};
		break;
	case STR2INT("moov"):
			chunk_type.resize(4);
			preferred_blocks = { "mvhd", "trak" };
			possible_blocks = { "mvhd", "trak", "udta", "iods", "meta", "mvex" };
			_blim_moov = 0;
			while (((_blim_moov++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				switch (STR2INT(chunk_type)) {
				case STR2INT("mvhd"):
					GENERATE_VAR(mvhd_block, ::g->mvhd_block.generate());
					VectorRemove(preferred_blocks, { "mvhd" });
					VectorRemove(possible_blocks, { "mvhd" });
					break;
				case STR2INT("trak"):
					GENERATE_VAR(trak_block, ::g->trak_block.generate());
					VectorRemove(preferred_blocks, { "trak" });
					VectorRemove(possible_blocks, { "trak" });
					break;
				case STR2INT("iods"):
					GENERATE_VAR(iods_block, ::g->iods_block.generate());
					VectorRemove(possible_blocks, { "iods" });
					break;
				case STR2INT("udta"):
					GENERATE_VAR(udta_block, ::g->udta_block.generate());
					VectorRemove(possible_blocks, { "udta" });
					break;
				case STR2INT("meta"):
					GENERATE_VAR(meta_block, ::g->meta_block.generate());
					VectorRemove(possible_blocks, { "meta" });
					break;
				case STR2INT("mvex"):
					GENERATE_VAR(mvex_block, ::g->mvex_block.generate());
					VectorRemove(possible_blocks, { "mvex" });
					break;
				default:
					GENERATE_VAR(unknown_block, ::g->unknown_block.generate());
					break;
				};
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("ftyp"):
			available_major_brands = { "isom", "iso2", "iso3", "iso4", "iso5", "iso6", "avc1", "mp41", "mp42", "mp71", "M4V ", "M4A ", "M4B ", "M4P ", "qt  ", "MSNV", "dash", "f4v ", "hvc1", "hev1", "av01", "3gp4", "3gp5", "3gp6", "3ge6", "3ge7", "CAEP", "mif1", "msf1", "heic", "heif" };
			selected_major_brand.resize(4);
			ReadBytes(selected_major_brand, FTell(), 4, available_major_brands);
			GENERATE_VAR(major_brand, ::g->major_brand.generate(4));
			GENERATE_VAR(minor_version, ::g->minor_version.generate());
			chunk_type.resize(4);
			compatiple_brands = { "isom", "iso2", "avc1", "mp41", "mp42", "dash", "hvc1", "hev1" };
			while (ReadBytes(chunk_type, FTell(), 4, compatiple_brands, compatiple_brands, 0.99)) {
				GENERATE_VAR(compatible_brand, ::g->compatible_brand.generate(4));
				VectorRemove(compatiple_brands, { chunk_type });
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("styp"):
			available_brands = { "isom", "iso2", "iso3", "iso6", "avc1", "mp41", "mp42" };
			selected_brand.resize(4);
			ReadBytes(selected_brand, FTell(), 4, available_brands);
			GENERATE_VAR(major_brand, ::g->major_brand.generate(4));
			GENERATE_VAR(minor_version, ::g->minor_version.generate());
			chunk_type.resize(4);
			compat_brands = { "isom", "iso2", "avc1", "mp41", "mp42" };
			while (ReadBytes(chunk_type, FTell(), 4, compat_brands, compat_brands, 0.99)) {
				GENERATE_VAR(compatible_brand, ::g->compatible_brand.generate(4));
				VectorRemove(compat_brands, { chunk_type });
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("mvhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(creation_time, ::g->creation_time.generate());
				GENERATE(modification_time, ::g->modification_time.generate());
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE(duration, ::g->duration.generate());
			} else {
				GENERATE(creation_time, ::g->creation_time_.generate());
				GENERATE(modification_time, ::g->modification_time_.generate());
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE(duration, ::g->duration_.generate());
			};
			GENERATE_VAR(rate, ::g->rate.generate());
			GENERATE_VAR(volume, ::g->volume.generate());
			GENERATE(reserved_, ::g->reserved_.generate(10));
			GENERATE_VAR(matrix_structure, ::g->matrix_structure.generate());
			GENERATE(pre_defined, ::g->pre_defined.generate(6));
			GENERATE_VAR(next_track_ID, ::g->next_track_ID.generate());
			break;
		;
	case STR2INT("mdat"):
			::g->mdatPosition = FTell();
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("free"):
	case STR2INT("skip"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("wide"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("iods"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE_VAR(OD_data, ::g->OD_data.generate((contentsize - 4)));
			};
			break;
		;
	case STR2INT("trak"):
			chunk_type.resize(4);
			preferred_blocks = { "tkhd", "mdia" };
			possible_blocks = { "tkhd", "mdia", "edts", "tref", "udta", "meta" };
			_blim_trak = 0;
			while (((_blim_trak++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				switch (STR2INT(chunk_type)) {
				case STR2INT("tkhd"):
					GENERATE_VAR(tkhd_block, ::g->tkhd_block.generate());
					VectorRemove(preferred_blocks, { "tkhd" });
					VectorRemove(possible_blocks, { "tkhd" });
					break;
				case STR2INT("mdia"):
					GENERATE_VAR(mdia_block, ::g->mdia_block.generate());
					VectorRemove(preferred_blocks, { "mdia" });
					VectorRemove(possible_blocks, { "mdia" });
					break;
				case STR2INT("edts"):
					GENERATE_VAR(edts_block, ::g->edts_block.generate());
					VectorRemove(possible_blocks, { "edts" });
					break;
				case STR2INT("tref"):
					GENERATE_VAR(tref_block, ::g->tref_block.generate());
					VectorRemove(possible_blocks, { "tref" });
					break;
				case STR2INT("udta"):
					GENERATE_VAR(udta_block, ::g->udta_block.generate());
					VectorRemove(possible_blocks, { "udta" });
					break;
				case STR2INT("meta"):
					GENERATE_VAR(meta_block, ::g->meta_block.generate());
					VectorRemove(possible_blocks, { "meta" });
					break;
				default:
					GENERATE_VAR(unknown_block, ::g->unknown_block.generate());
					break;
				};
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("tkhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(tkhd_fl, ::g->tkhd_fl.generate());
			if ((version() == 0)) {
				GENERATE(creation_time, ::g->creation_time.generate());
				GENERATE(modification_time, ::g->modification_time.generate());
				GENERATE_VAR(track_ID, ::g->track_ID.generate());
				GENERATE(reserved_, ::g->reserved__.generate());
				GENERATE(duration, ::g->duration.generate());
			} else {
				GENERATE(creation_time, ::g->creation_time_.generate());
				GENERATE(modification_time, ::g->modification_time_.generate());
				GENERATE_VAR(track_ID, ::g->track_ID.generate());
				GENERATE(reserved_, ::g->reserved__.generate());
				GENERATE(duration, ::g->duration_.generate());
			};
			GENERATE(reserved_2, ::g->reserved_2.generate());
			GENERATE_VAR(layer, ::g->layer.generate());
			GENERATE_VAR(alternate_group, ::g->alternate_group.generate());
			GENERATE_VAR(volume, ::g->volume.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(matrix_structure, ::g->matrix_structure.generate());
			GENERATE(width, ::g->width.generate());
			GENERATE(height, ::g->height.generate());
			break;
		;
	case STR2INT("mdia"):
			chunk_type.resize(4);
			preferred_blocks = { "mdhd", "hdlr", "minf" };
			possible_blocks = { "mdhd", "hdlr", "minf", "elng" };
			_blim_mdia = 0;
			while (((_blim_mdia++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				switch (STR2INT(chunk_type)) {
				case STR2INT("mdhd"):
					GENERATE_VAR(mdhd_block, ::g->mdhd_block.generate());
					VectorRemove(preferred_blocks, { "mdhd" });
					VectorRemove(possible_blocks, { "mdhd" });
					break;
				case STR2INT("hdlr"):
					GENERATE_VAR(hdlr_block, ::g->hdlr_block.generate());
					VectorRemove(preferred_blocks, { "hdlr" });
					VectorRemove(possible_blocks, { "hdlr" });
					break;
				case STR2INT("minf"):
					GENERATE_VAR(minf_block, ::g->minf_block.generate());
					VectorRemove(preferred_blocks, { "minf" });
					VectorRemove(possible_blocks, { "minf" });
					break;
				case STR2INT("elng"):
					GENERATE_VAR(elng_block, ::g->elng_block.generate());
					VectorRemove(possible_blocks, { "elng" });
					break;
				default:
					GENERATE_VAR(unknown_block, ::g->unknown_block.generate());
					break;
				};
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("mdhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(creation_time, ::g->creation_time.generate());
				GENERATE(modification_time, ::g->modification_time.generate());
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE(duration, ::g->duration.generate());
			} else {
				GENERATE(creation_time, ::g->creation_time_.generate());
				GENERATE(modification_time, ::g->modification_time_.generate());
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE(duration, ::g->duration_.generate());
			};
			GENERATE_VAR(language, ::g->language.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			break;
		;
	case STR2INT("hdlr"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE(pre_defined, ::g->pre_defined__.generate());
			if (::g->isVideo) {
				GENERATE_VAR(handler_type, ::g->handler_type.generate({ 0x76696465 }));
			} else {
				GENERATE_VAR(handler_type, ::g->handler_type.generate({ 0x736F756E }));
			};
			GENERATE(reserved_, ::g->reserved_.generate(12));
			if ((contentsize > 24)) {
				GENERATE(name, ::g->name.generate((contentsize - 24)));
			};
			break;
		;
	case STR2INT("edts"):
			chunk_type.resize(4);
			preferred_blocks = { "elst" };
			possible_blocks = { "elst" };
			_blim_edts = 0;
			while (((_blim_edts++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				GENERATE_VAR(child_block, ::g->child_block.generate());
				VectorRemove(possible_blocks, { chunk_type });
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("elst"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(elst_count, ::g->elst_count.generate({ 1 }));
			if ((version() == 0)) {
				for (i = 0; (i < elst_count()); i++) {
					GENERATE(entries, ::g->entries.generate());
				};
			} else {
				for (i = 0; (i < elst_count()); i++) {
					GENERATE(entries, ::g->entries_.generate());
				};
			};
			break;
		;
	case STR2INT("tref"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("udta"):
			_clim2 = 0;
			while (((_clim2++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(box, ::g->box.generate());
				FSeek(box().endOffset);
			};
			break;
		;
	case STR2INT("cprt"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(language, ::g->language.generate());
			if ((contentsize > 6)) {
				GENERATE_VAR(notice, ::g->notice.generate((contentsize - 6)));
			};
			break;
		;
	case STR2INT("meta"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			chunk_type.resize(4);
			preferred_blocks = { "hdlr" };
			possible_blocks = { "hdlr", "dinf", "iloc", "iinf", "pitm", "ipro", "ipmc", "iprp", "iref", "idat", "xml ", "bxml" };
			_blim_meta = 0;
			while (((_blim_meta++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				if ((chunk_type == "hdlr")) {
				VectorRemove(preferred_blocks, { "hdlr" });
				};
				VectorRemove(possible_blocks, { chunk_type });
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("minf"):
			chunk_type.resize(4);
			preferred_blocks = { "vmhd", "smhd", "dinf", "stbl" };
			possible_blocks = { "vmhd", "smhd", "hmhd", "nmhd", "dinf", "stbl" };
			_blim_minf = 0;
			while (((_blim_minf++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				switch (STR2INT(chunk_type)) {
				case STR2INT("vmhd"):
				case STR2INT("smhd"):
				case STR2INT("hmhd"):
				case STR2INT("nmhd"):
					GENERATE_VAR(header_block, ::g->header_block.generate());
					VectorRemove(preferred_blocks, { "vmhd", "smhd", "hmhd", "nmhd" });
					VectorRemove(possible_blocks, { "vmhd", "smhd", "hmhd", "nmhd" });
					break;
				case STR2INT("stbl"):
					GENERATE_VAR(stbl_block, ::g->stbl_block.generate());
					VectorRemove(preferred_blocks, { "stbl" });
					VectorRemove(possible_blocks, { "stbl" });
					break;
				case STR2INT("dinf"):
					GENERATE_VAR(dinf_block, ::g->dinf_block.generate());
					VectorRemove(preferred_blocks, { "dinf" });
					VectorRemove(possible_blocks, { "dinf" });
					break;
				default:
					GENERATE_VAR(unknown_block, ::g->unknown_block.generate());
					break;
				};
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("vmhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(vmhd_fl, ::g->vmhd_fl.generate());
			GENERATE_VAR(graphics_mode, qtgfxmode_generate());
			GENERATE_VAR(opcolor, ::g->opcolor.generate());
			break;
		;
	case STR2INT("smhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(balance, ::g->balance.generate());
			GENERATE(reserved_, ::g->reserved___.generate());
			break;
		;
	case STR2INT("nmhd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			break;
		;
	case STR2INT("dinf"):
			chunk_type.resize(4);
			preferred_blocks = { "dref", "url " };
			possible_blocks = { "dref", "url ", "urn " };
			_blim_dinf = 0;
			while (((_blim_dinf++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				VectorRemove(possible_blocks, { chunk_type });
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("dref"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(dref_count, ::g->dref_count.generate({ 1 }));
			for (i = 0; ((i < dref_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(entry_box, ::g->entry_box.generate());
			;
			};
			break;
		;
	case STR2INT("url "):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((contentsize > 4) && ((flag()[2] & 1) == 0))) {
				GENERATE_VAR(location, ::g->location.generate());
			};
			break;
		;
	case STR2INT("urn "):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE(name, ::g->name_.generate());
				GENERATE_VAR(location, ::g->location.generate());
			};
			break;
		;
	case STR2INT("stbl"):
			chunk_type.resize(4);
			preferred_blocks = { "stsd", "stts", "stsc", "stsz", "stco" };
			possible_blocks = { "stsd", "stts", "stsc", "stsz", "stz2", "stco", "co64", "stss", "ctts", "stsh", "sdtp", "sbgp", "sgpd", "cslg" };
			_blim_stbl = 0;
			while (((_blim_stbl++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				if (((chunk_type == "stco") || (chunk_type == "co64"))) {
					VectorRemove(preferred_blocks, { "stco", "co64" });
					VectorRemove(possible_blocks, { "stco", "co64" });
				} else {
				if (((chunk_type == "stsz") || (chunk_type == "stz2"))) {
					VectorRemove(preferred_blocks, { "stsz", "stz2" });
					VectorRemove(possible_blocks, { "stsz", "stz2" });
				} else {
					VectorRemove(preferred_blocks, { chunk_type });
					VectorRemove(possible_blocks, { chunk_type });
				};
				};
				if (((startOffset + size()) == (uint64)FTell())) {
				break;
				};
			};
			break;
		;
	case STR2INT("stsd"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stsd_count, ::g->stsd_count.generate({ 1 }));
			for (i = 0; ((i < stsd_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(sample_entry, ::g->sample_entry.generate());
			;
			};
			break;
		;
	case STR2INT("stts"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stts_count, ::g->stts_count.generate({ 1 }));
			GENERATE(entries, ::g->entries__.generate(stts_count()));
			break;
		;
	case STR2INT("ctts"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(ctts_count, ::g->ctts_count.generate({ 1 }));
			if ((version() == 0)) {
				GENERATE(entries, ::g->entries___.generate(ctts_count()));
			} else {
				GENERATE(entries, ::g->entries____.generate(ctts_count()));
			};
			break;
		;
	case STR2INT("stsc"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stsc_count, ::g->stsc_count.generate({ 1 }));
			GENERATE(entries, ::g->entries_____.generate(stsc_count()));
			break;
		;
	case STR2INT("stsz"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(sample_size, ::g->sample_size.generate({ 1 }));
			GENERATE_VAR(sample_count, ::g->sample_count.generate({ 1 }));
			if (((sample_size() == 0) && (sample_count() > 0))) {
				GENERATE(entry_size, ::g->entry_size.generate(sample_count()));
			};
			break;
		;
	case STR2INT("stz2"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(reserved_stz2, ::g->reserved_stz2.generate(3));
			GENERATE_VAR(field_size, ::g->field_size.generate());
			GENERATE_VAR(sample_count, ::g->sample_count.generate({ 1 }));
			if ((field_size() == 16)) {
				GENERATE(entry_size, ::g->entry_size_.generate(sample_count()));
			} else {
			if ((field_size() == 8)) {
				GENERATE(entry_size, ::g->entry_size__.generate(sample_count()));
			} else {
			if (((field_size() == 4) && (sample_count() > 0))) {
				GENERATE(entry_size, ::g->entry_size__.generate(((sample_count() + 1) / 2)));
			};
			};
			};
			break;
		;
	case STR2INT("stco"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stco_count, ::g->stco_count.generate({ 1 }));
			GENERATE(chunk_offset, ::g->chunk_offset.generate(stco_count()));
			break;
		;
	case STR2INT("co64"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(co64_count, ::g->co64_count.generate({ 1 }));
			GENERATE(chunk_offset, ::g->chunk_offset_.generate(co64_count()));
			break;
		;
	case STR2INT("stss"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stss_count, ::g->stss_count.generate({ 1 }));
			GENERATE_VAR(sample_number, ::g->sample_number.generate(stss_count()));
			break;
		;
	case STR2INT("stsh"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(stsh_count, ::g->stsh_count.generate({ 1 }));
			GENERATE(entries, ::g->entries______.generate(stsh_count()));
			break;
		;
	case STR2INT("sdtp"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE_VAR(sample_dependency_table, ::g->sample_dependency_table.generate((contentsize - 4)));
			};
			break;
		;
	case STR2INT("sbgp"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(grouping_type, ::g->grouping_type.generate());
			if ((version() == 1)) {
				GENERATE_VAR(grouping_type_parameter, ::g->grouping_type_parameter.generate());
			};
			GENERATE_VAR(sbgp_count, ::g->sbgp_count.generate({ 1 }));
			for (i = 0; (i < sbgp_count()); i++) {
					GENERATE_VAR(entry, ::g->entry.generate());
			;
			};
			break;
		;
	case STR2INT("sgpd"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(grouping_type, ::g->grouping_type.generate());
			if ((version() == 1)) {
				GENERATE_VAR(default_length, ::g->default_length.generate({ 1 }));
			};
			if ((version() >= 2)) {
				GENERATE_VAR(default_sample_description_index, ::g->default_sample_description_index.generate());
			};
			GENERATE_VAR(sgpd_count, ::g->sgpd_count.generate({ 1 }));
			for (i = 0; ((i < sgpd_count()) && (FTell() < endOffset)); i++) {
					if (((version() == 1) && (default_length() == 0))) {
					GENERATE_VAR(description_length, ::g->description_length.generate({ 1 }));
					GENERATE_VAR(description, ::g->description.generate(description_length()));
				} else {
				if ((version() == 1)) {
					GENERATE_VAR(description, ::g->description.generate(default_length()));
				} else {
					bytes_left = (endOffset - FTell());
					per_entry = (bytes_left / (sgpd_count() - i));
					if ((per_entry > 0)) {
						GENERATE_VAR(description, ::g->description.generate(per_entry));
					};
				};
				};
			;
			};
			break;
		;
	case STR2INT("cslg"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(compositionToDTSShift, ::g->compositionToDTSShift.generate());
				GENERATE(leastDecodeToDisplayDelta, ::g->leastDecodeToDisplayDelta.generate());
				GENERATE(greatestDecodeToDisplayDelta, ::g->greatestDecodeToDisplayDelta.generate());
				GENERATE(compositionStartTime, ::g->compositionStartTime.generate());
				GENERATE(compositionEndTime, ::g->compositionEndTime.generate());
			} else {
				GENERATE(compositionToDTSShift, ::g->compositionToDTSShift_.generate());
				GENERATE(leastDecodeToDisplayDelta, ::g->leastDecodeToDisplayDelta_.generate());
				GENERATE(greatestDecodeToDisplayDelta, ::g->greatestDecodeToDisplayDelta_.generate());
				GENERATE(compositionStartTime, ::g->compositionStartTime_.generate());
				GENERATE(compositionEndTime, ::g->compositionEndTime_.generate());
			};
			break;
		;
	case STR2INT("avc1"):
	case STR2INT("avc3"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim3 = 0;
			while (((_clim3++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("avcC"):
			GENERATE_VAR(configurationVersion, ::g->configurationVersion.generate({ 1 }));
			GENERATE_VAR(AVCProfileIndication, ::g->AVCProfileIndication.generate());
			GENERATE_VAR(profile_compatibility, ::g->profile_compatibility.generate());
			GENERATE_VAR(AVCLevelIndication, ::g->AVCLevelIndication.generate());
			GENERATE_VAR(lengthSizeMinusOne, ::g->lengthSizeMinusOne.generate());
			GENERATE_VAR(numOfSequenceParameterSets, ::g->numOfSequenceParameterSets.generate());
			numSPS = (numOfSequenceParameterSets() & 0x1F);
			for (j = 0; (j < numSPS); j++) {
					GENERATE_VAR(sequenceParameterSetLength, ::g->sequenceParameterSetLength.generate({ 1 }));
				GENERATE_VAR(sequenceParameterSetNALUnit, ::g->sequenceParameterSetNALUnit.generate(sequenceParameterSetLength()));
			;
			};
			GENERATE_VAR(numOfPictureParameterSets, ::g->numOfPictureParameterSets.generate());
			for (j = 0; (j < numOfPictureParameterSets()); j++) {
					GENERATE_VAR(pictureParameterSetLength, ::g->pictureParameterSetLength.generate({ 1 }));
				GENERATE_VAR(pictureParameterSetNALUnit, ::g->pictureParameterSetNALUnit.generate(pictureParameterSetLength()));
			;
			};
			if ((FTell() < endOffset)) {
				GENERATE_VAR(extra_data, ::g->extra_data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("avc4"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("hvc1"):
	case STR2INT("hev1"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim4 = 0;
			while (((_clim4++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("hvcC"):
			GENERATE_VAR(configurationVersion, ::g->configurationVersion.generate({ 1 }));
			GENERATE_VAR(general_profile_space_tier_idc, ::g->general_profile_space_tier_idc.generate());
			GENERATE_VAR(general_profile_compatibility_flags, ::g->general_profile_compatibility_flags.generate());
			GENERATE_VAR(general_constraint_indicator_flag, ::g->general_constraint_indicator_flag.generate(6));
			GENERATE_VAR(general_level_idc, ::g->general_level_idc.generate());
			GENERATE_VAR(min_spatial_segmentation_idc, ::g->min_spatial_segmentation_idc.generate());
			GENERATE_VAR(parallelismType, ::g->parallelismType.generate());
			GENERATE_VAR(chromaFormat, ::g->chromaFormat.generate());
			GENERATE_VAR(bitDepthLumaMinus8, ::g->bitDepthLumaMinus8.generate());
			GENERATE_VAR(bitDepthChromaMinus8, ::g->bitDepthChromaMinus8.generate());
			GENERATE_VAR(avgFrameRate, ::g->avgFrameRate.generate());
			GENERATE_VAR(constFR_numTempLayers_tidNested_lenSize, ::g->constFR_numTempLayers_tidNested_lenSize.generate());
			GENERATE_VAR(numOfArrays, ::g->numOfArrays.generate());
			for (k = 0; ((k < numOfArrays()) && (FTell() < endOffset)); k++) {
					GENERATE_VAR(hevc_array, ::g->hevc_array.generate());
			;
			};
			break;
		;
	case STR2INT("av01"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim5 = 0;
			while (((_clim5++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("av1C"):
			GENERATE_VAR(marker_version, ::g->marker_version.generate());
			GENERATE_VAR(seq_profile_level, ::g->seq_profile_level.generate());
			GENERATE_VAR(chroma_flags, ::g->chroma_flags.generate());
			GENERATE_VAR(delay_flags, ::g->delay_flags.generate());
			if ((FTell() < endOffset)) {
				GENERATE_VAR(configOBUs, ::g->configOBUs.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("dvav"):
	case STR2INT("dvhe"):
	case STR2INT("dvh1"):
	case STR2INT("dvvc"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim6 = 0;
			while (((_clim6++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("dvcC"):
			GENERATE_VAR(dv_version_major, ::g->dv_version_major.generate());
			GENERATE_VAR(dv_version_minor, ::g->dv_version_minor.generate());
			GENERATE_VAR(profile_level_flags, ::g->profile_level_flags.generate());
			GENERATE_VAR(bl_compat_and_reserved_, ::g->bl_compat_and_reserved_.generate());
			if ((FTell() < endOffset)) {
				GENERATE_VAR(reserved__data, ::g->reserved__data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("mp4v"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim7 = 0;
			while (((_clim7++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("encv"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(pre_defined1, ::g->pre_defined1.generate());
			GENERATE(reserved_2, ::g->reserved_2_.generate());
			GENERATE_VAR(pre_defined2, ::g->pre_defined2.generate(3));
			GENERATE(width, ::g->width_.generate());
			GENERATE(height, ::g->height_.generate());
			GENERATE_VAR(horizresolution, ::g->horizresolution.generate({ 0x00480000 }));
			GENERATE_VAR(vertresolution, ::g->vertresolution.generate({ 0x00480000 }));
			GENERATE(reserved_3, ::g->reserved_3_.generate());
			GENERATE_VAR(frame_count, ::g->frame_count.generate({ 1 }));
			GENERATE_VAR(compressorname, ::g->compressorname.generate(32));
			GENERATE_VAR(depth, ::g->depth.generate({ 0x0018 }));
			GENERATE_VAR(pre_defined3, ::g->pre_defined3.generate());
			_clim8 = 0;
			while (((_clim8++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("btrt"):
			GENERATE_VAR(bufferSizeDB, ::g->bufferSizeDB.generate());
			GENERATE_VAR(maxBitrate, ::g->maxBitrate.generate());
			GENERATE_VAR(avgBitrate, ::g->avgBitrate.generate());
			break;
		;
	case STR2INT("pasp"):
			GENERATE_VAR(hSpacing, ::g->hSpacing.generate());
			GENERATE_VAR(vSpacing, ::g->vSpacing.generate());
			break;
		;
	case STR2INT("clap"):
			GENERATE_VAR(cleanApertureWidthN, ::g->cleanApertureWidthN.generate());
			GENERATE_VAR(cleanApertureWidthD, ::g->cleanApertureWidthD.generate());
			GENERATE_VAR(cleanApertureHeightN, ::g->cleanApertureHeightN.generate());
			GENERATE_VAR(cleanApertureHeightD, ::g->cleanApertureHeightD.generate());
			GENERATE_VAR(horizOffN, ::g->horizOffN.generate());
			GENERATE_VAR(horizOffD, ::g->horizOffD.generate());
			GENERATE_VAR(vertOffN, ::g->vertOffN.generate());
			GENERATE_VAR(vertOffD, ::g->vertOffD.generate());
			break;
		;
	case STR2INT("colr"):
			GENERATE_VAR(colourType, ::g->colourType.generate(4));
			if (((colourType() == "nclx") || (colourType() == "nclc"))) {
				GENERATE_VAR(colour_primaries, ::g->colour_primaries.generate());
				GENERATE_VAR(transfer_characteristics, ::g->transfer_characteristics.generate());
				GENERATE_VAR(matrix_coefficients, ::g->matrix_coefficients.generate());
				if ((colourType() == "nclx")) {
					GENERATE_VAR(full_range_flag, ::g->full_range_flag.generate());
				};
			} else {
				if ((FTell() < endOffset)) {
					GENERATE_VAR(icc_profile, ::g->icc_profile.generate((endOffset - FTell())));
				};
			};
			break;
		;
	case STR2INT("mp4a"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim9 = 0;
			while (((_clim9++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("esds"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE_VAR(ES_Descriptor, ::g->ES_Descriptor.generate((contentsize - 4)));
			};
			break;
		;
	case STR2INT("ac-3"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE_VAR(compression_id, ::g->compression_id.generate());
			GENERATE_VAR(packet_size, ::g->packet_size.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim10 = 0;
			while (((_clim10++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("ec-3"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE_VAR(compression_id, ::g->compression_id.generate());
			GENERATE_VAR(packet_size, ::g->packet_size.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim11 = 0;
			while (((_clim11++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("dac3"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("dec3"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("ac-4"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim12 = 0;
			while (((_clim12++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("dtsc"):
	case STR2INT("dtsh"):
	case STR2INT("dtsl"):
	case STR2INT("dtse"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE_VAR(compression_id, ::g->compression_id.generate());
			GENERATE_VAR(packet_size, ::g->packet_size.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim13 = 0;
			while (((_clim13++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("Opus"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim14 = 0;
			while (((_clim14++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("dOps"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(outputChannelCount, ::g->outputChannelCount.generate());
			GENERATE_VAR(preSkip, ::g->preSkip.generate());
			GENERATE_VAR(inputSampleRate, ::g->inputSampleRate.generate());
			GENERATE_VAR(outputGain, ::g->outputGain.generate());
			GENERATE_VAR(channelMappingFamily, ::g->channelMappingFamily.generate());
			if ((channelMappingFamily() != 0)) {
				GENERATE_VAR(streamCount, ::g->streamCount.generate());
				GENERATE_VAR(coupledCount, ::g->coupledCount.generate());
				GENERATE_VAR(channelMapping, ::g->channelMapping.generate(outputChannelCount()));
			};
			break;
		;
	case STR2INT("flac"):
	case STR2INT("fLaC"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim15 = 0;
			while (((_clim15++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("dfLa"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(flac_metadata, ::g->flac_metadata.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("alac"):
			if ((contentsize > 24)) {
				GENERATE(reserved_1, ::g->reserved_1.generate(6));
				GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
				GENERATE(reserved_2, ::g->reserved_2__.generate(8));
				GENERATE_VAR(channelcount, ::g->channelcount.generate());
				GENERATE_VAR(samplesize, ::g->samplesize.generate());
				GENERATE(pre_defined, ::g->pre_defined_.generate());
				GENERATE(reserved_3, ::g->reserved_3.generate());
				GENERATE_VAR(samplerate, ::g->samplerate.generate());
				_clim16 = 0;
				while (((_clim16++ < 8) && (FTell() < endOffset))) {
					GENERATE_VAR(child_box, ::g->child_box.generate());
					FSeek(child_box().endOffset);
				};
			} else {
				if ((contentsize > 0)) {
					GENERATE_VAR(alac_specific_config, ::g->alac_specific_config.generate(contentsize));
				};
			};
			break;
		;
	case STR2INT("alaw"):
	case STR2INT("ulaw"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			break;
		;
	case STR2INT("wave"):
			_clim17 = 0;
			while (((_clim17++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("enca"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE(reserved_2, ::g->reserved_2__.generate(8));
			GENERATE_VAR(channelcount, ::g->channelcount.generate());
			GENERATE_VAR(samplesize, ::g->samplesize.generate());
			GENERATE(pre_defined, ::g->pre_defined_.generate());
			GENERATE(reserved_3, ::g->reserved_3.generate());
			GENERATE_VAR(samplerate, ::g->samplerate.generate());
			_clim18 = 0;
			while (((_clim18++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("drms"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("mp4s"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			_clim19 = 0;
			while (((_clim19++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("stpp"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(namespace_uri, ::g->namespace_uri.generate());
			GENERATE_VAR(schema_location, ::g->schema_location.generate());
			GENERATE_VAR(auxiliary_mime_types, ::g->auxiliary_mime_types.generate());
			_clim20 = 0;
			while (((_clim20++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("tx3g"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(display_flags, ::g->display_flags.generate());
			GENERATE_VAR(horizontal_justification, ::g->horizontal_justification.generate());
			GENERATE_VAR(vertical_justification, ::g->vertical_justification.generate());
			GENERATE_VAR(background_color_rgba, ::g->background_color_rgba.generate(4));
			GENERATE_VAR(box_top, ::g->box_top.generate());
			GENERATE_VAR(box_left, ::g->box_left.generate());
			GENERATE_VAR(box_bottom, ::g->box_bottom.generate());
			GENERATE_VAR(box_right, ::g->box_right.generate());
			GENERATE_VAR(startChar, ::g->startChar.generate());
			GENERATE_VAR(endChar, ::g->endChar.generate());
			GENERATE_VAR(font_ID, ::g->font_ID.generate());
			GENERATE_VAR(face_style_flags, ::g->face_style_flags.generate());
			GENERATE_VAR(font_size, ::g->font_size.generate());
			GENERATE_VAR(text_color_rgba, ::g->text_color_rgba.generate(4));
			_clim21 = 0;
			while (((_clim21++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("ftab"):
			GENERATE_VAR(ftab_count, ::g->ftab_count.generate({ 1 }));
			for (i = 0; ((i < ftab_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(font_entry, ::g->font_entry.generate());
			;
			};
			break;
		;
	case STR2INT("wvtt"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			_clim22 = 0;
			while (((_clim22++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("stxt"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			GENERATE_VAR(content_encoding, ::g->content_encoding.generate());
			GENERATE_VAR(mime_format, ::g->mime_format.generate());
			_clim23 = 0;
			while (((_clim23++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("sbtl"):
			GENERATE(reserved_1, ::g->reserved_1.generate(6));
			GENERATE_VAR(data_reference_index, ::g->data_reference_index.generate({ 1 }));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("xml "):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE_VAR(xml_data, ::g->xml_data.generate((contentsize - 4)));
			};
			break;
		;
	case STR2INT("bxml"):
			GENERATE_VAR(version, ::g->version.generate({ 0 }));
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((contentsize > 4)) {
				GENERATE_VAR(data, ::g->data.generate((contentsize - 4)));
			};
			break;
		;
	case STR2INT("ttml"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("frma"):
			GENERATE_VAR(data_format, ::g->data_format.generate(4));
			break;
		;
	case STR2INT("schm"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(scheme_type, ::g->scheme_type.generate(4));
			GENERATE_VAR(scheme_version, ::g->scheme_version.generate());
			if ((FTell() < endOffset)) {
				GENERATE_VAR(scheme_uri, ::g->scheme_uri.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("tenc"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE(reserved_1, ::g->reserved_1_.generate());
			if ((version() < 1)) {
				GENERATE(reserved_2, ::g->reserved_2___.generate());
			} else {
				GENERATE_VAR(default_crypt_skip_byte_block, ::g->default_crypt_skip_byte_block.generate());
			};
			GENERATE_VAR(default_isProtected, ::g->default_isProtected.generate());
			GENERATE_VAR(default_Per_Sample_IV_Size, ::g->default_Per_Sample_IV_Size.generate());
			GENERATE_VAR(default_KID, ::g->default_KID.generate(16));
			if ((default_Per_Sample_IV_Size() == 0)) {
				GENERATE_VAR(default_constant_IV_size, ::g->default_constant_IV_size.generate());
				GENERATE_VAR(default_constant_IV, ::g->default_constant_IV.generate(default_constant_IV_size()));
			};
			break;
		;
	case STR2INT("pssh"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(systemID, ::g->systemID.generate(16));
			if ((version() > 0)) {
				GENERATE_VAR(KID_count, ::g->KID_count.generate({ 1 }));
				for (i = 0; (i < KID_count()); i++) {
					GENERATE_VAR(KID, ::g->KID.generate(16));
				};
			};
			GENERATE_VAR(DataSize, ::g->DataSize.generate({ 1 }));
			if ((DataSize() > 0)) {
				GENERATE_VAR(Data, ::g->Data.generate(DataSize()));
			};
			break;
		;
	case STR2INT("senc"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(sample_count, ::g->sample_count.generate({ 1 }));
			for (i = 0; ((i < sample_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(senc_entry, ::g->senc_entry.generate());
			;
			};
			break;
		;
	case STR2INT("mfhd"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(sequence_number, ::g->sequence_number.generate());
			break;
		;
	case STR2INT("tfhd"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(track_ID, ::g->track_ID.generate());
			if (((flag()[2] & 0x01) != 0)) {
				GENERATE_VAR(base_data_offset, ::g->base_data_offset.generate());
			};
			if (((flag()[2] & 0x02) != 0)) {
				GENERATE_VAR(sample_description_index, ::g->sample_description_index.generate());
			};
			if (((flag()[2] & 0x08) != 0)) {
				GENERATE_VAR(default_sample_duration, ::g->default_sample_duration.generate());
			};
			if (((flag()[2] & 0x10) != 0)) {
				GENERATE_VAR(default_sample_size, ::g->default_sample_size.generate());
			};
			if (((flag()[2] & 0x20) != 0)) {
				GENERATE_VAR(default_sample_flags, ::g->default_sample_flags.generate());
			};
			break;
		;
	case STR2INT("tfdt"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(baseMediaDecodeTime, ::g->baseMediaDecodeTime.generate());
			} else {
				GENERATE(baseMediaDecodeTime, ::g->baseMediaDecodeTime_.generate());
			};
			break;
		;
	case STR2INT("trun"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(sample_count, ::g->sample_count.generate({ 1 }));
			if (((flag()[2] & 0x01) != 0)) {
				GENERATE_VAR(data_offset, ::g->data_offset.generate());
			};
			if (((flag()[2] & 0x04) != 0)) {
				GENERATE_VAR(first_sample_flags, ::g->first_sample_flags.generate());
			};
			for (i = 0; ((i < sample_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(trun_entry, ::g->trun_entry.generate());
			;
			};
			break;
		;
	case STR2INT("trex"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(track_ID, ::g->track_ID.generate());
			GENERATE_VAR(default_sample_description_index, ::g->default_sample_description_index.generate());
			GENERATE_VAR(default_sample_duration, ::g->default_sample_duration.generate());
			GENERATE_VAR(default_sample_size, ::g->default_sample_size.generate());
			GENERATE_VAR(default_sample_flags, ::g->default_sample_flags.generate());
			break;
		;
	case STR2INT("mehd"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(fragment_duration, ::g->fragment_duration.generate());
			} else {
				GENERATE(fragment_duration, ::g->fragment_duration_.generate());
			};
			break;
		;
	case STR2INT("saiz"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((flag()[2] & 1) != 0)) {
				GENERATE_VAR(aux_info_type, ::g->aux_info_type.generate());
				GENERATE_VAR(aux_info_type_parameter, ::g->aux_info_type_parameter.generate());
			};
			GENERATE_VAR(default_sample_info_size, ::g->default_sample_info_size.generate());
			GENERATE_VAR(sample_count, ::g->sample_count.generate({ 1 }));
			if (((default_sample_info_size() == 0) && (sample_count() > 0))) {
				GENERATE_VAR(sample_info_size, ::g->sample_info_size.generate(sample_count()));
			};
			break;
		;
	case STR2INT("saio"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((flag()[2] & 1) != 0)) {
				GENERATE_VAR(aux_info_type, ::g->aux_info_type.generate());
				GENERATE_VAR(aux_info_type_parameter, ::g->aux_info_type_parameter.generate());
			};
			GENERATE_VAR(saio_count, ::g->saio_count.generate({ 1 }));
			if ((version() == 0)) {
				GENERATE(offset, ::g->offset.generate(saio_count()));
			} else {
				GENERATE(offset, ::g->offset_.generate(saio_count()));
			};
			break;
		;
	case STR2INT("sidx"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(reference_ID, ::g->reference_ID.generate());
			GENERATE_VAR(timescale, ::g->timescale.generate());
			if ((version() == 0)) {
				GENERATE(earliest_presentation_time, ::g->earliest_presentation_time.generate());
				GENERATE(first_offset, ::g->first_offset.generate());
			} else {
				GENERATE(earliest_presentation_time, ::g->earliest_presentation_time_.generate());
				GENERATE(first_offset, ::g->first_offset_.generate());
			};
			GENERATE(reserved_, ::g->reserved___.generate());
			GENERATE_VAR(reference_count, ::g->reference_count.generate({ 1 }));
			GENERATE_VAR(references, ::g->references.generate(reference_count()));
			break;
		;
	case STR2INT("ssix"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(subsegment_count, ::g->subsegment_count.generate({ 1 }));
			for (i = 0; ((i < subsegment_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(subsegment, ::g->subsegment.generate());
			;
			};
			break;
		;
	case STR2INT("tfra"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(track_ID, ::g->track_ID.generate());
			GENERATE_VAR(reserved__and_lengths, ::g->reserved__and_lengths.generate());
			GENERATE_VAR(number_of_entry, ::g->number_of_entry.generate());
			if ((FTell() < endOffset)) {
				GENERATE_VAR(entry_data, ::g->entry_data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("mfro"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(mfra_size, ::g->mfra_size.generate());
			break;
		;
	case STR2INT("pitm"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE(item_ID, ::g->item_ID.generate());
			} else {
				GENERATE(item_ID, ::g->item_ID_.generate());
			};
			break;
		;
	case STR2INT("iinf"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(iinf_count, ::g->iinf_count.generate({ 1 }));
			for (i = 0; ((i < iinf_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(infe_box, ::g->infe_box.generate());
			;
			};
			break;
		;
	case STR2INT("infe"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((version() == 0) || (version() == 1))) {
				GENERATE(item_ID, ::g->item_ID.generate());
				GENERATE_VAR(item_protection_index, ::g->item_protection_index.generate());
				GENERATE_VAR(item_name, ::g->item_name.generate());
				GENERATE_VAR(content_type, ::g->content_type.generate());
				if ((FTell() < endOffset)) {
					GENERATE_VAR(content_encoding, ::g->content_encoding.generate());
				};
			};
			if ((version() >= 2)) {
				if ((version() == 2)) {
					GENERATE(item_ID, ::g->item_ID.generate());
				} else {
					GENERATE(item_ID, ::g->item_ID_.generate());
				};
				GENERATE_VAR(item_protection_index, ::g->item_protection_index.generate());
				GENERATE_VAR(item_type_bytes, ::g->item_type_bytes.generate(4));
				GENERATE_VAR(item_name, ::g->item_name.generate());
				it_str = "";
				it_str += item_type_bytes()[0];
				it_str += item_type_bytes()[1];
				it_str += item_type_bytes()[2];
				it_str += item_type_bytes()[3];
				if ((it_str == "mime")) {
					GENERATE_VAR(content_type, ::g->content_type.generate());
					if ((FTell() < endOffset)) {
						GENERATE_VAR(content_encoding, ::g->content_encoding.generate());
					};
				} else {
				if ((it_str == "uri ")) {
					GENERATE_VAR(item_uri_type, ::g->item_uri_type.generate());
				};
				};
			};
			break;
		;
	case STR2INT("iloc"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(offset_length_sizes, ::g->offset_length_sizes.generate());
			GENERATE_VAR(baseoffset_index_sizes, ::g->baseoffset_index_sizes.generate());
			GENERATE_VAR(iloc_item_count, ::g->iloc_item_count.generate({ 1 }));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(item_data, ::g->item_data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("idat"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("iref"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			_clim24 = 0;
			while (((_clim24++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(ref_box, ::g->ref_box.generate());
				FSeek(ref_box().endOffset);
			};
			break;
		;
	case STR2INT("ipma"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(ipma_count, ::g->ipma_count.generate({ 1 }));
			for (i = 0; ((i < ipma_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(ipma_entry, ::g->ipma_entry.generate(endOffset));
			;
			};
			break;
		;
	case STR2INT("ipro"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(protection_count, ::g->protection_count.generate({ 1 }));
			for (i = 0; ((i < protection_count()) && (FTell() < endOffset)); i++) {
					GENERATE_VAR(sinf_box, ::g->sinf_box.generate());
			;
			};
			break;
		;
	case STR2INT("ipmc"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((contentsize > 4) && (FTell() < endOffset))) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("ihdr"):
			GENERATE(height, ::g->height__.generate());
			GENERATE(width, ::g->width__.generate());
			GENERATE_VAR(num_components, ::g->num_components.generate());
			GENERATE_VAR(bits_per_component, ::g->bits_per_component.generate());
			GENERATE_VAR(compression_type, ::g->compression_type.generate());
			GENERATE_VAR(unknownColorspace, ::g->unknownColorspace.generate());
			GENERATE_VAR(intellectual_property, ::g->intellectual_property.generate());
			break;
		;
	case STR2INT("jp2c"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("emsg"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((version() == 0)) {
				GENERATE_VAR(scheme_id_uri, ::g->scheme_id_uri.generate());
				GENERATE(value, ::g->value____.generate());
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE_VAR(presentation_time_delta, ::g->presentation_time_delta.generate());
				GENERATE_VAR(event_duration, ::g->event_duration.generate());
				GENERATE_VAR(id, ::g->id.generate());
			} else {
				GENERATE_VAR(timescale, ::g->timescale.generate());
				GENERATE_VAR(presentation_time, ::g->presentation_time.generate());
				GENERATE_VAR(event_duration, ::g->event_duration.generate());
				GENERATE_VAR(id, ::g->id.generate());
				GENERATE_VAR(scheme_id_uri, ::g->scheme_id_uri.generate());
				GENERATE(value, ::g->value____.generate());
			};
			if ((FTell() < endOffset)) {
				GENERATE_VAR(message_data, ::g->message_data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("prft"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(reference_track_ID, ::g->reference_track_ID.generate());
			GENERATE_VAR(ntp_timestamp, ::g->ntp_timestamp.generate());
			if ((version() == 0)) {
				GENERATE(media_time, ::g->media_time.generate());
			} else {
				GENERATE(media_time, ::g->media_time__.generate());
			};
			break;
		;
	case STR2INT("pdin"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			_clim25 = 0;
			while (((_clim25++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(pdin_entry, ::g->pdin_entry.generate());
			};
			break;
		;
	case STR2INT("elng"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(extended_language, ::g->extended_language.generate());
			break;
		;
	case STR2INT("kind"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(schemeURI, ::g->schemeURI.generate());
			GENERATE(value, ::g->value____.generate());
			break;
		;
	case STR2INT("trep"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			GENERATE_VAR(track_ID, ::g->track_ID.generate());
			_clim26 = 0;
			while (((_clim26++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("mere"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((contentsize > 4) && (FTell() < endOffset))) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("uuid"):
			GENERATE_VAR(usertype, ::g->usertype.generate(16));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("ilst"):
			_clim27 = 0;
			while (((_clim27++ < 8) && (FTell() < endOffset))) {
				GENERATE_VAR(child_box, ::g->child_box.generate());
				FSeek(child_box().endOffset);
			};
			break;
		;
	case STR2INT("data"):
			GENERATE_VAR(type_indicator, ::g->type_indicator.generate());
			GENERATE_VAR(locale, ::g->locale.generate());
			if ((FTell() < endOffset)) {
				GENERATE(value, ::g->value_____.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("fpar"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if (((contentsize > 4) && (FTell() < endOffset))) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("fiin"):
	case STR2INT("paen"):
	case STR2INT("fire"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("lhdr"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("cdsc"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("pvc1"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("dnld"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("alst"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("afra"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("eqiv"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("mmpu"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("pdam"):
			if ((contentsize > 0)) {
				GENERATE_VAR(data, ::g->data.generate(contentsize));
			};
			break;
		;
	case STR2INT("ihra"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("alis"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(aliasInfo, ::g->aliasInfo.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("avcn"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(parameterSets, ::g->parameterSets.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("avss"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(subSampleInformation, ::g->subSampleInformation.generate((endOffset - FTell())));
			};
			break;
		;
	case STR2INT("fpat"):
	case STR2INT("fprt"):
	case STR2INT("ftap"):
			GENERATE_VAR(version, ::g->version.generate());
			GENERATE_VAR(flag, ::g->flag.generate(3));
			if ((FTell() < endOffset)) {
				GENERATE_VAR(data, ::g->data.generate((endOffset - FTell())));
			};
			break;
		;
	default:
			if ((contentsize > 0)) {
				ChangeArrayLength();
				GENERATE_VAR(unknown, ::g->unknown.generate(contentsize));
				EndChangeArrayLength();
			};
			break;
		;
	};
	EndChangeArrayLength();
	if ((size() && (FTell() != endOffset))) {
		parsedSize = (FTell() - startOffset);
		if (((endOffset > FTell()) && ((endOffset - FTell()) < 4))) {
			FSeek(endOffset);
		};
	};
	writePosition = FTell();
	FSeek(startOffset);
	newSize = (writePosition - startOffset);
	evil = SetEvilBit(false);
	GENERATE_VAR(size, ::g->size.generate({ newSize }));
	SetEvilBit(evil);
	FSeek(writePosition);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


mp4file* mp4file::generate() {
	if (generated == 1) {
		mp4file* new_instance = new mp4file(instances);
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

	chunk_type.resize(4);
	preferred_blocks = { "ftyp" };
	possible_blocks = { "ftyp", "styp" };
	_blim_file = 0;
	while (((_blim_file++ < 25) && ReadBytes(chunk_type, (FTell() + 4), 4, preferred_blocks, possible_blocks))) {
		switch (STR2INT(chunk_type)) {
		case STR2INT("ftyp"):
		case STR2INT("styp"):
			GENERATE_VAR(ftyp_block, ::g->ftyp_block.generate());
			preferred_blocks = { "mdat", "moov" };
			possible_blocks = { "mdat", "moov", "free", "skip", "wide", "moof", "sidx", "ssix", "emsg", "pdin", "meta", "mfra", "styp", "prft", "uuid" };
			break;
		case STR2INT("mdat"):
			GENERATE_VAR(mdat_block, ::g->mdat_block.generate());
			VectorRemove(preferred_blocks, { "mdat" });
			VectorRemove(possible_blocks, { "mdat" });
			break;
		case STR2INT("moov"):
			GENERATE_VAR(moov_block, ::g->moov_block.generate());
			VectorRemove(preferred_blocks, { "moov" });
			VectorRemove(possible_blocks, { "moov" });
			break;
		case STR2INT("moof"):
			GENERATE_VAR(moof_block, ::g->moof_block.generate());
			VectorRemove(possible_blocks, { "moof" });
			break;
		case STR2INT("sidx"):
			GENERATE_VAR(sidx_block, ::g->sidx_block.generate());
			VectorRemove(possible_blocks, { "sidx" });
			break;
		case STR2INT("ssix"):
			GENERATE_VAR(ssix_block, ::g->ssix_block.generate());
			VectorRemove(possible_blocks, { "ssix" });
			break;
		case STR2INT("emsg"):
			GENERATE_VAR(emsg_block, ::g->emsg_block.generate());
			VectorRemove(possible_blocks, { "emsg" });
			break;
		case STR2INT("pdin"):
			GENERATE_VAR(pdin_block, ::g->pdin_block.generate());
			VectorRemove(possible_blocks, { "pdin" });
			break;
		case STR2INT("meta"):
			GENERATE_VAR(meta_block, ::g->meta_block.generate());
			VectorRemove(possible_blocks, { "meta" });
			break;
		case STR2INT("mfra"):
			GENERATE_VAR(mfra_block, ::g->mfra_block.generate());
			VectorRemove(possible_blocks, { "mfra" });
			break;
		case STR2INT("prft"):
			GENERATE_VAR(prft_block, ::g->prft_block.generate());
			VectorRemove(possible_blocks, { "prft" });
			break;
		case STR2INT("uuid"):
			GENERATE_VAR(uuid_block, ::g->uuid_block.generate());
			VectorRemove(possible_blocks, { "uuid" });
			break;
		case STR2INT("free"):
		case STR2INT("skip"):
		case STR2INT("wide"):
			GENERATE_VAR(free_block, ::g->free_block.generate());
			VectorRemove(possible_blocks, { "free" });
			VectorRemove(possible_blocks, { "skip" });
			VectorRemove(possible_blocks, { "wide" });
			break;
		default:
			GENERATE_VAR(unknown_block, ::g->unknown_block.generate());
			break;
		};
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}



void generate_file() {
	::g = new globals_class();

	BigEndian();
	::g->sharedSamplecountVar = 0;
	::g->mdatPosition = 0;
	::g->isVideo = false;
	GENERATE(file, ::g->file.generate());

	file_acc.finish();
	delete_globals();
}

void delete_globals() { delete ::g; }

