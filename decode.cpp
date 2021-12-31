

//////////////////////////////////////////////////////////////////////
//
// decode.cpp - implementation for decode class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"

using namespace std;

extern unsigned char cdr_buf[1000];
extern unsigned char start_signature[3];


ostream& operator<<(ostream& out, IPAddress x)
{
	out<<
	x.first_int<<"."<<
	x.second_int<<"."<<
	x.third_int<<"."<<
	x.fourth_int<<endl;

	return out;
}

ostream& operator<<(ostream& out, qos x)
{
	out<<endl<<
	"reliability = "<<x.reliability<<", "<<
	"delay = "<<x.delay<<", "<<
	"precedence = "<<x.precedence<<", "<<
	"peakThroughput = "<<x.peakThroughput<<", "<<
	"meanThroughput="<<x.meanThroughput<<endl;

	return out;
}

bool gprs_cdr_decode::get_cdr_start()
{
	if ( (start_signature[4]==0x01) && (start_signature[5]==0x02) && (start_signature[6]==0x03) )
	{
		return true;
	}
	return false;
	
}



bool gprs_cdr_decode::get_start_signature()
{
	init_var_length_field(position_to_decode_from);

	//unpack U;
	//U.get_BCD(position_to_decode_from+1, get_read_field_length(),start_signature);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_servedIMSI()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	U.get_TBCD(position_to_decode_from+1, get_read_field_length(),servedIMSI);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_listOfTrafficVolumes_SGSN()
{
	init_var_length_field(position_to_decode_from);

	unsigned char QOSArray[100];
	
	unpack U;
	
	print_array_in_hex(QOSArray, U.get_sub_field(position_to_decode_from+2,QOSArray));
	
	unsigned char* a = QOSArray;

	for (int k=1; k<3; k++)
	{
		switch (*a)
		{
			case 0xA1:	{ 
						extract_fields_from_qosRequested_SGSN(a+2);
						//extract_fields_from_QOS(a+2);
						int length = *(a+1);
						a=a+length+2;
						}
						break;
			case 0xA2:	{
						extract_fields_from_qosNegotiated_SGSN(a+2);
						//extract_fields_from_QOS(a+2);
						int length = *(a+1);
						a=a+length+2;
						}
		}
	}

	dataUplink_SGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "dataUplink : " << dataUplink_SGSN << endl;

	dataDownlink_SGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "dataDownlink : " << dataDownlink_SGSN << endl;

	changeCondition_SGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "changeCondition : " << changeCondition_SGSN << endl;

	U.get_BCD(a+2, 6,changeTime_SGSN);
	U.get_ASCII(a+8, 1, changeTime_SGSN+12);
	U.get_BCD(a+9, 2,changeTime_SGSN+13);
	//cout << "changeTime_SGSN : " << changeTime_SGSN << endl;			
	
	
	move_to_next_record(get_move_field_length());
	return true;
}


bool gprs_cdr_decode::get_listOfTrafficVolumes_GGSN()
{
	init_var_length_field(position_to_decode_from);

	

	unsigned char QOSArray[100];
		
	unpack U;
	print_array_in_hex(QOSArray, U.get_sub_field(position_to_decode_from+2,QOSArray));

	unsigned char* a = QOSArray;

	for (int k=1; k<3; k++)
	{
		switch (*a)
		{
			case 0xA1:	{ 
						//extract_fields_from_QOS(a+2);
						int length = *(a+1);
						a=a+length+2;
						}
						break;
			case 0xA2:	{
						extract_fields_from_qosNegotiated_SGSN(a+2);
						//extract_fields_from_QOS(a+2);
						int length = *(a+1);
						a=a+length+2;
						}
		}
	}

	dataUplink_GGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "dataUplink : " << dataUplink_GGSN << endl;

	dataDownlink_GGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "dataDownlink : " << dataDownlink_GGSN << endl;

	changeCondition_GGSN = U.get_INTVAL(a+2, *(a+1));
	a=a+*(a+1)+2;
	//cout << "changeCondition : " << changeCondition_GGSN << endl;

	U.get_BCD(a+2, 6,changeTime_GGSN);
	U.get_ASCII(a+8, 1, changeTime_GGSN+12);
	U.get_BCD(a+9, 2,changeTime_GGSN+13);
	//cout << "changeTime : " << changeTime_GGSN << endl;			
	
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_recordType()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	recordType = U.get_BIN(*(position_to_decode_from+1));
	
	move_to_next_record(get_move_field_length());
	return true;
}


bool gprs_cdr_decode::get_ggsnAddress()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),ggsnAddress);
	ggsnAddress.first_int = U.get_INTVAL(position_to_decode_from+3, 1);
	ggsnAddress.second_int = U.get_INTVAL(position_to_decode_from+4, 1);
	ggsnAddress.third_int = U.get_INTVAL(position_to_decode_from+5, 1);
	ggsnAddress.fourth_int = U.get_INTVAL(position_to_decode_from+6, 1);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_chargingID()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),chargingID);
	chargingID = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_dataUplink_SGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),chargingID);
	dataUplink_SGSN = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_dataUplink_GGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),chargingID);
	dataUplink_GGSN = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_dataDownlink_SGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),chargingID);
	dataUplink_SGSN = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_dataDownlink_GGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),chargingID);
	dataDownlink_GGSN = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_sgsnAddress()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),sgsnAddress);

	sgsnAddress.first_int = U.get_INTVAL(position_to_decode_from+3, 1);
	sgsnAddress.second_int = U.get_INTVAL(position_to_decode_from+4, 1);
	sgsnAddress.third_int = U.get_INTVAL(position_to_decode_from+5, 1);
	sgsnAddress.fourth_int = U.get_INTVAL(position_to_decode_from+6, 1);
		
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_accessPointName()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),accessPointName);
	U.get_ASCII(position_to_decode_from+1, get_read_field_length(),accessPointName);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_pdpType()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	pdpType = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_servedPDPAddress()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),servedPDPAddress);
	servedPDPAddress.first_int = U.get_INTVAL(position_to_decode_from+5, 1);
	servedPDPAddress.second_int = U.get_INTVAL(position_to_decode_from+6, 1);
	servedPDPAddress.third_int = U.get_INTVAL(position_to_decode_from+7, 1);
	servedPDPAddress.fourth_int = U.get_INTVAL(position_to_decode_from+8, 1);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_dynamicAddressFlag()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	U.get_TBCD(position_to_decode_from+1, get_read_field_length(),dynamicAddressFlag);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_listOfTrafficVolumes()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	U.get_TBCD(position_to_decode_from+1, get_read_field_length(),listOfTrafficVolumes);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_recordOpeningTime_GGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_BCD(position_to_decode_from+1, get_read_field_length(),recordOpeningTime);
	U.get_BCD(position_to_decode_from+1, 6,recordOpeningTime_GGSN);
	U.get_ASCII(position_to_decode_from+7, 1, recordOpeningTime_GGSN+12);
	U.get_BCD(position_to_decode_from+8, 2,recordOpeningTime_GGSN+13);
	
	move_to_next_record(get_move_field_length());

	return true;
}

