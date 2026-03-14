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



class ELF_HEADER {
	std::vector<ELF_HEADER*>& instances;

	ubyte ei_mag0_var;
	ubyte ei_mag1_var;
	ubyte ei_mag2_var;
	ubyte ei_mag3_var;
	ubyte ei_class_var;
	ubyte ei_data_var;
	ubyte ei_version_var;
	ubyte ei_osabi_var;
	ubyte ei_abiversion_var;
	ubyte ei_pad0_var;
	ubyte ei_pad1_var;
	ubyte ei_pad2_var;
	ubyte ei_pad3_var;
	ubyte ei_pad4_var;
	ubyte ei_pad5_var;
	ubyte ei_pad6_var;
	uint16 e_type_var;
	uint16 e_machine_var;
	uint32 e_version_var;
	uint64 e_entry_var;
	uint64 e_phoff_var;
	uint64 e_shoff_var;
	uint32 e_flags_var;
	uint16 e_ehsize_var;
	uint16 e_phentsize_var;
	uint16 e_phnum_var;
	uint16 e_shentsize_var;
	uint16 e_shnum_var;
	uint16 e_shstrndx_var;

public:
	bool ei_mag0_exists = false;
	bool ei_mag1_exists = false;
	bool ei_mag2_exists = false;
	bool ei_mag3_exists = false;
	bool ei_class_exists = false;
	bool ei_data_exists = false;
	bool ei_version_exists = false;
	bool ei_osabi_exists = false;
	bool ei_abiversion_exists = false;
	bool ei_pad0_exists = false;
	bool ei_pad1_exists = false;
	bool ei_pad2_exists = false;
	bool ei_pad3_exists = false;
	bool ei_pad4_exists = false;
	bool ei_pad5_exists = false;
	bool ei_pad6_exists = false;
	bool e_type_exists = false;
	bool e_machine_exists = false;
	bool e_version_exists = false;
	bool e_entry_exists = false;
	bool e_phoff_exists = false;
	bool e_shoff_exists = false;
	bool e_flags_exists = false;
	bool e_ehsize_exists = false;
	bool e_phentsize_exists = false;
	bool e_phnum_exists = false;
	bool e_shentsize_exists = false;
	bool e_shnum_exists = false;
	bool e_shstrndx_exists = false;

