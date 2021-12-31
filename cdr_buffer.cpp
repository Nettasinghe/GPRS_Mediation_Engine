

//////////////////////////////////////////////////////////////////////
//
// cdr_buffer.cpp - implementation for cdr_buffer class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"


// from 5 th byte in CDR
#define CIRCUIT_OFFSET 4  // 4 bytes from 0xff to start of circuit allocation time stamp
#define CALL_OFFSET 13    // 13 bytes from 0xff to start of call time stamp
#define FF_OFFSET 4		  // 4 bytes from start of cdr to 0xff


unsigned char bcd_to_int(unsigned char a)
{
	return ((unsigned char) ((((a & 0xf0)>>4)*10) + (a & 0x0f)));
}


// open a vaild file pointer and collects a bit of statistics as well
bool cdr_buffer::read_cdr_file(FILE *fp, cdr_file_statistics *s)
{
	bool found = false;
	// read_cdr_file();
	//cout <<"buffer_size : "<< buffer_size << endl;
	bytes_read = fread(buffer, sizeof(unsigned char), buffer_size, fp);
	//cout <<"bytes_read : "<< bytes_read << endl;
	statistics = s;
	statistics->bytes_read = bytes_read;

	if(bytes_read == 0)
	{
		return false;
	}
	else if (bytes_read == buffer_size)
	{
		cout<<"<ERROR> possible cdr buffer overflow "<<bytes_read<<endl;
		return false;
		//exit(1);
	}

	data_end = buffer + bytes_read;	//Why
	//data_end = buffer + 200;
	current =  buffer;				// WHY????

	return found; // all data files read
}


void cdr_buffer::init()
{
	bytes_read		= 0;
	current			= buffer;
	data_end		= buffer;
	cdr_length		= 0;
	cdr_count		= 0;
	cdr_position	= 0;				// location of cdr from start of file

// inialise buffer area, useful for debugging only
//	for(unsigned char* a=buffer; a<end_of_buffer; a++)
//		*a=0x00;
}

// object lives for lifetime of program
cdr_buffer::cdr_buffer(int size)
{
	buffer_size = size;
	buffer = new unsigned char[buffer_size];
	if (!buffer)
	{
		cout<<"ERR: FATAL cant allocate "<<buffer_size/1024<<" KB  for CDR buffer"<<endl;
		exit(1);
	}

	end_of_buffer = buffer+buffer_size;
	init();
}


class cdr_tm
{
public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	
	bool check_from_year();
	bool check_from_month();
};


bool cdr_tm::check_from_month()
{
	bool valid = true;
	if ( !(month >=1 && month <= 12))
		valid = false;
	else if ( !(day >=1 && day <= 31))
		valid = false;
	else if (!(hour >= 0 && hour <= 23))
		valid = false;
	else if (!(min >=0 && min <= 59 ))
		valid = false;
	else if (!(sec >= 0 && sec <= 59))
		valid = false;
	
	return valid;
}


bool cdr_tm::check_from_year()
{
	bool valid=check_from_month();

	if (!(year >= 0 && year <= 99))
		valid = false;
	
	return valid;
}




bool cdr_buffer::get_cdr_start()
{
	// The cdr start signature (*=don't care nibble, x is hex)
	// length is five bytes
	//     0x**    0x23    0x03    0x01	   0x02	   0x03  
	//		0		1		2		3		4		5		<- location in array
	//	   -5	   -4			   -2	   -1		0		= current and offsets from current

	unsigned char *b_ptr; // buffer pointer
	
	unsigned char record_length;
	b_ptr = current-1;
	
	//( (*(b_ptr+2))==0x03 && (*(b_ptr+3))==0x01 && (*(b_ptr+4))==0x02 && (*(b_ptr+5))==0x03 )

	do 
	{
		b_ptr++;
		//cout << "(*(b_ptr+1) :" << int(*(b_ptr+1)) << endl;
		
		if((*(b_ptr+1))!=0x23)		// move along till 0x23 is found
			continue;
		
		if ( ((*(b_ptr+2))==0x03) && ((*(b_ptr+3))==0x01) && ((*(b_ptr+4))==0x02) && ((*(b_ptr+5))==0x03))	// pattern match
		{
			record_length = *(b_ptr-1);

			// check cdr does not exceed file end
			if(b_ptr+record_length > data_end)
			{
				cout<<"WARN ------------PARTIAL CDR----------"<<endl;
				statistics->reject_cdr_count++;
				continue;
			}
				
			//	passes initial sanity checks
			//current		= b_ptr;
			current		= b_ptr+6;
			cdr_length	= record_length; 
			cdr_count++;
			statistics->valid_cdr_count++;
			cdr_position = current - buffer;
			return true;  // cdr start signature found
		}


	}while (b_ptr < data_end);

	return false;
}


// current must be at start of cdr 
// or else premature exit
void cdr_buffer::print_cdr_in_hex()
{
	int k=0;
	
	for(unsigned char *i=current; i<=current+cdr_length; i++)
	{
		if(i > data_end)
		{
			printf(" ERR: Out of vaild data sequence ");
			return;
		}
		if (!(k%8))
			printf("   ");
		if (!(k%16))
			printf("\n %04x  ",i-buffer);
		printf(" %02x",(int)(*i));
		k++;
	}
	printf("\n");
}

int cdr_buffer::get_cdr_position()
{
	return cdr_position;
}