bool gprs_cdr_decode::get_recordOpeningTime_SGSN()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	//U.get_BCD(position_to_decode_from+1, get_read_field_length(),recordOpeningTime);
	U.get_BCD(position_to_decode_from+1, 6,recordOpeningTime_SGSN);
	U.get_ASCII(position_to_decode_from+7, 1, recordOpeningTime_SGSN+12);
	U.get_BCD(position_to_decode_from+8, 2,recordOpeningTime_SGSN+13);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_duration()
{
	init_var_length_field_with_trailer(position_to_decode_from);

	unpack U;
	//U.get_TBCD(position_to_decode_from+1, get_read_field_length(),duration);
	duration = U.get_INTVAL(position_to_decode_from+1, get_read_field_length_with_trailer());
			
	move_to_next_record(get_move_field_length());		
	return true;
}

bool gprs_cdr_decode::get_causeForRecClosing()
{
	init_var_length_field_with_trailer(position_to_decode_from);

	unpack U;
	causeForRecClosing = U.get_INTVAL(position_to_decode_from+1, get_read_field_length_with_trailer());
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_recordSequenceNumber()
{
	init_var_length_field_with_trailer(position_to_decode_from);

	unpack U;
	recordSequenceNumber = U.get_INTVAL(position_to_decode_from+1, get_read_field_length_with_trailer());
	
	move_to_next_record(get_move_field_length());		
	return true;
}

bool gprs_cdr_decode::get_nodeID()
{
	init_var_length_field_with_trailer(position_to_decode_from);

	unpack U;
	U.get_ASCII(position_to_decode_from+1, get_read_field_length_with_trailer(),nodeID);
	
	move_to_next_record(get_move_field_length());		
	return true;
}

bool gprs_cdr_decode::get_servedMSISDN()
{
	init_var_length_field_with_trailer(position_to_decode_from);

	unpack U;
	U.get_TBCD(position_to_decode_from+1, get_read_field_length_with_trailer(),servedMSISDN);
	
	move_to_next_record(get_move_field_length());		
	return true;
}

bool gprs_cdr_decode::get_routingArea()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	U.get_BCD(position_to_decode_from+1, get_read_field_length(),routingArea);
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_cellIdentity()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	cellIdentity = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_locationAreaCode()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	locationAreaCode = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_msNetworkCapability()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	msNetworkCapability = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	
	move_to_next_record(get_move_field_length());
	return true;
}

