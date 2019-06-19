// Ioannis Rovithakis | sdi1800164

#include <stdio.h>
#include <stdlib.h>

#include "Session.h"


#define SWITCH_CHOICES 18	// Here just to make adding choices to the switch easier 
#define DEFAULT_SITE "https://www.google.com/"	// The default Session Opening Address 
#define MAX_ADDRESS_LENGTH 50	// The max lenght of string it can take (for example as a link)


void PrintChoices(void);	// A simple function that prints the available choises


int main(void){

	char *tmp;							// String storage
	int Inp=1;							// Input storage
	int ActiveSession=0;				// Current active session number stored here
	InfoSessionPtr *MySessions=NULL;	// The base of the Session array


	if( (MySessions=malloc(sizeof(InfoSessionPtr)))==NULL||	// Allocate the needed memory
		(tmp=malloc(MAX_ADDRESS_LENGTH*sizeof(char)))==NULL ){
		printf(" >Fatal memory error: Failed to allocate memory.\n");
		printf(" >Terminating program...\n");
		return 1;
	}

	// Initialize the two sessions to NULL
	MySessions[0]=NULL;
	MySessions[1]=NULL;

	// Prepare the screen for the UI
	system("clear");

	// Main execution loop
	while(Inp!=0){

		// Print Session State and choises
		PrintSessionActivity(MySessions, ActiveSession);
		PrintChoices();

		// Is Current Active Session Open?
		if(MySessions[ActiveSession]!=NULL){
			PrintUI(MySessions[ActiveSession]); // Print UI
		}
		else{ // There current active session is closed, print the correct message
			if(MySessions[0]==NULL&&MySessions[1]==NULL){
				printf(" > Sorry, there are no active sessions currently running.\n");
				printf(" Please create one to proceed\n");
			}
			else{
				printf(" > The currently active session is not created yet, please\n");
				printf(" create it or switch to the other available session.\n");
			}
		}

		// Get user input for function choice
		if(scanf("%d", &Inp)!=1 || Inp<0 || Inp>SWITCH_CHOICES-1){ // Is the input incorrect?
			getchar(); // helps getting rid of big strange input strings (fixed a bug)
			system("clear");
			printf(" >User Input Error: Wrong input given. Try again:\n");
			continue;
		}
		else{ // Correct input move on
			switch(Inp){
				case 0: // Quit
					printf(" >Quitting...\n");
					// Free whatever is left behind
					if(MySessions[0]!=NULL){
						SessionClose(MySessions[0]);
					}
					if(MySessions[1]!=NULL){
						SessionClose(MySessions[1]);
					}
					break;

				case 1: // New Session
					if(MySessions[ActiveSession]==NULL){ // Check if current active session is closed, if its not, this function is not available
						MySessions[ActiveSession]=SessionNew(DEFAULT_SITE);
					}
					else{
						system("clear");
						printf(" >The current session is already open, please close it\n");
						printf(" or change session to make a new one.\n");
						continue;
					}
					break;

				case 2: // New Tab
					if(MySessions[ActiveSession]!=NULL){ // Make this function executable only if active session is open
						SessionNewTab(MySessions[ActiveSession]);
					}
					
					break;

				case 3: // show tab data 
					if(MySessions[ActiveSession]!=NULL){
						system("clear");
						printf(" >The content of current tab is:\n");
						SessionTabShow(MySessions[ActiveSession]);
						continue;
					}
					
					break;

				case 4: // Prev tab
					if(MySessions[ActiveSession]!=NULL){
						SessionTabPrev(MySessions[ActiveSession]);	
					}
					
					break;

				case 5: // Next tab
					if(MySessions[ActiveSession]!=NULL){
						SessionTabNext(MySessions[ActiveSession]);
					}
					
					break;

				case 6: // Move tab left
					if(MySessions[ActiveSession]!=NULL){
						SessionTabMoveLeft(MySessions[ActiveSession]);
					}
					
					break;

				case 7: // Move tab right
					if(MySessions[ActiveSession]!=NULL){
						SessionTabMoveRight(MySessions[ActiveSession]);
					}
					
					break;

				case 8: // Change default adress
					if(MySessions[ActiveSession]!=NULL){
						printf(" >Please type the desired new opening address:\n");
						scanf("%s", tmp);
						SessionNewOpeningAddress(MySessions[ActiveSession], tmp);
					}
					
					break;

				case 9: // Print default adress
					if(MySessions[ActiveSession]!=NULL){
						system("clear");
						printf(" >Here is the current opening address:\n");
						SessionShowOpeningAddress(MySessions[ActiveSession]);
						continue;
					}
					
					break;

				case 10: // Move to next site
					if(MySessions[ActiveSession]!=NULL){
						SessionSiteNext(MySessions[ActiveSession]);
					}
					
					break;

				case 11: // Move to previous site
					if(MySessions[ActiveSession]!=NULL){
						SessionSitePrev(MySessions[ActiveSession]);
					}
					
					break;

				case 12: // See current site
					if(MySessions[ActiveSession]!=NULL){
						system("clear");
						SessionSiteShow(MySessions[ActiveSession]);
						continue;
					}

					break;

				case 13: // Close current tab
					if(MySessions[ActiveSession]!=NULL){
						SessionTabClose(MySessions[ActiveSession]);
						if(GetFlag()){ // Case we deleted the last tab and so the whole session
							MySessions[ActiveSession]=NULL; // reinitialize the session to null to avoid UI errors
							ZeroFlag(); // Reset flag
						}
					}
					break;

				case 14: // Close current Session
					if(MySessions[ActiveSession]!=NULL){
						SessionClose(MySessions[ActiveSession]);
						MySessions[ActiveSession]=NULL; // reinitialize the session to null to avoid UI errors
					}
					
					break;

				case 15: // Open site adress on current tab
					if(MySessions[ActiveSession]!=NULL){
						printf(" >Please type the site adress\n");
						scanf("%s", tmp);
						SessionNewAddress(MySessions[ActiveSession], tmp);
					}
					
					break;

				case 16: // Open site adress on new tab
					if(MySessions[ActiveSession]!=NULL){
						printf(" >Please type the site adress\n");
						scanf("%s", tmp);
						SessionOpenNewTab(MySessions[ActiveSession], tmp);
					}
					
					break;
					
				case 17: // Change active session
					// If i needed more Sessions i would make a custom struct(list) for them
					// and i would switch between them from here with a function
					if(ActiveSession==0){
						system("clear");
						printf(" >Changed to Session 2!\n");
						ActiveSession=1;
						continue;
					}
					else{
						system("clear");
						printf(" >Changed to Session 1!\n");
						ActiveSession=0;
						continue;
					}
					break;
			}
		}

		system("clear");

		if(messageHandler()){ // Print whatever message may be needed from the last executed function
			return 1;
		}
	}

	// free the remaining
	free(MySessions);
	free(tmp);
	
	return 0;
}

void PrintChoices(void){
	printf(" ____________________________________________________________________________________________\n");
	printf("|                                > DI browser v1.0 <                                         |\n");
	printf("|  >Type the number of the desired function number and press enter:                          |\n");
	printf("|  0.  Quit                                          |  9.  Show default opening adress      |\n");
	printf("|  1.  Create New Session                            |  10. Make next site your current      |\n");
	printf("|  2.  Create New Tab on current session             |  11. Make previous site your current  |\n");
	printf("|  3.  Show current Tab data                         |  12. See current site                 |\n");
	printf("|  4.  Move to the previous tab in current session   |  13. Close current Tab                |\n");
	printf("|  5.  Move to the next tab in current session       |  14. Close current session            |\n");
	printf("|  6.  Switch the current tab with its previous one  |  15. Open site adress on current tab  |\n");
	printf("|  7.  Switch the current tab with its next one      |  16. Open site adress on new tab      |\n");
	printf("|  8.  Change default opening adress                 |  17. Change Sessions                  |\n");
	printf("|____________________________________________________________________________________________|\n");
}
