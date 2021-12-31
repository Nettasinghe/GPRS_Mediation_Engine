

//////////////////////////////////////////////////////////////////////
//
// rated_cdr.cpp - implementation for rated_cdr class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


// contains all the data required to rate a CDR
#include "cdr.h"
#include "db_data_containers.h"

//extern rated_cdr *cdr_block;
//extern value_added_services	*gsm_value_added_services;
//extern roaming_networks	*gsm_roaming_networks;
//extern 	call_partner_networks	*gsm_call_partner_networks;

extern bool core_dump;
extern gprs_cdr_decode raw_cdr;			// all the methods to extract data from a cdr
extern cdr_buffer	*cdr_store;


void rated_cdr::init(int f_id, int f_pos)
{
	vaild=true;

	// cdr management
	file_id = f_id;			// the number of the file
	file_pos  =f_pos;		// the bytes from start of cdr where file started

	

};

// unpack the bits
bool rated_cdr::unpack_Uplink(gprs_cdr_decode *cdr, cdr_file_statistics *s)
{
	// fields
	recordType			= cdr->recordType;
	strcpy(servedIMSI,cdr->servedIMSI);
	sgsnAddress			= cdr->sgsnAddress;
	msNetworkCapability	= cdr->msNetworkCapability;
	strcpy(routingArea,cdr->routingArea);
	locationAreaCode	= cdr->locationAreaCode;
	cellIdentity		= cdr->cellIdentity;
	chargingID			= cdr->chargingID;
	ggsnAddress			= cdr->ggsnAddress;
	strcpy(accessPointName,cdr->accessPointName);
	pdpType				= cdr->pdpType;
	servedPDPAddress	= cdr->servedPDPAddress;

	qosRequested_SGSN	= cdr->qosRequested_SGSN;
	qosNegotiated_SGSN	= cdr->qosNegotiated_SGSN;
	dataUplink_SGSN		= cdr->dataUplink_SGSN;
	dataDownlink_SGSN	= cdr->dataDownlink_SGSN;
	changeCondition_SGSN=cdr->changeCondition_SGSN;
	strcpy(changeTime_SGSN,cdr->changeTime_SGSN);

	qosNegotiated_GGSN	= cdr->qosNegotiated_GGSN;
	dataUplink_GGSN		= cdr->dataUplink_GGSN;		
	dataDownlink_GGSN	= cdr->dataDownlink_GGSN;
	changeCondition_GGSN= cdr->changeCondition_GGSN;
	strcpy(changeTime_GGSN,cdr->changeTime_GGSN);

	strcpy(recordOpeningTime_SGSN,cdr->recordOpeningTime_SGSN);
	strcpy(recordOpeningTime_GGSN,cdr->recordOpeningTime_GGSN);
	duration			= cdr->duration;
	causeForRecClosing	= cdr->causeForRecClosing;
	recordSequenceNumber= cdr->recordSequenceNumber;
	strcpy(nodeID,cdr->nodeID);
	strcpy(servedMSISDN,cdr->servedMSISDN);
	// fields - end

	data_volume			= cdr->dataUplink_SGSN;
	call_duration		= cdr->dataUplink_SGSN;
	type_of_call		= "GPRS_UP";
	service_type_id		= "GPRS";

	//circuit_allocation_time_stamp = cdr->circuit_allocation_time_stamp; // billed on this time
	circuit_allocation_time_stamp = cdr->changeTime_SGSN; // billed on this time
	circuit_allocation_time_stamp[12]='\0';

	//cout << "circuit_allocation_time_stamp - cdr->changeTime_SGSN" << circuit_allocation_time_stamp << endl;
	
	// make Y2K compliant 50-99 in 1900 00-49 in 2000 
	if(circuit_allocation_time_stamp.substr(0,2) < "50")
		circuit_allocation_time_stamp = "20"+circuit_allocation_time_stamp;
	else
	{
		circuit_allocation_time_stamp = "19"+circuit_allocation_time_stamp;
	}

	// sieve for max and min cdr times in file (adds 5% extra to decode time)
	string min_max_time=circuit_allocation_time_stamp;

	cdr_store->statistics = s;

	if (min_max_time < cdr_store->statistics->first_cdr_date)
		cdr_store->statistics->first_cdr_date = min_max_time;
	
	if (min_max_time > cdr_store->statistics->last_cdr_date)
		cdr_store->statistics->last_cdr_date = min_max_time;
	
	// after Y2K fix YYYYMMDDHHMISS
	d_circuit_allocation_time.set_time((char*)circuit_allocation_time_stamp.c_str()+8);
	d_circuit_allocation_date.set_date((char*)circuit_allocation_time_stamp.c_str());




	//#ifdef SUN

		char datearray[50];
        sprintf(datearray,"20%s",cdr->changeTime_SGSN);
        datearray[14] = '\0';
        cdr_date.set_date(datearray);
	/*
	#else

		string cdrdate = "20";
		cdrdate.append(cdr->changeTime_SGSN);
		char datearray[50];
		strcpy(datearray,cdrdate.c_str()); 
		cdr_date.set_date(datearray);

	#endif
	*/
	
	datearray[14] = '\0';
	cdr_time_stamp.set_date_time(datearray);

	servedIMSI[15] = '\0';

	mobile_subscriber_identity = servedIMSI;

	if ("41302"  != mobile_subscriber_identity.substr(0,5)  )
	{
		roam = 1;
	}
	else
	{
		roam = 0;
	}

	strcpy(start_signature,cdr->start_signature);

	return true;
}


