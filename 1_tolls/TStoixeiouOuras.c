/*************************************************************************
Implementation File	: TStoixeiouOyras.c
Author	Date		: Y. Cotronis 07/03/2016
Purpose 			: Ylopoihsh typou stoixeiou ths oyras
Revision			: I. Rovithakis sdi1800164 20/03/2019
**************************************************************************/
#include <stdio.h>
#include "TStoixeiouOuras.h"

void TSOurasSetValue(TSOuras *stoixeioPtr, TSOuras data){   
	*stoixeioPtr = data;  /* basic type assignment */
}

void PelatisSetXronoEisodou(TSOuras *stoixeioPtr, int xronos){
	stoixeioPtr->XronosEisodou=xronos;
}

int PelatisGetXronoEisodou(TSOuras stoixeio){
	return stoixeio.XronosEisodou;
}

void PelatisSetXronoEksipiretisis (TSOuras *stoixeioPtr, int duration){
	stoixeioPtr->XronosEksipiretisis=duration;
	return;
}

int PelatisGetXronoEksipiretisis (TSOuras stoixeio){
	return stoixeio.XronosEksipiretisis;
}