bool gprs_cdr_decode::get_diagnostics()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	U.get_TBCD(position_to_decode_from+1, get_read_field_length(),diagnostics);
	
	move_to_next_record(get_move_field_length()+1);		// +1 for end of field tag (9F)
	return true;
}

/*
bool gprs_cdr_decode::get_changeCondition()
{
	init_var_length_field(position_to_decode_from);

	unpack U;
	changeCondition = U.get_INTVAL(position_to_decode_from+1, get_read_field_length());
	
	move_to_next_record(get_move_field_length());
	return true;
}
*/

bool gprs_cdr_decode::skip_field()
{
	init_var_length_field(position_to_decode_from);
	move_to_next_record(get_move_field_length());
	return true;
}

void gprs_cdr_decode::set_statistics_collector(cdr_file_statistics *s)
{
	statistics = s;
}

/*
char* unpack::get_TBCD(unsigned char *a, int length, char *buf)
{
	int k;
	unsigned char b,c;
	for(k=0; k<length*2; k++)
	{
		b = *(a+k/2);		// the byte must be visited twice to get both digits.
							// implicit rounding to floor during integer divison does this
		
		if (k%2)			// even digit, this sequence is swapped in BCD conversion
			b = b >> 4;		// most significant nibble 
		else			
			b = b & 0x0f;	// least significant nibble  
		
		c = b+'0';			// get ASCII digit

		if (!isdigit(c))
		{
			// 0xf is the end of record filler in the  cdr spec
			// others characters arrive but no body has explained how yet!
			// does not seem to do any harm so suppress errors may not be wise (ajit)
			if (!(0xf==b || 0xa==b || 0xc==b) ) 
			{
				cout<<"<ERROR> TBCD value not a digit = {"<<c<<"}"<<endl;
				//core_dump=true;
			}
			break;
		}
		buf[k]=c;
	}
	buf[k]='\0';			// for loop exits with k= length*2 +1 
							// or breaks with K set to 1+last decoded char position 

	return buf;
}
*/

