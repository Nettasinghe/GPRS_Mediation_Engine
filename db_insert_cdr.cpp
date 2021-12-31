
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned long magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[39];
};
static const struct sqlcxp sqlfpn =
{
    38,
    "d:\\src\\gprs_mediation\\db_insert_cdr.pc"
};


static unsigned long sqlctx = 425974411;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
            void  *sqhstv[38];
   unsigned int   sqhstl[38];
            int   sqhsts[38];
            void  *sqindv[38];
            int   sqinds[38];
   unsigned int   sqharm[38];
   unsigned int   *sqharc[38];
   unsigned short  sqadto[38];
   unsigned short  sqtdso[38];
} sqlstm = {10,38};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned long *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned long *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned long *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(char *, int *); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4146,0,0,0,
5,0,0,1,825,0,3,207,0,0,38,38,0,1,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,
1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,
0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,5,0,0,1,5,0,0,1,5,0,0,
172,0,0,2,0,0,29,248,0,0,0,0,0,1,0,
};



//////////////////////////////////////////////////////////////////////
// db_insert_cdr.pc
// GPRS mediation module
// Copyright Millennium IT Software 2002
//////////////////////////////////////////////////////////////////////

#define SQLCA_STORAGE_CLASS extern 
#define ORACA_STORAGE_CLASS extern 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlcpr.h>

//#include "db.h"

#ifndef ORA_PROC
	#include "db.h"
	#include "db_data_containers.h"
#endif

#define INSERT_SIZE 100
#define BUF_LEN	50
 

//#ifndef code_skip
//#include <fstream>
extern rated_cdr *gsm_cdr_block;
//#endif




