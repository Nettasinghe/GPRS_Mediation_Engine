

//////////////////////////////////////////////////////////////////////
//
// cdr.h - main class definitions
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


#ifndef CDR
#define CDR
#pragma warning(disable:4786)
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
//#include <rvcpp.h>
#include <iso646.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
using namespace std;

#define	BUF_LEN	50

//#include "cdr_data_def.h"
// comment to disable cdr filter
#define CDR_FILTER

// File handling
// Referances
//   a) C++ Primer Third edition Stanly B.Lippman Section 20 (page 1063-1121)
//   b) 

class LocateCDR;
class cdr_file_statistics;

class imsi_filter
{
public:
	set<string> valid_imsi_list;
	
	bool is_valid_imsi(string a);
	bool read_imsi_file(string name);
	void print();
};

/*
class unpack
{
public:
	inline unsigned char get_most_significant_nibble(unsigned char a);
	inline unsigned char get_least_significant_nibble(unsigned char a);
	unsigned char get_TBCD(unsigned char a);
	unsigned char get_BIN(unsigned char a);
	char* get_BCD(unsigned char *a, int length, char *buf);
	char* get_TBCD(unsigned char *a, int length, char *buf);
	int get_HEXA(unsigned char *a, int length);
	char* get_ASCII(unsigned char *a, int length, char *buf);
};
*/

class no_identity
{
public:
	int ext;
	char id[256];
	//init(void);
};

ostream& operator<<(ostream& out, no_identity x);


// walks the pointer in the buffer of the cdr_buffer classes 
/*
class cdr_decode
{
	unsigned char*	position_to_decode_from;
	unsigned char* cdr_start;
	int record_length;
	int checked_record_length;
	int cdr_length;
	cdr_file_statistics *statistics;
	bool valid;

	void init();

public:
	
	unpack U;   // a buffer to put the upacked stuff into
	
	bool init_var_length_field(unsigned char *s);
	int  get_field_length();
	int  get_move_field_length();
	int  adjust_read_field_length(int a);
	bool is_over_run(int a);
	int  get_read_field_length();
	
	bool move_to_next_filed(int length);
	bool move_to_next_record(int length);
	
	// Fixed legth Arrrays
	char circuit_allocation_time_stamp[circuit_allocation_time_stamp_LENGTH*2+1];
	char call_time_stamp[call_time_stamp_LENGTH*2+1];
	// string InformationFromFixedNetwork;  // not used yet
	
	// Variable length Arrays
	char mobile_station_identity[mobile_station_identity_LENGTH*2+1];			//IMEI (International moble equipment identity)
	char invoked_supplementary_services[invoked_supplementary_services_LENGTH*2+1];
	char link_information[link_information_LENGTH*2+1];
	char mobile_subscriber_identity[mobile_subscriber_identity_LENGTH*2+1];	//IMSI (International mobile subswcriber identity)
	
	no_identity msc;
	
	no_identity call_partner;
	
	no_identity ms_location;

	char MCC[MCC_LENGTH*2+1];			// mobile country code
	char MNC[MNC_LENGTH*2+1];			// mobile number code ?
	int  LAC;							// location access code ?
	int  CI;							// cell id
	char required_bearer_capability[required_bearer_capability_LENGTH+2+1];
	
	int type_of_msc;
	int type_of_call;
	int call_termination_type;
	int origin_of_call_indicator;
	int charging_indicator;
	int required_tele_service;
	int required_bearer_service;
	int call_duration;
	
	
	char* get_imsi();
	
	// fixed
	bool get_circuit_allocation_time_stamp();
	bool get_call_time_stamp();
	
	// Variable
	bool get_mobile_station_identity();
	bool get_invoked_supplementary_services();
	bool get_link_information();
	bool get_mobile_subscriber_identity();
	bool get_msc_identity();
	bool get_call_partner_identity();
	bool get_ms_location_identity();
	bool get_ms_location_identity_extension(); // Mobile switching center
	bool get_required_bearer_capability();
	
	int get_three_byte_binary(unsigned char * a);
	bool get_ints();
	
	int decode(unsigned char *K); //, imsi_filter *F);
	void set_statistics_collector(cdr_file_statistics *s);
};

ostream& operator<<(ostream& out, cdr_decode x);
*/