bool gprs_cdr_decode::init_var_length_field(unsigned char *s)
{
	position_to_decode_from = s;
	record_length = *position_to_decode_from;
	checked_record_length = record_length;
	return true;
}

bool gprs_cdr_decode::init_var_length_field_with_trailer(unsigned char *s)
{
	position_to_decode_from = s;
	record_length = (*position_to_decode_from)+1;	// +1 for end of field tag (9F)
	checked_record_length = record_length;
	return true;
}

int  gprs_cdr_decode::get_read_field_length()
{
	return checked_record_length;
}

int  gprs_cdr_decode::get_read_field_length_with_trailer()
{
	return (checked_record_length-1);				// -1 for end of field tag (9F)
}

int  gprs_cdr_decode::get_move_field_length()
{
	return record_length;
}


int  gprs_cdr_decode::adjust_read_field_length(int a)
{
	checked_record_length=a;
	valid=false;
	return checked_record_length;
}


bool gprs_cdr_decode::move_to_next_record(int length)
{
	position_to_decode_from += (length+2);

	// check if length of CDR is exceded
	// asssumes linear address space 
	//if(position_to_decode_from > (cdr_start+cdr_length))
	//{
		//cout<<"CDR Overun ERROR {"<<hex<<(int)position_to_decode_from<<"} {"<<(int)(cdr_start+cdr_length)<<"}"<<dec<<endl;
		//core_dump=true;
	//}
	return true;
}


int gprs_cdr_decode::decode(unsigned char *current)
{
	//init();  // all the variables
	cdr_start	= current;
	//cdr_length	= *current;
	if ( (*(current-8)) == 0x81 )		// 10000001 - length of length = 1
	{
		cdr_length	= *(current-7);
		//cout << "One byte length" << endl;
	}
	else if ( (*(current-9)) == 0x82 )	// 10000010 - length of length = 2
	{
		cdr_length	= (*(current-8))*256 + (*(current-7));
		//cout << "Two byte length" << endl;
	}
	else
	{
		cout << "Invalid length of length" << endl;
	}

	//cout << "cdr_length :" << cdr_length << endl;
	position_to_decode_from=current+1;

	unpack U;

	U.get_BCD_with_char((current-6), 6, start_signature);

	for (int i=1; i<21; i++)		
	{
		get_field();
	}
	return 1;
}


