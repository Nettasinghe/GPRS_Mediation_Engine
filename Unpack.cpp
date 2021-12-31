

//////////////////////////////////////////////////////////////////////
//
// Unpack.cpp - implementation for unpack class 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////



#include "cdr.h"
#include <ctype.h>

//extern bool core_dump;
//extern cdr_buffer *cdr_store;

// upacks all the condensed data into ascii strings
//	a) BCD	= Binary coded decimal
//	b) TBCD	= Telephony binary coded decimal, BCD with swapped digits)
//	c) BIN	= Plain binary
//  d) HEXA = Hex same as binary

inline unsigned char unpack::get_most_significant_nibble(unsigned char a)
{
	return( a>>4);
}


unsigned char unpack::get_least_significant_nibble(unsigned char a)
{
	return( a & 0x0f);
}


// The decimal digits are swapped compared BCD
unsigned char unpack::get_TBCD(unsigned char a)
{
	unsigned char MSN, LSN;
	LSN=get_most_significant_nibble(a);
	MSN=get_least_significant_nibble(a);

	return( (MSN*10) | LSN);
}


unsigned char unpack::get_BIN(unsigned char a)
{
	return (a);
}


// put in ascii digit string a cdr format bcd record
// the conversion terminates when a non digit character is found
char* unpack::get_BCD(unsigned char *a, int length, char *buf)
{
	int k;
	unsigned char b,c;
	for(k=0; k<length*2; k++)
	{
		b = *(a+k/2);		// the byte must be visited twice to get both digits.
							// implicit rounding to floor during integer divison does this

		if (!(k%2))			// odd (not even) digit, this sequence is swapped in TBCD conversion
			b = b >> 4;		// most significant nibble 
		else			
			b = b & 0x0f;	// least significant nibble

		c = b+'0';			// get ASCII digit

		if (!isdigit(c))
		{
			// 0xf if the end of record filler in the  cdr spec
			if (!(0xf == b || 0xa==b || 0xc==b)) 
			{
				cout<<"<ERROR> BCD value not a digit = {"<<c<<"}"<<endl;
				//core_dump=true;
				
			}
			break;
		}
		buf[k]=c;
	}
	buf[k]='\0';		// for loop exits with k= length*2 +1 
						// or breaks with K set to 1+last decoded char position 
	return buf;
}

// put in ascii digit string a cdr format Telephony BCD record
// the conversion terminates when a non digit character is found
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


int unpack::get_HEXA(unsigned char *a, int length)
{
	int val=0;


	val = int(*a)*256+int(*(a+1));

	return val;
}


// copy ascii characters around
char* unpack::get_ASCII(unsigned char *a, int length, char *buf)
{
	int i;
	for(i=0; i<length; i++)
	{
		buf[i]=a[i];
	}
	buf[i] ='\0';
	return buf;
}

// new one
long int unpack::get_INTVAL(unsigned char *a, int length)
{
	long int k=0;
	int i;
	for(i=0; i<length; i++)
	{
		int n=int(a[i]);
		k = k*256+n;
	}
	return k;
}


int unpack::get_sub_field(unsigned char *a, unsigned char sub_field[])
{
	int length=*a;
	//cout << "llllenth :" << length << endl;
	for(int i=1; i<(length+1); i++)
	{
		sub_field[i-1]=int(a[i]);
	}
	sub_field[length+1]='\0';

	return length;
}

int unpack::get_sub_sub_field(unsigned char *a, unsigned char sub_field[], unsigned char balance_field[])
{
	int length=*(a+1);
	//cout << "llllenth :" << length << endl;
	for(int i=1; i<(length+2); i++)
	{
		sub_field[i-1]=int(a[i]);
	}
	sub_field[length+2]='\0';

	int k = length+2, j=0;
	while (a[k] != '\0')
	{
		balance_field[j] = a[k];
		k++;
		j++;
	}
	balance_field[k] = '\0';


	return length;
}

char* unpack::get_BCD_with_char(unsigned char *a, int length, char *buf)
{
	int k;
	unsigned char b,c;
	for(k=0; k<length*2; k++)
	{
		b = *(a+k/2);		// the byte must be visited twice to get both digits.
							// implicit rounding to floor during integer divison does this

		if (!(k%2))			// odd (not even) digit, this sequence is swapped in TBCD conversion
			b = b >> 4;		// most significant nibble 
		else			
			b = b & 0x0f;	// least significant nibble

		c = b+'0';			// get ASCII digit

		buf[k]=c;
	}
	buf[k]='\0';		// for loop exits with k= length*2 +1 
						// or breaks with K set to 1+last decoded char position 
	return buf;
}

