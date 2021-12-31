

//////////////////////////////////////////////////////////////////////
//
// Debug.h 
// GPRS Mediation Engine
// developer - Chandika Nettasinghe
// development - 2002
//
//////////////////////////////////////////////////////////////////////


inline void debug (const char*); //

#ifdef DEBUG

inline void debug (const char * msg) //
{
	cerr << "DEBUG> " << msg << endl; //
}

#else

inline void debug (const char * msg) { ; } //

#endif