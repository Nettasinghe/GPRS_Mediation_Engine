

//////////////////////////////////////////////////////////////////////
//
// cdr_file_locations.cpp - implementation for file_locations class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////



#include "cdr.h"



void file_locations::init(string i)
{
	path=i;
	path_and_name ="";
}


char* file_locations::get_full_file_name(string file_name)
{
	path_and_name = path+file_name;
	return ((char*)path_and_name.c_str());
}






