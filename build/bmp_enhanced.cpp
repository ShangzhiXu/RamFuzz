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



class BMP_FILE_HEADER {
	std::vector<BMP_FILE_HEADER*>& instances;

	std::string signature_var;
	uint32 file_size_var;
	uint16 reserved1_var;
	uint16 reserved2_var;
	uint32 pixel_data_offset_var;

public:
	bool signature_exists = false;
	bool file_size_exists = false;
	bool reserved1_exists = false;
	bool reserved2_exists = false;
	bool pixel_data_offset_exists = false;

	std::string& signature() {
		assert_cond(signature_exists, "struct field signature does not exist");
		return signature_var;
	}
	uint32& file_size() {
		assert_cond(file_size_exists, "struct field file_size does not exist");
		return file_size_var;
	}
	uint16& reserved1() {
		assert_cond(reserved1_exists, "struct field reserved1 does not exist");
		return reserved1_var;
	}
	uint16& reserved2() {
		assert_cond(reserved2_exists, "struct field reserved2 does not exist");
		return reserved2_var;
	}
	uint32& pixel_data_offset() {
		assert_cond(pixel_data_offset_exists, "struct field pixel_data_offset does not exist");
		return pixel_data_offset_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BMP_FILE_HEADER& operator () () { return *instances.back(); }
	BMP_FILE_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BMP_FILE_HEADER(std::vector<BMP_FILE_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~BMP_FILE_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BMP_FILE_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BMP_FILE_HEADER* generate();
};

int BMP_FILE_HEADER::_parent_id = 0;
int BMP_FILE_HEADER::_index_start = 0;



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



class BITMAPINFOHEADER {
	std::vector<BITMAPINFOHEADER*>& instances;

	uint32 header_size_var;
	int32 width_var;
	int32 height_var;
	uint16 color_planes_var;
	uint16 bits_per_pixel_var;
	uint32 compression_var;
	uint32 image_size_var;
	int32 x_ppm_var;
	int32 y_ppm_var;
	uint32 colors_used_var;
	uint32 colors_important_var;

public:
	bool header_size_exists = false;
	bool width_exists = false;
	bool height_exists = false;
	bool color_planes_exists = false;
	bool bits_per_pixel_exists = false;
	bool compression_exists = false;
	bool image_size_exists = false;
	bool x_ppm_exists = false;
	bool y_ppm_exists = false;
	bool colors_used_exists = false;
	bool colors_important_exists = false;

	uint32& header_size() {
		assert_cond(header_size_exists, "struct field header_size does not exist");
		return header_size_var;
	}
	int32& width() {
		assert_cond(width_exists, "struct field width does not exist");
		return width_var;
	}
	int32& height() {
		assert_cond(height_exists, "struct field height does not exist");
		return height_var;
	}
	uint16& color_planes() {
		assert_cond(color_planes_exists, "struct field color_planes does not exist");
		return color_planes_var;
	}
	uint16& bits_per_pixel() {
		assert_cond(bits_per_pixel_exists, "struct field bits_per_pixel does not exist");
		return bits_per_pixel_var;
	}
	uint32& compression() {
		assert_cond(compression_exists, "struct field compression does not exist");
		return compression_var;
	}
	uint32& image_size() {
		assert_cond(image_size_exists, "struct field image_size does not exist");
		return image_size_var;
	}
	int32& x_ppm() {
		assert_cond(x_ppm_exists, "struct field x_ppm does not exist");
		return x_ppm_var;
	}
	int32& y_ppm() {
		assert_cond(y_ppm_exists, "struct field y_ppm does not exist");
		return y_ppm_var;
	}
	uint32& colors_used() {
		assert_cond(colors_used_exists, "struct field colors_used does not exist");
		return colors_used_var;
	}
	uint32& colors_important() {
		assert_cond(colors_important_exists, "struct field colors_important does not exist");
		return colors_important_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BITMAPINFOHEADER& operator () () { return *instances.back(); }
	BITMAPINFOHEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BITMAPINFOHEADER(std::vector<BITMAPINFOHEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~BITMAPINFOHEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BITMAPINFOHEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BITMAPINFOHEADER* generate();
};

int BITMAPINFOHEADER::_parent_id = 0;
int BITMAPINFOHEADER::_index_start = 0;



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



class bmp_file {
	std::vector<bmp_file*>& instances;

	BMP_FILE_HEADER* file_hdr_var;
	BITMAPINFOHEADER* dib_hdr_var;
	std::vector<ubyte> color_table_var;
	std::vector<ubyte> pixel_data_var;

public:
	bool file_hdr_exists = false;
	bool dib_hdr_exists = false;
	bool color_table_exists = false;
	bool pixel_data_exists = false;

	BMP_FILE_HEADER& file_hdr() {
		assert_cond(file_hdr_exists, "struct field file_hdr does not exist");
		return *file_hdr_var;
	}
	BITMAPINFOHEADER& dib_hdr() {
		assert_cond(dib_hdr_exists, "struct field dib_hdr does not exist");
		return *dib_hdr_var;
	}
	std::vector<ubyte>& color_table() {
		assert_cond(color_table_exists, "struct field color_table does not exist");
		return color_table_var;
	}
	std::vector<ubyte>& pixel_data() {
		assert_cond(pixel_data_exists, "struct field pixel_data does not exist");
		return pixel_data_var;
	}

	/* locals */
	uint32 ct_size;
	int32 abs_h;
	uint32 row_size;
	uint32 pixel_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	bmp_file& operator () () { return *instances.back(); }
	bmp_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	bmp_file(std::vector<bmp_file*>& instances) : instances(instances) { instances.push_back(this); }
	~bmp_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			bmp_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	bmp_file* generate();
};

int bmp_file::_parent_id = 0;
int bmp_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "BM" };


std::vector<BMP_FILE_HEADER*> BMP_FILE_HEADER_file_hdr_instances;
std::vector<BITMAPINFOHEADER*> BITMAPINFOHEADER_dib_hdr_instances;
std::vector<bmp_file*> bmp_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "signature", "char_array_class" }, { "file_size", "uint32_class" }, { "reserved1", "uint16_class" }, { "reserved2", "uint16_class" }, { "pixel_data_offset", "uint32_class" }, { "file_hdr", "BMP_FILE_HEADER" }, { "header_size", "uint32_class" }, { "width", "int32_class" }, { "height", "int32_class" }, { "color_planes", "uint16_class" }, { "bits_per_pixel", "uint16_class" }, { "compression", "uint32_class" }, { "image_size", "uint32_class" }, { "x_ppm", "int32_class" }, { "y_ppm", "int32_class" }, { "colors_used", "uint32_class" }, { "colors_important", "uint32_class" }, { "dib_hdr", "BITMAPINFOHEADER" }, { "color_table", "ubyte_array_class" }, { "pixel_data", "ubyte_array_class" }, { "file", "bmp_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 1, 512 }, { 1, 512 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	char_class signature_element;
	char_array_class signature;
	uint32_class file_size;
	uint16_class reserved1;
	uint16_class reserved2;
	uint32_class pixel_data_offset;
	BMP_FILE_HEADER file_hdr;
	uint32_class header_size;
	int32_class width;
	int32_class height;
	uint16_class color_planes;
	uint16_class bits_per_pixel;
	uint32_class compression;
	uint32_class image_size;
	int32_class x_ppm;
	int32_class y_ppm;
	uint32_class colors_used;
	uint32_class colors_important;
	BITMAPINFOHEADER dib_hdr;
	ubyte_class color_table_element;
	ubyte_array_class color_table;
	ubyte_class pixel_data_element;
	ubyte_array_class pixel_data;
	bmp_file file;


	globals_class() :
		signature_element(false),
		signature(signature_element),
		file_size(1),
		reserved1(1),
		reserved2(1),
		pixel_data_offset(1),
		file_hdr(BMP_FILE_HEADER_file_hdr_instances),
		header_size(1),
		width(3),
		height(4),
		color_planes(1),
		bits_per_pixel(1),
		compression(1),
		image_size(1),
		x_ppm(1),
		y_ppm(1),
		colors_used(1),
		colors_important(1),
		dib_hdr(BITMAPINFOHEADER_dib_hdr_instances),
		color_table_element(false),
		color_table(color_table_element),
		pixel_data_element(false),
		pixel_data(pixel_data_element),
		file(bmp_file_file_instances)
	{}
};

globals_class* g;


BMP_FILE_HEADER* BMP_FILE_HEADER::generate() {
	if (generated == 1) {
		BMP_FILE_HEADER* new_instance = new BMP_FILE_HEADER(instances);
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

	GENERATE_VAR(signature, ::g->signature.generate(2, { "BM" }));
	GENERATE_VAR(file_size, ::g->file_size.generate());
	GENERATE_VAR(reserved1, ::g->reserved1.generate({ 0 }));
	GENERATE_VAR(reserved2, ::g->reserved2.generate({ 0 }));
	GENERATE_VAR(pixel_data_offset, ::g->pixel_data_offset.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


BITMAPINFOHEADER* BITMAPINFOHEADER::generate() {
	if (generated == 1) {
		BITMAPINFOHEADER* new_instance = new BITMAPINFOHEADER(instances);
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

	GENERATE_VAR(header_size, ::g->header_size.generate({ 40 }));
	GENERATE_VAR(width, ::g->width.generate());
	GENERATE_VAR(height, ::g->height.generate());
	GENERATE_VAR(color_planes, ::g->color_planes.generate({ 1 }));
	GENERATE_VAR(bits_per_pixel, ::g->bits_per_pixel.generate({ 1, 4, 8, 24, 32 }));
	GENERATE_VAR(compression, ::g->compression.generate({ 0 }));
	GENERATE_VAR(image_size, ::g->image_size.generate());
	GENERATE_VAR(x_ppm, ::g->x_ppm.generate());
	GENERATE_VAR(y_ppm, ::g->y_ppm.generate());
	GENERATE_VAR(colors_used, ::g->colors_used.generate());
	GENERATE_VAR(colors_important, ::g->colors_important.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


bmp_file* bmp_file::generate() {
	if (generated == 1) {
		bmp_file* new_instance = new bmp_file(instances);
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

	GENERATE_VAR(file_hdr, ::g->file_hdr.generate());
	GENERATE_VAR(dib_hdr, ::g->dib_hdr.generate());
	ct_size = 0;
	if ((dib_hdr().bits_per_pixel() <= 8)) {
		ct_size = ((dib_hdr().colors_used() > 0) ? dib_hdr().colors_used() : (1 << dib_hdr().bits_per_pixel()));
		if ((ct_size > 256)) {
		ct_size = 256;
		};
		GENERATE_VAR(color_table, ::g->color_table.generate((ct_size * 4)));
	};
	abs_h = dib_hdr().height();
	if ((abs_h < 0)) {
	abs_h = -abs_h;
	};
	row_size = ((((dib_hdr().bits_per_pixel() * dib_hdr().width()) + 31) / 32) * 4);
	pixel_size = (row_size * abs_h);
	if (((pixel_size > 0) && (pixel_size < 1048576))) {
		GENERATE_VAR(pixel_data, ::g->pixel_data.generate(pixel_size));
	} else {
		GENERATE_VAR(pixel_data, ::g->pixel_data.generate(64));
	};

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

