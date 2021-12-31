

//////////////////////////////////////////////////////////////////////
//
// db.h - class definitions for database interaction 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


#ifndef DB_H
#define DB_H

void	db_error(char*);
void	sql_error(char *msg);
void	db_login(char*);
void	db_logout();

void	db_insert_rated_cdr(int cdr_count);

#define INSERT_SIZE 100


#endif