class file_locations
{
private:
	string path;
	string path_and_name;
public:	
	void init(string i);
	char* get_full_file_name(string i);
};

unsigned char bcd_to_int(unsigned char a);

class cdr_file_statistics
{
public:
	int file_id;
	int valid_cdr_count;
	int error_count;
	int bytes_read;
	int reject_cdr_count;
	string first_cdr_date;		// date of newest cdr
	string last_cdr_date;		// date of oldest cdr
	string rating_start_date;
	int rating_duration;
	void init();
};
ostream& operator<<(ostream& out, cdr_file_statistics x);


typedef map <string, cdr_file_statistics, less<string> > DUMP_DEF;
// read in list of cdr file names

class cdr_files
{
//private:
public:
	DUMP_DEF dumps;
	DUMP_DEF::iterator open_file_name_iter;
	FILE *cdr_dump_file;
	cdr_file_statistics *statistics;	// from files container
	bool file_open;						// there is a vaild open cdr data file
	int reads_from_file;				// number of times the file has been accessed, when 1 upstream buffers are flushed
	int bytes_read;						// the data raed per read
	long total_bytes_read;				// applies to all data file, total for the whole rating run
	int  file_id;						// The CDR file inventory number
	long file_position;					// start of cdr from begining of the cdr file (in bytes)

	file_locations active_file;
public:
	bool read_cdr_dump_file_list(char *name);
	bool open_cdr_dump_file(char *name);
	bool insert(string file_name, cdr_file_statistics s);
	void db_read();
	void db_update(cdr_file_statistics s);
	bool get_next_file(FILE **fp, cdr_file_statistics **s); // bad coupling here
	int get_first_file_id();
public:
	void print();
	bool init(string path);
	int get_cdr_location();

	~cdr_files();
};


// The methods will vary for different CDR types in
// the inherited classes
// length = leading_guard + trailing_guard + buffer_length
class cdr_buffer
{
private:
	//cdr_file_statistics *statistics;// useage statistics
	int bytes_read;					// bytes read in by block read
	int cdr_count;
	int cdr_position;				// location of cdr from start of file
	int buffer_size;				// size of buffer in bytes
	unsigned char cdr_length;

public:
	cdr_file_statistics *statistics;// useage statistics
	unsigned char *buffer;			// start of cdr buffer 
	unsigned char *current;			// read pointer {buffer <= current <= (buffer+length)}
	unsigned char *data_end;		// the end of the requested data sequence { buffer <= data_end <= (buffer+length)}
									// used for walking current pointer only
	unsigned char *end_of_buffer;	// end of allocated space for buffer. used for verifcation only
	bool get_cdr_start(); // =0		// locate a new cdr
public:

	bool read_cdr_file(FILE *fp, cdr_file_statistics *s);
	bool get_new_cdr();
	void print_cdr_in_hex();
	cdr_buffer(int size);
	void init();
	int get_cdr_position();
};


//----------------------- Added to END
class IPAddress
{
public:
	int	first_int;
	int second_int;
	int	third_int;
	int	fourth_int;
};

ostream& operator<<(ostream& out, IPAddress x);

class qos
{
public:
	int reliability;
    int delay;
    int precedence;
    int peakThroughput;
    int meanThroughput;
};

ostream& operator<<(ostream& out, qos x);



class gprs_cdr_decode
{
	public:
	int		cdr_length;
	unsigned char* cdr_start;
	bool get_cdr_start();

	int record_length;
	int checked_record_length;
	bool valid;
	cdr_file_statistics *statistics;

	unsigned char*	position_to_decode_from;
	unsigned char start_length_seq[3];

	// fields
	int			recordType;
	char		servedIMSI[BUF_LEN];
	IPAddress	sgsnAddress;
	int			msNetworkCapability;
	char		routingArea[BUF_LEN];
	int			locationAreaCode;
	int			cellIdentity;
	long int	chargingID;
	IPAddress	ggsnAddress;
	char		accessPointName[BUF_LEN];
	int			pdpType;
	IPAddress	servedPDPAddress;