bool gprs_cdr_decode::get_all_fields()
{
	//get_start_signature();		cout <<"start_signature : "		<< start_signature	<< endl;
	get_recordType();			cout <<"recordType : "			<< recordType		<< endl;
	get_servedIMSI();			cout <<"servedIMSI : "			<< servedIMSI		<< endl;
	get_ggsnAddress();			cout <<"IP Address ? : "			<< ggsnAddress		<< endl;	
	get_msNetworkCapability();	cout <<"msNetworkCapability : " << msNetworkCapability << endl;	
	get_routingArea();			cout <<"routingArea : "			<< routingArea		<< endl;
	get_locationAreaCode();		cout <<"locationAreaCode : "	<< locationAreaCode << endl;	
	get_cellIdentity();			cout <<"cellIdentity : "		<< cellIdentity		<< endl;
	get_chargingID();			cout <<"chargingID : "			<< chargingID		<< endl;	
	get_sgsnAddress();			cout <<"IP Address ? : "			<< sgsnAddress		<< endl;	
	get_accessPointName();		cout <<"accessPointName : "		<< accessPointName	<< endl;	
	get_pdpType();				cout <<"pdpType : "				<< pdpType			<< endl;	
	get_servedPDPAddress();		cout <<"IP Address ? : "	<< servedPDPAddress << endl;	
	//get_dynamicAddressFlag();	cout <<"dynamicAddressFlag : "	<< dynamicAddressFlag << endl;	
	//skip_field();
	//skip_field();
	//get_QOS();			cout <<"liOfTrafVolSqosRequested : "			<< qos		<< endl;
	//get_QOS();			cout <<"liOfTrafVolSqosNegotiated: "			<< qos		<< endl;
///	get_dataUplink();			cout <<"lOTVSdataVolGPRSUplink : "			<< dataUplink		<< endl;	
///	get_dataDownlink();			cout <<"liOfTrafVolSdataVolGPRSDownlink : "		<< dataDownlink		<< endl;
///	get_changeCondition();		cout <<"liOfTrafVolSchangeCondition : "		<< changeCondition		<< endl;
///	get_recordOpeningTime();	cout <<"liOfTrafVolSchangeTime : "	<< recordOpeningTime << endl;
	//get_QOS();					cout <<"liOfTrafVolGqosNegotiated: "			<< qos		<< endl;
///	get_dataUplink();			cout <<"liOfTrafVolGdataVolGPRSUplink  : "			<< dataUplink		<< endl;	
///	get_dataDownlink();			cout <<"liOfTrafVolGdataVolGPRSDownlink : "		<< dataDownlink		<< endl;
///	get_changeCondition();		cout <<"liOfTrafVolGchangeCondition : "		<< changeCondition		<< endl;
///	get_recordOpeningTime();	cout <<"liOfTrafVolGchangeTime : "	<< recordOpeningTime << endl;
///	get_recordOpeningTime();	cout <<"recordOpeningTimeS : "	<< recordOpeningTime << endl;
///	get_recordOpeningTime();	cout <<"recordOpeningTimeG : "	<< recordOpeningTime << endl;
	get_duration();				cout <<"duration : "			<< duration << endl;	
	get_causeForRecClosing();	cout <<"causeForRecClosing : "	<< causeForRecClosing << endl;
	//skip_field();
	//get_recordSequenceNumber();	cout <<"recordSequenceNumber : "<< recordSequenceNumber << endl;	
	get_nodeID();				cout <<"nodeID : "				<< nodeID			<< endl;	
	get_servedMSISDN();			cout <<"servedMSISDN : "		<< servedMSISDN		<< endl;	
	//get_diagnostics();			cout <<"diagnostics : "			<< diagnostics		<< endl;
	cout<<endl;
	cout<<endl;

	return true;
}



bool gprs_cdr_decode::get_field()
{
	switch (*(position_to_decode_from-1 ))
	{
		case 0x80:	get_recordType();				break;			
		case 0x83:	get_servedIMSI();				break;
		case 0xA5:	get_sgsnAddress();				break;
		case 0x86:	get_msNetworkCapability();		break;
		case 0x87:	get_routingArea();				break;
		case 0x88:	get_locationAreaCode();			break;
		case 0x89:	get_cellIdentity();				break;
		case 0x8A:	get_chargingID();				break;
		case 0xAB:	get_ggsnAddress();				break;
		case 0x8C:	get_accessPointName();			break;
		case 0x8D:	get_pdpType();					break;
		case 0xAE:	get_servedPDPAddress();			break;
		case 0xAF:	get_listOfTrafficVolumes_SGSN();break;
		case 0xB0:	get_listOfTrafficVolumes_GGSN();break;
		case 0x9B:	get_recordOpeningTime_SGSN();	break;		
		case 0x9C:	get_recordOpeningTime_GGSN();	break;		
		case 0x9D:	get_duration();					break; //		
		case 0x1F:	get_causeForRecClosing();		break; //
		case 0x20:	get_recordSequenceNumber();		break; //	
		case 0x22:	get_nodeID();					break; //				
		case 0x65:	get_servedMSISDN();				break; //			
		default :	cout << "field not found" << endl;

	}
	return true;
}

void gprs_cdr_decode::print_array_in_hex(unsigned char* a, int length)
{
	/*
	for( int k=0; k<(length+1); k++)
	{
		printf(" %02x",(int)(*(a+k)));
		//printf("\n %x  ",QOSArray[k]);
	}
	printf("\n");
	*/
}