void db_insert_rated_cdr(int cdr_count)
{
/* EXEC SQL BEGIN DECLARE SECTION; */ 

 
static struct db_cdr
{
		int		change_condition_sgsn;				//		NUMBER (3), 
		char	ggsn_address[BUF_LEN];				//		VARCHAR2 (20),  
		char	change_time_ggsn[BUF_LEN];			//		VARCHAR2 (20), 
		int		cause_for_rec_closing;				//		NUMBER (20), 
		int		ms_network_capability;				//		NUMBER (10), 
  		int		data_downlink_ggsn;					//		NUMBER (30), 
		char	imsi[BUF_LEN];						//		VARCHAR2 (20), 
		int		record_sequence_no;					//		NUMBER (20), 
		int		change_condition_ggsn;				//		NUMBER (3), 
		char	served_pdp_address[BUF_LEN];		//		VARCHAR2 (20), 
		char	region_code_id[BUF_LEN];			//		VARCHAR2 (5),----null 
		char	qos_negotiated_sgsn[BUF_LEN];		//		VARCHAR2 (30), 
		int		roam;								//		NUMBER (1), ---refer R3 - 1 for roaming, 0 for non-roaming
		char	qos_requested_sgsn[BUF_LEN];		//		VARCHAR2 (30),  
		char	network_group_id[BUF_LEN];			//		VARCHAR2 (5), --------null
		int		location_area_code;					//		NUMBER (10), 
		char	record_opening_time_ggsn[BUF_LEN];	//		VARCHAR2 (20), 
		char	sgsn_address[BUF_LEN];				//		VARCHAR2 (20), 
		char	qos_negotiated_ggsn[BUF_LEN];		//		VARCHAR2 (30), 
		int		data_volume;						//		NUMBER (9), 
		char	routing_area[BUF_LEN];				//		VARCHAR2 (20), 
		int		duration;							//		NUMBER (20), 
		char	uplink_downlink[BUF_LEN];			//		VARCHAR2 (10), 
		int		cell_identity;						//		NUMBER (10), 
		char	node_id[BUF_LEN];					//		VARCHAR2 (20), 
		char	served_msisdn[BUF_LEN];				//		VARCHAR2 (30), 
		int		charging_id;						//		NUMBER (20), 
		char	access_point_name[BUF_LEN];			//		VARCHAR2 (50), 
  		int		data_uplink_ggsn;					//		NUMBER (30), 
  		char	change_time_sgsn[BUF_LEN];			//		VARCHAR2 (20), 
		int		pdp_type;							//		NUMBER (3), 
		int		record_type;						//		NUMBER (3), 
		int		service_type_id;					//		NUMBER (3)    NOT NULL,    ------GPRS - 11 
  		int		file_id; 							//		number(9)NOT NULL,
		int		file_pos;							//		number(9)NOT NULL,
		char	call_time[BUF_LEN];					//		DATE NOT NULL
		char	route_group_id[BUF_LEN];      		//		VARCHAR2 (5),-------------- null
  		char	day_type_id[BUF_LEN];				//      VARCHAR2 (5) ----- null
} a[INSERT_SIZE]; 

	int rows_to_insert;

/* EXEC SQL END DECLARE SECTION; */ 

	rows_to_insert = cdr_count;

	char buf[100]; 

	for(int j=0; j<INSERT_SIZE; j++)
	{
		a[j].file_pos = 0;
	}

	for(int i=0; i<INSERT_SIZE; i++)
	{
		
		a[i].file_id =  gsm_cdr_block[i].file_id; 
		a[i].file_pos = gsm_cdr_block[i].file_pos;
		
		//sprintf(buf,"%04d%02d%02d%02d%02d%02d",d.year,d.month,d.day,t.hour,t.min,t.second);	
		//strcpy(a[i].call_time, buf);

		a[i].data_volume = gsm_cdr_block[i].data_volume;							//              NUMBER (9), 
		a[i].record_type = gsm_cdr_block[i].recordType;							//                NUMBER (3), 
		strcpy(a[i].uplink_downlink, gsm_cdr_block[i].type_of_call.substr(0,10).c_str());			//           VARCHAR2 (10), 
		reng_date d=gsm_cdr_block[i].cdr_time_stamp.date;
		reng_time t=gsm_cdr_block[i].cdr_time_stamp.time;
		sprintf(buf,"%02d%s%02d%s%04d%s%02d%s%02d%s%02d",d.day,"/",d.month,"/",d.year," ",t.hour,":",t.min,":",t.second); 
		
		strcpy(a[i].call_time, buf);		//                 VARCHAR2 (14), 
		sprintf(a[i].sgsn_address,"%d.%d.%d.%d",gsm_cdr_block[i].sgsnAddress.first_int,gsm_cdr_block[i].sgsnAddress.second_int,gsm_cdr_block[i].sgsnAddress.third_int,gsm_cdr_block[i].sgsnAddress.fourth_int);
		sprintf(a[i].ggsn_address,"%d.%d.%d.%d",gsm_cdr_block[i].ggsnAddress.first_int,gsm_cdr_block[i].ggsnAddress.second_int,gsm_cdr_block[i].ggsnAddress.third_int,gsm_cdr_block[i].ggsnAddress.fourth_int);
		sprintf(a[i].served_pdp_address,"%d.%d.%d.%d",gsm_cdr_block[i].servedPDPAddress.first_int,gsm_cdr_block[i].servedPDPAddress.second_int,gsm_cdr_block[i].servedPDPAddress.third_int,gsm_cdr_block[i].servedPDPAddress.fourth_int);
	 
		sprintf(a[i].qos_requested_sgsn,"%d,%d,%d,%d.%d",gsm_cdr_block[i].qosRequested_SGSN.reliability,gsm_cdr_block[i].qosRequested_SGSN.delay,gsm_cdr_block[i].qosRequested_SGSN.precedence,gsm_cdr_block[i].qosRequested_SGSN.peakThroughput,gsm_cdr_block[i].qosRequested_SGSN.meanThroughput);
		sprintf(a[i].qos_negotiated_sgsn,"%d,%d,%d,%d.%d",gsm_cdr_block[i].qosNegotiated_SGSN.reliability,gsm_cdr_block[i].qosNegotiated_SGSN.delay,gsm_cdr_block[i].qosNegotiated_SGSN.precedence,gsm_cdr_block[i].qosNegotiated_SGSN.peakThroughput,gsm_cdr_block[i].qosNegotiated_SGSN.meanThroughput);
		sprintf(a[i].qos_negotiated_ggsn,"%d,%d,%d,%d.%d",gsm_cdr_block[i].qosNegotiated_GGSN.reliability,gsm_cdr_block[i].qosNegotiated_GGSN.delay,gsm_cdr_block[i].qosNegotiated_GGSN.precedence,gsm_cdr_block[i].qosNegotiated_GGSN.peakThroughput,gsm_cdr_block[i].qosNegotiated_GGSN.meanThroughput);
		
		a[i].pdp_type = gsm_cdr_block[i].pdpType;								//                   NUMBER (3), 
		a[i].change_condition_sgsn = gsm_cdr_block[i].changeCondition_SGSN;					//      NUMBER (3), 
		a[i].change_condition_ggsn = gsm_cdr_block[i].changeCondition_GGSN;					//      NUMBER (3), 
		strcpy(a[i].change_time_sgsn, gsm_cdr_block[i].changeTime_SGSN);		//          VARCHAR2 (20), 
		strcpy(a[i].change_time_ggsn, gsm_cdr_block[i].changeTime_GGSN);			//          VARCHAR2 (20), 
		strcpy(a[i].record_opening_time_ggsn, gsm_cdr_block[i].recordOpeningTime_GGSN);	//  VARCHAR2 (20), 
		a[i].ms_network_capability = gsm_cdr_block[i].msNetworkCapability;					//      NUMBER (10), 
		a[i].location_area_code = gsm_cdr_block[i].locationAreaCode;						//         NUMBER (10), 
		a[i].cell_identity = gsm_cdr_block[i].cellIdentity;							//              NUMBER (10), 
		a[i].data_uplink_ggsn = gsm_cdr_block[i].dataUplink_GGSN;						//           NUMBER (30), 
		a[i].data_downlink_ggsn = gsm_cdr_block[i].dataDownlink_GGSN;						//         NUMBER (30), 
		a[i].charging_id = gsm_cdr_block[i].chargingID;							//                NUMBER (20), 
		a[i].duration = gsm_cdr_block[i].duration;								//                   NUMBER (20), 
		a[i].cause_for_rec_closing = gsm_cdr_block[i].causeForRecClosing;					//      NUMBER (20), 
		a[i].record_sequence_no = gsm_cdr_block[i].recordSequenceNumber;						//         NUMBER (20), 
		strcpy(a[i].routing_area, gsm_cdr_block[i].routingArea);				//              VARCHAR2 (20), 
		strcpy(a[i].access_point_name, gsm_cdr_block[i].accessPointName);			//         VARCHAR2 (50), 
		strcpy(a[i].node_id, gsm_cdr_block[i].nodeID);					//                  VARCHAR2 (20), 
		strcpy(a[i].served_msisdn, gsm_cdr_block[i].servedMSISDN);				//             VARCHAR2 (30), 
		
		strcpy(a[i].imsi, gsm_cdr_block[i].servedIMSI);	

		a[i].roam = gsm_cdr_block[i].roam;
		a[i].service_type_id = 20;
		
		// null stuff
		strcpy(a[i].region_code_id, "");
		strcpy(a[i].network_group_id, "");
		strcpy(a[i].route_group_id, "");
		strcpy(a[i].day_type_id, "");
	} 

// ------------------
/*

	cout<<" ----------------- rows to insert "<<rows_to_insert<<endl;
	//for(int k=0; k<INSERT_SIZE; k++)
	for(int k=0; k<2; k++)
	{
		cout<<" "<<k<<"="<<a[k].file_pos ;
	}

	for(int l=0; l<rows_to_insert; l++)
	//for(int l=0; l<2; l++)
	{
		cout<<l<<" change_condition_sgsn = "<<a[l].change_condition_sgsn	<<"|"<<" n(3)"<<endl; 							
		cout<<l<<" ggsn_address			 = "<<a[l].ggsn_address				<<"|"<<" v(20)"<<endl;							
		cout<<l<<" change_time_ggsn		 = "<<a[l].change_time_ggsn			<<"|"<<" v(20)"<<endl;								
		cout<<l<<" cause_for_rec_closing = "<<a[l].cause_for_rec_closing	<<"|"<<" n(20)"<<endl;						
		cout<<l<<" ms_network_capability = "<<a[l].ms_network_capability	<<"|"<<" n(10)"<<endl;								
		cout<<l<<" data_downlink_ggsn	 = "<<a[l].data_downlink_ggsn		<<"|"<<" n(30)"<<endl;								
		cout<<l<<" imsi					 = "<<a[l].imsi						<<"|"<<" v(20)"<<endl; 				
		cout<<l<<" record_sequence_no	 = "<<a[l].record_sequence_no		<<"|"<<" n(20)"<<endl;								
		cout<<l<<" change_condition_ggsn = "<<a[l].change_condition_ggsn	<<"|"<<" n(3)"<<endl;				
		cout<<l<<" served_pdp_address	 = "<<a[l].served_pdp_address		<<"|"<<" v(20)"<<endl;					
		cout<<l<<" region_code_id		 = "<<a[l].region_code_id			<<"|"<<" v(5)--null"<<endl;					
		cout<<l<<" qos_negotiated_sgsn	 = "<<a[l].qos_negotiated_sgsn		<<"|"<<" v(30)"<<endl;							
		cout<<l<<" roam					 = "<<a[l].roam						<<"|"<<" n(1)"<<endl; 					
		cout<<l<<" qos_requested_sgsn	 = "<<a[l].qos_requested_sgsn		<<"|"<<" v(30)"<<endl;			
		cout<<l<<" network_group_id		 = "<<a[l].network_group_id			<<"|"<<" v(5)--null"<<endl; 						
		cout<<l<<" location_area_code	 = "<<a[l].location_area_code		<<"|"<<" n(10)"<<endl;					
		cout<<l<<" record_opening_time_ggsn="<<a[l].record_opening_time_ggsn <<"|"<<" v(20)"<<endl;						
		cout<<l<<" sgsn_address			 = "<<a[l].sgsn_address				<<"|"<<" v(20)"<<endl;								
		cout<<l<<" qos_negotiated_ggsn	 = "<<a[l].qos_negotiated_ggsn		<<"|"<<" v(30)"<<endl;							
		cout<<l<<" data_volume			 = "<<a[l].data_volume				<<"|"<<" n(9)"<<endl;							
		cout<<l<<" routing_area			 = "<<a[l].routing_area				<<"|"<<" v(20)"<<endl;
		cout<<l<<" duration				 = "<<a[l].duration					<<"|"<<" n(20)"<<endl;				
		cout<<l<<" uplink_downlink		 = "<<a[l].uplink_downlink			<<"|"<<" v(10)"<<endl;							
		cout<<l<<" cell_identity		 = "<<a[l].cell_identity			<<"|"<<" n(10)"<<endl;							
		cout<<l<<" node_id				 = "<<a[l].node_id					<<"|"<<" v(20)"<<endl;									
		cout<<l<<" served_msisdn		 = "<<a[l].served_msisdn			<<"|"<<" v(30)"<<endl; 									
		cout<<l<<" charging_id			 = "<<a[l].charging_id				<<"|"<<" n(20)"<<endl;
		cout<<l<<" access_point_name	 = "<<a[l].access_point_name		<<"|"<<" v(50)"<<endl;						
		cout<<l<<" data_uplink_ggsn		 = "<<a[l].data_uplink_ggsn			<<"|"<<" n(30)"<<endl;						
		cout<<l<<" change_time_sgsn		 = "<<a[l].change_time_sgsn			<<"|"<<" v(20)"<<endl;						
		cout<<l<<" pdp_type				 = "<<a[l].pdp_type					<<"|"<<" n(3)"<<endl;						
		cout<<l<<" record_type			 = "<<a[l].record_type				<<"|"<<" n(3)"<<endl;						
		cout<<l<<" service_type_id		 = "<<a[l].service_type_id			<<"|"<<" n(3)- not null"<<endl;
		cout<<l<<" file_id				 = "<<a[l].file_id					<<"|"<<" n(9)- not null"<<endl;						
		cout<<l<<" file_pos				 = "<<a[l].file_pos					<<"|"<<" n(9)- not null"<<endl;						
		cout<<l<<" call_time			 = "<<a[l].call_time				<<"|"<<" date - not null"<<endl;						
		cout<<l<<" route_group_id		 = "<<a[l].route_group_id			<<"|"<<" v(5) - null"<<endl;						
		cout<<l<<" day_type_id			 = "<<a[l].day_type_id				<<"|"<<" v(5) - null"<<endl;						
	}
*/
//------

/* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 

/* EXEC SQL FOR :rows_to_insert INSERT INTO DYN_4_UDR(
		change_condition_sgsn,
		ggsn_address,  
		change_time_ggsn,
		cause_for_rec_closing,
		ms_network_capability,
  		data_downlink_ggsn,
		imsi,
		record_sequance_no,
		change_condition_ggsn,
		served_pdp_address,
		region_code_id,
		qos_negotiated_sgsn,
		roam,
		qos_requested_sgsn,
		network_group_id,
		location_area_code,
		record_opening_time_ggsn,
		sgsn_address,
		qos_negotiated_ggsn,
		data_volume,
		routing_area,
		duration,
		uplink_downlink,
		cell_identity,
		node_id,
		served_msisdn,
		charging_id,
		access_point_name,
  		data_uplink_ggsn,
  		change_time_sgsn,
		pdp_type, 
		record_type,
		service_type_id,
  		file_id,
		file_pos,
		call_time,
		route_group_id,
  		day_type_id)
		VALUES (:a); */ 

{
struct sqlexd sqlstm;
sqlstm.sqlvsn = 10;
sqlstm.arrsiz = 38;
sqlstm.sqladtp = &sqladt;
sqlstm.sqltdsp = &sqltds;
sqlstm.stmt = "insert into DYN_4_UDR (change_condition_sgsn,ggsn_address,cha\
nge_time_ggsn,cause_for_rec_closing,ms_network_capability,data_downlink_ggsn,i\
msi,record_sequance_no,change_condition_ggsn,served_pdp_address,region_code_id\
,qos_negotiated_sgsn,roam,qos_requested_sgsn,network_group_id,location_area_co\
de,record_opening_time_ggsn,sgsn_address,qos_negotiated_ggsn,data_volume,routi\
ng_area,duration,uplink_downlink,cell_identity,node_id,served_msisdn,charging_\
id,access_point_name,data_uplink_ggsn,change_time_sgsn,pdp_type,record_type,se\
rvice_type_id,file_id,file_pos,call_time,route_group_id,day_type_id) values (:\
s1 ,:s2 ,:s3 ,:s4 ,:s5 ,:s6 ,:s7 ,:s8 ,:s9 ,:s10 ,:s11 ,:s12 ,:s13 ,:s14 ,:s15\
 ,:s16 ,:s17 ,:s18 ,:s19 ,:s20 ,:s21 ,:s22 ,:s23 ,:s24 ,:s25 ,:s26 ,:s27 ,:s28\
 ,:s29 ,:s30 ,:s31 ,:s32 ,:s33 ,:s34 ,:s35 ,:s36 ,:s37 ,:s38 )";
sqlstm.iters = (unsigned int  )rows_to_insert;
sqlstm.offset = (unsigned int  )5;
sqlstm.cud = sqlcud0;
sqlstm.sqlest = (unsigned char  *)&sqlca;
sqlstm.sqlety = (unsigned short)256;
sqlstm.occurs = (unsigned int  )0;
sqlstm.sqhstv[0] = (         void  *)&a->change_condition_sgsn;
sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[0] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[0] = (         void  *)0;
sqlstm.sqinds[0] = (         int  )0;
sqlstm.sqharm[0] = (unsigned int  )0;
sqlstm.sqharc[0] = (unsigned int   *)0;
sqlstm.sqadto[0] = (unsigned short )0;
sqlstm.sqtdso[0] = (unsigned short )0;
sqlstm.sqhstv[1] = (         void  *)a->ggsn_address;
sqlstm.sqhstl[1] = (unsigned int  )50;
sqlstm.sqhsts[1] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[1] = (         void  *)0;
sqlstm.sqinds[1] = (         int  )0;
sqlstm.sqharm[1] = (unsigned int  )0;
sqlstm.sqharc[1] = (unsigned int   *)0;
sqlstm.sqadto[1] = (unsigned short )0;
sqlstm.sqtdso[1] = (unsigned short )0;
sqlstm.sqhstv[2] = (         void  *)a->change_time_ggsn;
sqlstm.sqhstl[2] = (unsigned int  )50;
sqlstm.sqhsts[2] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[2] = (         void  *)0;
sqlstm.sqinds[2] = (         int  )0;
sqlstm.sqharm[2] = (unsigned int  )0;
sqlstm.sqharc[2] = (unsigned int   *)0;
sqlstm.sqadto[2] = (unsigned short )0;
sqlstm.sqtdso[2] = (unsigned short )0;
sqlstm.sqhstv[3] = (         void  *)&a->cause_for_rec_closing;
sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[3] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[3] = (         void  *)0;
sqlstm.sqinds[3] = (         int  )0;
sqlstm.sqharm[3] = (unsigned int  )0;
sqlstm.sqharc[3] = (unsigned int   *)0;
sqlstm.sqadto[3] = (unsigned short )0;
sqlstm.sqtdso[3] = (unsigned short )0;
sqlstm.sqhstv[4] = (         void  *)&a->ms_network_capability;
sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[4] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[4] = (         void  *)0;
sqlstm.sqinds[4] = (         int  )0;
sqlstm.sqharm[4] = (unsigned int  )0;
sqlstm.sqharc[4] = (unsigned int   *)0;
sqlstm.sqadto[4] = (unsigned short )0;
sqlstm.sqtdso[4] = (unsigned short )0;
sqlstm.sqhstv[5] = (         void  *)&a->data_downlink_ggsn;
sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[5] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[5] = (         void  *)0;
sqlstm.sqinds[5] = (         int  )0;
sqlstm.sqharm[5] = (unsigned int  )0;
sqlstm.sqharc[5] = (unsigned int   *)0;
sqlstm.sqadto[5] = (unsigned short )0;
sqlstm.sqtdso[5] = (unsigned short )0;
sqlstm.sqhstv[6] = (         void  *)a->imsi;
sqlstm.sqhstl[6] = (unsigned int  )50;
sqlstm.sqhsts[6] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[6] = (         void  *)0;
sqlstm.sqinds[6] = (         int  )0;
sqlstm.sqharm[6] = (unsigned int  )0;
sqlstm.sqharc[6] = (unsigned int   *)0;
sqlstm.sqadto[6] = (unsigned short )0;
sqlstm.sqtdso[6] = (unsigned short )0;
sqlstm.sqhstv[7] = (         void  *)&a->record_sequence_no;
sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[7] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[7] = (         void  *)0;
sqlstm.sqinds[7] = (         int  )0;
sqlstm.sqharm[7] = (unsigned int  )0;
sqlstm.sqharc[7] = (unsigned int   *)0;
sqlstm.sqadto[7] = (unsigned short )0;
sqlstm.sqtdso[7] = (unsigned short )0;
sqlstm.sqhstv[8] = (         void  *)&a->change_condition_ggsn;
sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[8] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[8] = (         void  *)0;
sqlstm.sqinds[8] = (         int  )0;
sqlstm.sqharm[8] = (unsigned int  )0;
sqlstm.sqharc[8] = (unsigned int   *)0;
sqlstm.sqadto[8] = (unsigned short )0;
sqlstm.sqtdso[8] = (unsigned short )0;
sqlstm.sqhstv[9] = (         void  *)a->served_pdp_address;
sqlstm.sqhstl[9] = (unsigned int  )50;
sqlstm.sqhsts[9] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[9] = (         void  *)0;
sqlstm.sqinds[9] = (         int  )0;
sqlstm.sqharm[9] = (unsigned int  )0;
sqlstm.sqharc[9] = (unsigned int   *)0;
sqlstm.sqadto[9] = (unsigned short )0;
sqlstm.sqtdso[9] = (unsigned short )0;
sqlstm.sqhstv[10] = (         void  *)a->region_code_id;
sqlstm.sqhstl[10] = (unsigned int  )50;
sqlstm.sqhsts[10] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[10] = (         void  *)0;
sqlstm.sqinds[10] = (         int  )0;
sqlstm.sqharm[10] = (unsigned int  )0;
sqlstm.sqharc[10] = (unsigned int   *)0;
sqlstm.sqadto[10] = (unsigned short )0;
sqlstm.sqtdso[10] = (unsigned short )0;
sqlstm.sqhstv[11] = (         void  *)a->qos_negotiated_sgsn;
sqlstm.sqhstl[11] = (unsigned int  )50;
sqlstm.sqhsts[11] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[11] = (         void  *)0;
sqlstm.sqinds[11] = (         int  )0;
sqlstm.sqharm[11] = (unsigned int  )0;
sqlstm.sqharc[11] = (unsigned int   *)0;
sqlstm.sqadto[11] = (unsigned short )0;
sqlstm.sqtdso[11] = (unsigned short )0;
sqlstm.sqhstv[12] = (         void  *)&a->roam;
sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[12] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[12] = (         void  *)0;
sqlstm.sqinds[12] = (         int  )0;
sqlstm.sqharm[12] = (unsigned int  )0;
sqlstm.sqharc[12] = (unsigned int   *)0;
sqlstm.sqadto[12] = (unsigned short )0;
sqlstm.sqtdso[12] = (unsigned short )0;
sqlstm.sqhstv[13] = (         void  *)a->qos_requested_sgsn;
sqlstm.sqhstl[13] = (unsigned int  )50;
sqlstm.sqhsts[13] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[13] = (         void  *)0;
sqlstm.sqinds[13] = (         int  )0;
sqlstm.sqharm[13] = (unsigned int  )0;
sqlstm.sqharc[13] = (unsigned int   *)0;
sqlstm.sqadto[13] = (unsigned short )0;
sqlstm.sqtdso[13] = (unsigned short )0;
sqlstm.sqhstv[14] = (         void  *)a->network_group_id;
sqlstm.sqhstl[14] = (unsigned int  )50;
sqlstm.sqhsts[14] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[14] = (         void  *)0;
sqlstm.sqinds[14] = (         int  )0;
sqlstm.sqharm[14] = (unsigned int  )0;
sqlstm.sqharc[14] = (unsigned int   *)0;
sqlstm.sqadto[14] = (unsigned short )0;
sqlstm.sqtdso[14] = (unsigned short )0;
sqlstm.sqhstv[15] = (         void  *)&a->location_area_code;
sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[15] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[15] = (         void  *)0;
sqlstm.sqinds[15] = (         int  )0;
sqlstm.sqharm[15] = (unsigned int  )0;
sqlstm.sqharc[15] = (unsigned int   *)0;
sqlstm.sqadto[15] = (unsigned short )0;
sqlstm.sqtdso[15] = (unsigned short )0;
sqlstm.sqhstv[16] = (         void  *)a->record_opening_time_ggsn;
sqlstm.sqhstl[16] = (unsigned int  )50;
sqlstm.sqhsts[16] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[16] = (         void  *)0;
sqlstm.sqinds[16] = (         int  )0;
sqlstm.sqharm[16] = (unsigned int  )0;
sqlstm.sqharc[16] = (unsigned int   *)0;
sqlstm.sqadto[16] = (unsigned short )0;
sqlstm.sqtdso[16] = (unsigned short )0;
sqlstm.sqhstv[17] = (         void  *)a->sgsn_address;
sqlstm.sqhstl[17] = (unsigned int  )50;
sqlstm.sqhsts[17] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[17] = (         void  *)0;
sqlstm.sqinds[17] = (         int  )0;
sqlstm.sqharm[17] = (unsigned int  )0;
sqlstm.sqharc[17] = (unsigned int   *)0;
sqlstm.sqadto[17] = (unsigned short )0;
sqlstm.sqtdso[17] = (unsigned short )0;
sqlstm.sqhstv[18] = (         void  *)a->qos_negotiated_ggsn;
sqlstm.sqhstl[18] = (unsigned int  )50;
sqlstm.sqhsts[18] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[18] = (         void  *)0;
sqlstm.sqinds[18] = (         int  )0;
sqlstm.sqharm[18] = (unsigned int  )0;
sqlstm.sqharc[18] = (unsigned int   *)0;
sqlstm.sqadto[18] = (unsigned short )0;
sqlstm.sqtdso[18] = (unsigned short )0;
sqlstm.sqhstv[19] = (         void  *)&a->data_volume;
sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[19] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[19] = (         void  *)0;
sqlstm.sqinds[19] = (         int  )0;
sqlstm.sqharm[19] = (unsigned int  )0;
sqlstm.sqharc[19] = (unsigned int   *)0;
sqlstm.sqadto[19] = (unsigned short )0;
sqlstm.sqtdso[19] = (unsigned short )0;
sqlstm.sqhstv[20] = (         void  *)a->routing_area;
sqlstm.sqhstl[20] = (unsigned int  )50;
sqlstm.sqhsts[20] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[20] = (         void  *)0;
sqlstm.sqinds[20] = (         int  )0;
sqlstm.sqharm[20] = (unsigned int  )0;
sqlstm.sqharc[20] = (unsigned int   *)0;
sqlstm.sqadto[20] = (unsigned short )0;
sqlstm.sqtdso[20] = (unsigned short )0;
sqlstm.sqhstv[21] = (         void  *)&a->duration;
sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[21] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[21] = (         void  *)0;
sqlstm.sqinds[21] = (         int  )0;
sqlstm.sqharm[21] = (unsigned int  )0;
sqlstm.sqharc[21] = (unsigned int   *)0;
sqlstm.sqadto[21] = (unsigned short )0;
sqlstm.sqtdso[21] = (unsigned short )0;
sqlstm.sqhstv[22] = (         void  *)a->uplink_downlink;
sqlstm.sqhstl[22] = (unsigned int  )50;
sqlstm.sqhsts[22] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[22] = (         void  *)0;
sqlstm.sqinds[22] = (         int  )0;
sqlstm.sqharm[22] = (unsigned int  )0;
sqlstm.sqharc[22] = (unsigned int   *)0;
sqlstm.sqadto[22] = (unsigned short )0;
sqlstm.sqtdso[22] = (unsigned short )0;
sqlstm.sqhstv[23] = (         void  *)&a->cell_identity;
sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[23] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[23] = (         void  *)0;
sqlstm.sqinds[23] = (         int  )0;
sqlstm.sqharm[23] = (unsigned int  )0;
sqlstm.sqharc[23] = (unsigned int   *)0;
sqlstm.sqadto[23] = (unsigned short )0;
sqlstm.sqtdso[23] = (unsigned short )0;
sqlstm.sqhstv[24] = (         void  *)a->node_id;
sqlstm.sqhstl[24] = (unsigned int  )50;
sqlstm.sqhsts[24] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[24] = (         void  *)0;
sqlstm.sqinds[24] = (         int  )0;
sqlstm.sqharm[24] = (unsigned int  )0;
sqlstm.sqharc[24] = (unsigned int   *)0;
sqlstm.sqadto[24] = (unsigned short )0;
sqlstm.sqtdso[24] = (unsigned short )0;
sqlstm.sqhstv[25] = (         void  *)a->served_msisdn;
sqlstm.sqhstl[25] = (unsigned int  )50;
sqlstm.sqhsts[25] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[25] = (         void  *)0;
sqlstm.sqinds[25] = (         int  )0;
sqlstm.sqharm[25] = (unsigned int  )0;
sqlstm.sqharc[25] = (unsigned int   *)0;
sqlstm.sqadto[25] = (unsigned short )0;
sqlstm.sqtdso[25] = (unsigned short )0;
sqlstm.sqhstv[26] = (         void  *)&a->charging_id;
sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[26] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[26] = (         void  *)0;
sqlstm.sqinds[26] = (         int  )0;
sqlstm.sqharm[26] = (unsigned int  )0;
sqlstm.sqharc[26] = (unsigned int   *)0;
sqlstm.sqadto[26] = (unsigned short )0;
sqlstm.sqtdso[26] = (unsigned short )0;
sqlstm.sqhstv[27] = (         void  *)a->access_point_name;
sqlstm.sqhstl[27] = (unsigned int  )50;
sqlstm.sqhsts[27] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[27] = (         void  *)0;
sqlstm.sqinds[27] = (         int  )0;
sqlstm.sqharm[27] = (unsigned int  )0;
sqlstm.sqharc[27] = (unsigned int   *)0;
sqlstm.sqadto[27] = (unsigned short )0;
sqlstm.sqtdso[27] = (unsigned short )0;
sqlstm.sqhstv[28] = (         void  *)&a->data_uplink_ggsn;
sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[28] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[28] = (         void  *)0;
sqlstm.sqinds[28] = (         int  )0;
sqlstm.sqharm[28] = (unsigned int  )0;
sqlstm.sqharc[28] = (unsigned int   *)0;
sqlstm.sqadto[28] = (unsigned short )0;
sqlstm.sqtdso[28] = (unsigned short )0;
sqlstm.sqhstv[29] = (         void  *)a->change_time_sgsn;
sqlstm.sqhstl[29] = (unsigned int  )50;
sqlstm.sqhsts[29] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[29] = (         void  *)0;
sqlstm.sqinds[29] = (         int  )0;
sqlstm.sqharm[29] = (unsigned int  )0;
sqlstm.sqharc[29] = (unsigned int   *)0;
sqlstm.sqadto[29] = (unsigned short )0;
sqlstm.sqtdso[29] = (unsigned short )0;
sqlstm.sqhstv[30] = (         void  *)&a->pdp_type;
sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[30] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[30] = (         void  *)0;
sqlstm.sqinds[30] = (         int  )0;
sqlstm.sqharm[30] = (unsigned int  )0;
sqlstm.sqharc[30] = (unsigned int   *)0;
sqlstm.sqadto[30] = (unsigned short )0;
sqlstm.sqtdso[30] = (unsigned short )0;
sqlstm.sqhstv[31] = (         void  *)&a->record_type;
sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[31] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[31] = (         void  *)0;
sqlstm.sqinds[31] = (         int  )0;
sqlstm.sqharm[31] = (unsigned int  )0;
sqlstm.sqharc[31] = (unsigned int   *)0;
sqlstm.sqadto[31] = (unsigned short )0;
sqlstm.sqtdso[31] = (unsigned short )0;
sqlstm.sqhstv[32] = (         void  *)&a->service_type_id;
sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[32] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[32] = (         void  *)0;
sqlstm.sqinds[32] = (         int  )0;
sqlstm.sqharm[32] = (unsigned int  )0;
sqlstm.sqharc[32] = (unsigned int   *)0;
sqlstm.sqadto[32] = (unsigned short )0;
sqlstm.sqtdso[32] = (unsigned short )0;
sqlstm.sqhstv[33] = (         void  *)&a->file_id;
sqlstm.sqhstl[33] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[33] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[33] = (         void  *)0;
sqlstm.sqinds[33] = (         int  )0;
sqlstm.sqharm[33] = (unsigned int  )0;
sqlstm.sqharc[33] = (unsigned int   *)0;
sqlstm.sqadto[33] = (unsigned short )0;
sqlstm.sqtdso[33] = (unsigned short )0;
sqlstm.sqhstv[34] = (         void  *)&a->file_pos;
sqlstm.sqhstl[34] = (unsigned int  )sizeof(int);
sqlstm.sqhsts[34] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[34] = (         void  *)0;
sqlstm.sqinds[34] = (         int  )0;
sqlstm.sqharm[34] = (unsigned int  )0;
sqlstm.sqharc[34] = (unsigned int   *)0;
sqlstm.sqadto[34] = (unsigned short )0;
sqlstm.sqtdso[34] = (unsigned short )0;
sqlstm.sqhstv[35] = (         void  *)a->call_time;
sqlstm.sqhstl[35] = (unsigned int  )50;
sqlstm.sqhsts[35] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[35] = (         void  *)0;
sqlstm.sqinds[35] = (         int  )0;
sqlstm.sqharm[35] = (unsigned int  )0;
sqlstm.sqharc[35] = (unsigned int   *)0;
sqlstm.sqadto[35] = (unsigned short )0;
sqlstm.sqtdso[35] = (unsigned short )0;
sqlstm.sqhstv[36] = (         void  *)a->route_group_id;
sqlstm.sqhstl[36] = (unsigned int  )50;
sqlstm.sqhsts[36] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[36] = (         void  *)0;
sqlstm.sqinds[36] = (         int  )0;
sqlstm.sqharm[36] = (unsigned int  )0;
sqlstm.sqharc[36] = (unsigned int   *)0;
sqlstm.sqadto[36] = (unsigned short )0;
sqlstm.sqtdso[36] = (unsigned short )0;
sqlstm.sqhstv[37] = (         void  *)a->day_type_id;
sqlstm.sqhstl[37] = (unsigned int  )50;
sqlstm.sqhsts[37] = (         int  )sizeof(struct db_cdr);
sqlstm.sqindv[37] = (         void  *)0;
sqlstm.sqinds[37] = (         int  )0;
sqlstm.sqharm[37] = (unsigned int  )0;
sqlstm.sqharc[37] = (unsigned int   *)0;
sqlstm.sqadto[37] = (unsigned short )0;
sqlstm.sqtdso[37] = (unsigned short )0;
sqlstm.sqphsv = sqlstm.sqhstv;
sqlstm.sqphsl = sqlstm.sqhstl;
sqlstm.sqphss = sqlstm.sqhsts;
sqlstm.sqpind = sqlstm.sqindv;
sqlstm.sqpins = sqlstm.sqinds;
sqlstm.sqparm = sqlstm.sqharm;
sqlstm.sqparc = sqlstm.sqharc;
sqlstm.sqpadto = sqlstm.sqadto;
sqlstm.sqptdso = sqlstm.sqtdso;
sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}



/* EXEC SQL COMMIT; */ 

{
struct sqlexd sqlstm;
sqlstm.sqlvsn = 10;
sqlstm.arrsiz = 38;
sqlstm.sqladtp = &sqladt;
sqlstm.sqltdsp = &sqltds;
sqlstm.iters = (unsigned int  )1;
sqlstm.offset = (unsigned int  )172;
sqlstm.cud = sqlcud0;
sqlstm.sqlest = (unsigned char  *)&sqlca;
sqlstm.sqlety = (unsigned short)256;
sqlstm.occurs = (unsigned int  )0;
sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}


}