bool rated_cdr::unpack_Downlink(gprs_cdr_decode *cdr, cdr_file_statistics *s)
{
	// fields
	recordType			= cdr->recordType;
	strcpy(servedIMSI,cdr->servedIMSI);
	sgsnAddress			= cdr->sgsnAddress;
	msNetworkCapability	= cdr->msNetworkCapability;
	strcpy(routingArea,cdr->routingArea);
	locationAreaCode	= cdr->locationAreaCode;
	cellIdentity		= cdr->cellIdentity;
	chargingID			= cdr->chargingID;
	ggsnAddress			= cdr->ggsnAddress;
	strcpy(accessPointName,cdr->accessPointName);
	pdpType				= cdr->pdpType;
	servedPDPAddress	= cdr->servedPDPAddress;

	qosRequested_SGSN	= cdr->qosRequested_SGSN;
	qosNegotiated_SGSN	= cdr->qosNegotiated_SGSN;
	dataUplink_SGSN		= cdr->dataUplink_SGSN;
	dataDownlink_SGSN	= cdr->dataDownlink_SGSN;
	changeCondition_SGSN= cdr->changeCondition_SGSN;
	strcpy(changeTime_SGSN,cdr->changeTime_SGSN);

	qosNegotiated_GGSN	= cdr->qosNegotiated_GGSN;
	dataUplink_GGSN		= cdr->dataUplink_GGSN;		
	dataDownlink_GGSN	= cdr->dataDownlink_GGSN;
	changeCondition_GGSN= cdr->changeCondition_GGSN;
	strcpy(changeTime_GGSN,cdr->changeTime_GGSN);

	strcpy(recordOpeningTime_SGSN,cdr->recordOpeningTime_SGSN);
	strcpy(recordOpeningTime_GGSN,cdr->recordOpeningTime_GGSN);
	duration			= cdr->duration;
	causeForRecClosing	= cdr->causeForRecClosing;
	recordSequenceNumber=cdr->recordSequenceNumber;
	strcpy(nodeID,cdr->nodeID);
	strcpy(servedMSISDN,cdr->servedMSISDN);
	// fields - end
	data_volume			= cdr->dataDownlink_SGSN;
	call_duration		= cdr->dataDownlink_SGSN;
	type_of_call		= "GPRS_DOWN";
	service_type_id		= "GPRS";

	//circuit_allocation_time_stamp = cdr->circuit_allocation_time_stamp; // billed on this time
	circuit_allocation_time_stamp = cdr->changeTime_SGSN; // billed on this time
	circuit_allocation_time_stamp[12]='\0';

	
	// make Y2K compliant 50-99 in 1900 00-49 in 2000 
	if(circuit_allocation_time_stamp.substr(0,2) < "50")
		circuit_allocation_time_stamp = "20"+circuit_allocation_time_stamp;
	else
	{
		circuit_allocation_time_stamp = "19"+circuit_allocation_time_stamp;
	}

	// sieve for max and min cdr times in file (adds 5% extra to decode time)
	string min_max_time=circuit_allocation_time_stamp;

	cdr_store->statistics = s;

	if (min_max_time < cdr_store->statistics->first_cdr_date)
		cdr_store->statistics->first_cdr_date = min_max_time;
	
	if (min_max_time > cdr_store->statistics->last_cdr_date)
		cdr_store->statistics->last_cdr_date = min_max_time;
	
	// after Y2K fix YYYYMMDDHHMISS
	d_circuit_allocation_time.set_time((char*)circuit_allocation_time_stamp.c_str()+8);
	d_circuit_allocation_date.set_date((char*)circuit_allocation_time_stamp.c_str());


	//#ifdef SUN

		char datearray[50];
        sprintf(datearray,"20%s",cdr->changeTime_SGSN);
        datearray[14] = '\0';
        cdr_date.set_date(datearray);
	/*
	#else

		string cdrdate = "20";
		cdrdate.append(cdr->changeTime_SGSN);
		char datearray[50];
		strcpy(datearray,cdrdate.c_str()); 
		cdr_date.set_date(datearray);

	#endif
	*/

	
	//cout << "cdr_date : "<< cdr_date << endl;
	datearray[14] = '\0';
	cdr_time_stamp.set_date_time(datearray);
	//cout << "cdr_time_stamp : " << cdr_time_stamp << endl;

	servedIMSI[15] = '\0';
	mobile_subscriber_identity = servedIMSI;

	if ("41302"  != mobile_subscriber_identity.substr(0,5)  )
	{
		roam = 1;
	}
	else
	{
		roam = 0;
	}

	strcpy(start_signature,cdr->start_signature);

	return true;
}



bool rated_cdr::print()
{
	/*
	fstream array_log("c:\array_log.doc");
	rated_cdr *a=r_cdr_block;

	for(int i=0; i<INSERT_SIZE; i++)
	{
	// open a file and write to it before logging
	array_log<<i<<"="<<a[i].result_id<<","<<a[i].account_no<<","<<a[i].termination_type<<","<<a[i].units<<","
	<<a[i].charge<<","<<a[i].call_partner_id<<","<<a[i].duration<<","
	<<endl;
	}
	array_log.close();
	*/
	return true;
}




ostream& operator<<(ostream& out, rated_cdr x)
{
	return out;
}