// A Recursive method to extract sub fields of QOS
/*
void gprs_cdr_decode::extract_fields_from_QOS(unsigned char* a)
{
	unpack U;
	switch (*a)
	{
		case 0x80:	{ 
					int length = *(a+1);
					cout << "length "<< length;
					qos.reliability	=U.get_INTVAL((a+2), length);
					a=a+length+2;
					cout << "*a :"<< int(*a) << endl;
					cout << "qos.reliability :"<<	qos.reliability << endl;
					extract_fields_from_QOS(a);
					}
					break;
		case 0x81:	{ 
					int length = *(a+1);	
					qos.delay	=U.get_INTVAL((a+2), length);
					a = a+length+2;
					cout << "qos.delay :"<<	qos.delay << endl;
					extract_fields_from_QOS(a);
					}
					break;	
		case 0x82:	{ 
					int length = *(a+1);	
					qos.precedence	=U.get_INTVAL((a+2), length);
					a = a+length+2;
					cout << "qos.precedence :"<<	qos.precedence << endl;
					extract_fields_from_QOS(a);
					}
					break;		
		case 0x83:	{ 
					int length = *(a+1);	
					qos.peakThroughput	=U.get_INTVAL((a+2), length);
					a = a+length+2;
					cout << "qos.peakThroughput :"<<	qos.peakThroughput << endl;
					extract_fields_from_QOS(a);
					}
					break;
		case 0x84:	{ 
					int length = *(a+1);	
					qos.meanThroughput	=U.get_INTVAL((a+2), length);
					a = a+length+2;
					cout << "qos.meanThroughput :"<<	qos.meanThroughput << endl;
					extract_fields_from_QOS(a);
					}
					break;
		default :	cout << "non found, *(a+1) :" << endl;
	}
}
*/


void gprs_cdr_decode::extract_fields_from_qosRequested_SGSN(unsigned char* a)
{
	unpack U;
	
	int length = *(a+1);
	//cout << "length "<< length;
	qosRequested_SGSN.reliability	=U.get_INTVAL((a+2), length);
	a=a+length+2;
	//cout << "qos.reliability :"<<	qos.reliability << endl;
					
	length = *(a+1);	
	qosRequested_SGSN.delay	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.delay :"<<	qos.delay << endl;
					
	length = *(a+1);	
	qosRequested_SGSN.precedence	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.precedence :"<<	qos.precedence << endl;
					
	length = *(a+1);	
	qosRequested_SGSN.peakThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.peakThroughput :"<<	qos.peakThroughput << endl;
					
	length = *(a+1);	
	qosRequested_SGSN.meanThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.meanThroughput :"<<	qos.meanThroughput << endl;
}

void gprs_cdr_decode::extract_fields_from_qosNegotiated_SGSN(unsigned char* a)
{
	unpack U;
	
	int length = *(a+1);
	//cout << "length "<< length;
	qosNegotiated_SGSN.reliability	=U.get_INTVAL((a+2), length);
	a=a+length+2;
	//cout << "qos.reliability :"<<	qos.reliability << endl;
					
	length = *(a+1);	
	qosNegotiated_SGSN.delay	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.delay :"<<	qos.delay << endl;
					
	length = *(a+1);	
	qosNegotiated_SGSN.precedence	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.precedence :"<<	qos.precedence << endl;
					
	length = *(a+1);	
	qosNegotiated_SGSN.peakThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.peakThroughput :"<<	qos.peakThroughput << endl;
					
	length = *(a+1);	
	qosNegotiated_SGSN.meanThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.meanThroughput :"<<	qos.meanThroughput << endl;
}


