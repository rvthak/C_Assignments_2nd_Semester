/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: Ioannis Rovithakis sdi1800164
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // For linux time calc

#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"
#include "assert.h"

// The size of the main data storage array in Evretirio
#define EVRETIRIO_SIZE 7200 

// The required input files
#define INPUT_FILE_1 "airportsLinuxRandom.txt" 
#define INPUT_FILE_2 "airportsLinuxSorted.txt"

// Routes data input file
#define ROUTES_FILE "routesLinux.txt" 

// Simple define on Evretirio.h / 1 for BST / 0 for AVL
#if (Simple)
    #define OUTPUT_FILE_1 "OUTPUTRandomBST.txt"
	#define OUTPUT_FILE_2 "OUTPUTSortedBST.txt"
#else
    #define OUTPUT_FILE_1 "OUTPUTRandomAVL.txt"
	#define OUTPUT_FILE_2 "OUTPUTSortedAVL.txt"
#endif

// Helping functions to keep things tidy and consistent
int Construct(EvrPtr *E);  // Construct Evretirio on E
int InsertData(EvrPtr E, char *InputFile);  // Read data from Input file and store on Evretirio
int SearchData(EvrPtr E, char *InputFile, char *OutputFile);  // Read data from Routes file, update data on Evretirio and output some stats on output file
int PrintOutput(EvrPtr E, char *OutputFile); // Move throught the tree on Evretirio and write the data sorted on output file
int Destroy(EvrPtr *E);	   // Destroy the Evretirio
int RouteParse(FILE *from, int *In, int *Out);  // Function that helps with data reading from defined routes file / works twogether with searchData

int main(int argc, char *argv[]){
	
	EvrPtr E; // The main Evretirio pointer

	printf("\n-Random Input------------------------------------------\n\n");
	
	// Random Input Run:
	if( Construct(&E)){ printf(" >Fatal Error: Failed to Construct Evretirio.\n"); return 1; }
	if( InsertData(E, INPUT_FILE_1)){ printf(" >Fatal Error: Failed to Insert Data.\n"); return 2; }
	if( SearchData(E, ROUTES_FILE, OUTPUT_FILE_1)){ printf(" >Fatal Error: Failed to Update Data.\n"); return 3; }
	if( PrintOutput(E, OUTPUT_FILE_1)){ printf(" >Fatal Error: Failed to Print Output.\n"); return 4; }
	if( Destroy(&E)){ printf(" >Fatal Error: Failed to Destroy EvrPtr\n"); return 5; }

	printf("\n-Sorted Input------------------------------------------\n\n");
	
	// Sorted Input Run:
	if( Construct(&E)){ printf(" >Fatal Error: Failed to Construct Evretirio.\n"); return 1; }
	if( InsertData(E, INPUT_FILE_2)){ printf(" >Fatal Error: Failed to Insert Data.\n"); return 2; }
	if( SearchData(E, ROUTES_FILE, OUTPUT_FILE_2)){ printf(" >Fatal Error: Failed to Update Data.\n"); return 3; }
	if( PrintOutput(E, OUTPUT_FILE_2)){ printf(" >Fatal Error: Failed to Print Output.\n"); return 4; }
	if( Destroy(&E)){ printf(" >Fatal Error: Failed to Destroy EvrPtr\n"); return 5; }
  
  	printf("\n-------------------------------------------------------\n");
	getchar(); // just a pause
	return 0;
}

int Construct(EvrPtr *E){
	// Create Evretirio and error check
	printf(" >Constructing Evretirio...\n");
	*E=EvrConstruct(EVRETIRIO_SIZE);
	if((*E)==NULL){ return 1;}
	printf(" >Evretirio Constructed.\n\n");
	return 0;
}

