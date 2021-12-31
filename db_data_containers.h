

//////////////////////////////////////////////////////////////////////
//
// db_data_containers.h - class definitions rated_cdr class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////



#ifndef DB_DATA_CONTAINERS
#define DB_DATA_CONTAINERS


#pragma warning(disable:4786)

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stdio.h>
#include "cdr.h"

using namespace std;

#define MIN_YEAR 1949
#define MAX_YEAR 2051




class reng_time;

class reng_time
{
public:
	int hour;
	int min;
	int second;
	bool set_time(int h, int m, int s=0);
	bool set_time(char *t);
	bool set_h_m(const char *t);
	bool set_from_db(char *t, int secs);

	bool operator < (const reng_time  &s) const;
	reng_time operator+ (int s) const;
	void Print();
	void init();
};


ostream& operator<<(ostream& out, reng_time x);

class reng_date
{
public:
	int year;
	int month;
	int day;
	bool operator < (const reng_date  &s) const;
	bool set_date(int y, int m, int d);
	bool set_date(char *d);
	void init();
};

ostream& operator<<(ostream& out, reng_date x);


class reng_date_time
{
public:
	reng_date date;
	reng_time time;
	bool set_date_time(char *d);
	bool operator < (const reng_date_time  &s) const;
};

ostream& operator<<(ostream& out, reng_date_time x);




class rated_cdr
{
public:
	bool vaild;

	int file_id;			// the number of the file
	int file_pos;			// the bytes from start of cdr where file started

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

	char		start_signature[BUF_LEN];
	// fields - end

	// calculated
	int			data_volume;
	reng_date_time	cdr_time_stamp;
	reng_date	cdr_date;

	// call detail
	
	string type_of_call;
	int call_duration;
	string mobile_subscriber_identity;
	string circuit_allocation_time_stamp;
	string service_type_id;
	int		roam;	

	// decoded stuff
	reng_time d_circuit_allocation_time;
	reng_date d_circuit_allocation_date;
	
	bool unpack_Uplink(gprs_cdr_decode *cdr, cdr_file_statistics *s);
	bool unpack_Downlink(gprs_cdr_decode *cdr, cdr_file_statistics *s);
	void init(int f_id, int f_pos);

	bool print();

	
};

ostream& operator<<(ostream& out, rated_cdr x);


#endif









