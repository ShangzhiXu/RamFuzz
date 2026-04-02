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



class pdf_file {
	std::vector<pdf_file*>& instances;

	ubyte h00_var;
	ubyte h01_var;
	ubyte h02_var;
	ubyte h03_var;
	ubyte h04_var;
	ubyte h05_var;
	ubyte h06_var;
	ubyte h07_var;
	ubyte h08_var;
	ubyte h09_var;
	ubyte h10_var;
	ubyte h11_var;
	ubyte h12_var;
	ubyte h13_var;
	ubyte h14_var;
	std::string obj1_var;
	std::string obj2_var;
	std::string obj3_var;
	std::string obj4_var;
	std::string obj5h_var;
	std::string obj5d_var;
	std::string obj5e_var;
	std::string xhdr_var;
	std::string xe0_var;
	std::string xe1_var;
	std::string xe2_var;
	std::string xe3_var;
	std::string xe4_var;
	std::string xe5_var;
	std::string trail_var;
	std::string xoff_var;
	std::string eofm_var;

public:
	bool h00_exists = false;
	bool h01_exists = false;
	bool h02_exists = false;
	bool h03_exists = false;
	bool h04_exists = false;
	bool h05_exists = false;
	bool h06_exists = false;
	bool h07_exists = false;
	bool h08_exists = false;
	bool h09_exists = false;
	bool h10_exists = false;
	bool h11_exists = false;
	bool h12_exists = false;
	bool h13_exists = false;
	bool h14_exists = false;
	bool obj1_exists = false;
	bool obj2_exists = false;
	bool obj3_exists = false;
	bool obj4_exists = false;
	bool obj5h_exists = false;
	bool obj5d_exists = false;
	bool obj5e_exists = false;
	bool xhdr_exists = false;
	bool xe0_exists = false;
	bool xe1_exists = false;
	bool xe2_exists = false;
	bool xe3_exists = false;
	bool xe4_exists = false;
	bool xe5_exists = false;
	bool trail_exists = false;
	bool xoff_exists = false;
	bool eofm_exists = false;

	ubyte& h00() {
		assert_cond(h00_exists, "struct field h00 does not exist");
		return h00_var;
	}
	ubyte& h01() {
		assert_cond(h01_exists, "struct field h01 does not exist");
		return h01_var;
	}
	ubyte& h02() {
		assert_cond(h02_exists, "struct field h02 does not exist");
		return h02_var;
	}
	ubyte& h03() {
		assert_cond(h03_exists, "struct field h03 does not exist");
		return h03_var;
	}
	ubyte& h04() {
		assert_cond(h04_exists, "struct field h04 does not exist");
		return h04_var;
	}
	ubyte& h05() {
		assert_cond(h05_exists, "struct field h05 does not exist");
		return h05_var;
	}
	ubyte& h06() {
		assert_cond(h06_exists, "struct field h06 does not exist");
		return h06_var;
	}
	ubyte& h07() {
		assert_cond(h07_exists, "struct field h07 does not exist");
		return h07_var;
	}
	ubyte& h08() {
		assert_cond(h08_exists, "struct field h08 does not exist");
		return h08_var;
	}
	ubyte& h09() {
		assert_cond(h09_exists, "struct field h09 does not exist");
		return h09_var;
	}
	ubyte& h10() {
		assert_cond(h10_exists, "struct field h10 does not exist");
		return h10_var;
	}
	ubyte& h11() {
		assert_cond(h11_exists, "struct field h11 does not exist");
		return h11_var;
	}
	ubyte& h12() {
		assert_cond(h12_exists, "struct field h12 does not exist");
		return h12_var;
	}
	ubyte& h13() {
		assert_cond(h13_exists, "struct field h13 does not exist");
		return h13_var;
	}
	ubyte& h14() {
		assert_cond(h14_exists, "struct field h14 does not exist");
		return h14_var;
	}
	std::string& obj1() {
		assert_cond(obj1_exists, "struct field obj1 does not exist");
		return obj1_var;
	}
	std::string& obj2() {
		assert_cond(obj2_exists, "struct field obj2 does not exist");
		return obj2_var;
	}
	std::string& obj3() {
		assert_cond(obj3_exists, "struct field obj3 does not exist");
		return obj3_var;
	}
	std::string& obj4() {
		assert_cond(obj4_exists, "struct field obj4 does not exist");
		return obj4_var;
	}
	std::string& obj5h() {
		assert_cond(obj5h_exists, "struct field obj5h does not exist");
		return obj5h_var;
	}
	std::string& obj5d() {
		assert_cond(obj5d_exists, "struct field obj5d does not exist");
		return obj5d_var;
	}
	std::string& obj5e() {
		assert_cond(obj5e_exists, "struct field obj5e does not exist");
		return obj5e_var;
	}
	std::string& xhdr() {
		assert_cond(xhdr_exists, "struct field xhdr does not exist");
		return xhdr_var;
	}
	std::string& xe0() {
		assert_cond(xe0_exists, "struct field xe0 does not exist");
		return xe0_var;
	}
	std::string& xe1() {
		assert_cond(xe1_exists, "struct field xe1 does not exist");
		return xe1_var;
	}
	std::string& xe2() {
		assert_cond(xe2_exists, "struct field xe2 does not exist");
		return xe2_var;
	}
	std::string& xe3() {
		assert_cond(xe3_exists, "struct field xe3 does not exist");
		return xe3_var;
	}
	std::string& xe4() {
		assert_cond(xe4_exists, "struct field xe4 does not exist");
		return xe4_var;
	}
	std::string& xe5() {
		assert_cond(xe5_exists, "struct field xe5 does not exist");
		return xe5_var;
	}
	std::string& trail() {
		assert_cond(trail_exists, "struct field trail does not exist");
		return trail_var;
	}
	std::string& xoff() {
		assert_cond(xoff_exists, "struct field xoff does not exist");
		return xoff_var;
	}
	std::string& eofm() {
		assert_cond(eofm_exists, "struct field eofm does not exist");
		return eofm_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	pdf_file& operator () () { return *instances.back(); }
	pdf_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	pdf_file(std::vector<pdf_file*>& instances) : instances(instances) { instances.push_back(this); }
	~pdf_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			pdf_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	pdf_file* generate();
};

int pdf_file::_parent_id = 0;
int pdf_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "%PDF", "xref", "%%EO" };


