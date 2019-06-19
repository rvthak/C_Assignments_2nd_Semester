// Ioannis Rovithakis | sdi1800164 | TSEvr.c

#include "TSEvr.h"
#include <string.h>
#include <stdlib.h>

#define AMOUNT_OF_SAVED_MEMBERS 6 // The amount of members that the struct data has saved on the file (all except IN/Out)

int TSEvr_setValue(TStoixeiouEvr *target, TStoixeiouEvr source){

	// allocate the needed memory
	if( (target->Name=malloc((strlen(source.Name)+1)*sizeof(char)))==NULL ){ return 1; }
	if( (target->City=malloc((strlen(source.City)+1)*sizeof(char)))==NULL ){ return 1; }
	if( (target->Country=malloc((strlen(source.Country)+1)*sizeof(char)))==NULL ){ return 1; }
	
	// we dont always have data on these 2 so we sometimes need to let them NULL
	if(source.IATA!=NULL){
		// allocate space
    	if( (target->IATA=malloc((strlen(source.IATA)+1)*sizeof(char)))==NULL ){ return 1; }
    	strcpy(target->IATA, source.IATA); // pass the value
    }
    else{
    	target->IATA=NULL; // make it null
    }

    if(source.ICAO!=NULL){
    	if( (target->ICAO=malloc((strlen(source.ICAO)+1)*sizeof(char)))==NULL ){ return 1; }
    	strcpy(target->ICAO, source.ICAO);
    }
    else{
    	target->ICAO=NULL;
    }

    // copy data
	target->AirportID=source.AirportID;
	strcpy(target->Name, source.Name);
	strcpy(target->City, source.City);
	strcpy(target->Country, source.Country);
	target->In=source.In;
	target->Out=source.Out;

	return 0;
}

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem){
	int ch;

	// buf to write + position
	int pos;
	char *buf;
	
	// an array of strings of different sizes to store whatever we read temporarily + the string position
	int loc=0;
	char **tempstore;

	// allocate the base memory
	if( (tempstore=malloc(AMOUNT_OF_SAVED_MEMBERS*sizeof(char *)))==NULL ){ return 1; } 
	if( (buf=malloc(120*sizeof(char)))==NULL ){ return 1; }

	ch=getc(from); // get next char

	if(ch==EOF){ return -1; } // avoid errors in case of function call after the file has been fully passed through
	
	while(ch!='\n'&&ch!=EOF){ // while we are on the same line
		pos=0; // get pos of buf to 0 in order to start writing new word to buf
		while( ch!=';' && ch!='\n' && ch!=EOF){ // while we are on the same 'word'
			buf[pos]=ch; 	// keep the char
			pos++;			// move to the next pos
			ch=getc(from);	// get the next char
		}
		buf[pos]='\0'; // put a '\0' on the end of the string to make it usable with string functions

		// malloc enough space to write the 'word'
		if( (tempstore[loc]=malloc((strlen(buf)+1)*sizeof(char)))==NULL ){ printf("MALLOC ERROR\n"); return 1; }

		// copy the value
		strncpy(tempstore[loc], buf, pos+1);
		
		loc++; // move to the next space of tempstore

		if(ch==';'){ // Get a new char only if ch == ; (\n to not affect next line, but in case of ch==EOF dont get any other char)
			ch=getc(from);
		}
	}

	free(buf); // free the buff

	// Allocate space for the strings
	if( (Elem->Name=malloc((strlen(tempstore[1])+1)*sizeof(char)))==NULL ){ return 1; }
	if( (Elem->City=malloc((strlen(tempstore[2])+1)*sizeof(char)))==NULL ){ return 1; }
	if( (Elem->Country=malloc((strlen(tempstore[3])+1)*sizeof(char)))==NULL ){ return 1; }

	// Pass the values
	Elem->AirportID=atoi(tempstore[0]);
	strcpy(Elem->Name, tempstore[1]);
	strcpy(Elem->City, tempstore[2]);
	strcpy(Elem->Country, tempstore[3]);
	
	// handle cases when NULL needs to be passed
	if(strcmp(tempstore[4],"\\N")==0){
		Elem->IATA=NULL;
	}
	else{
		if( (Elem->IATA=malloc((strlen(tempstore[4])+1)*sizeof(char)))==NULL ){ return 1; }
		strcpy(Elem->IATA, tempstore[4]);
	}

	if(strcmp(tempstore[5],"\\N")==0){
		Elem->ICAO=NULL;
	}
	else{
		if( (Elem->ICAO=malloc((strlen(tempstore[5])+1)*sizeof(char)))==NULL ){ return 1; }
		strcpy(Elem->ICAO, tempstore[5]);
	}

	// Initialize In/Out
	Elem->In=0;
	Elem->Out=0;

	// free the strings stored on tempstore
	for(pos=0; pos<AMOUNT_OF_SAVED_MEMBERS; pos++){
		free(tempstore[pos]);
	}

	free(tempstore); // free tempstore

	if(ch==EOF){ return -1; } // if ch == EOF reached the end of the file= return -1 to end the read loop
	return 0;
}

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem){
	fprintf(to, " >%d - In: %d Out: %d\n", Elem.AirportID, Elem.In, Elem.Out);
	return 0;
}

int TSEvr_cleanUp(TStoixeiouEvr dataElem){
	// free the strings that were malloced from readvalue to avoid memory leaks
	free( dataElem.Name);
    free( dataElem.City);
    free( dataElem.Country);

    // in some cases there has not been a malloc so we dont need to free
    if(dataElem.IATA!=NULL){
    	free( dataElem.IATA);
    }
    if(dataElem.ICAO!=NULL){
    	free( dataElem.ICAO);
    }
    
    return 0;
}

int TSEvr_InIncrease(TStoixeiouEvr *stoixeio){
	stoixeio->In++;
	return 0;
}

int TSEvr_OutIncrease(TStoixeiouEvr *stoixeio){
	stoixeio->Out++;
	return 0;
}