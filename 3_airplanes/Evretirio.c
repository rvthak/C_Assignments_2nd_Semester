// Ioannis Rovithakis | sdi1800164 | Evretirio.c

#include "Evretirio.h"

// Decided to move #define Simple 1 to Evretirio.h instead in order to change the filenames also

// Include the correct tree module
#if (Simple)
    #include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
    #include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif

struct EvrNode{
    int Index;                  /* index of first available element in array */
    TStoixeiouEvr *DataArray;   /* array of size MaxSize */
    typos_deikti TreeRoot;      /* Root of DDA */
} EvrNode;

// this function declaration is here because it uses typos_deikti as a parameter which is not known in Evretirio.h
int EvrPrintAllRec(EvrPtr E, typos_deikti node, FILE *out, int *counter);

EvrPtr EvrConstruct(int MaxSize){

    EvrPtr evretir;         // the main pointer to Evretirio  
    TStoixeiouEvr *table;   // the base of the array of data
    typos_deikti TreeRoot;  // the root of the tree

    // Allocate the needed memory
    if((evretir=malloc(sizeof(struct EvrNode)))==NULL){
        return NULL; // Fatal Error failed to allocate memory
    }

    if((table=malloc(MaxSize*sizeof(struct data)))==NULL){
        return NULL; // Fatal Error failed to allocate memory
    }

    // They both just NULL TreeRoot
    #if (Simple)
        //printf("   Use simple BST\n");
        Tree_dimiourgia(&TreeRoot);
    #else   
        //printf("   Use AVL BST\n");
        AVLTree_dimiourgia(&TreeRoot);
    #endif

    // Link the resulting pointers and initialize index
    evretir->Index=0;
    evretir->DataArray=table;
    evretir->TreeRoot=TreeRoot;

    return evretir;
}

int EvrDestruct(EvrPtr *E){
    int i;
    int tmp=(*E)->Index;
    // Free the data table strings
    for(i=0; i<(tmp-1); i++){
        free( (*E)->DataArray[i].Name);
        free( (*E)->DataArray[i].City);
        free( (*E)->DataArray[i].Country);

        // in case they have never been allocated dont do anything
        if( ((*E)->DataArray[i].IATA)!=NULL){
            free( (*E)->DataArray[i].IATA);
        }
        if( ((*E)->DataArray[i].ICAO)!=NULL){
            free( (*E)->DataArray[i].ICAO);   
        }
    }
    // Free the Data Table
    free((*E)->DataArray);

    // Free the tree
    #if (Simple)
        Tree_katastrofi(&((*E)->TreeRoot));
        printf(" >Destroyed simple BST\n");
    #else   
        AVLTree_katastrofi(&((*E)->TreeRoot));
        printf(" >Destroyed AVL BST\n");
    #endif

    // Check for errors - Return failure
    if((*E)->TreeRoot!=NULL){ return 1; } 

    // Finally free the Evretirio itself
    free((*E));

    // Set its value back to NULL
    *E=NULL;

    // Return success
    return 0;
}

int EvrInsert(EvrPtr E, TStoixeiouEvr Data){

    int error;
    TStoixeiouDDA keyindex; // tmp store used to pass needed data to insert function

   #if(!Simple) // compile this conditionally since it is only being used when using AVL
        int ypsilotero; // Just a placeholder var needed for AVLTree_eisagogi value does not matter
    #endif

    // Insert Data to table and check for errors - Return failure
    if(TSEvr_setValue(&(E->DataArray[E->Index]), Data)){ return 1; }

    // Insert Key and Location to KeyIndex to pass them as one entity to BSD
    if(TSDDA_setKey( &(keyindex.key) , Data.AirportID )) { return 1; }
    if(TSDDA_setIndex( &(keyindex.arrayIndex), E->Index )){ return 1; }

    // Insert KeyIndex struct to Tree
    #if (Simple)
        Tree_eisagogi(&(E->TreeRoot), keyindex , &error);
    #else   
        AVLTree_eisagogi(&(E->TreeRoot), keyindex, &ypsilotero, &error);
    #endif

    if(error){ return 1; } // check for errors

    // Filled this place, move to the next one
    E->Index++;

    return 0; // Return success
}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found){
    TStoixeiouDDA stoixeio;
    typos_deikti deiktis;
    int foundflag;
    
    // Prepare TStoixeiouDDA stoixeio for search
    // Copy the key we are searching for
    if(TSDDA_setKey(&(stoixeio.key), key)) { return 1; }
    // Throw a random number for index for now
    if(TSDDA_setIndex(&(stoixeio.arrayIndex), 0)) { return 1; } 
    
    // Call the search function
    #if (Simple)
        Tree_anazitisi(E->TreeRoot, stoixeio, &deiktis, &foundflag);
    #else   
        AVLTree_anazitisi(E->TreeRoot, stoixeio, &deiktis, &foundflag);
    #endif

    // Manage the results
    if(foundflag){
        // Found it! Now deiktis points to the tree node containing the data we need

        // Update found to 1
        *found=1;

        // Get the data from the tree
        #if (Simple)
            Tree_periexomeno(deiktis, &stoixeio);
        #else   
            AVLTree_periexomeno(deiktis, &stoixeio);
        #endif

        // Check InOut value and act accordingly
        if(InOut){ // 1 => out++
            TSEvr_OutIncrease(&(E->DataArray[stoixeio.arrayIndex]));
        }
        else{ // 0 => in ++
            TSEvr_InIncrease(&(E->DataArray[stoixeio.arrayIndex]));
        }
    }
    else{ // Did not found it
        // Just turn found to 0
        *found=0;
    }

    return 0;
}

int EvrPrintAll(EvrPtr E, FILE *out, int *counter){
    if((E->TreeRoot)==NULL){ return 1; } // check if the tree exists
    *counter=1; // count the top node 

    // call the recursive print function
    if(EvrPrintAllRec(E, (typos_deikti)E->TreeRoot, out, counter)){return 1; }
    return 0;
}

int EvrPrintAllRec(EvrPtr E, typos_deikti node, FILE *out, int *counter){
    typos_deikti temp;
    TStoixeiouDDA data;

    #if (Simple)

        // Check if left(smaller-priority) node is available
        if( (temp=Tree_apaidi(node))!=NULL){
            // Move/Print its way
            (*counter)++; // count this node 
            if(EvrPrintAllRec(E, (typos_deikti)temp, out, counter)){ return 1; } // move on 
        }
        // Print its own data (every node is counted by its parent)
        Tree_periexomeno(node, &data);
        TSEvr_writeValue(out, E->DataArray[data.arrayIndex]);

        // Check if right(bigger-last priority) node is available
        if( (temp=Tree_dpaidi(node))!=NULL){
            (*counter)++;
            if(EvrPrintAllRec(E, (typos_deikti)temp, out, counter)){ return 1; }
        }

    #else
        
        // Check if left(smaller-priority) node is available
        if( (temp=AVLTree_apaidi(node))!=NULL){
            (*counter)++;
            if(EvrPrintAllRec(E, (typos_deikti)temp, out, counter)){ return 1; }
        }

        // Print its own data
        AVLTree_periexomeno(node, &data);
        TSEvr_writeValue(out, E->DataArray[data.arrayIndex]);

        // Check if right(bigger-last priority) node is available
        if( (temp=AVLTree_dpaidi(node))!=NULL){
            (*counter)++;
            if(EvrPrintAllRec(E, (typos_deikti)temp, out, counter)){ return 1; }
        }

    #endif

    return 0;
}
