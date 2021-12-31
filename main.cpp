

////////////////////////////////////////////////////////////////////////////////////////////
//
// Telco Switch Mediation Engine for GPRS – 
// Telecom Switches such as MSCs, GGSNs, SMSCs and VAS servers store subscribers Call Detail 
// Record (CDR) data in encoded formats of either proprietary or ASN.1. Switch Mediation Engine
// functions as the intermediary between the Telco Network and the Billing System by decoding
// the CDRs and transforming(amalgamating, stitching and enhancing) them to the input format 
// expected by the Billing System.
// GPRS Mediation Engine decodes the CDRs generated in GGSN switch element for GPRS service.
// These CDRs are encoded in ASN.1 format.
//
/////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
// main.cpp
// main program for the GPRS Mediation Engine
// main method contains here
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////

#define DBLOG

#include <iostream>
#include "db.h"
#include "db_data_containers.h"
#include "cdr.h"
#include <time.h>
// Comment out the following line to turn off debug messages
//#define DEBUG
#include "Debug.h"

using namespace std;

FILE *login;
unsigned char cdr_buf[1000];
char dump_file[256];
char cdr_dump_location[128];
char db_connect_string[128];
unsigned char start_signature[3];

cdr_buffer *cdr_store;
bool core_dump;



rated_cdr				*Uplink_rated_cdr;
rated_cdr				*Downlink_rated_cdr;
rated_cdr				*gsm_cdr_block;

int	global_cdr_count;

// --db data containers end

	//cdr_decode raw_cdr;			// all the methods to extract data from a cdr
	gprs_cdr_decode raw_cdr;	

	//gprs_cdr_decode gprsdecode;

int main(int argc,char** argv)
{
	char *ver = "1.0.2";

	cout<<"CDR Decoding  Engine for GPRS "<<ver<<endl
	<<"Build Time "<<__DATE__<<" at "<<__TIME__<<endl
	<<"Millennium IT"<<endl
	<<"Colombo, Sri Lanka"<<endl<<endl;

	debug("In debug mode");
	

	
	// db data containers memory allocation start
	cdr_store					= new cdr_buffer(1024*1024*70); // allocate space in memory for binary read of whole cdr file
	Uplink_rated_cdr			= new rated_cdr;
	Downlink_rated_cdr			= new rated_cdr;
	gsm_cdr_block				= new rated_cdr[INSERT_SIZE];


	// db data containers memory allocation end
	
	// allocate space in memory for binary read of whole cdr file
	cdr_files cdr_f;


	// get config data
	if( (login  = fopen( "./gprs_cdr_eng.config", "r" )) == NULL )
	{
		printf( "The file 'gprs_cdr_eng.config' was not opened\n" );
		exit(0);
	}

	fscanf( login, "%s", db_connect_string );
	fscanf( login, "%s", cdr_dump_location );

	//cout<<cust_care_login<<" "<<rate_login<<" "<<cdr_dump_location<<endl;
	cout <<"cdr_dump_location : " << cdr_dump_location<<endl;

	if( fclose( login ) )
		printf( "The file 'rate_eng.config' was not closed\n" );

	debug("\nReady to connect to CDR data base\n");
	db_login(db_connect_string);

	cdr_f.db_read();		// read in list of cdrs files to be rated from database
	
	cdr_f.init(cdr_dump_location);

	// Rate eng performance measurement defs
	time_t	run_start_time,		// when decoding process was awakend
		run_end_time,			// when decoding process stopped
		file_start_time,		// start of decoding a cdr file
		file_end_time;			// when cdr file stopped rating
		//time_now;
	
	int	total_cdrs_rated = 0;	// cumilative for this run over all cdr files
	int cdrs_pending_insert = 0;// must allways be less than block size
	int cdrs_inserted = 0;		// must allways be less than block size


	FILE *fp;
	cdr_file_statistics *s;		// the stuff is stored in a map so dont allocate storage,
								// this gives access to storage area in map, but must assign!!
	


	time( &run_start_time );					// time rate engine woke up
	while(cdr_f.get_next_file(&fp,&s))			// get handle of cdr file
	{
		global_cdr_count=0;
		time(&file_start_time);					// time this cdr file rateing began

		//cdr_store->init();
		
		cdr_store->read_cdr_file(fp,s);			// read in whole file to buffer
		//cout<<" cdr data "<<s->file_id<<endl;
		raw_cdr.set_statistics_collector(s);	// direct statistics to file statistics area
		
		while(cdr_store->get_cdr_start())		// look for start of a cdr in the file
		{
			//gprsdecode.position_to_decode_from=gprsdecode.current; // Added
			//cdr_store->current = gprsdecode.current; // Added

			raw_cdr.decode(cdr_store->current);
			
			//if (core_dump)								// if  error dump to screen
			//{
				//cdr_store->print_cdr_in_hex();
				//cout<<raw_cdr<<endl;
			//}

			Uplink_rated_cdr->init(s->file_id, cdr_store->get_cdr_position());
			Downlink_rated_cdr->init(s->file_id, cdr_store->get_cdr_position());

			Uplink_rated_cdr->unpack_Uplink(&raw_cdr, s);			// extract all the info from the file format rec
			Downlink_rated_cdr->unpack_Downlink(&raw_cdr, s);

			//database log and perfromance statistics
			gsm_cdr_block[cdrs_pending_insert] = (*Uplink_rated_cdr);
			global_cdr_count++;
			cdrs_pending_insert++;
			total_cdrs_rated++; 

			if (INSERT_SIZE == cdrs_pending_insert)
			{
				cdrs_inserted += cdrs_pending_insert;
				#ifdef DBLOG
				db_insert_rated_cdr(cdrs_pending_insert);
				#endif
				cdrs_pending_insert = 0;	// must allways be after the insert!!
			}

			gsm_cdr_block[cdrs_pending_insert] = (*Downlink_rated_cdr);
			global_cdr_count++;
			cdrs_pending_insert++;
			total_cdrs_rated++; 

			if (INSERT_SIZE == cdrs_pending_insert)
			{
				cdrs_inserted += cdrs_pending_insert;
				#ifdef DBLOG
				db_insert_rated_cdr(cdrs_pending_insert);
				#endif
				cdrs_pending_insert = 0;	// must allways be after the insert!!
			}
			
		}

		if(fclose(fp))
			cout<<"<ERROR> cant close cdr file"<<endl; // only valid files get here
		
		time( &file_end_time );
		
		// time file was decoded
		char time_buf[50];
		strftime(time_buf, 15, "%Y%m%d%H%M%S",localtime(&file_start_time));
		s->rating_start_date	= time_buf;
		s->rating_duration		= (int)difftime(file_end_time, file_start_time); 
	
		cout<<"Statistics : " <<*s<<endl;
		cdr_f.db_update(*s);
		
		if(s->error_count > 0)
			cout<<"         Error count "<<s->error_count<<endl;
		cdr_store->init(); // rest all pointers
			
			cdr_store->init(); // rest all pointers	
	}
	
	// get any partial block size inserts
	cout <<"FINAL cdrs_pending_insert : " << cdrs_pending_insert << endl;
	if(cdrs_pending_insert > 0)
	{
		cdrs_inserted += cdrs_pending_insert;
#ifdef DBLOG
		db_insert_rated_cdr(cdrs_pending_insert);
#endif
	}

	db_logout();

	time( &run_end_time );
	cout<<"INFO: decoding done in = "<<difftime(run_end_time, run_start_time)<<" secs"<<endl<<endl;

	return 0;
}