int InsertData(EvrPtr E, char *InputFile){
	int total=0;			// counter of total amount of entries inserted
	FILE *file;				// the file to open the input file
	double elapsedTime;		// var used for time stats output
	struct timeval t1, t2;	// structs used to get time stats	
    TStoixeiouEvr dataElem;	// struct used for taking and passing data between utility functions 

	printf(" >Loading Data from input file: %s\n", InputFile);
	gettimeofday(&t1, NULL); // get the starting time

	if( (file=fopen(InputFile, "r"))==NULL ) { return 1; } // Open file

	while(TSEvr_readValue(file, &dataElem)==0){ // Read a line from file and pass the data to dataelem
		// insert the data to the tree 
		if(EvrInsert(E, dataElem)){ printf(" >Error inserting data to Evretirio\n"); return 1;}
		TSEvr_cleanUp(dataElem); // clean up needed to avoid memory leaks
		total++; // increment amount of entries added on the tree

		switch(total){ // when total reaches the wanted values output the time
			case 511:
				// clac time and output it
				gettimeofday(&t2, NULL);
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
			    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
				printf("   Time for 511 : %g ms\n", elapsedTime);
				break;
			case 1023:
				gettimeofday(&t2, NULL);
			    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
			    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
				printf("   Time for 1023: %g ms\n", elapsedTime);
				break;
			case 2047:
				gettimeofday(&t2, NULL);
			    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
			    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
				printf("   Time for 2047: %g ms\n", elapsedTime);
				break;
			case 4095:
				gettimeofday(&t2, NULL);
			    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
			    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
				printf("   Time for 4095: %g ms\n", elapsedTime);
				break;
			default:
				break;
		}
	}

	fclose(file); // close the file

	// calculate the time
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	// Output result
	printf("   Time to complete: %g ms\n", elapsedTime);
	printf(" >Loaded the data of %d airports.\n", total);
	printf(" >Data Load completed.\n\n");
	return 0;
}

int SearchData(EvrPtr E, char *InputFile, char *OutputFile){
	int flag=0; // flag for return of EvrSearch result
	
	// Vars used to store data (count the amount of keys searched/found/not found) on In and Out
	int total=0;

	int found=0;
	int tmpfound=0;

	int notfound=0;
	int tmpnotfound=0;

	// used to get values from route parse function
	int tmpIn;
	int tmpOut;

	// Vars + struct used to hold time data needed
	struct timeval t1, t2, t3, t4;
    double elapsedTime;
    double elapsedTimeTmp;
    double elapsedTimeSum=0; // sum of all time used for average

	FILE *file;

	printf(" >Starting Data update...\n");
	if( (file=fopen(InputFile, "r"))==NULL ){ return 1; } // open file


	gettimeofday(&t1, NULL); // get the time


	while(RouteParse(file, &tmpIn, &tmpOut)==0){ // Get the In and Out key values from file

		if(tmpIn!=0){ // if we have a key on tmpIn search for it else consider it not found

			gettimeofday(&t3, NULL); // get time before search
			if(EvrSearch(E, tmpIn, 0, &flag)){ printf("Failed in search\n"); return 1; } // search for the key 
			gettimeofday(&t4, NULL); // get time after search
			// do the nessesary calculations
			elapsedTimeTmp= (t4.tv_sec - t3.tv_sec) * 1000.0;
    		elapsedTimeTmp+= (t4.tv_usec - t3.tv_usec) / 1000.0;
    		elapsedTimeSum+=elapsedTimeTmp; // add it to the time total 
			if(flag){ found++; } // if found add one to found
			else{ notfound++; }	 // else not found
		}
		else{
			notfound++;
		}

		// the same thing here but for tmpOut / inout=1
		if(tmpOut!=0){
			gettimeofday(&t3, NULL);
			if(EvrSearch(E, tmpOut, 1, &flag)){ printf("Failed out search\n"); return 1; }
			gettimeofday(&t4, NULL);
			elapsedTimeTmp= (t4.tv_sec - t3.tv_sec) * 1000.0;
    		elapsedTimeTmp+= (t4.tv_usec - t3.tv_usec) / 1000.0;
    		elapsedTimeSum+=elapsedTimeTmp;
			if(flag){ tmpfound++; }
			else{ tmpnotfound++; }
		}
		else{
			tmpnotfound++;
		}
		
		total++;
	}

	// We exit the loop before we search for the data of the last line so we must run the loop code once more to search for the last line
	if(tmpIn!=0){
		gettimeofday(&t3, NULL);
		if(EvrSearch(E, tmpIn, 0, &flag)){ printf("Failed in search\n"); return 1; }
		gettimeofday(&t4, NULL);
		elapsedTimeTmp= (t4.tv_sec - t3.tv_sec) * 1000.0;
    	elapsedTimeTmp+= (t4.tv_usec - t3.tv_usec) / 1000.0;
   		elapsedTimeSum+=elapsedTimeTmp;
		if(flag){ found++; }
		else{ notfound++; }
	}
	else{
		notfound++;
	}

	if(tmpOut!=0){
		gettimeofday(&t3, NULL);
		if(EvrSearch(E, tmpOut, 1, &flag)){ printf("Failed out search\n"); return 1; }
		gettimeofday(&t4, NULL);
		elapsedTimeTmp= (t4.tv_sec - t3.tv_sec) * 1000.0;
    	elapsedTimeTmp+= (t4.tv_usec - t3.tv_usec) / 1000.0;
   		elapsedTimeSum+=elapsedTimeTmp;
		if(flag){ tmpfound++; }
		else{ tmpnotfound++; }
	}
	else{
		tmpnotfound++;
	}
		
	total++; // increment the total amount of keys searched

	fclose(file); // close file

	// calc the stats
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    // Console output
	printf(" >Total Time: %g ms\n", elapsedTime);
	printf(" >Average search time: %g ms\n", elapsedTimeSum/(double)total);

	printf("   Total Connections: %d\n", total);
	printf("   Total Arrivals found: %d\n", found);
	printf("   Total Arrivals not found: %d\n", notfound);
	
	printf("   Total Departures found: %d\n", tmpfound);
	printf("   Total Departures not found: %d\n", tmpnotfound);

	// File output
	if( (file=fopen(OutputFile, "w"))==NULL ){ return 1; }

	fprintf(file, " >Total Time: %g ms\n", elapsedTime);
	fprintf(file, " >Average search time: %g ms\n", elapsedTimeSum/(double)total);

	fprintf(file, "   Total Connections: %d\n", total);
	fprintf(file, "   Total Arrivals found: %d\n", found);
	fprintf(file, "   Total Arrivals not found: %d\n", notfound);
	
	fprintf(file, "   Total Departures found: %d\n", tmpfound);
	fprintf(file, "   Total Departures not found: %d\n\n", tmpnotfound);

	fclose(file);
	printf(" >Completed Data update.\n\n");
	return 0;
}
	
