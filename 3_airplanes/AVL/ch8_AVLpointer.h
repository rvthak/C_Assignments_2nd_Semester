/*********************************************************
Áñ÷åßï Åðéêåöáëßäáò	: ch8_AVLpointer.h
ÓõããñáöÝáò			:  
Óêïðüò				: Õëïðïßçóç ìå äåßêôåò ÁÔÄ, AVL ÄÝíôñï
**********************************************************/

#ifndef __CH8_AVLPOINTER__ 
#define __CH8_AVLPOINTER__

#include "../TSDDA.h"

typedef struct typos_komvou *typos_deikti; 


void AVLTree_dimiourgia(typos_deikti *riza);
void AVLTree_katastrofi(typos_deikti *riza);

int	AVLTree_keno(typos_deikti riza);

void AVLTree_eisagogi(typos_deikti *riza,TStoixeiouDDA stoixeio,int *ypsilotero,int *error);
void AVLTree_diagrafi(typos_deikti *riza,TStoixeiouDDA stoixeio,int *ypsilotero,int *error);

typos_deikti AVLTree_apaidi(typos_deikti p);
typos_deikti AVLTree_dpaidi(typos_deikti p);

void AVLTree_pateras(typos_deikti riza, typos_deikti *pateras, typos_deikti paidi, int *error);

void AVLTree_anazitisi(typos_deikti riza, TStoixeiouDDA stoixeio, typos_deikti *deiktis, int *found);

void AVLTree_periexomeno(typos_deikti riza,TStoixeiouDDA *stoixeio);

#endif /*#ifndef __CH8_AVLPOINTER__ */
