/*************************************************
Arxeio ylopoihshs	: ch6_Simulation.c
Syggrafeas			: Y. Cotronis 07/03/2016
Skopos				: Ylopoihsh ouras prosomoiwshs
Revision 			: I. Rovithakis sdi1800164 20/03/2019
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ch6_QArray.h"
#include "controller.h"
#include "TStoixeiouOuras.h"


#define QUEUES 10		// Max number of QUEUES - default 10
#define DYNAMIC 1		// 0 for a set amount of controllers despite the traffic, 1 for dynamic handling

int NofQUEUES; // i would normally do this without a global variable (i try to avoid them) but since i decided to add it on the 6th part it was much work to go back and change everything(add it as a parameter in function ect)

void order(unsigned int *a, unsigned int *b);	// Re-orders the two variables if needed to have the smalles first
int minqueue(TOuras *oures, char *flags);		// Returns the number of the ACTIVE queue that has the least customers waiting
void queueFlag(TOuras *oures, char *flags);	// Checks current state of QUEUES and "flags" them ON/OFF

int main(void){	

	int temp;					// just a temp multi-use var
	int i=0;					// another general use var

	unsigned int xronos=0;				// roloi prosomoiwshs
	unsigned int xronos_prosomoiosis; 	//synolikos xronos prosomoiwshs
	unsigned int xronos_anamonis=0;		// synolikos xronos anamonhs
	unsigned int checktime;				// stores a value that affects how often are the QUEUES checked for possible changes == one NofQUEUES life cycle
	unsigned int mintime;				// min and max possible time values given by the user == possible serving time for each customer range
	unsigned int maxtime;
	unsigned int	arithmos_pelaton=0; 	// plh8os e3yphreth8entwn pelatwn
	time_t t;
	float mesos_xronos;					// mesos xronos anamonhs tvn pelatvn
	float randomAfixi;		
	float pithanotita_afiksis; 			// pi8anothta afikshs
	char *flags;
	
	TSOuras	Pelatis;		 	// o pelaths sthn oyra
	TOuras *oures;				// The Array of Oures
	TController *controllers;	// The Array of Controllers

	// Starting User Input 
	printf("Dwste units of time prosomoiwshs (0 <=), pi8anothta afikshs in unit of time (0,1) kai xrono e3yphrethshs min and max possible values (>=1) in unit of times )\n");
	scanf("%u %f %u %u",&xronos_prosomoiosis,&pithanotita_afiksis,&mintime, &maxtime); // it would be a good idea to handle user input in a better way to ensure no negative values are given that would cause underflow and strange behavior
	getchar();
	printf("H prosomoiwsh 8a diarkesei %4u units of time.\n",xronos_prosomoiosis);
	printf("H pi8anothta afikshs pelath se ena unit of time einai: %4.2f.\n",pithanotita_afiksis);
	printf("H diarkeia e3yphrethshs enos pelath einai metavalomeni metaxu %u  and %u units of time .\n",mintime, maxtime);
	// End of user input


	// Start up setup and checks
	checktime=0;
	if(mintime==maxtime){ // if they are the same we later end up with rand % 0 => error
		printf("FATAL ERROR: Please give two different values for time range\n");
		return 1;
	}
	if(maxtime==0||mintime==0){
		printf("FATAL ERROR: Invalid user input - cant give 0 as input in time range\n");
		printf("A customer service cant take 0 time, please give another value\n");
		return 1;
	}
	order(&mintime, &maxtime); 	// Set min and max in the right order in case it was wrong
	if(QUEUES==1){
		NofQUEUES=1;
	}
	else{
		NofQUEUES=QUEUES/2; 		// initialize queue amount to half the max
	}
	srand(time(&t)); 			// initialize random number generator with a time seed


	// Allocate memory for the arrays
	if( (oures=malloc(QUEUES*sizeof(TOuras)))==NULL ||
	 	(controllers=malloc(QUEUES*sizeof(TController)))==NULL ||
	 	(flags=malloc(QUEUES*sizeof(char)))==NULL ) 
	{ 
		fprintf(stderr, "Fatal error: Failed to allocate memory\n");
		return 1;
	}

	for(temp=0; temp<QUEUES; temp++){ // Create/initialize the Arrays
		OuraDimiourgia(&oures[temp]);
		ControllerDimiourgia(&controllers[temp]);
		if(temp<NofQUEUES){ // Start with half the controllers/Oures closed
			flags[temp]='a';
		}
		else{
			flags[temp]='i';
		}
	}


	// Main execution loop
	while( xronos < xronos_prosomoiosis ){	

		// Pelatis - Aytokinhto
		if ( (randomAfixi=(float)rand()/(float)RAND_MAX) < pithanotita_afiksis ){
			PelatisSetXronoEisodou(&Pelatis, xronos);
			PelatisSetXronoEksipiretisis (&Pelatis, mintime+rand()%(maxtime-mintime) );

			temp=minqueue(oures, flags); // New customers enter the smallest queue

			if (!OuraProsthesi(&oures[temp], Pelatis)){
            	printf("H oyra einai mikrh! H prosomoivsh stamataei \n");
            	getchar();
            	return 0;
        	}
        	i++;
    	}


    	// Oures - Controllers
		for(temp=0; temp<QUEUES; temp++){ // for each oura-controller

			if(flags[temp]=='a'){ // if its active
				if ( ControllerFree(controllers[temp])){ // if its available

					if (!OuraKeni(oures[temp])){ // if there are people waiting in line

						OuraApomakrynsh(&oures[temp],&Pelatis); // get a customer waiting in oura
		    			ControllerNewCustomer(&controllers[temp]); // take him to the controller
		    			ControllerSetXrono(&controllers[temp], Pelatis.XronosEksipiretisis); // collect time data
						ControllerBusy(&controllers[temp]);	// the controller now helps the customer
		    			
						xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);
					}
					else {
						ControllerNoWork(&controllers[temp]); // the controller stays incative
					}
				}
				else{
					ControllerBusy(&controllers[temp]); // the controller now helps the customer
				}
			}
			else{
				ControllerOff(&controllers[temp]); // the controller is closed
			}
		}

		if(DYNAMIC){
			if(checktime==(QUEUES/2)){ 	// check the states of the controllers each set amount of time 
				queueFlag(oures, flags);	// to ensure effectivness and avoid turning them on and off without reason
				checktime=0;
			}
		}
		
		checktime++; 
		xronos++;
	}
	// End of Main loop


	// Final Output
	arithmos_pelaton=0;
	for(temp=0; temp<QUEUES; temp++){
		arithmos_pelaton+=ControllerGetArithmosPelatwn(controllers[temp]);
	}

	if (arithmos_pelaton == 0){
		mesos_xronos = 0.0;
	}
	else{
		mesos_xronos = ((float)xronos_anamonis)/((float)arithmos_pelaton);
	}
	printf("\nEksyphreth8hkan sunolika %d pelates\n",arithmos_pelaton);



	arithmos_pelaton=0;
	for(temp=0; temp<QUEUES; temp++){
		arithmos_pelaton+=OuraGetSize(oures[temp]);
	}
	printf("Den eksyphreth8hkan sunolika %d pelates\n", arithmos_pelaton );



	arithmos_pelaton=0;
	for(temp=0; temp<QUEUES; temp++){
		arithmos_pelaton+=GetCountIn(oures[temp]);
	}
	printf("Mpikan sunolika %d pelates\n", arithmos_pelaton );



	arithmos_pelaton=0;
	for(temp=0; temp<QUEUES; temp++){
		arithmos_pelaton+=GetCountOut(oures[temp]);
	}
	printf("Vgikan sunolika %d pelates\n", arithmos_pelaton );



	printf("O mesos xronos anamonhs htan %4.2f units of time.\n",mesos_xronos);



	for(temp=0; temp<QUEUES; temp++){
		printf("\n\n Stin oura %d hrthan sunolika %d pelates\n", temp+1, GetCountIn(oures[temp]));
		printf("O tamias %d exupurethse %d customers\n", temp+1, ControllerGetArithmosPelatwn(controllers[temp]) );
		printf("O tamias %d den prolave na exupiretisei %d customers\n", temp+1, GetCountIn(oures[temp]) - ControllerGetArithmosPelatwn(controllers[temp]));
		printf("O tamias %d htan adranhs gia %d units of time\n", temp+1, ControllerGetInactiveXronos(controllers[temp]) );
		printf("To tameio htan kleisto gia %d units of time\n", ControllerGetTimeOff(controllers[temp]));

	}
	// End of Output

    getchar(); // just a pause :)
	return 0;
}

// Functions ---

void queueFlag(TOuras *oures, char *flags){
	int inact=0;
	int i;

	for(i=0; i<QUEUES; i++){ // count the active QUEUES not currently working
		if(OuraKeni(oures[i]) && flags[i]=='a'){
			inact++; 
		}
	}

	if(inact==0){ //all active QUEUES working
		if(NofQUEUES!=QUEUES){ // if there are inactive QUEUES available for activation
			// activate the first inactive you find
			for(i=0; flags[i]=='a'; i++){
				;
			}
			NofQUEUES++;
			flags[i]='a';
			//printf("Activate %d\n", i+1);
			return;
		}
	}
	else if(inact>0 && NofQUEUES>1){ // there are more than one active QUEUES not working
		// deactivate the first active you find from the end
		for(i=QUEUES-1; flags[i]=='i'; i--){
			;
		}
		NofQUEUES--;
		flags[i]='i';
		//printf("Deactivate %d\n", i+1);
		return;
	}
	return; // no need for changes
}

void order(unsigned int *a, unsigned int *b){
	int tmp;
	if(*a<*b){
		return;
	}
	tmp=*a;
	*a=*b;
	*b=tmp;
	return;
}

int minqueue(TOuras *oures, char *flags){
	unsigned int i, m=0;
	unsigned int min=QSIZE+1, temp=0; // QSIZE = max amount of QUEUES = max value of temp => QSIZE+1>temp 
	for(i=0; i<QUEUES; i++){
		if( (min > (temp=OuraGetSize(oures[i]))) && flags[i]=='a' ){
			min=temp;
			m=i;
		}
	}
	return m;
}

// Ideally for easyer queue and controller managment and flexibility  
// would make  a list struct that has one queue and one controller
// and handle then as one (create/delete etc) but its too late
// now i should have planned better ahead