	ubyte& ei_mag0() {
		assert_cond(ei_mag0_exists, "struct field ei_mag0 does not exist");
		return ei_mag0_var;
	}
	ubyte& ei_mag1() {
		assert_cond(ei_mag1_exists, "struct field ei_mag1 does not exist");
		return ei_mag1_var;
	}
	ubyte& ei_mag2() {
		assert_cond(ei_mag2_exists, "struct field ei_mag2 does not exist");
		return ei_mag2_var;
	}
	ubyte& ei_mag3() {
		assert_cond(ei_mag3_exists, "struct field ei_mag3 does not exist");
		return ei_mag3_var;
	}
	ubyte& ei_class() {
		assert_cond(ei_class_exists, "struct field ei_class does not exist");
		return ei_class_var;
	}
	ubyte& ei_data() {
		assert_cond(ei_data_exists, "struct field ei_data does not exist");
		return ei_data_var;
	}
	ubyte& ei_version() {
		assert_cond(ei_version_exists, "struct field ei_version does not exist");
		return ei_version_var;
	}
	ubyte& ei_osabi() {
		assert_cond(ei_osabi_exists, "struct field ei_osabi does not exist");
		return ei_osabi_var;
	}
	ubyte& ei_abiversion() {
		assert_cond(ei_abiversion_exists, "struct field ei_abiversion does not exist");
		return ei_abiversion_var;
	}
	ubyte& ei_pad0() {
		assert_cond(ei_pad0_exists, "struct field ei_pad0 does not exist");
		return ei_pad0_var;
	}
	ubyte& ei_pad1() {
		assert_cond(ei_pad1_exists, "struct field ei_pad1 does not exist");
		return ei_pad1_var;
	}
	ubyte& ei_pad2() {
		assert_cond(ei_pad2_exists, "struct field ei_pad2 does not exist");
		return ei_pad2_var;
	}
	ubyte& ei_pad3() {
		assert_cond(ei_pad3_exists, "struct field ei_pad3 does not exist");
		return ei_pad3_var;
	}
	ubyte& ei_pad4() {
		assert_cond(ei_pad4_exists, "struct field ei_pad4 does not exist");
		return ei_pad4_var;
	}
	ubyte& ei_pad5() {
		assert_cond(ei_pad5_exists, "struct field ei_pad5 does not exist");
		return ei_pad5_var;
	}
	ubyte& ei_pad6() {
		assert_cond(ei_pad6_exists, "struct field ei_pad6 does not exist");
		return ei_pad6_var;
	}
	uint16& e_type() {
		assert_cond(e_type_exists, "struct field e_type does not exist");
		return e_type_var;
	}
	uint16& e_machine() {
		assert_cond(e_machine_exists, "struct field e_machine does not exist");
		return e_machine_var;
	}
	uint32& e_version() {
		assert_cond(e_version_exists, "struct field e_version does not exist");
		return e_version_var;
	}
	uint64& e_entry() {
		assert_cond(e_entry_exists, "struct field e_entry does not exist");
		return e_entry_var;
	}
	uint64& e_phoff() {
		assert_cond(e_phoff_exists, "struct field e_phoff does not exist");
		return e_phoff_var;
	}
	uint64& e_shoff() {
		assert_cond(e_shoff_exists, "struct field e_shoff does not exist");
		return e_shoff_var;
	}
	uint32& e_flags() {
		assert_cond(e_flags_exists, "struct field e_flags does not exist");
		return e_flags_var;
	}
	uint16& e_ehsize() {
		assert_cond(e_ehsize_exists, "struct field e_ehsize does not exist");
		return e_ehsize_var;
	}
	uint16& e_phentsize() {
		assert_cond(e_phentsize_exists, "struct field e_phentsize does not exist");
		return e_phentsize_var;
	}
	uint16& e_phnum() {
		assert_cond(e_phnum_exists, "struct field e_phnum does not exist");
		return e_phnum_var;
	}
	uint16& e_shentsize() {
		assert_cond(e_shentsize_exists, "struct field e_shentsize does not exist");
		return e_shentsize_var;
	}
	uint16& e_shnum() {
		assert_cond(e_shnum_exists, "struct field e_shnum does not exist");
		return e_shnum_var;
	}
	uint16& e_shstrndx() {
		assert_cond(e_shstrndx_exists, "struct field e_shstrndx does not exist");
		return e_shstrndx_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ELF_HEADER& operator () () { return *instances.back(); }
	ELF_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ELF_HEADER(std::vector<ELF_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~ELF_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ELF_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ELF_HEADER* generate();
};

int ELF_HEADER::_parent_id = 0;
int ELF_HEADER::_index_start = 0;



class PROGRAM_HEADER_PHDR {
	std::vector<PROGRAM_HEADER_PHDR*>& instances;

	uint32 p_type_var;
	uint32 p_flags_var;
	uint64 p_offset_var;
	uint64 p_vaddr_var;
	uint64 p_paddr_var;
	uint64 p_filesz_var;
	uint64 p_memsz_var;
	uint64 p_align_var;

public:
	bool p_type_exists = false;
	bool p_flags_exists = false;
	bool p_offset_exists = false;
	bool p_vaddr_exists = false;
	bool p_paddr_exists = false;
	bool p_filesz_exists = false;
	bool p_memsz_exists = false;
	bool p_align_exists = false;

	uint32& p_type() {
		assert_cond(p_type_exists, "struct field p_type does not exist");
		return p_type_var;
	}
	uint32& p_flags() {
		assert_cond(p_flags_exists, "struct field p_flags does not exist");
		return p_flags_var;
	}
	uint64& p_offset() {
		assert_cond(p_offset_exists, "struct field p_offset does not exist");
		return p_offset_var;
	}
	uint64& p_vaddr() {
		assert_cond(p_vaddr_exists, "struct field p_vaddr does not exist");
		return p_vaddr_var;
	}
	uint64& p_paddr() {
		assert_cond(p_paddr_exists, "struct field p_paddr does not exist");
		return p_paddr_var;
	}
	uint64& p_filesz() {
		assert_cond(p_filesz_exists, "struct field p_filesz does not exist");
		return p_filesz_var;
	}
	uint64& p_memsz() {
		assert_cond(p_memsz_exists, "struct field p_memsz does not exist");
		return p_memsz_var;
	}
	uint64& p_align() {
		assert_cond(p_align_exists, "struct field p_align does not exist");
		return p_align_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PROGRAM_HEADER_PHDR& operator () () { return *instances.back(); }
	PROGRAM_HEADER_PHDR& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PROGRAM_HEADER_PHDR(std::vector<PROGRAM_HEADER_PHDR*>& instances) : instances(instances) { instances.push_back(this); }
	~PROGRAM_HEADER_PHDR() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PROGRAM_HEADER_PHDR* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PROGRAM_HEADER_PHDR* generate();
};

int PROGRAM_HEADER_PHDR::_parent_id = 0;
int PROGRAM_HEADER_PHDR::_index_start = 0;



class PROGRAM_HEADER_LOAD {
	std::vector<PROGRAM_HEADER_LOAD*>& instances;

	uint32 p_type_var;
	uint32 p_flags_var;
	uint64 p_offset_var;
	uint64 p_vaddr_var;
	uint64 p_paddr_var;
	uint64 p_filesz_var;
	uint64 p_memsz_var;
	uint64 p_align_var;

public:
	bool p_type_exists = false;
	bool p_flags_exists = false;
	bool p_offset_exists = false;
	bool p_vaddr_exists = false;
	bool p_paddr_exists = false;
	bool p_filesz_exists = false;
	bool p_memsz_exists = false;
	bool p_align_exists = false;

	uint32& p_type() {
		assert_cond(p_type_exists, "struct field p_type does not exist");
		return p_type_var;
	}
	uint32& p_flags() {
		assert_cond(p_flags_exists, "struct field p_flags does not exist");
		return p_flags_var;
	}
	uint64& p_offset() {
		assert_cond(p_offset_exists, "struct field p_offset does not exist");
		return p_offset_var;
	}
	uint64& p_vaddr() {
		assert_cond(p_vaddr_exists, "struct field p_vaddr does not exist");
		return p_vaddr_var;
	}
	uint64& p_paddr() {
		assert_cond(p_paddr_exists, "struct field p_paddr does not exist");
		return p_paddr_var;
	}
	uint64& p_filesz() {
		assert_cond(p_filesz_exists, "struct field p_filesz does not exist");
		return p_filesz_var;
	}
	uint64& p_memsz() {
		assert_cond(p_memsz_exists, "struct field p_memsz does not exist");
		return p_memsz_var;
	}
	uint64& p_align() {
		assert_cond(p_align_exists, "struct field p_align does not exist");
		return p_align_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PROGRAM_HEADER_LOAD& operator () () { return *instances.back(); }
	PROGRAM_HEADER_LOAD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PROGRAM_HEADER_LOAD(std::vector<PROGRAM_HEADER_LOAD*>& instances) : instances(instances) { instances.push_back(this); }
	~PROGRAM_HEADER_LOAD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PROGRAM_HEADER_LOAD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PROGRAM_HEADER_LOAD* generate();
};

int PROGRAM_HEADER_LOAD::_parent_id = 0;
int PROGRAM_HEADER_LOAD::_index_start = 0;



class PROGRAM_HEADER_NOTE {
	std::vector<PROGRAM_HEADER_NOTE*>& instances;

	uint32 p_type_var;
	uint32 p_flags_var;
	uint64 p_offset_var;
	uint64 p_vaddr_var;
	uint64 p_paddr_var;
	uint64 p_filesz_var;
	uint64 p_memsz_var;
	uint64 p_align_var;

public:
	bool p_type_exists = false;
	bool p_flags_exists = false;
	bool p_offset_exists = false;
	bool p_vaddr_exists = false;
	bool p_paddr_exists = false;
	bool p_filesz_exists = false;
	bool p_memsz_exists = false;
	bool p_align_exists = false;

	uint32& p_type() {
		assert_cond(p_type_exists, "struct field p_type does not exist");
		return p_type_var;
	}
	uint32& p_flags() {
		assert_cond(p_flags_exists, "struct field p_flags does not exist");
		return p_flags_var;
	}
	uint64& p_offset() {
		assert_cond(p_offset_exists, "struct field p_offset does not exist");
		return p_offset_var;
	}
	uint64& p_vaddr() {
		assert_cond(p_vaddr_exists, "struct field p_vaddr does not exist");
		return p_vaddr_var;
	}
	uint64& p_paddr() {
		assert_cond(p_paddr_exists, "struct field p_paddr does not exist");
		return p_paddr_var;
	}
	uint64& p_filesz() {
		assert_cond(p_filesz_exists, "struct field p_filesz does not exist");
		return p_filesz_var;
	}
	uint64& p_memsz() {
		assert_cond(p_memsz_exists, "struct field p_memsz does not exist");
		return p_memsz_var;
	}
	uint64& p_align() {
		assert_cond(p_align_exists, "struct field p_align does not exist");
		return p_align_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PROGRAM_HEADER_NOTE& operator () () { return *instances.back(); }
	PROGRAM_HEADER_NOTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PROGRAM_HEADER_NOTE(std::vector<PROGRAM_HEADER_NOTE*>& instances) : instances(instances) { instances.push_back(this); }
	~PROGRAM_HEADER_NOTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PROGRAM_HEADER_NOTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PROGRAM_HEADER_NOTE* generate();
};

int PROGRAM_HEADER_NOTE::_parent_id = 0;
int PROGRAM_HEADER_NOTE::_index_start = 0;



class TEXT_SECTION {
	std::vector<TEXT_SECTION*>& instances;

	ubyte insn0_var;
	ubyte insn1_var;
	ubyte insn2_var;
	ubyte insn3_var;
	ubyte insn4_var;
	ubyte insn5_var;
	ubyte insn6_var;
	ubyte insn7_var;
	ubyte insn8_var;
	ubyte insn9_var;

public:
	bool insn0_exists = false;
	bool insn1_exists = false;
	bool insn2_exists = false;
	bool insn3_exists = false;
	bool insn4_exists = false;
	bool insn5_exists = false;
	bool insn6_exists = false;
	bool insn7_exists = false;
	bool insn8_exists = false;
	bool insn9_exists = false;

	ubyte& insn0() {
		assert_cond(insn0_exists, "struct field insn0 does not exist");
		return insn0_var;
	}
	ubyte& insn1() {
		assert_cond(insn1_exists, "struct field insn1 does not exist");
		return insn1_var;
	}
	ubyte& insn2() {
		assert_cond(insn2_exists, "struct field insn2 does not exist");
		return insn2_var;
	}
	ubyte& insn3() {
		assert_cond(insn3_exists, "struct field insn3 does not exist");
		return insn3_var;
	}
	ubyte& insn4() {
		assert_cond(insn4_exists, "struct field insn4 does not exist");
		return insn4_var;
	}
	ubyte& insn5() {
		assert_cond(insn5_exists, "struct field insn5 does not exist");
		return insn5_var;
	}
	ubyte& insn6() {
		assert_cond(insn6_exists, "struct field insn6 does not exist");
		return insn6_var;
	}
	ubyte& insn7() {
		assert_cond(insn7_exists, "struct field insn7 does not exist");
		return insn7_var;
	}
	ubyte& insn8() {
		assert_cond(insn8_exists, "struct field insn8 does not exist");
		return insn8_var;
	}
	ubyte& insn9() {
		assert_cond(insn9_exists, "struct field insn9 does not exist");
		return insn9_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	TEXT_SECTION& operator () () { return *instances.back(); }
	TEXT_SECTION& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	TEXT_SECTION(std::vector<TEXT_SECTION*>& instances) : instances(instances) { instances.push_back(this); }
	~TEXT_SECTION() {
		if (generated == 2)
			return;
		while (instances.size()) {
			TEXT_SECTION* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	TEXT_SECTION* generate();
};

int TEXT_SECTION::_parent_id = 0;
int TEXT_SECTION::_index_start = 0;



class NOTE_SECTION {
	std::vector<NOTE_SECTION*>& instances;

	uint32 n_namesz_var;
	uint32 n_descsz_var;
	uint32 n_type_var;
	ubyte name0_var;
	ubyte name1_var;
	ubyte name2_var;
	ubyte name3_var;
	ubyte desc0_var;
	ubyte desc1_var;
	ubyte desc2_var;
	ubyte desc3_var;
	ubyte desc4_var;
	ubyte desc5_var;
	ubyte desc6_var;
	ubyte desc7_var;
	ubyte desc8_var;
	ubyte desc9_var;
	ubyte desc10_var;
	ubyte desc11_var;
	ubyte desc12_var;
	ubyte desc13_var;
	ubyte desc14_var;
	ubyte desc15_var;

public:
	bool n_namesz_exists = false;
	bool n_descsz_exists = false;
	bool n_type_exists = false;
	bool name0_exists = false;
	bool name1_exists = false;
	bool name2_exists = false;
	bool name3_exists = false;
	bool desc0_exists = false;
	bool desc1_exists = false;
	bool desc2_exists = false;
	bool desc3_exists = false;
	bool desc4_exists = false;
	bool desc5_exists = false;
	bool desc6_exists = false;
	bool desc7_exists = false;
	bool desc8_exists = false;
	bool desc9_exists = false;
	bool desc10_exists = false;
	bool desc11_exists = false;
	bool desc12_exists = false;
	bool desc13_exists = false;
	bool desc14_exists = false;
	bool desc15_exists = false;

	uint32& n_namesz() {
		assert_cond(n_namesz_exists, "struct field n_namesz does not exist");
		return n_namesz_var;
	}
	uint32& n_descsz() {
		assert_cond(n_descsz_exists, "struct field n_descsz does not exist");
		return n_descsz_var;
	}
	uint32& n_type() {
		assert_cond(n_type_exists, "struct field n_type does not exist");
		return n_type_var;
	}
	ubyte& name0() {
		assert_cond(name0_exists, "struct field name0 does not exist");
		return name0_var;
	}
	ubyte& name1() {
		assert_cond(name1_exists, "struct field name1 does not exist");
		return name1_var;
	}
	ubyte& name2() {
		assert_cond(name2_exists, "struct field name2 does not exist");
		return name2_var;
	}
	ubyte& name3() {
		assert_cond(name3_exists, "struct field name3 does not exist");
		return name3_var;
	}
	ubyte& desc0() {
		assert_cond(desc0_exists, "struct field desc0 does not exist");
		return desc0_var;
	}
	ubyte& desc1() {
		assert_cond(desc1_exists, "struct field desc1 does not exist");
		return desc1_var;
	}
	ubyte& desc2() {
		assert_cond(desc2_exists, "struct field desc2 does not exist");
		return desc2_var;
	}
	ubyte& desc3() {
		assert_cond(desc3_exists, "struct field desc3 does not exist");
		return desc3_var;
	}
	ubyte& desc4() {
		assert_cond(desc4_exists, "struct field desc4 does not exist");
		return desc4_var;
	}
	ubyte& desc5() {
		assert_cond(desc5_exists, "struct field desc5 does not exist");
		return desc5_var;
	}
	ubyte& desc6() {
		assert_cond(desc6_exists, "struct field desc6 does not exist");
		return desc6_var;
	}
	ubyte& desc7() {
		assert_cond(desc7_exists, "struct field desc7 does not exist");
		return desc7_var;
	}
	ubyte& desc8() {
		assert_cond(desc8_exists, "struct field desc8 does not exist");
		return desc8_var;
	}
	ubyte& desc9() {
		assert_cond(desc9_exists, "struct field desc9 does not exist");
		return desc9_var;
	}
	ubyte& desc10() {
		assert_cond(desc10_exists, "struct field desc10 does not exist");
		return desc10_var;
	}
	ubyte& desc11() {
		assert_cond(desc11_exists, "struct field desc11 does not exist");
		return desc11_var;
	}
	ubyte& desc12() {
		assert_cond(desc12_exists, "struct field desc12 does not exist");
		return desc12_var;
	}
	ubyte& desc13() {
		assert_cond(desc13_exists, "struct field desc13 does not exist");
		return desc13_var;
	}
	ubyte& desc14() {
		assert_cond(desc14_exists, "struct field desc14 does not exist");
		return desc14_var;
	}
	ubyte& desc15() {
		assert_cond(desc15_exists, "struct field desc15 does not exist");
		return desc15_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	NOTE_SECTION& operator () () { return *instances.back(); }
	NOTE_SECTION& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	NOTE_SECTION(std::vector<NOTE_SECTION*>& instances) : instances(instances) { instances.push_back(this); }
	~NOTE_SECTION() {
		if (generated == 2)
			return;
		while (instances.size()) {
			NOTE_SECTION* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	NOTE_SECTION* generate();
};

int NOTE_SECTION::_parent_id = 0;
int NOTE_SECTION::_index_start = 0;



class SHSTRTAB_SECTION {
	std::vector<SHSTRTAB_SECTION*>& instances;

	ubyte s0_var;
	ubyte s1_var;
	ubyte s2_var;
	ubyte s3_var;
	ubyte s4_var;
	ubyte s5_var;
	ubyte s6_var;
	ubyte s7_var;
	ubyte s8_var;
	ubyte s9_var;
	ubyte s10_var;
	ubyte s11_var;
	ubyte s12_var;
	ubyte s13_var;
	ubyte s14_var;
	ubyte s15_var;
	ubyte s16_var;
	ubyte s17_var;
	ubyte s18_var;
	ubyte s19_var;
	ubyte s20_var;
	ubyte s21_var;
	ubyte s22_var;

public:
	bool s0_exists = false;
	bool s1_exists = false;
	bool s2_exists = false;
	bool s3_exists = false;
	bool s4_exists = false;
	bool s5_exists = false;
	bool s6_exists = false;
	bool s7_exists = false;
	bool s8_exists = false;
	bool s9_exists = false;
	bool s10_exists = false;
	bool s11_exists = false;
	bool s12_exists = false;
	bool s13_exists = false;
	bool s14_exists = false;
	bool s15_exists = false;
	bool s16_exists = false;
	bool s17_exists = false;
	bool s18_exists = false;
	bool s19_exists = false;
	bool s20_exists = false;
	bool s21_exists = false;
	bool s22_exists = false;

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
	ubyte& s8() {
		assert_cond(s8_exists, "struct field s8 does not exist");
		return s8_var;
	}
	ubyte& s9() {
		assert_cond(s9_exists, "struct field s9 does not exist");
		return s9_var;
	}
	ubyte& s10() {
		assert_cond(s10_exists, "struct field s10 does not exist");
		return s10_var;
	}
	ubyte& s11() {
		assert_cond(s11_exists, "struct field s11 does not exist");
		return s11_var;
	}
	ubyte& s12() {
		assert_cond(s12_exists, "struct field s12 does not exist");
		return s12_var;
	}
	ubyte& s13() {
		assert_cond(s13_exists, "struct field s13 does not exist");
		return s13_var;
	}
	ubyte& s14() {
		assert_cond(s14_exists, "struct field s14 does not exist");
		return s14_var;
	}
	ubyte& s15() {
		assert_cond(s15_exists, "struct field s15 does not exist");
		return s15_var;
	}
	ubyte& s16() {
		assert_cond(s16_exists, "struct field s16 does not exist");
		return s16_var;
	}
	ubyte& s17() {
		assert_cond(s17_exists, "struct field s17 does not exist");
		return s17_var;
	}
	ubyte& s18() {
		assert_cond(s18_exists, "struct field s18 does not exist");
		return s18_var;
	}
	ubyte& s19() {
		assert_cond(s19_exists, "struct field s19 does not exist");
		return s19_var;
	}
	ubyte& s20() {
		assert_cond(s20_exists, "struct field s20 does not exist");
		return s20_var;
	}
	ubyte& s21() {
		assert_cond(s21_exists, "struct field s21 does not exist");
		return s21_var;
	}
	ubyte& s22() {
		assert_cond(s22_exists, "struct field s22 does not exist");
		return s22_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SHSTRTAB_SECTION& operator () () { return *instances.back(); }
	SHSTRTAB_SECTION& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SHSTRTAB_SECTION(std::vector<SHSTRTAB_SECTION*>& instances) : instances(instances) { instances.push_back(this); }
	~SHSTRTAB_SECTION() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SHSTRTAB_SECTION* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SHSTRTAB_SECTION* generate();
};

int SHSTRTAB_SECTION::_parent_id = 0;
int SHSTRTAB_SECTION::_index_start = 0;



class ALIGNMENT_PAD {
	std::vector<ALIGNMENT_PAD*>& instances;

	ubyte pad0_var;
	ubyte pad1_var;
	ubyte pad2_var;
	ubyte pad3_var;
	ubyte pad4_var;
	ubyte pad5_var;
	ubyte pad6_var;

public:
	bool pad0_exists = false;
	bool pad1_exists = false;
	bool pad2_exists = false;
	bool pad3_exists = false;
	bool pad4_exists = false;
	bool pad5_exists = false;
	bool pad6_exists = false;

	ubyte& pad0() {
		assert_cond(pad0_exists, "struct field pad0 does not exist");
		return pad0_var;
	}
	ubyte& pad1() {
		assert_cond(pad1_exists, "struct field pad1 does not exist");
		return pad1_var;
	}
	ubyte& pad2() {
		assert_cond(pad2_exists, "struct field pad2 does not exist");
		return pad2_var;
	}
	ubyte& pad3() {
		assert_cond(pad3_exists, "struct field pad3 does not exist");
		return pad3_var;
	}
	ubyte& pad4() {
		assert_cond(pad4_exists, "struct field pad4 does not exist");
		return pad4_var;
	}
	ubyte& pad5() {
		assert_cond(pad5_exists, "struct field pad5 does not exist");
		return pad5_var;
	}
	ubyte& pad6() {
		assert_cond(pad6_exists, "struct field pad6 does not exist");
		return pad6_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ALIGNMENT_PAD& operator () () { return *instances.back(); }
	ALIGNMENT_PAD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ALIGNMENT_PAD(std::vector<ALIGNMENT_PAD*>& instances) : instances(instances) { instances.push_back(this); }
	~ALIGNMENT_PAD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ALIGNMENT_PAD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ALIGNMENT_PAD* generate();
};

int ALIGNMENT_PAD::_parent_id = 0;
int ALIGNMENT_PAD::_index_start = 0;



class SECTION_HEADER_NULL {
	std::vector<SECTION_HEADER_NULL*>& instances;

	uint32 sh_name_var;
	uint32 sh_type_var;
	uint64 sh_flags_var;
	uint64 sh_addr_var;
	uint64 sh_offset_var;
	uint64 sh_size_var;
	uint32 sh_link_var;
	uint32 sh_info_var;
	uint64 sh_addralign_var;
	uint64 sh_entsize_var;

public:
	bool sh_name_exists = false;
	bool sh_type_exists = false;
	bool sh_flags_exists = false;
	bool sh_addr_exists = false;
	bool sh_offset_exists = false;
	bool sh_size_exists = false;
	bool sh_link_exists = false;
	bool sh_info_exists = false;
	bool sh_addralign_exists = false;
	bool sh_entsize_exists = false;

	uint32& sh_name() {
		assert_cond(sh_name_exists, "struct field sh_name does not exist");
		return sh_name_var;
	}
	uint32& sh_type() {
		assert_cond(sh_type_exists, "struct field sh_type does not exist");
		return sh_type_var;
	}
	uint64& sh_flags() {
		assert_cond(sh_flags_exists, "struct field sh_flags does not exist");
		return sh_flags_var;
	}
	uint64& sh_addr() {
		assert_cond(sh_addr_exists, "struct field sh_addr does not exist");
		return sh_addr_var;
	}
	uint64& sh_offset() {
		assert_cond(sh_offset_exists, "struct field sh_offset does not exist");
		return sh_offset_var;
	}
	uint64& sh_size() {
		assert_cond(sh_size_exists, "struct field sh_size does not exist");
		return sh_size_var;
	}
	uint32& sh_link() {
		assert_cond(sh_link_exists, "struct field sh_link does not exist");
		return sh_link_var;
	}
	uint32& sh_info() {
		assert_cond(sh_info_exists, "struct field sh_info does not exist");
		return sh_info_var;
	}
	uint64& sh_addralign() {
		assert_cond(sh_addralign_exists, "struct field sh_addralign does not exist");
		return sh_addralign_var;
	}
	uint64& sh_entsize() {
		assert_cond(sh_entsize_exists, "struct field sh_entsize does not exist");
		return sh_entsize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SECTION_HEADER_NULL& operator () () { return *instances.back(); }
	SECTION_HEADER_NULL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SECTION_HEADER_NULL(std::vector<SECTION_HEADER_NULL*>& instances) : instances(instances) { instances.push_back(this); }
	~SECTION_HEADER_NULL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SECTION_HEADER_NULL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SECTION_HEADER_NULL* generate();
};

int SECTION_HEADER_NULL::_parent_id = 0;
int SECTION_HEADER_NULL::_index_start = 0;



class SECTION_HEADER_TEXT {
	std::vector<SECTION_HEADER_TEXT*>& instances;

	uint32 sh_name_var;
	uint32 sh_type_var;
	uint64 sh_flags_var;
	uint64 sh_addr_var;
	uint64 sh_offset_var;
	uint64 sh_size_var;
	uint32 sh_link_var;
	uint32 sh_info_var;
	uint64 sh_addralign_var;
	uint64 sh_entsize_var;

public:
	bool sh_name_exists = false;
	bool sh_type_exists = false;
	bool sh_flags_exists = false;
	bool sh_addr_exists = false;
	bool sh_offset_exists = false;
	bool sh_size_exists = false;
	bool sh_link_exists = false;
	bool sh_info_exists = false;
	bool sh_addralign_exists = false;
	bool sh_entsize_exists = false;

	uint32& sh_name() {
		assert_cond(sh_name_exists, "struct field sh_name does not exist");
		return sh_name_var;
	}
	uint32& sh_type() {
		assert_cond(sh_type_exists, "struct field sh_type does not exist");
		return sh_type_var;
	}
	uint64& sh_flags() {
		assert_cond(sh_flags_exists, "struct field sh_flags does not exist");
		return sh_flags_var;
	}
	uint64& sh_addr() {
		assert_cond(sh_addr_exists, "struct field sh_addr does not exist");
		return sh_addr_var;
	}
	uint64& sh_offset() {
		assert_cond(sh_offset_exists, "struct field sh_offset does not exist");
		return sh_offset_var;
	}
	uint64& sh_size() {
		assert_cond(sh_size_exists, "struct field sh_size does not exist");
		return sh_size_var;
	}
	uint32& sh_link() {
		assert_cond(sh_link_exists, "struct field sh_link does not exist");
		return sh_link_var;
	}
	uint32& sh_info() {
		assert_cond(sh_info_exists, "struct field sh_info does not exist");
		return sh_info_var;
	}
	uint64& sh_addralign() {
		assert_cond(sh_addralign_exists, "struct field sh_addralign does not exist");
		return sh_addralign_var;
	}
	uint64& sh_entsize() {
		assert_cond(sh_entsize_exists, "struct field sh_entsize does not exist");
		return sh_entsize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SECTION_HEADER_TEXT& operator () () { return *instances.back(); }
	SECTION_HEADER_TEXT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SECTION_HEADER_TEXT(std::vector<SECTION_HEADER_TEXT*>& instances) : instances(instances) { instances.push_back(this); }
	~SECTION_HEADER_TEXT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SECTION_HEADER_TEXT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SECTION_HEADER_TEXT* generate();
};

int SECTION_HEADER_TEXT::_parent_id = 0;
int SECTION_HEADER_TEXT::_index_start = 0;



class SECTION_HEADER_NOTE {
	std::vector<SECTION_HEADER_NOTE*>& instances;

	uint32 sh_name_var;
	uint32 sh_type_var;
	uint64 sh_flags_var;
	uint64 sh_addr_var;
	uint64 sh_offset_var;
	uint64 sh_size_var;
	uint32 sh_link_var;
	uint32 sh_info_var;
	uint64 sh_addralign_var;
	uint64 sh_entsize_var;

public:
	bool sh_name_exists = false;
	bool sh_type_exists = false;
	bool sh_flags_exists = false;
	bool sh_addr_exists = false;
	bool sh_offset_exists = false;
	bool sh_size_exists = false;
	bool sh_link_exists = false;
	bool sh_info_exists = false;
	bool sh_addralign_exists = false;
	bool sh_entsize_exists = false;

	uint32& sh_name() {
		assert_cond(sh_name_exists, "struct field sh_name does not exist");
		return sh_name_var;
	}
	uint32& sh_type() {
		assert_cond(sh_type_exists, "struct field sh_type does not exist");
		return sh_type_var;
	}
	uint64& sh_flags() {
		assert_cond(sh_flags_exists, "struct field sh_flags does not exist");
		return sh_flags_var;
	}
	uint64& sh_addr() {
		assert_cond(sh_addr_exists, "struct field sh_addr does not exist");
		return sh_addr_var;
	}
	uint64& sh_offset() {
		assert_cond(sh_offset_exists, "struct field sh_offset does not exist");
		return sh_offset_var;
	}
	uint64& sh_size() {
		assert_cond(sh_size_exists, "struct field sh_size does not exist");
		return sh_size_var;
	}
	uint32& sh_link() {
		assert_cond(sh_link_exists, "struct field sh_link does not exist");
		return sh_link_var;
	}
	uint32& sh_info() {
		assert_cond(sh_info_exists, "struct field sh_info does not exist");
		return sh_info_var;
	}
	uint64& sh_addralign() {
		assert_cond(sh_addralign_exists, "struct field sh_addralign does not exist");
		return sh_addralign_var;
	}
	uint64& sh_entsize() {
		assert_cond(sh_entsize_exists, "struct field sh_entsize does not exist");
		return sh_entsize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SECTION_HEADER_NOTE& operator () () { return *instances.back(); }
	SECTION_HEADER_NOTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SECTION_HEADER_NOTE(std::vector<SECTION_HEADER_NOTE*>& instances) : instances(instances) { instances.push_back(this); }
	~SECTION_HEADER_NOTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SECTION_HEADER_NOTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SECTION_HEADER_NOTE* generate();
};

int SECTION_HEADER_NOTE::_parent_id = 0;
int SECTION_HEADER_NOTE::_index_start = 0;



class SECTION_HEADER_SHSTRTAB {
	std::vector<SECTION_HEADER_SHSTRTAB*>& instances;

	uint32 sh_name_var;
	uint32 sh_type_var;
	uint64 sh_flags_var;
	uint64 sh_addr_var;
	uint64 sh_offset_var;
	uint64 sh_size_var;
	uint32 sh_link_var;
	uint32 sh_info_var;
	uint64 sh_addralign_var;
	uint64 sh_entsize_var;

public:
	bool sh_name_exists = false;
	bool sh_type_exists = false;
	bool sh_flags_exists = false;
	bool sh_addr_exists = false;
	bool sh_offset_exists = false;
	bool sh_size_exists = false;
	bool sh_link_exists = false;
	bool sh_info_exists = false;
	bool sh_addralign_exists = false;
	bool sh_entsize_exists = false;

	uint32& sh_name() {
		assert_cond(sh_name_exists, "struct field sh_name does not exist");
		return sh_name_var;
	}
	uint32& sh_type() {
		assert_cond(sh_type_exists, "struct field sh_type does not exist");
		return sh_type_var;
	}
	uint64& sh_flags() {
		assert_cond(sh_flags_exists, "struct field sh_flags does not exist");
		return sh_flags_var;
	}
	uint64& sh_addr() {
		assert_cond(sh_addr_exists, "struct field sh_addr does not exist");
		return sh_addr_var;
	}
	uint64& sh_offset() {
		assert_cond(sh_offset_exists, "struct field sh_offset does not exist");
		return sh_offset_var;
	}
	uint64& sh_size() {
		assert_cond(sh_size_exists, "struct field sh_size does not exist");
		return sh_size_var;
	}
	uint32& sh_link() {
		assert_cond(sh_link_exists, "struct field sh_link does not exist");
		return sh_link_var;
	}
	uint32& sh_info() {
		assert_cond(sh_info_exists, "struct field sh_info does not exist");
		return sh_info_var;
	}
	uint64& sh_addralign() {
		assert_cond(sh_addralign_exists, "struct field sh_addralign does not exist");
		return sh_addralign_var;
	}
	uint64& sh_entsize() {
		assert_cond(sh_entsize_exists, "struct field sh_entsize does not exist");
		return sh_entsize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SECTION_HEADER_SHSTRTAB& operator () () { return *instances.back(); }
	SECTION_HEADER_SHSTRTAB& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SECTION_HEADER_SHSTRTAB(std::vector<SECTION_HEADER_SHSTRTAB*>& instances) : instances(instances) { instances.push_back(this); }
	~SECTION_HEADER_SHSTRTAB() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SECTION_HEADER_SHSTRTAB* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SECTION_HEADER_SHSTRTAB* generate();
};

int SECTION_HEADER_SHSTRTAB::_parent_id = 0;
int SECTION_HEADER_SHSTRTAB::_index_start = 0;



class elf_file {
	std::vector<elf_file*>& instances;

	ELF_HEADER* ehdr_var;
	PROGRAM_HEADER_PHDR* phdr_phdr_var;
	PROGRAM_HEADER_LOAD* phdr_load_var;
	PROGRAM_HEADER_NOTE* phdr_note_var;
	TEXT_SECTION* text_section_var;
	NOTE_SECTION* note_section_var;
	SHSTRTAB_SECTION* shstrtab_section_var;
	ALIGNMENT_PAD* align_pad_var;
	SECTION_HEADER_NULL* shdr_null_var;
	SECTION_HEADER_TEXT* shdr_text_var;
	SECTION_HEADER_NOTE* shdr_note_var;
	SECTION_HEADER_SHSTRTAB* shdr_shstrtab_var;

public:
	bool ehdr_exists = false;
	bool phdr_phdr_exists = false;
	bool phdr_load_exists = false;
	bool phdr_note_exists = false;
	bool text_section_exists = false;
	bool note_section_exists = false;
	bool shstrtab_section_exists = false;
	bool align_pad_exists = false;
	bool shdr_null_exists = false;
	bool shdr_text_exists = false;
	bool shdr_note_exists = false;
	bool shdr_shstrtab_exists = false;

	ELF_HEADER& ehdr() {
		assert_cond(ehdr_exists, "struct field ehdr does not exist");
		return *ehdr_var;
	}
	PROGRAM_HEADER_PHDR& phdr_phdr() {
		assert_cond(phdr_phdr_exists, "struct field phdr_phdr does not exist");
		return *phdr_phdr_var;
	}
	PROGRAM_HEADER_LOAD& phdr_load() {
		assert_cond(phdr_load_exists, "struct field phdr_load does not exist");
		return *phdr_load_var;
	}
	PROGRAM_HEADER_NOTE& phdr_note() {
		assert_cond(phdr_note_exists, "struct field phdr_note does not exist");
		return *phdr_note_var;
	}
	TEXT_SECTION& text_section() {
		assert_cond(text_section_exists, "struct field text_section does not exist");
		return *text_section_var;
	}
	NOTE_SECTION& note_section() {
		assert_cond(note_section_exists, "struct field note_section does not exist");
		return *note_section_var;
	}
	SHSTRTAB_SECTION& shstrtab_section() {
		assert_cond(shstrtab_section_exists, "struct field shstrtab_section does not exist");
		return *shstrtab_section_var;
	}
	ALIGNMENT_PAD& align_pad() {
		assert_cond(align_pad_exists, "struct field align_pad does not exist");
		return *align_pad_var;
	}
	SECTION_HEADER_NULL& shdr_null() {
		assert_cond(shdr_null_exists, "struct field shdr_null does not exist");
		return *shdr_null_var;
	}
	SECTION_HEADER_TEXT& shdr_text() {
		assert_cond(shdr_text_exists, "struct field shdr_text does not exist");
		return *shdr_text_var;
	}
	SECTION_HEADER_NOTE& shdr_note() {
		assert_cond(shdr_note_exists, "struct field shdr_note does not exist");
		return *shdr_note_var;
	}
	SECTION_HEADER_SHSTRTAB& shdr_shstrtab() {
		assert_cond(shdr_shstrtab_exists, "struct field shdr_shstrtab does not exist");
		return *shdr_shstrtab_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	elf_file& operator () () { return *instances.back(); }
	elf_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	elf_file(std::vector<elf_file*>& instances) : instances(instances) { instances.push_back(this); }
	~elf_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			elf_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	elf_file* generate();
};

int elf_file::_parent_id = 0;
int elf_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "\x7FELF" };


std::vector<ELF_HEADER*> ELF_HEADER_ehdr_instances;
std::vector<PROGRAM_HEADER_PHDR*> PROGRAM_HEADER_PHDR_phdr_phdr_instances;
std::vector<PROGRAM_HEADER_LOAD*> PROGRAM_HEADER_LOAD_phdr_load_instances;
std::vector<PROGRAM_HEADER_NOTE*> PROGRAM_HEADER_NOTE_phdr_note_instances;
std::vector<TEXT_SECTION*> TEXT_SECTION_text_section_instances;
std::vector<NOTE_SECTION*> NOTE_SECTION_note_section_instances;
std::vector<SHSTRTAB_SECTION*> SHSTRTAB_SECTION_shstrtab_section_instances;
std::vector<ALIGNMENT_PAD*> ALIGNMENT_PAD_align_pad_instances;
std::vector<SECTION_HEADER_NULL*> SECTION_HEADER_NULL_shdr_null_instances;
std::vector<SECTION_HEADER_TEXT*> SECTION_HEADER_TEXT_shdr_text_instances;
std::vector<SECTION_HEADER_NOTE*> SECTION_HEADER_NOTE_shdr_note_instances;
std::vector<SECTION_HEADER_SHSTRTAB*> SECTION_HEADER_SHSTRTAB_shdr_shstrtab_instances;
std::vector<elf_file*> elf_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "ei_mag0", "ubyte_class" }, { "ei_mag1", "ubyte_class" }, { "ei_mag2", "ubyte_class" }, { "ei_mag3", "ubyte_class" }, { "ei_class", "ubyte_class" }, { "ei_data", "ubyte_class" }, { "ei_version", "ubyte_class" }, { "ei_osabi", "ubyte_class" }, { "ei_abiversion", "ubyte_class" }, { "ei_pad0", "ubyte_class" }, { "ei_pad1", "ubyte_class" }, { "ei_pad2", "ubyte_class" }, { "ei_pad3", "ubyte_class" }, { "ei_pad4", "ubyte_class" }, { "ei_pad5", "ubyte_class" }, { "ei_pad6", "ubyte_class" }, { "e_type", "uint16_class" }, { "e_machine", "uint16_class" }, { "e_version", "uint32_class" }, { "e_entry", "uint64_class" }, { "e_phoff", "uint64_class" }, { "e_shoff", "uint64_class" }, { "e_flags", "uint32_class" }, { "e_ehsize", "uint16_class" }, { "e_phentsize", "uint16_class" }, { "e_phnum", "uint16_class" }, { "e_shentsize", "uint16_class" }, { "e_shnum", "uint16_class" }, { "e_shstrndx", "uint16_class" }, { "ehdr", "ELF_HEADER" }, { "p_type", "uint32_class" }, { "p_flags", "uint32_class" }, { "p_offset", "uint64_class" }, { "p_vaddr", "uint64_class" }, { "p_paddr", "uint64_class" }, { "p_filesz", "uint64_class" }, { "p_memsz", "uint64_class" }, { "p_align", "uint64_class" }, { "phdr_phdr", "PROGRAM_HEADER_PHDR" }, { "phdr_load", "PROGRAM_HEADER_LOAD" }, { "phdr_note", "PROGRAM_HEADER_NOTE" }, { "insn0", "ubyte_class" }, { "insn1", "ubyte_class" }, { "insn2", "ubyte_class" }, { "insn3", "ubyte_class" }, { "insn4", "ubyte_class" }, { "insn5", "ubyte_class" }, { "insn6", "ubyte_class" }, { "insn7", "ubyte_class" }, { "insn8", "ubyte_class" }, { "insn9", "ubyte_class" }, { "text_section", "TEXT_SECTION" }, { "n_namesz", "uint32_class" }, { "n_descsz", "uint32_class" }, { "n_type", "uint32_class" }, { "name0", "ubyte_class" }, { "name1", "ubyte_class" }, { "name2", "ubyte_class" }, { "name3", "ubyte_class" }, { "desc0", "ubyte_class" }, { "desc1", "ubyte_class" }, { "desc2", "ubyte_class" }, { "desc3", "ubyte_class" }, { "desc4", "ubyte_class" }, { "desc5", "ubyte_class" }, { "desc6", "ubyte_class" }, { "desc7", "ubyte_class" }, { "desc8", "ubyte_class" }, { "desc9", "ubyte_class" }, { "desc10", "ubyte_class" }, { "desc11", "ubyte_class" }, { "desc12", "ubyte_class" }, { "desc13", "ubyte_class" }, { "desc14", "ubyte_class" }, { "desc15", "ubyte_class" }, { "note_section", "NOTE_SECTION" }, { "s0", "ubyte_class" }, { "s1", "ubyte_class" }, { "s2", "ubyte_class" }, { "s3", "ubyte_class" }, { "s4", "ubyte_class" }, { "s5", "ubyte_class" }, { "s6", "ubyte_class" }, { "s7", "ubyte_class" }, { "s8", "ubyte_class" }, { "s9", "ubyte_class" }, { "s10", "ubyte_class" }, { "s11", "ubyte_class" }, { "s12", "ubyte_class" }, { "s13", "ubyte_class" }, { "s14", "ubyte_class" }, { "s15", "ubyte_class" }, { "s16", "ubyte_class" }, { "s17", "ubyte_class" }, { "s18", "ubyte_class" }, { "s19", "ubyte_class" }, { "s20", "ubyte_class" }, { "s21", "ubyte_class" }, { "s22", "ubyte_class" }, { "shstrtab_section", "SHSTRTAB_SECTION" }, { "pad0", "ubyte_class" }, { "pad1", "ubyte_class" }, { "pad2", "ubyte_class" }, { "pad3", "ubyte_class" }, { "pad4", "ubyte_class" }, { "pad5", "ubyte_class" }, { "pad6", "ubyte_class" }, { "align_pad", "ALIGNMENT_PAD" }, { "sh_name", "uint32_class" }, { "sh_type", "uint32_class" }, { "sh_flags", "uint64_class" }, { "sh_addr", "uint64_class" }, { "sh_offset", "uint64_class" }, { "sh_size", "uint64_class" }, { "sh_link", "uint32_class" }, { "sh_info", "uint32_class" }, { "sh_addralign", "uint64_class" }, { "sh_entsize", "uint64_class" }, { "shdr_null", "SECTION_HEADER_NULL" }, { "shdr_text", "SECTION_HEADER_TEXT" }, { "shdr_note", "SECTION_HEADER_NOTE" }, { "shdr_shstrtab", "SECTION_HEADER_SHSTRTAB" }, { "file", "elf_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	ubyte_class ei_mag0;
	ubyte_class ei_mag1;
	ubyte_class ei_mag2;
	ubyte_class ei_mag3;
	ubyte_class ei_class;
	ubyte_class ei_data;
	ubyte_class ei_version;
	ubyte_class ei_osabi;
	ubyte_class ei_abiversion;
	ubyte_class ei_pad0;
	ubyte_class ei_pad1;
	ubyte_class ei_pad2;
	ubyte_class ei_pad3;
	ubyte_class ei_pad4;
	ubyte_class ei_pad5;
	ubyte_class ei_pad6;
	uint16_class e_type;
	uint16_class e_machine;
	uint32_class e_version;
	uint64_class e_entry;
	uint64_class e_phoff;
	uint64_class e_shoff;
	uint32_class e_flags;
	uint16_class e_ehsize;
	uint16_class e_phentsize;
	uint16_class e_phnum;
	uint16_class e_shentsize;
	uint16_class e_shnum;
	uint16_class e_shstrndx;
	ELF_HEADER ehdr;
	uint32_class p_type;
	uint32_class p_flags;
	uint64_class p_offset;
	uint64_class p_vaddr;
	uint64_class p_paddr;
	uint64_class p_filesz;
	uint64_class p_memsz;
	uint64_class p_align;
	PROGRAM_HEADER_PHDR phdr_phdr;
	PROGRAM_HEADER_LOAD phdr_load;
	PROGRAM_HEADER_NOTE phdr_note;
	ubyte_class insn0;
	ubyte_class insn1;
	ubyte_class insn2;
	ubyte_class insn3;
	ubyte_class insn4;
	ubyte_class insn5;
	ubyte_class insn6;
	ubyte_class insn7;
	ubyte_class insn8;
	ubyte_class insn9;
	TEXT_SECTION text_section;
	uint32_class n_namesz;
	uint32_class n_descsz;
	uint32_class n_type;
	ubyte_class name0;
	ubyte_class name1;
	ubyte_class name2;
	ubyte_class name3;
	ubyte_class desc0;
	ubyte_class desc1;
	ubyte_class desc2;
	ubyte_class desc3;
	ubyte_class desc4;
	ubyte_class desc5;
	ubyte_class desc6;
	ubyte_class desc7;
	ubyte_class desc8;
	ubyte_class desc9;
	ubyte_class desc10;
	ubyte_class desc11;
	ubyte_class desc12;
	ubyte_class desc13;
	ubyte_class desc14;
	ubyte_class desc15;
	NOTE_SECTION note_section;
	ubyte_class s0;
	ubyte_class s1;
	ubyte_class s2;
	ubyte_class s3;
	ubyte_class s4;
	ubyte_class s5;
	ubyte_class s6;
	ubyte_class s7;
	ubyte_class s8;
	ubyte_class s9;
	ubyte_class s10;
	ubyte_class s11;
	ubyte_class s12;
	ubyte_class s13;
	ubyte_class s14;
	ubyte_class s15;
	ubyte_class s16;
	ubyte_class s17;
	ubyte_class s18;
	ubyte_class s19;
	ubyte_class s20;
	ubyte_class s21;
	ubyte_class s22;
	SHSTRTAB_SECTION shstrtab_section;
	ubyte_class pad0;
	ubyte_class pad1;
	ubyte_class pad2;
	ubyte_class pad3;
	ubyte_class pad4;
	ubyte_class pad5;
	ubyte_class pad6;
	ALIGNMENT_PAD align_pad;
	uint32_class sh_name;
	uint32_class sh_type;
	uint64_class sh_flags;
	uint64_class sh_addr;
	uint64_class sh_offset;
	uint64_class sh_size;
	uint32_class sh_link;
	uint32_class sh_info;
	uint64_class sh_addralign;
	uint64_class sh_entsize;
	SECTION_HEADER_NULL shdr_null;
	SECTION_HEADER_TEXT shdr_text;
	SECTION_HEADER_NOTE shdr_note;
	SECTION_HEADER_SHSTRTAB shdr_shstrtab;
	elf_file file;


	globals_class() :
		ei_mag0(1),
		ei_mag1(1),
		ei_mag2(1),
		ei_mag3(1),
		ei_class(1),
		ei_data(1),
		ei_version(1),
		ei_osabi(1),
		ei_abiversion(1),
		ei_pad0(1),
		ei_pad1(1),
		ei_pad2(1),
		ei_pad3(1),
		ei_pad4(1),
		ei_pad5(1),
		ei_pad6(1),
		e_type(1),
		e_machine(1),
		e_version(1),
		e_entry(1),
		e_phoff(1),
		e_shoff(1),
		e_flags(1),
		e_ehsize(1),
		e_phentsize(1),
		e_phnum(1),
		e_shentsize(1),
		e_shnum(1),
		e_shstrndx(1),
		ehdr(ELF_HEADER_ehdr_instances),
		p_type(1),
		p_flags(1),
		p_offset(1),
		p_vaddr(1),
		p_paddr(1),
		p_filesz(1),
		p_memsz(1),
		p_align(1),
		phdr_phdr(PROGRAM_HEADER_PHDR_phdr_phdr_instances),
		phdr_load(PROGRAM_HEADER_LOAD_phdr_load_instances),
		phdr_note(PROGRAM_HEADER_NOTE_phdr_note_instances),
		insn0(1),
		insn1(1),
		insn2(1),
		insn3(1),
		insn4(1),
		insn5(1),
		insn6(1),
		insn7(1),
		insn8(1),
		insn9(1),
		text_section(TEXT_SECTION_text_section_instances),
		n_namesz(1),
		n_descsz(1),
		n_type(1),
		name0(1),
		name1(1),
		name2(1),
		name3(1),
		desc0(1),
		desc1(1),
		desc2(1),
		desc3(1),
		desc4(1),
		desc5(1),
		desc6(1),
		desc7(1),
		desc8(1),
		desc9(1),
		desc10(1),
		desc11(1),
		desc12(1),
		desc13(1),
		desc14(1),
		desc15(1),
		note_section(NOTE_SECTION_note_section_instances),
		s0(1),
		s1(1),
		s2(1),
		s3(1),
		s4(1),
		s5(1),
		s6(1),
		s7(1),
		s8(1),
		s9(1),
		s10(1),
		s11(1),
		s12(1),
		s13(1),
		s14(1),
		s15(1),
		s16(1),
		s17(1),
		s18(1),
		s19(1),
		s20(1),
		s21(1),
		s22(1),
		shstrtab_section(SHSTRTAB_SECTION_shstrtab_section_instances),
		pad0(1),
		pad1(1),
		pad2(1),
		pad3(1),
		pad4(1),
		pad5(1),
		pad6(1),
		align_pad(ALIGNMENT_PAD_align_pad_instances),
		sh_name(1),
		sh_type(1),
		sh_flags(1),
		sh_addr(1),
		sh_offset(1),
		sh_size(1),
		sh_link(1),
		sh_info(1),
		sh_addralign(1),
		sh_entsize(1),
		shdr_null(SECTION_HEADER_NULL_shdr_null_instances),
		shdr_text(SECTION_HEADER_TEXT_shdr_text_instances),
		shdr_note(SECTION_HEADER_NOTE_shdr_note_instances),
		shdr_shstrtab(SECTION_HEADER_SHSTRTAB_shdr_shstrtab_instances),
		file(elf_file_file_instances)
	{}
};

globals_class* g;


ELF_HEADER* ELF_HEADER::generate() {
	if (generated == 1) {
		ELF_HEADER* new_instance = new ELF_HEADER(instances);
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

	GENERATE_VAR(ei_mag0, ::g->ei_mag0.generate({ 0x7F }));
	GENERATE_VAR(ei_mag1, ::g->ei_mag1.generate({ 0x45 }));
	GENERATE_VAR(ei_mag2, ::g->ei_mag2.generate({ 0x4C }));
	GENERATE_VAR(ei_mag3, ::g->ei_mag3.generate({ 0x46 }));
	GENERATE_VAR(ei_class, ::g->ei_class.generate({ 2 }));
	GENERATE_VAR(ei_data, ::g->ei_data.generate({ 1 }));
	GENERATE_VAR(ei_version, ::g->ei_version.generate({ 1 }));
	GENERATE_VAR(ei_osabi, ::g->ei_osabi.generate({ 0, 3 }));
	GENERATE_VAR(ei_abiversion, ::g->ei_abiversion.generate({ 0 }));
	GENERATE_VAR(ei_pad0, ::g->ei_pad0.generate({ 0 }));
	GENERATE_VAR(ei_pad1, ::g->ei_pad1.generate({ 0 }));
	GENERATE_VAR(ei_pad2, ::g->ei_pad2.generate({ 0 }));
	GENERATE_VAR(ei_pad3, ::g->ei_pad3.generate({ 0 }));
	GENERATE_VAR(ei_pad4, ::g->ei_pad4.generate({ 0 }));
	GENERATE_VAR(ei_pad5, ::g->ei_pad5.generate({ 0 }));
	GENERATE_VAR(ei_pad6, ::g->ei_pad6.generate({ 0 }));
	GENERATE_VAR(e_type, ::g->e_type.generate({ 2 }));
	GENERATE_VAR(e_machine, ::g->e_machine.generate({ 62 }));
	GENERATE_VAR(e_version, ::g->e_version.generate({ 1 }));
	GENERATE_VAR(e_entry, ::g->e_entry.generate());
	GENERATE_VAR(e_phoff, ::g->e_phoff.generate());
	GENERATE_VAR(e_shoff, ::g->e_shoff.generate());
	GENERATE_VAR(e_flags, ::g->e_flags.generate({ 0 }));
	GENERATE_VAR(e_ehsize, ::g->e_ehsize.generate({ 64 }));
	GENERATE_VAR(e_phentsize, ::g->e_phentsize.generate({ 56 }));
	GENERATE_VAR(e_phnum, ::g->e_phnum.generate());
	GENERATE_VAR(e_shentsize, ::g->e_shentsize.generate({ 64 }));
	GENERATE_VAR(e_shnum, ::g->e_shnum.generate());
	GENERATE_VAR(e_shstrndx, ::g->e_shstrndx.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


PROGRAM_HEADER_PHDR* PROGRAM_HEADER_PHDR::generate() {
	if (generated == 1) {
		PROGRAM_HEADER_PHDR* new_instance = new PROGRAM_HEADER_PHDR(instances);
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

	GENERATE_VAR(p_type, ::g->p_type.generate({ 6 }));
	GENERATE_VAR(p_flags, ::g->p_flags.generate({ 4 }));
	GENERATE_VAR(p_offset, ::g->p_offset.generate());
	GENERATE_VAR(p_vaddr, ::g->p_vaddr.generate());
	GENERATE_VAR(p_paddr, ::g->p_paddr.generate());
	GENERATE_VAR(p_filesz, ::g->p_filesz.generate());
	GENERATE_VAR(p_memsz, ::g->p_memsz.generate());
	GENERATE_VAR(p_align, ::g->p_align.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


PROGRAM_HEADER_LOAD* PROGRAM_HEADER_LOAD::generate() {
	if (generated == 1) {
		PROGRAM_HEADER_LOAD* new_instance = new PROGRAM_HEADER_LOAD(instances);
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

	GENERATE_VAR(p_type, ::g->p_type.generate({ 1 }));
	GENERATE_VAR(p_flags, ::g->p_flags.generate({ 5 }));
	GENERATE_VAR(p_offset, ::g->p_offset.generate());
	GENERATE_VAR(p_vaddr, ::g->p_vaddr.generate());
	GENERATE_VAR(p_paddr, ::g->p_paddr.generate());
	GENERATE_VAR(p_filesz, ::g->p_filesz.generate());
	GENERATE_VAR(p_memsz, ::g->p_memsz.generate());
	GENERATE_VAR(p_align, ::g->p_align.generate({ 4096 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


PROGRAM_HEADER_NOTE* PROGRAM_HEADER_NOTE::generate() {
	if (generated == 1) {
		PROGRAM_HEADER_NOTE* new_instance = new PROGRAM_HEADER_NOTE(instances);
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

	GENERATE_VAR(p_type, ::g->p_type.generate({ 4 }));
	GENERATE_VAR(p_flags, ::g->p_flags.generate({ 4 }));
	GENERATE_VAR(p_offset, ::g->p_offset.generate());
	GENERATE_VAR(p_vaddr, ::g->p_vaddr.generate());
	GENERATE_VAR(p_paddr, ::g->p_paddr.generate());
	GENERATE_VAR(p_filesz, ::g->p_filesz.generate());
	GENERATE_VAR(p_memsz, ::g->p_memsz.generate());
	GENERATE_VAR(p_align, ::g->p_align.generate({ 4 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


TEXT_SECTION* TEXT_SECTION::generate() {
	if (generated == 1) {
		TEXT_SECTION* new_instance = new TEXT_SECTION(instances);
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

	GENERATE_VAR(insn0, ::g->insn0.generate({ 0xB8 }));
	GENERATE_VAR(insn1, ::g->insn1.generate({ 0x3C }));
	GENERATE_VAR(insn2, ::g->insn2.generate({ 0x00 }));
	GENERATE_VAR(insn3, ::g->insn3.generate({ 0x00 }));
	GENERATE_VAR(insn4, ::g->insn4.generate({ 0x00 }));
	GENERATE_VAR(insn5, ::g->insn5.generate({ 0x48 }));
	GENERATE_VAR(insn6, ::g->insn6.generate({ 0x31 }));
	GENERATE_VAR(insn7, ::g->insn7.generate({ 0xFF }));
	GENERATE_VAR(insn8, ::g->insn8.generate({ 0x0F }));
	GENERATE_VAR(insn9, ::g->insn9.generate({ 0x05 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


NOTE_SECTION* NOTE_SECTION::generate() {
	if (generated == 1) {
		NOTE_SECTION* new_instance = new NOTE_SECTION(instances);
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

	GENERATE_VAR(n_namesz, ::g->n_namesz.generate({ 4 }));
	GENERATE_VAR(n_descsz, ::g->n_descsz.generate({ 16 }));
	GENERATE_VAR(n_type, ::g->n_type.generate({ 3 }));
	GENERATE_VAR(name0, ::g->name0.generate({ 0x47 }));
	GENERATE_VAR(name1, ::g->name1.generate({ 0x4E }));
	GENERATE_VAR(name2, ::g->name2.generate({ 0x55 }));
	GENERATE_VAR(name3, ::g->name3.generate({ 0x00 }));
	GENERATE_VAR(desc0, ::g->desc0.generate());
	GENERATE_VAR(desc1, ::g->desc1.generate());
	GENERATE_VAR(desc2, ::g->desc2.generate());
	GENERATE_VAR(desc3, ::g->desc3.generate());
	GENERATE_VAR(desc4, ::g->desc4.generate());
	GENERATE_VAR(desc5, ::g->desc5.generate());
	GENERATE_VAR(desc6, ::g->desc6.generate());
	GENERATE_VAR(desc7, ::g->desc7.generate());
	GENERATE_VAR(desc8, ::g->desc8.generate());
	GENERATE_VAR(desc9, ::g->desc9.generate());
	GENERATE_VAR(desc10, ::g->desc10.generate());
	GENERATE_VAR(desc11, ::g->desc11.generate());
	GENERATE_VAR(desc12, ::g->desc12.generate());
	GENERATE_VAR(desc13, ::g->desc13.generate());
	GENERATE_VAR(desc14, ::g->desc14.generate());
	GENERATE_VAR(desc15, ::g->desc15.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SHSTRTAB_SECTION* SHSTRTAB_SECTION::generate() {
	if (generated == 1) {
		SHSTRTAB_SECTION* new_instance = new SHSTRTAB_SECTION(instances);
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

	GENERATE_VAR(s0, ::g->s0.generate({ 0x00 }));
	GENERATE_VAR(s1, ::g->s1.generate({ 0x2E }));
	GENERATE_VAR(s2, ::g->s2.generate({ 0x74 }));
	GENERATE_VAR(s3, ::g->s3.generate({ 0x65 }));
	GENERATE_VAR(s4, ::g->s4.generate({ 0x78 }));
	GENERATE_VAR(s5, ::g->s5.generate({ 0x74 }));
	GENERATE_VAR(s6, ::g->s6.generate({ 0x00 }));
	GENERATE_VAR(s7, ::g->s7.generate({ 0x2E }));
	GENERATE_VAR(s8, ::g->s8.generate({ 0x6E }));
	GENERATE_VAR(s9, ::g->s9.generate({ 0x6F }));
	GENERATE_VAR(s10, ::g->s10.generate({ 0x74 }));
	GENERATE_VAR(s11, ::g->s11.generate({ 0x65 }));
	GENERATE_VAR(s12, ::g->s12.generate({ 0x00 }));
	GENERATE_VAR(s13, ::g->s13.generate({ 0x2E }));
	GENERATE_VAR(s14, ::g->s14.generate({ 0x73 }));
	GENERATE_VAR(s15, ::g->s15.generate({ 0x68 }));
	GENERATE_VAR(s16, ::g->s16.generate({ 0x73 }));
	GENERATE_VAR(s17, ::g->s17.generate({ 0x74 }));
	GENERATE_VAR(s18, ::g->s18.generate({ 0x72 }));
	GENERATE_VAR(s19, ::g->s19.generate({ 0x74 }));
	GENERATE_VAR(s20, ::g->s20.generate({ 0x61 }));
	GENERATE_VAR(s21, ::g->s21.generate({ 0x62 }));
	GENERATE_VAR(s22, ::g->s22.generate({ 0x00 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ALIGNMENT_PAD* ALIGNMENT_PAD::generate() {
	if (generated == 1) {
		ALIGNMENT_PAD* new_instance = new ALIGNMENT_PAD(instances);
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

	GENERATE_VAR(pad0, ::g->pad0.generate({ 0 }));
	GENERATE_VAR(pad1, ::g->pad1.generate({ 0 }));
	GENERATE_VAR(pad2, ::g->pad2.generate({ 0 }));
	GENERATE_VAR(pad3, ::g->pad3.generate({ 0 }));
	GENERATE_VAR(pad4, ::g->pad4.generate({ 0 }));
	GENERATE_VAR(pad5, ::g->pad5.generate({ 0 }));
	GENERATE_VAR(pad6, ::g->pad6.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SECTION_HEADER_NULL* SECTION_HEADER_NULL::generate() {
	if (generated == 1) {
		SECTION_HEADER_NULL* new_instance = new SECTION_HEADER_NULL(instances);
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

	GENERATE_VAR(sh_name, ::g->sh_name.generate({ 0 }));
	GENERATE_VAR(sh_type, ::g->sh_type.generate({ 0 }));
	GENERATE_VAR(sh_flags, ::g->sh_flags.generate({ 0 }));
	GENERATE_VAR(sh_addr, ::g->sh_addr.generate({ 0 }));
	GENERATE_VAR(sh_offset, ::g->sh_offset.generate({ 0 }));
	GENERATE_VAR(sh_size, ::g->sh_size.generate({ 0 }));
	GENERATE_VAR(sh_link, ::g->sh_link.generate({ 0 }));
	GENERATE_VAR(sh_info, ::g->sh_info.generate({ 0 }));
	GENERATE_VAR(sh_addralign, ::g->sh_addralign.generate({ 0 }));
	GENERATE_VAR(sh_entsize, ::g->sh_entsize.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SECTION_HEADER_TEXT* SECTION_HEADER_TEXT::generate() {
	if (generated == 1) {
		SECTION_HEADER_TEXT* new_instance = new SECTION_HEADER_TEXT(instances);
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

	GENERATE_VAR(sh_name, ::g->sh_name.generate());
	GENERATE_VAR(sh_type, ::g->sh_type.generate({ 1 }));
	GENERATE_VAR(sh_flags, ::g->sh_flags.generate({ 6 }));
	GENERATE_VAR(sh_addr, ::g->sh_addr.generate());
	GENERATE_VAR(sh_offset, ::g->sh_offset.generate());
	GENERATE_VAR(sh_size, ::g->sh_size.generate());
	GENERATE_VAR(sh_link, ::g->sh_link.generate({ 0 }));
	GENERATE_VAR(sh_info, ::g->sh_info.generate({ 0 }));
	GENERATE_VAR(sh_addralign, ::g->sh_addralign.generate({ 16 }));
	GENERATE_VAR(sh_entsize, ::g->sh_entsize.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SECTION_HEADER_NOTE* SECTION_HEADER_NOTE::generate() {
	if (generated == 1) {
		SECTION_HEADER_NOTE* new_instance = new SECTION_HEADER_NOTE(instances);
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

	GENERATE_VAR(sh_name, ::g->sh_name.generate());
	GENERATE_VAR(sh_type, ::g->sh_type.generate({ 7 }));
	GENERATE_VAR(sh_flags, ::g->sh_flags.generate({ 2 }));
	GENERATE_VAR(sh_addr, ::g->sh_addr.generate());
	GENERATE_VAR(sh_offset, ::g->sh_offset.generate());
	GENERATE_VAR(sh_size, ::g->sh_size.generate());
	GENERATE_VAR(sh_link, ::g->sh_link.generate({ 0 }));
	GENERATE_VAR(sh_info, ::g->sh_info.generate({ 0 }));
	GENERATE_VAR(sh_addralign, ::g->sh_addralign.generate({ 4 }));
	GENERATE_VAR(sh_entsize, ::g->sh_entsize.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SECTION_HEADER_SHSTRTAB* SECTION_HEADER_SHSTRTAB::generate() {
	if (generated == 1) {
		SECTION_HEADER_SHSTRTAB* new_instance = new SECTION_HEADER_SHSTRTAB(instances);
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

	GENERATE_VAR(sh_name, ::g->sh_name.generate());
	GENERATE_VAR(sh_type, ::g->sh_type.generate({ 3 }));
	GENERATE_VAR(sh_flags, ::g->sh_flags.generate({ 0 }));
	GENERATE_VAR(sh_addr, ::g->sh_addr.generate({ 0 }));
	GENERATE_VAR(sh_offset, ::g->sh_offset.generate());
	GENERATE_VAR(sh_size, ::g->sh_size.generate());
	GENERATE_VAR(sh_link, ::g->sh_link.generate({ 0 }));
	GENERATE_VAR(sh_info, ::g->sh_info.generate({ 0 }));
	GENERATE_VAR(sh_addralign, ::g->sh_addralign.generate({ 1 }));
	GENERATE_VAR(sh_entsize, ::g->sh_entsize.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


elf_file* elf_file::generate() {
	if (generated == 1) {
		elf_file* new_instance = new elf_file(instances);
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

	GENERATE_VAR(ehdr, ::g->ehdr.generate());
	GENERATE_VAR(phdr_phdr, ::g->phdr_phdr.generate());
	GENERATE_VAR(phdr_load, ::g->phdr_load.generate());
	GENERATE_VAR(phdr_note, ::g->phdr_note.generate());
	GENERATE_VAR(text_section, ::g->text_section.generate());
	GENERATE_VAR(note_section, ::g->note_section.generate());
	GENERATE_VAR(shstrtab_section, ::g->shstrtab_section.generate());
	GENERATE_VAR(align_pad, ::g->align_pad.generate());
	GENERATE_VAR(shdr_null, ::g->shdr_null.generate());
	GENERATE_VAR(shdr_text, ::g->shdr_text.generate());
	GENERATE_VAR(shdr_note, ::g->shdr_note.generate());
	GENERATE_VAR(shdr_shstrtab, ::g->shdr_shstrtab.generate());

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