void gprs_cdr_decode::extract_fields_from_qosNegotiated_GGSN(unsigned char* a)
{
	unpack U;
	
	int length = *(a+1);
	//cout << "length "<< length;
	qosNegotiated_GGSN.reliability	=U.get_INTVAL((a+2), length);
	a=a+length+2;
	//cout << "qos.reliability :"<<	qos.reliability << endl;
					
	length = *(a+1);	
	qosNegotiated_GGSN.delay	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.delay :"<<	qos.delay << endl;
					
	length = *(a+1);	
	qosNegotiated_GGSN.precedence	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.precedence :"<<	qos.precedence << endl;
					
	length = *(a+1);	
	qosNegotiated_GGSN.peakThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.peakThroughput :"<<	qos.peakThroughput << endl;
					
	length = *(a+1);	
	qosNegotiated_GGSN.meanThroughput	=U.get_INTVAL((a+2), length);
	a = a+length+2;
	//cout << "qos.meanThroughput :"<<	qos.meanThroughput << endl;
}



ostream& operator<<(ostream& out, gprs_cdr_decode x)
{
	out <<"recordType			= {" << x.recordType <<"}"<< endl;	
	out <<"servedIMSI			= {" << x.servedIMSI <<"}"<< endl;	
	out <<"sgsnAddress			= {" << x.sgsnAddress <<"}"<< endl;	
	out <<"msNetworkCapability	= {" << x.msNetworkCapability <<"}"<< endl;
	out <<"routingArea			= {" << x.routingArea <<"}"<< endl;	
	out <<"locationAreaCode		= {" << x.locationAreaCode <<"}"<< endl;	
	out <<"cellIdentity			= {" << x.cellIdentity <<"}"<< endl;	
	out <<"chargingID			= {" << x.chargingID <<"}"<< endl;	
	out <<"ggsnAddress			= {" << x.ggsnAddress <<"}"<< endl;	
	out <<"accessPointName		= {" << x.accessPointName <<"}"<< endl;	
	out <<"pdpType				= {" << x.pdpType <<"}"<< endl;	
	out <<"servedPDPAddress		= {" << x.servedPDPAddress <<"}"<< endl;

	out <<"qosRequested_SGSN	= {" << x.qosRequested_SGSN <<"}"<< endl;	
	out <<"qosNegotiated_SGSN	= {" << x.qosNegotiated_SGSN <<"}"<< endl;
	out <<"dataUplink_SGSN		= {" << x.dataUplink_SGSN <<"}"<< endl;	
	out <<"dataDownlink_SGSN	= {" << x.dataDownlink_SGSN <<"}"<< endl;	
	out <<"changeCondition_SGSN	= {" << x.changeCondition_SGSN <<"}"<< endl;	
	out <<"changeTime_SGSN		= {" << x.changeTime_SGSN <<"}"<< endl;

	out <<"qosNegotiated_GGSN	= {" << x.qosNegotiated_GGSN <<"}"<< endl;
	out <<"dataUplink_GGSN		= {" << x.dataUplink_GGSN <<"}"<< endl;	
	out <<"dataDownlink_GGSN	= {" << x.dataDownlink_GGSN <<"}"<< endl;	
	out <<"changeCondition_GGSN	= {" << x.changeCondition_GGSN <<"}"<< endl;	
	out <<"changeTime_GGSN		= {" << x.changeTime_GGSN <<"}"<< endl;

	out <<"recordOpeningTimeS	= {" << x.recordOpeningTime_SGSN <<"}"<< endl;	
	out <<"recordOpeningTimeG	= {" << x.recordOpeningTime_GGSN <<"}"<< endl;	
	out <<"duration				= {" << x.duration <<"}"<< endl;	
	out <<"causeForRecClosing	= {" << x.causeForRecClosing <<"}"<< endl;	
	out <<"recordSequenceNumber	= {" << x.recordSequenceNumber <<"}"<< endl;	
	out <<"nodeID				= {" << x.nodeID <<"}"<< endl;	
	out <<"servedMSISDN			= {" << x.servedMSISDN <<"}"<< endl;

	
	return out;
}

