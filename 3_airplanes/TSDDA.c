// Ioannis Rovithakis | sdi1800164 | TSDDA.c

#include "TSDDA.h"

// For the first 3 functions you just pass the values
int TSDDA_setValue(TStoixeiouDDA *target, TStoixeiouDDA source){
	target->key=source.key;
	target->arrayIndex=source.arrayIndex;
	return 0;
}

int TSDDA_setKey(keyType *key, keyType Val){
	*key=Val;
	return 0;
}

int TSDDA_setIndex(int *Index, int Val){
	*Index=Val;
	return 0;
}

// Placeholder function not actually needed / just used in AVL module
int TSDDA_writeValue(FILE *out, TStoixeiouDDA stoixeio){
	// decided to comment it out it is not needed to have a correct output
	//fprintf(out, " %d %d\n", stoixeio.key, stoixeio.arrayIndex);
	return 0;
}

// For these 3 functions you can just right away return the logical result
int TSDDA_iso(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return s1.key==s2.key;
}

int TSDDA_mikrotero(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return s1.key<s2.key;
}

int TSDDA_megalytero(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return s1.key>s2.key;
}

/* The Following are already Implemented using Above */

int TSDDA_mikrotero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{ 
    return TSDDA_mikrotero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_megalytero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return TSDDA_megalytero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_diaforo(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return !TSDDA_iso(s1,s2);
}