std::vector<pdf_file*> pdf_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "h00", "ubyte_class" }, { "h01", "ubyte_class" }, { "h02", "ubyte_class" }, { "h03", "ubyte_class" }, { "h04", "ubyte_class" }, { "h05", "ubyte_class" }, { "h06", "ubyte_class" }, { "h07", "ubyte_class" }, { "h08", "ubyte_class" }, { "h09", "ubyte_class" }, { "h10", "ubyte_class" }, { "h11", "ubyte_class" }, { "h12", "ubyte_class" }, { "h13", "ubyte_class" }, { "h14", "ubyte_class" }, { "obj1", "char_array_class" }, { "obj2", "char_array_class" }, { "obj3", "char_array_class" }, { "obj4", "char_array_class" }, { "obj5h", "char_array_class" }, { "obj5d", "char_array_class" }, { "obj5e", "char_array_class" }, { "xhdr", "char_array_class" }, { "xe0", "char_array_class" }, { "xe1", "char_array_class" }, { "xe2", "char_array_class" }, { "xe3", "char_array_class" }, { "xe4", "char_array_class" }, { "xe5", "char_array_class" }, { "trail", "char_array_class" }, { "xoff", "char_array_class" }, { "eofm", "char_array_class" }, { "file", "pdf_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	ubyte_class h00;
	ubyte_class h01;
	ubyte_class h02;
	ubyte_class h03;
	ubyte_class h04;
	ubyte_class h05;
	ubyte_class h06;
	ubyte_class h07;
	ubyte_class h08;
	ubyte_class h09;
	ubyte_class h10;
	ubyte_class h11;
	ubyte_class h12;
	ubyte_class h13;
	ubyte_class h14;
	char_class obj1_element;
	char_array_class obj1;
	char_class obj2_element;
	char_array_class obj2;
	char_class obj3_element;
	char_array_class obj3;
	char_class obj4_element;
	char_array_class obj4;
	char_class obj5h_element;
	char_array_class obj5h;
	char_class obj5d_element;
	char_array_class obj5d;
	char_class obj5e_element;
	char_array_class obj5e;
	char_class xhdr_element;
	char_array_class xhdr;
	char_class xe0_element;
	char_array_class xe0;
	char_class xe1_element;
	char_array_class xe1;
	char_class xe2_element;
	char_array_class xe2;
	char_class xe3_element;
	char_array_class xe3;
	char_class xe4_element;
	char_array_class xe4;
	char_class xe5_element;
	char_array_class xe5;
	char_class trail_element;
	char_array_class trail;
	char_class xoff_element;
	char_array_class xoff;
	char_class eofm_element;
	char_array_class eofm;
	pdf_file file;


	globals_class() :
		h00(1),
		h01(1),
		h02(1),
		h03(1),
		h04(1),
		h05(1),
		h06(1),
		h07(1),
		h08(1),
		h09(1),
		h10(1),
		h11(1),
		h12(1),
		h13(1),
		h14(1),
		obj1_element(false),
		obj1(obj1_element),
		obj2_element(false),
		obj2(obj2_element),
		obj3_element(false),
		obj3(obj3_element),
		obj4_element(false),
		obj4(obj4_element),
		obj5h_element(false),
		obj5h(obj5h_element),
		obj5d_element(false),
		obj5d(obj5d_element),
		obj5e_element(false),
		obj5e(obj5e_element),
		xhdr_element(false),
		xhdr(xhdr_element),
		xe0_element(false),
		xe0(xe0_element),
		xe1_element(false),
		xe1(xe1_element),
		xe2_element(false),
		xe2(xe2_element),
		xe3_element(false),
		xe3(xe3_element),
		xe4_element(false),
		xe4(xe4_element),
		xe5_element(false),
		xe5(xe5_element),
		trail_element(false),
		trail(trail_element),
		xoff_element(false),
		xoff(xoff_element),
		eofm_element(false),
		eofm(eofm_element),
		file(pdf_file_file_instances)
	{}
};