int PrintOutput(EvrPtr E, char *OutputFile){
	FILE *file;				// the file to open the output file
	int counter=0;			// return val for printAll
	double elapsedTime;		// var used for time stats output
	struct timeval t1, t2;	// structs used to get time stats

	printf(" >Outputing results to %s\n", OutputFile);
	if( (file=fopen(OutputFile, "a+"))==NULL ){ return 1;} // Open the correct file

	gettimeofday(&t1, NULL); // save time 

	if(EvrPrintAll(E, file, &counter)){ return 1; } // Call main print function

	// complete the time stat calc
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	// Console Output
	printf("   Printed: %d\n", counter);
	printf(" >Total Output Time: %g ms\n", elapsedTime);

	// File Output
	fprintf(file, "   \nPrinted: %d\n", counter);
	fprintf(file, "Total Output Time: %g ms\n", elapsedTime);

	fclose(file); // close th file
	printf(" >Output completed.\n\n");
	return 0;
}

int Destroy(EvrPtr *E){
	printf(" >Destoying Evretirio...\n");
	if(EvrDestruct(E)){ // Destroy Evretirio and error check
  		fprintf(stderr, " >Fatal Error: Failed to destoy Evretirio.\n");
  		return 1;
	}
	if((*E)!=NULL){ return 1; }
	printf(" >Evretirio destoyed.\n");
	return 0;
}

int RouteParse(FILE *from, int *In, int *Out){
	int ch;  	// just a var to temp store the incoming chars
	int pos; 	// the memory position/distance away from the beggining of the buf
	char *buf;	// a buffer big enough to fit any possible input from the given files | i built the strings char by char on it
	int n=0;	// a counter that tells on which string we are = we can pick the string we need
	
	if( (buf=malloc(100*sizeof(char)))==NULL ){ return 1; } // allocate the needed memory + some extra to be safe

	ch=getc(from); // Get the next char of from stream

	if(ch==EOF){ return -1; } // avoid errors in case of function call after the file has been fully passed through

	while(ch!='\n'&&ch!=EOF){ // while we are reading one line (EOF in case we are on the last line)
		
		pos=0; // start from first char of buff
		while( ch!=';' && ch!='\n' && ch!=EOF){ // while we are reading one word (\n in case we are on the last word)
			buf[pos]=ch; 	// put the new char on the buf
			pos++;		 	// increment pos
			ch=getc(from);	// get the next char
		}
		buf[pos]='\0';	// when we leave the loop we have ';' or '\n' on ch, so we add '\0' to the last position to end the string
		

		if(n==3){ // the airport in is the 3rd word
			*In=atoi(buf); // turn it to a number (In case its not a number, atoi returns 0 != any airport ID so i can see if its not a string)
		}
		else if(n==5){ // the airport out is the 5th word
			*Out=atoi(buf);
		}

		if(ch==';'){ // Get a new char only if ch == ; (\n to not affect next line, but in case of ch==EOF dont get any other char)
			ch=getc(from);
		}

		n++; // increment word count
	}	
	
	free(buf); // free the buf

	if(ch==EOF){ return -1; } // if ch == EOF reached the end of the file= return -1 to end the read loop
	return 0;
}
