#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"


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



class PCAP_GLOBAL_HEADER {
	std::vector<PCAP_GLOBAL_HEADER*>& instances;

	uint32 magic_number_var;
	uint16 version_major_var;
	uint16 version_minor_var;
	int32 thiszone_var;
	uint32 sigfigs_var;
	uint32 snaplen_var;
	uint32 network_var;

public:
	bool magic_number_exists = false;
	bool version_major_exists = false;
	bool version_minor_exists = false;
	bool thiszone_exists = false;
	bool sigfigs_exists = false;
	bool snaplen_exists = false;
	bool network_exists = false;

	uint32& magic_number() {
		assert_cond(magic_number_exists, "struct field magic_number does not exist");
		return magic_number_var;
	}
	uint16& version_major() {
		assert_cond(version_major_exists, "struct field version_major does not exist");
		return version_major_var;
	}
	uint16& version_minor() {
		assert_cond(version_minor_exists, "struct field version_minor does not exist");
		return version_minor_var;
	}
	int32& thiszone() {
		assert_cond(thiszone_exists, "struct field thiszone does not exist");
		return thiszone_var;
	}
	uint32& sigfigs() {
		assert_cond(sigfigs_exists, "struct field sigfigs does not exist");
		return sigfigs_var;
	}
	uint32& snaplen() {
		assert_cond(snaplen_exists, "struct field snaplen does not exist");
		return snaplen_var;
	}
	uint32& network() {
		assert_cond(network_exists, "struct field network does not exist");
		return network_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PCAP_GLOBAL_HEADER& operator () () { return *instances.back(); }
	PCAP_GLOBAL_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PCAP_GLOBAL_HEADER(std::vector<PCAP_GLOBAL_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~PCAP_GLOBAL_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PCAP_GLOBAL_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PCAP_GLOBAL_HEADER* generate();
};

int PCAP_GLOBAL_HEADER::_parent_id = 0;
int PCAP_GLOBAL_HEADER::_index_start = 0;



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



class ETHERNET_HEADER {
	std::vector<ETHERNET_HEADER*>& instances;

	std::vector<ubyte> dst_mac_var;
	std::vector<ubyte> src_mac_var;
	uint16 ether_type_var;

public:
	bool dst_mac_exists = false;
	bool src_mac_exists = false;
	bool ether_type_exists = false;

	std::vector<ubyte>& dst_mac() {
		assert_cond(dst_mac_exists, "struct field dst_mac does not exist");
		return dst_mac_var;
	}
	std::vector<ubyte>& src_mac() {
		assert_cond(src_mac_exists, "struct field src_mac does not exist");
		return src_mac_var;
	}
	uint16& ether_type() {
		assert_cond(ether_type_exists, "struct field ether_type does not exist");
		return ether_type_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	ETHERNET_HEADER& operator () () { return *instances.back(); }
	ETHERNET_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	ETHERNET_HEADER(std::vector<ETHERNET_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~ETHERNET_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			ETHERNET_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	ETHERNET_HEADER* generate();
};

int ETHERNET_HEADER::_parent_id = 0;
int ETHERNET_HEADER::_index_start = 0;



class IPV4_HEADER {
	std::vector<IPV4_HEADER*>& instances;

	ubyte ver_ihl_var;
	ubyte dscp_ecn_var;
	uint16 total_length_var;
	uint16 identification_var;
	uint16 flags_fragoff_var;
	ubyte ttl_var;
	ubyte protocol_var;
	uint16 header_checksum_var;
	uint32 src_ip_var;
	uint32 dst_ip_var;

public:
	bool ver_ihl_exists = false;
	bool dscp_ecn_exists = false;
	bool total_length_exists = false;
	bool identification_exists = false;
	bool flags_fragoff_exists = false;
	bool ttl_exists = false;
	bool protocol_exists = false;
	bool header_checksum_exists = false;
	bool src_ip_exists = false;
	bool dst_ip_exists = false;

	ubyte& ver_ihl() {
		assert_cond(ver_ihl_exists, "struct field ver_ihl does not exist");
		return ver_ihl_var;
	}
	ubyte& dscp_ecn() {
		assert_cond(dscp_ecn_exists, "struct field dscp_ecn does not exist");
		return dscp_ecn_var;
	}
	uint16& total_length() {
		assert_cond(total_length_exists, "struct field total_length does not exist");
		return total_length_var;
	}
	uint16& identification() {
		assert_cond(identification_exists, "struct field identification does not exist");
		return identification_var;
	}
	uint16& flags_fragoff() {
		assert_cond(flags_fragoff_exists, "struct field flags_fragoff does not exist");
		return flags_fragoff_var;
	}
	ubyte& ttl() {
		assert_cond(ttl_exists, "struct field ttl does not exist");
		return ttl_var;
	}
	ubyte& protocol() {
		assert_cond(protocol_exists, "struct field protocol does not exist");
		return protocol_var;
	}
	uint16& header_checksum() {
		assert_cond(header_checksum_exists, "struct field header_checksum does not exist");
		return header_checksum_var;
	}
	uint32& src_ip() {
		assert_cond(src_ip_exists, "struct field src_ip does not exist");
		return src_ip_var;
	}
	uint32& dst_ip() {
		assert_cond(dst_ip_exists, "struct field dst_ip does not exist");
		return dst_ip_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	IPV4_HEADER& operator () () { return *instances.back(); }
	IPV4_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	IPV4_HEADER(std::vector<IPV4_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~IPV4_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			IPV4_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	IPV4_HEADER* generate();
};

int IPV4_HEADER::_parent_id = 0;
int IPV4_HEADER::_index_start = 0;



class TCP_HEADER {
	std::vector<TCP_HEADER*>& instances;

	uint16 src_port_var;
	uint16 dst_port_var;
	uint32 seq_number_var;
	uint32 ack_number_var;
	ubyte data_off_reserved_var;
	ubyte tcp_flags_var;
	uint16 window_size_var;
	uint16 checksum_var;
	uint16 urgent_ptr_var;

public:
	bool src_port_exists = false;
	bool dst_port_exists = false;
	bool seq_number_exists = false;
	bool ack_number_exists = false;
	bool data_off_reserved_exists = false;
	bool tcp_flags_exists = false;
	bool window_size_exists = false;
	bool checksum_exists = false;
	bool urgent_ptr_exists = false;

	uint16& src_port() {
		assert_cond(src_port_exists, "struct field src_port does not exist");
		return src_port_var;
	}
	uint16& dst_port() {
		assert_cond(dst_port_exists, "struct field dst_port does not exist");
		return dst_port_var;
	}
	uint32& seq_number() {
		assert_cond(seq_number_exists, "struct field seq_number does not exist");
		return seq_number_var;
	}
	uint32& ack_number() {
		assert_cond(ack_number_exists, "struct field ack_number does not exist");
		return ack_number_var;
	}
	ubyte& data_off_reserved() {
		assert_cond(data_off_reserved_exists, "struct field data_off_reserved does not exist");
		return data_off_reserved_var;
	}
	ubyte& tcp_flags() {
		assert_cond(tcp_flags_exists, "struct field tcp_flags does not exist");
		return tcp_flags_var;
	}
	uint16& window_size() {
		assert_cond(window_size_exists, "struct field window_size does not exist");
		return window_size_var;
	}
	uint16& checksum() {
		assert_cond(checksum_exists, "struct field checksum does not exist");
		return checksum_var;
	}
	uint16& urgent_ptr() {
		assert_cond(urgent_ptr_exists, "struct field urgent_ptr does not exist");
		return urgent_ptr_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	TCP_HEADER& operator () () { return *instances.back(); }
	TCP_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	TCP_HEADER(std::vector<TCP_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~TCP_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			TCP_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	TCP_HEADER* generate();
};

int TCP_HEADER::_parent_id = 0;
int TCP_HEADER::_index_start = 0;



class UDP_HEADER {
	std::vector<UDP_HEADER*>& instances;

	uint16 src_port_var;
	uint16 dst_port_var;
	uint16 udp_length_var;
	uint16 checksum_var;

public:
	bool src_port_exists = false;
	bool dst_port_exists = false;
	bool udp_length_exists = false;
	bool checksum_exists = false;

	uint16& src_port() {
		assert_cond(src_port_exists, "struct field src_port does not exist");
		return src_port_var;
	}
	uint16& dst_port() {
		assert_cond(dst_port_exists, "struct field dst_port does not exist");
		return dst_port_var;
	}
	uint16& udp_length() {
		assert_cond(udp_length_exists, "struct field udp_length does not exist");
		return udp_length_var;
	}
	uint16& checksum() {
		assert_cond(checksum_exists, "struct field checksum does not exist");
		return checksum_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	UDP_HEADER& operator () () { return *instances.back(); }
	UDP_HEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	UDP_HEADER(std::vector<UDP_HEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~UDP_HEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			UDP_HEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	UDP_HEADER* generate();
};

int UDP_HEADER::_parent_id = 0;
int UDP_HEADER::_index_start = 0;



class PCAP_PACKET {
	std::vector<PCAP_PACKET*>& instances;

	uint32 ts_sec_var;
	uint32 ts_usec_var;
	uint32 incl_len_var;
	uint32 orig_len_var;
	ETHERNET_HEADER* eth_var;
	IPV4_HEADER* ip_var;
	TCP_HEADER* tcp_var;
	std::vector<ubyte> payload_var;
	UDP_HEADER* udp_var;

public:
	bool ts_sec_exists = false;
	bool ts_usec_exists = false;
	bool incl_len_exists = false;
	bool orig_len_exists = false;
	bool eth_exists = false;
	bool ip_exists = false;
	bool tcp_exists = false;
	bool payload_exists = false;
	bool udp_exists = false;

	uint32& ts_sec() {
		assert_cond(ts_sec_exists, "struct field ts_sec does not exist");
		return ts_sec_var;
	}
	uint32& ts_usec() {
		assert_cond(ts_usec_exists, "struct field ts_usec does not exist");
		return ts_usec_var;
	}
	uint32& incl_len() {
		assert_cond(incl_len_exists, "struct field incl_len does not exist");
		return incl_len_var;
	}
	uint32& orig_len() {
		assert_cond(orig_len_exists, "struct field orig_len does not exist");
		return orig_len_var;
	}
	ETHERNET_HEADER& eth() {
		assert_cond(eth_exists, "struct field eth does not exist");
		return *eth_var;
	}
	IPV4_HEADER& ip() {
		assert_cond(ip_exists, "struct field ip does not exist");
		return *ip_var;
	}
	TCP_HEADER& tcp() {
		assert_cond(tcp_exists, "struct field tcp does not exist");
		return *tcp_var;
	}
	std::vector<ubyte>& payload() {
		assert_cond(payload_exists, "struct field payload does not exist");
		return payload_var;
	}
	UDP_HEADER& udp() {
		assert_cond(udp_exists, "struct field udp does not exist");
		return *udp_var;
	}

	/* locals */
	uint32 payload_size;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PCAP_PACKET& operator () () { return *instances.back(); }
	PCAP_PACKET& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PCAP_PACKET(std::vector<PCAP_PACKET*>& instances) : instances(instances) { instances.push_back(this); }
	~PCAP_PACKET() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PCAP_PACKET* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PCAP_PACKET* generate();
};

int PCAP_PACKET::_parent_id = 0;
int PCAP_PACKET::_index_start = 0;



class pcap_file {
	std::vector<pcap_file*>& instances;

	PCAP_GLOBAL_HEADER* global_hdr_var;
	PCAP_PACKET* pkt1_var;
	PCAP_PACKET* pkt2_var;
	PCAP_PACKET* pkt3_var;

public:
	bool global_hdr_exists = false;
	bool pkt1_exists = false;
	bool pkt2_exists = false;
	bool pkt3_exists = false;

	PCAP_GLOBAL_HEADER& global_hdr() {
		assert_cond(global_hdr_exists, "struct field global_hdr does not exist");
		return *global_hdr_var;
	}
	PCAP_PACKET& pkt1() {
		assert_cond(pkt1_exists, "struct field pkt1 does not exist");
		return *pkt1_var;
	}
	PCAP_PACKET& pkt2() {
		assert_cond(pkt2_exists, "struct field pkt2 does not exist");
		return *pkt2_var;
	}
	PCAP_PACKET& pkt3() {
		assert_cond(pkt3_exists, "struct field pkt3 does not exist");
		return *pkt3_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	pcap_file& operator () () { return *instances.back(); }
	pcap_file& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	pcap_file(std::vector<pcap_file*>& instances) : instances(instances) { instances.push_back(this); }
	~pcap_file() {
		if (generated == 2)
			return;
		while (instances.size()) {
			pcap_file* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	pcap_file* generate();
};

int pcap_file::_parent_id = 0;
int pcap_file::_index_start = 0;

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
std::vector<std::string> ReadBytesInitValues = { "\xD4\xC3\xB2\xA1" };


std::vector<PCAP_GLOBAL_HEADER*> PCAP_GLOBAL_HEADER_global_hdr_instances;
std::vector<ETHERNET_HEADER*> ETHERNET_HEADER_eth_instances;
std::vector<IPV4_HEADER*> IPV4_HEADER_ip_instances;
std::vector<TCP_HEADER*> TCP_HEADER_tcp_instances;
std::vector<UDP_HEADER*> UDP_HEADER_udp_instances;
std::vector<PCAP_PACKET*> PCAP_PACKET_pkt1_instances;
std::vector<PCAP_PACKET*> PCAP_PACKET_pkt2_instances;
std::vector<PCAP_PACKET*> PCAP_PACKET_pkt3_instances;
std::vector<pcap_file*> pcap_file_file_instances;


std::unordered_map<std::string, std::string> variable_types = { { "magic_number", "uint32_class" }, { "version_major", "uint16_class" }, { "version_minor", "uint16_class" }, { "thiszone", "int32_class" }, { "sigfigs", "uint32_class" }, { "snaplen", "uint32_class" }, { "network", "uint32_class" }, { "global_hdr", "PCAP_GLOBAL_HEADER" }, { "ts_sec", "uint32_class" }, { "ts_usec", "uint32_class" }, { "incl_len", "uint32_class" }, { "orig_len", "uint32_class" }, { "dst_mac", "ubyte_array_class" }, { "src_mac", "ubyte_array_class" }, { "ether_type", "uint16_class" }, { "eth", "ETHERNET_HEADER" }, { "ver_ihl", "ubyte_class" }, { "dscp_ecn", "ubyte_class" }, { "total_length", "uint16_class" }, { "identification", "uint16_class" }, { "flags_fragoff", "uint16_class" }, { "ttl", "ubyte_class" }, { "protocol", "ubyte_class" }, { "header_checksum", "uint16_class" }, { "src_ip", "uint32_class" }, { "dst_ip", "uint32_class" }, { "ip", "IPV4_HEADER" }, { "src_port", "uint16_class" }, { "dst_port", "uint16_class" }, { "seq_number", "uint32_class" }, { "ack_number", "uint32_class" }, { "data_off_reserved", "ubyte_class" }, { "tcp_flags", "ubyte_class" }, { "window_size", "uint16_class" }, { "checksum", "uint16_class" }, { "urgent_ptr", "uint16_class" }, { "tcp", "TCP_HEADER" }, { "payload", "ubyte_array_class" }, { "udp_length", "uint16_class" }, { "udp", "UDP_HEADER" }, { "pkt1", "PCAP_PACKET" }, { "pkt2", "PCAP_PACKET" }, { "pkt3", "PCAP_PACKET" }, { "file", "pcap_file" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 1, 65535 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	uint32_class magic_number;
	uint16_class version_major;
	uint16_class version_minor;
	int32_class thiszone;
	uint32_class sigfigs;
	uint32_class snaplen;
	uint32_class network;
	PCAP_GLOBAL_HEADER global_hdr;
	uint32_class ts_sec;
	uint32_class ts_usec;
	uint32_class incl_len;
	uint32_class orig_len;
	ubyte_class dst_mac_element;
	ubyte_array_class dst_mac;
	ubyte_class src_mac_element;
	ubyte_array_class src_mac;
	uint16_class ether_type;
	ETHERNET_HEADER eth;
	ubyte_class ver_ihl;
	ubyte_class dscp_ecn;
	uint16_class total_length;
	uint16_class identification;
	uint16_class flags_fragoff;
	ubyte_class ttl;
	ubyte_class protocol;
	uint16_class header_checksum;
	uint32_class src_ip;
	uint32_class dst_ip;
	IPV4_HEADER ip;
	uint16_class src_port;
	uint16_class dst_port;
	uint32_class seq_number;
	uint32_class ack_number;
	ubyte_class data_off_reserved;
	ubyte_class tcp_flags;
	uint16_class window_size;
	uint16_class checksum;
	uint16_class urgent_ptr;
	TCP_HEADER tcp;
	ubyte_class payload_element;
	ubyte_array_class payload;
	uint16_class udp_length;
	UDP_HEADER udp;
	PCAP_PACKET pkt1;
	PCAP_PACKET pkt2;
	PCAP_PACKET pkt3;
	pcap_file file;


	globals_class() :
		magic_number(1),
		version_major(1),
		version_minor(1),
		thiszone(1),
		sigfigs(1),
		snaplen(1),
		network(1),
		global_hdr(PCAP_GLOBAL_HEADER_global_hdr_instances),
		ts_sec(1),
		ts_usec(1),
		incl_len(1),
		orig_len(1),
		dst_mac_element(false),
		dst_mac(dst_mac_element),
		src_mac_element(false),
		src_mac(src_mac_element),
		ether_type(1),
		eth(ETHERNET_HEADER_eth_instances),
		ver_ihl(1),
		dscp_ecn(1),
		total_length(1),
		identification(1),
		flags_fragoff(1),
		ttl(1),
		protocol(1, { 6 }),
		header_checksum(1),
		src_ip(1),
		dst_ip(1),
		ip(IPV4_HEADER_ip_instances),
		src_port(3),
		dst_port(1),
		seq_number(1),
		ack_number(1),
		data_off_reserved(1),
		tcp_flags(1),
		window_size(1),
		checksum(1),
		urgent_ptr(1),
		tcp(TCP_HEADER_tcp_instances),
		payload_element(false),
		payload(payload_element),
		udp_length(1),
		udp(UDP_HEADER_udp_instances),
		pkt1(PCAP_PACKET_pkt1_instances),
		pkt2(PCAP_PACKET_pkt2_instances),
		pkt3(PCAP_PACKET_pkt3_instances),
		file(pcap_file_file_instances)
	{}
};

globals_class* g;


PCAP_GLOBAL_HEADER* PCAP_GLOBAL_HEADER::generate() {
	if (generated == 1) {
		PCAP_GLOBAL_HEADER* new_instance = new PCAP_GLOBAL_HEADER(instances);
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

	GENERATE_VAR(magic_number, ::g->magic_number.generate({ 0xA1B2C3D4 }));
	GENERATE_VAR(version_major, ::g->version_major.generate({ 2 }));
	GENERATE_VAR(version_minor, ::g->version_minor.generate({ 4 }));
	GENERATE_VAR(thiszone, ::g->thiszone.generate({ 0 }));
	GENERATE_VAR(sigfigs, ::g->sigfigs.generate({ 0 }));
	GENERATE_VAR(snaplen, ::g->snaplen.generate({ 65535 }));
	GENERATE_VAR(network, ::g->network.generate({ 1 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


ETHERNET_HEADER* ETHERNET_HEADER::generate() {
	if (generated == 1) {
		ETHERNET_HEADER* new_instance = new ETHERNET_HEADER(instances);
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

	GENERATE_VAR(dst_mac, ::g->dst_mac.generate(6));
	GENERATE_VAR(src_mac, ::g->src_mac.generate(6));
	GENERATE_VAR(ether_type, ::g->ether_type.generate({ 0x0800 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


IPV4_HEADER* IPV4_HEADER::generate() {
	if (generated == 1) {
		IPV4_HEADER* new_instance = new IPV4_HEADER(instances);
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

	GENERATE_VAR(ver_ihl, ::g->ver_ihl.generate({ 0x45 }));
	GENERATE_VAR(dscp_ecn, ::g->dscp_ecn.generate());
	GENERATE_VAR(total_length, ::g->total_length.generate());
	GENERATE_VAR(identification, ::g->identification.generate());
	GENERATE_VAR(flags_fragoff, ::g->flags_fragoff.generate());
	GENERATE_VAR(ttl, ::g->ttl.generate({ 64, 128 }));
	GENERATE_VAR(protocol, ::g->protocol.generate({ 6, 17 }));
	GENERATE_VAR(header_checksum, ::g->header_checksum.generate());
	GENERATE_VAR(src_ip, ::g->src_ip.generate());
	GENERATE_VAR(dst_ip, ::g->dst_ip.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


TCP_HEADER* TCP_HEADER::generate() {
	if (generated == 1) {
		TCP_HEADER* new_instance = new TCP_HEADER(instances);
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

	GENERATE_VAR(src_port, ::g->src_port.generate());
	GENERATE_VAR(dst_port, ::g->dst_port.generate({ 80, 443, 8080, 22, 53 }));
	GENERATE_VAR(seq_number, ::g->seq_number.generate());
	GENERATE_VAR(ack_number, ::g->ack_number.generate());
	GENERATE_VAR(data_off_reserved, ::g->data_off_reserved.generate({ 0x50 }));
	GENERATE_VAR(tcp_flags, ::g->tcp_flags.generate());
	GENERATE_VAR(window_size, ::g->window_size.generate());
	GENERATE_VAR(checksum, ::g->checksum.generate());
	GENERATE_VAR(urgent_ptr, ::g->urgent_ptr.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


UDP_HEADER* UDP_HEADER::generate() {
	if (generated == 1) {
		UDP_HEADER* new_instance = new UDP_HEADER(instances);
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

	GENERATE_VAR(src_port, ::g->src_port.generate());
	GENERATE_VAR(dst_port, ::g->dst_port.generate({ 53, 123, 161, 443 }));
	GENERATE_VAR(udp_length, ::g->udp_length.generate());
	GENERATE_VAR(checksum, ::g->checksum.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


PCAP_PACKET* PCAP_PACKET::generate() {
	if (generated == 1) {
		PCAP_PACKET* new_instance = new PCAP_PACKET(instances);
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

	GENERATE_VAR(ts_sec, ::g->ts_sec.generate());
	GENERATE_VAR(ts_usec, ::g->ts_usec.generate());
	GENERATE_VAR(incl_len, ::g->incl_len.generate());
	GENERATE_VAR(orig_len, ::g->orig_len.generate());
	GENERATE_VAR(eth, ::g->eth.generate());
	GENERATE_VAR(ip, ::g->ip.generate());
	if ((ip().protocol() == 6)) {
		GENERATE_VAR(tcp, ::g->tcp.generate());
		payload_size = 16;
		GENERATE_VAR(payload, ::g->payload.generate(payload_size));
	} else {
		GENERATE_VAR(udp, ::g->udp.generate());
		payload_size = 8;
		GENERATE_VAR(payload, ::g->payload.generate(payload_size));
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


pcap_file* pcap_file::generate() {
	if (generated == 1) {
		pcap_file* new_instance = new pcap_file(instances);
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

	GENERATE_VAR(global_hdr, ::g->global_hdr.generate());
	GENERATE_VAR(pkt1, ::g->pkt1.generate());
	GENERATE_VAR(pkt2, ::g->pkt2.generate());
	GENERATE_VAR(pkt3, ::g->pkt3.generate());

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