globals_class* g;


pdf_file* pdf_file::generate() {
	if (generated == 1) {
		pdf_file* new_instance = new pdf_file(instances);
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

	GENERATE_VAR(h00, ::g->h00.generate({ 0x25 }));
	GENERATE_VAR(h01, ::g->h01.generate({ 0x50 }));
	GENERATE_VAR(h02, ::g->h02.generate({ 0x44 }));
	GENERATE_VAR(h03, ::g->h03.generate({ 0x46 }));
	GENERATE_VAR(h04, ::g->h04.generate({ 0x2D }));
	GENERATE_VAR(h05, ::g->h05.generate({ 0x31 }));
	GENERATE_VAR(h06, ::g->h06.generate({ 0x2E }));
	GENERATE_VAR(h07, ::g->h07.generate({ 0x34, 0x35, 0x36, 0x37 }));
	GENERATE_VAR(h08, ::g->h08.generate({ 0x0A }));
	GENERATE_VAR(h09, ::g->h09.generate({ 0x25 }));
	GENERATE_VAR(h10, ::g->h10.generate({ 0xE2 }));
	GENERATE_VAR(h11, ::g->h11.generate({ 0xE3 }));
	GENERATE_VAR(h12, ::g->h12.generate({ 0xCF }));
	GENERATE_VAR(h13, ::g->h13.generate({ 0xD3 }));
	GENERATE_VAR(h14, ::g->h14.generate({ 0x0A }));
	GENERATE_VAR(obj1, ::g->obj1.generate(49, { "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n" }));
	GENERATE_VAR(obj2, ::g->obj2.generate(81, { "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 /MediaBox [0 0 612 792] >>\nendobj\n" }));
	GENERATE_VAR(obj3, ::g->obj3.generate(102, { "3 0 obj\n<< /Type /Page /Parent 2 0 R /Resources << /Font << /F1 4 0 R >> >> /Contents 5 0 R >>\nendobj\n" }));
	GENERATE_VAR(obj4, ::g->obj4.generate(97, { "4 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica /Encoding /WinAnsiEncoding >>\nendobj\n" }));
	GENERATE_VAR(obj5h, ::g->obj5h.generate(32, { "5 0 obj\n<< /Length 43 >>\nstream\n" }));
	GENERATE_VAR(obj5d, ::g->obj5d.generate(43, { "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET" }));
	GENERATE_VAR(obj5e, ::g->obj5e.generate(18, { "\nendstream\nendobj\n" }));
	GENERATE_VAR(xhdr, ::g->xhdr.generate(9, { "xref\n0 6\n" }));
	GENERATE_VAR(xe0, ::g->xe0.generate(20, { "0000000000 65535 f \n" }));
	GENERATE_VAR(xe1, ::g->xe1.generate(20, { "0000000015 00000 n \n" }));
	GENERATE_VAR(xe2, ::g->xe2.generate(20, { "0000000064 00000 n \n" }));
	GENERATE_VAR(xe3, ::g->xe3.generate(20, { "0000000145 00000 n \n" }));
	GENERATE_VAR(xe4, ::g->xe4.generate(20, { "0000000247 00000 n \n" }));
	GENERATE_VAR(xe5, ::g->xe5.generate(20, { "0000000344 00000 n \n" }));
	GENERATE_VAR(trail, ::g->trail.generate(44, { "trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n" }));
	GENERATE_VAR(xoff, ::g->xoff.generate(4, { "437\n" }));
	GENERATE_VAR(eofm, ::g->eofm.generate(6, { "%%EOF\n" }));

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

