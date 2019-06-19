/*************************************************************************
Header File Name		: QArray.h
Author Date				: Y. Cotronis 07/03/2016
Purpose					: Header file of ATD Queue - counter - array
Revision				: I. Rovithakis sdi1800164 20/03/2019
**************************************************************************/
#ifndef __CH2_QARRAY__ 
#define __CH2_QARRAY__
#include "TStoixeiouOuras.h"


#define QSIZE 1000

typedef struct {
	int embros;		/* position of first element */
	int piso;		/* position of last  element */
	int metritis;   /* counter - elements in queue */
	int incoming;	/* counter - elements that entered the queue*/
	int outcoming;	/* counter - elements that left the queue*/
	TSOuras pinakas[QSIZE];	/* array of queue elements */
} TOuras;	   /* New Name of Type Queue */

void OuraDimiourgia(TOuras *oura);

int	OuraKeni(TOuras oura);

int OuraProsthesi	(TOuras *oura, TSOuras stoixeio);
int OuraApomakrynsh (TOuras *oura, TSOuras *stoixeio);

int OuraGetSize(TOuras oura); // oura metritis

int GetCountIn(TOuras oura); // oura IO
int GetCountOut(TOuras oura);

#endif