	qos			qosRequested_SGSN;
	qos			qosNegotiated_SGSN;
	int			dataUplink_SGSN;
	int			dataDownlink_SGSN;
	int			changeCondition_SGSN;
	char		changeTime_SGSN[BUF_LEN];

	qos			qosNegotiated_GGSN;
	int			dataUplink_GGSN;		
	int			dataDownlink_GGSN;
	int			changeCondition_GGSN;
	char		changeTime_GGSN[BUF_LEN];

	char		recordOpeningTime_SGSN[BUF_LEN];
	char		recordOpeningTime_GGSN[BUF_LEN];
	int			duration;
	int			causeForRecClosing;
	int			recordSequenceNumber;
	char		nodeID[BUF_LEN];
	char		servedMSISDN[BUF_LEN];

	char		start_signature[BUF_LEN];		// ???
	char		dynamicAddressFlag[BUF_LEN];	// ???
	char		listOfTrafficVolumes[BUF_LEN];	// ???
	char		diagnostics[BUF_LEN];			// ???
	// fields - end
	
	bool get_start_signature();
	bool get_recordType();
	bool get_servedIMSI();
	bool get_ggsnAddress();
	bool get_chargingID();
	bool get_sgsnAddress();
	bool get_accessPointName();
	bool get_pdpType();
	bool get_servedPDPAddress();
	bool get_dynamicAddressFlag();
	bool get_listOfTrafficVolumes();
	bool get_recordOpeningTime_SGSN();
	bool get_recordOpeningTime_GGSN();
	bool get_duration();
	bool get_causeForRecClosing();
	bool get_recordSequenceNumber();
	bool get_nodeID();
	bool get_servedMSISDN();
	bool get_routingArea();
	bool get_locationAreaCode();
	bool get_cellIdentity();
	bool get_msNetworkCapability();
	bool get_diagnostics();
	bool get_dataUplink_GGSN();
	bool get_dataUplink_SGSN();
	bool get_dataDownlink_GGSN();
	bool get_dataDownlink_SGSN();
	bool get_listOfTrafficVolumes_SGSN();
	bool get_listOfTrafficVolumes_GGSN();
	
	bool init_var_length_field(unsigned char *s);
	bool init_var_length_field_with_trailer(unsigned char *s);
	int  get_field_length();
	int  get_move_field_length();
	int  adjust_read_field_length(int a);
	int  get_read_field_length();
	int  get_read_field_length_with_trailer();
	bool move_to_next_record(int length);

	bool get_field();
	bool get_all_fields();
	bool skip_field();
	void print_array_in_hex(unsigned char* a, int length);
	void extract_fields_from_qosRequested_SGSN(unsigned char* a);
	void extract_fields_from_qosNegotiated_SGSN(unsigned char* a);
	void extract_fields_from_qosNegotiated_GGSN(unsigned char* a);
	int	 decode(unsigned char *current);
	void set_statistics_collector(cdr_file_statistics *s);
};

ostream& operator<<(ostream& out, gprs_cdr_decode x);	


class temp_field
{
	public:
	int		length;
	unsigned char tag;
	unsigned char value_buf[100];
};	


class unpack
{
public:
	inline unsigned char get_most_significant_nibble(unsigned char a);
	inline unsigned char get_least_significant_nibble(unsigned char a);
	unsigned char get_TBCD(unsigned char a);
	unsigned char get_BIN(unsigned char a);
	char* get_BCD(unsigned char *a, int length, char *buf);
	char* get_TBCD(unsigned char *a, int length, char *buf);
	int get_HEXA(unsigned char *a, int length);
	char* get_ASCII(unsigned char *a, int length, char *buf);
	long int get_INTVAL(unsigned char *a, int length);
	int get_sub_field(unsigned char *a, unsigned char sub_field[]);
	int get_sub_sub_field(unsigned char *a, unsigned char sub_field[], unsigned char balance_field[]);
	char* get_BCD_with_char(unsigned char *a, int length, char *buf);
};

#endif
