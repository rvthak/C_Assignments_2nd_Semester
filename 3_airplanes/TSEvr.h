// Ioannis Rovithakis | sdi1800164 | TSEvr.h

#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>

typedef struct data {
	int AirportID;
	char *Name;
	char *City;
	char *Country;
	char *IATA;
	char *ICAO;
	int In;
	int Out;
} TStoixeiouEvr;

int TSEvr_setValue(TStoixeiouEvr *target, TStoixeiouEvr source);
int TSEvr_readValue(FILE *from,  TStoixeiouEvr *Elem);
int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

// added these to for consistency
int TSEvr_InIncrease(TStoixeiouEvr *stoixeio);
int TSEvr_OutIncrease(TStoixeiouEvr *stoixeio);

// frees the pointers allocated from readValue to avoid memory leaks
int TSEvr_cleanUp(TStoixeiouEvr dataElem); 

#endif
