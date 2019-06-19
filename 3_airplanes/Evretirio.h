// Ioannis Rovithakis | sdi1800164 | Evretirio.h

#ifndef __Evr__
#define __Evr__

#include <stdlib.h>
#include <stdio.h>
#include "TSEvr.h"
#include "TSDDA.h"

// Moved it here from Evretirio .c in order to be able to change all parameters between BST and AVL from a single point
#define Simple 0 /* 0 for AVL - any Evr integer for Simple  */

typedef struct EvrNode *EvrPtr;

EvrPtr EvrConstruct(int MaxSize);	/* gia erwthma 1 */
int EvrDestruct(EvrPtr *E);			/* gia erwthma 5 */

int EvrInsert(EvrPtr E, TStoixeiouEvr Data); 					/* gia erwthma 2 */
int EvrSearch(EvrPtr E, keyType key, int InOut, int * found); 	/* gia erwthma 3 */
int EvrPrintAll(EvrPtr E, FILE *out, int *counter); 			/* gia Erwthma 4 */

#endif
