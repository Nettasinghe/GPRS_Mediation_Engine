
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
           char  filnam[28];
};
static const struct sqlcxp sqlfpn =
{
    27,
    "D:\\src\\gprs_mediation\\db.pc"
};


static unsigned long sqlctx = 820194155;


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
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {10,4};

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
5,0,0,1,0,0,27,55,0,0,4,4,0,1,0,1,5,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,59,0,1,57,0,0,0,0,0,1,0,
51,0,0,3,0,0,30,63,0,0,0,0,0,1,0,
};



//////////////////////////////////////////////////////////////////////
// db.pc
// GPRS mediation module
// Copyright Millennium IT Software 2002
//////////////////////////////////////////////////////////////////////

#include <sqlca.h>

#ifndef ORA_PROC
	#include "db.h"
	#include <iostream>
#endif

#pragma warning(disable:4786)
using namespace std;

/*
void sql_error(char *msg)
{
    cout << endl << msg << endl;
    sqlca.sqlerrm.sqlerrmc[sqlca.sqlerrm.sqlerrml] = '\0';
    oraca.orastxt.orastxtc[oraca.orastxt.orastxtl] = '\0';
    oraca.orasfnm.orasfnmc[oraca.orasfnm.orasfnml] = '\0';
    cout << sqlca.sqlerrm.sqlerrmc << endl;
    cout << "in " << oraca.orastxt.orastxtc << endl;
    cout << "on line " << oraca.oraslnr << " of " << oraca.orasfnm.orasfnmc
         << endl << endl;

  //-- Roll back any pending changes and disconnect from Oracle.

    EXEC SQL ROLLBACK RELEASE;
    exit(1);
}
*/

void db_error(char* zErrorMsg)
{
	/* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

	cout << endl << zErrorMsg << endl<<flush;
	cout << sqlca.sqlerrm.sqlerrmc << endl<<flush;
	exit(0);
}

void db_login(char* zLoginString)
{
	/* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 

	//EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error--");

	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char* z_LoginString;
	/* EXEC SQL END DECLARE SECTION; */ 
	

	z_LoginString = zLoginString;
	/* EXEC SQL CONNECT :z_LoginString; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )10;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)z_LoginString;
 sqlstm.sqhstl[0] = (unsigned int  )0;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
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


	cout<<"\nUser Log To the DataBase"<<endl<<endl;
	/* EXEC SQL ALTER SESSION SET NLS_DATE_FORMAT="DD/MM/YYYY HH24:MI:SS"; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "alter SESSION SET NLS_DATE_FORMAT = \"DD/MM/YYYY HH24:MI:SS\"";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )36;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}

 
}

void db_logout()
{
	/* EXEC SQL WHENEVER SQLERROR DO db_error("ORACLE error:"); */ 

	/* EXEC SQL COMMIT WORK RELEASE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )51;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) db_error("ORACLE error:");
}


	cout<<"\nDisconnect from oracle "<<endl;
}

