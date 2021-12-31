
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
           char  filnam[38];
};
static const struct sqlcxp sqlfpn =
{
    37,
    "D:\\src\\gprs_mediation\\db_cdr_files.pc"
};


static unsigned long sqlctx = 1934515645;


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
            void  *sqhstv[6];
   unsigned int   sqhstl[6];
            int   sqhsts[6];
            void  *sqindv[6];
            int   sqinds[6];
   unsigned int   sqharm[6];
   unsigned int   *sqharc[6];
   unsigned short  sqadto[6];
   unsigned short  sqtdso[6];
} sqlstm = {10,6};

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

 static const char *sq0001 = 
"select FILE_NAME ,CDR_FILE_ID_NO  from sys_gprs_dump_files where DECODED_DAT\
E is null            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4146,0,0,0,
5,0,0,1,97,0,9,57,0,0,0,0,0,1,0,
20,0,0,1,0,0,13,63,0,0,2,0,0,1,0,2,5,0,0,2,3,0,0,
43,0,0,1,0,0,15,78,0,0,0,0,0,1,0,
58,0,0,2,221,0,5,126,0,0,6,6,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,
0,0,
97,0,0,3,0,0,29,143,0,0,0,0,0,1,0,
};



//////////////////////////////////////////////////////////////////////
// db_cdr_files.pc
// GPRS mediation module
// Copyright Millennium IT Software 2002
//////////////////////////////////////////////////////////////////////

#define SQLCA_STORAGE_CLASS extern 
#define ORACA_STORAGE_CLASS extern 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlcpr.h>


#ifndef ORA_PROC
	#include "db.h"
	#include "cdr.h"
#endif

#define BUF_L		102
#define BUF_LENTH	20
#define FETCH_SIZE	10

extern int global_cdr_count;



// get cdr files
void cdr_files::db_read()
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	struct cdr_file_t
	{ 
		char file_name[BUF_L];			// varchar2(123)
		int file_id;					// called id_no in table number(9)
	} a[FETCH_SIZE]; 
	int rows_to_fetch, rows_before, rows_this_time; 

	/* EXEC SQL END DECLARE SECTION; */ 


	int i;

	rows_to_fetch = FETCH_SIZE;		// number of rows in each "batch"  
	rows_before = 0;				// previous value of sqlerrd[2]   
	rows_this_time = FETCH_SIZE;
	 
	/* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 

    /* EXEC SQL DECLARE c_cdr_file CURSOR FOR 
	SELECT	FILE_NAME,  CDR_FILE_ID_NO
//	FROM	cdr_dump_files
	FROM	sys_gprs_dump_files
	WHERE DECODED_DATE IS NULL; */ 

       
    /* EXEC SQL OPEN c_cdr_file; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 0;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0001;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}

 
	/* EXEC SQL WHENEVER NOT FOUND CONTINUE; */ 

	/* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 
 

	while (rows_this_time == rows_to_fetch) 
	{ 
		/* EXEC SQL FETCH c_cdr_file INTO :a; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )10;
  sqlstm.offset = (unsigned int  )20;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)a->file_name;
  sqlstm.sqhstl[0] = (unsigned int  )102;
  sqlstm.sqhsts[0] = (         int  )sizeof(struct cdr_file_t);
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqharc[0] = (unsigned int   *)0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&a->file_id;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )sizeof(struct cdr_file_t);
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqharc[1] = (unsigned int   *)0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
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

 		 
		rows_this_time = sqlca.sqlerrd[2] - rows_before; 
		rows_before = sqlca.sqlerrd[2]; 
		//printf(" this=%d before=%d to_fetch=%d\n", rows_this_time, rows_before, rows_to_fetch);


		cdr_file_statistics cd;
		cd.init();
		for(i=0; i<rows_this_time; i++)
		{
			cd.file_id = a[i].file_id;			
			insert(a[i].file_name, cd);
		}
	} 

    /* EXEC SQL CLOSE c_cdr_file; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )43;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}

 
 
    printf("\n %d  cdr files loaded.\n\n",rows_before);
}



void cdr_files::db_update(cdr_file_statistics s)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	struct cdr_file_t
	{ 
		 int valid_cdr_count;					//  number(7)
		 int error_count;						//	number(7)
		 int bytes_read;						//	number(9)
		 char first_cdr_date[BUF_LENTH];				//	varchar2(14)
		 char last_cdr_date[BUF_LENTH];				//	varchar2(14)
		 int rating_duration;
		 char rating_start_date[BUF_LENTH];	//	varchar2(14)

		 int id_no;						//	number(9)
 	} a; 

	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL WHENEVER NOT FOUND GOTO nofile; */ 


//#ifndef code_skip

	 //cout << "a.id_no :" <<a.id_no<<endl;
	 //cout <<"s.file_id : "<<s.file_id<<endl;
	 a.id_no = s.file_id;
	 //cout << "a.id_no :" <<a.id_no<<endl;
	 //cout <<"s.file_id : "<<s.file_id<<endl;

	 //a.valid_cdr_count = s.valid_cdr_count;
	 a.valid_cdr_count = global_cdr_count;
	 a.error_count = s.error_count;
	 a.bytes_read = s.bytes_read;
	 strcpy(a.first_cdr_date, s.first_cdr_date.c_str());
	 strcpy(a.last_cdr_date, s.last_cdr_date.c_str());
	 a.rating_duration = s.rating_duration;
	 strcpy(a.rating_start_date, s.rating_start_date.c_str());
	 
	 	
//#endif

	 /* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 

	 /* EXEC SQL	
//	 UPDATE cdr_dump_files 
// 	 UPDATE cdr_dump_files2  
 	 //UPDATE cdr_dump_files3
	 UPDATE sys_gprs_dump_files

	 SET 
		valid_cdr_count			= :a.valid_cdr_count, 
		error_count				= :a.error_count,
		bytes_read				= :a.bytes_read,
		first_cdr_date			= to_date(:a.first_cdr_date,'YYYYMMDDHH24MISS'),
		last_cdr_date			= to_date(:a.last_cdr_date,'YYYYMMDDHH24MISS'),
		//rating_duration			= :a.rating_duration,
		//decoded_date		= to_date(:a.rating_start_date,'YYYYMMDDHH24MISS')
		decoded_date		= SYSDATE
	 WHERE cdr_file_id_no  = :a.id_no; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 6;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "update sys_gprs_dump_files  set valid_cdr_count=:b0,error_c\
ount=:b1,bytes_read=:b2,first_cdr_date=to_date(:b3,'YYYYMMDDHH24MISS'),last_cd\
r_date=to_date(:b4,'YYYYMMDDHH24MISS'),decoded_date=SYSDATE where cdr_file_id_\
no=:b5";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )58;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&(a.valid_cdr_count);
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&(a.error_count);
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&(a.bytes_read);
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)(a.first_cdr_date);
  sqlstm.sqhstl[3] = (unsigned int  )20;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)(a.last_cdr_date);
  sqlstm.sqhstl[4] = (unsigned int  )20;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&(a.id_no);
  sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
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
  if (sqlca.sqlcode == 1403) goto nofile;
  if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}



	 /* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 6;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )97;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}


 
    printf("\n cdr file id=%d log updated.\n\n", s.file_id);
	return;
nofile:
	printf("\n <ERROR> file id = %d  not found to update.\n\n", s.file_id);
}


