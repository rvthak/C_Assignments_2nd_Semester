// Ioannis Rovithakis | sdi1800164

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Session.h"

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;

// Global Variables Used for communicating with the message Handler and letting the client know if he can print the ui or not
int message=0; // Used to transfer message codes to be printed out
char flag=0;   // used to let the client know if he should reset the active session pointer to null to avoid ui errors

struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;

	int TotalTabsOpened;
	int CurrentTabsOpen;
};

struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;

	TabNodePtr BonusTab;
	SiteNodePtr BonusSite;
	int TabID;
};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};


InfoSessionPtr SessionNew(char * Addr){
	InfoSessionPtr NewInfoSession;
	TabNodePtr newTab;
	SiteNodePtr newSite;

	// Allocate the needed memory
	if( (NewInfoSession=malloc(sizeof(struct InfoSession)))==NULL ||
		(NewInfoSession->OpeningAddress=malloc(strlen(Addr)+1)) ==NULL ||
		(newTab=malloc(sizeof(struct TabNode)))==NULL ||
		(newSite=malloc(sizeof(struct SiteNode)))==NULL ||
		(newSite->Address=malloc(strlen(Addr)+1)) ==NULL ){

		message= -1; // leave a failure message
		return NULL;
	}
	flag=0;

	// Handle Infosession
	NewInfoSession->AuxTab=NULL;
	NewInfoSession->FirstTab=newTab;
	NewInfoSession->LastTab=newTab;
	NewInfoSession->CurrTab=newTab;

	strcpy( NewInfoSession->OpeningAddress , Addr);

	// Handle TabNode
	newTab->PrevTab=newTab;
	newTab->NextTab=newTab;
	newTab->FirstSite=newSite;
	newTab->CurrSite=newSite;

	// keep some info for the ui
	NewInfoSession->TotalTabsOpened=1;
	newTab->TabID=NewInfoSession->TotalTabsOpened;

	// Handle bonus
	newTab->BonusTab=NULL;
	newTab->BonusSite=NULL;

	// Handle SiteNode
	newSite->PrevSite=NULL;
	newSite->NextSite=NULL;
	newSite->UpTab=newTab;

	strcpy( newSite->Address , Addr);

	message=1; // leave a succes message
	return NewInfoSession;
}

void SessionNewTab(InfoSessionPtr Session){
	TabNodePtr newTab;
	SiteNodePtr newSite;

	if( (newTab=malloc(sizeof(struct TabNode)))==NULL ||
		(newSite=malloc(sizeof(struct SiteNode)))==NULL ||
		(newSite->Address=malloc(strlen(Session->OpeningAddress)+1)) ==NULL ){
		message= -1;
		return;
	}
	
	// Update the UI needed
	Session->TotalTabsOpened++;
	newTab->TabID=Session->TotalTabsOpened;

	// Handle tab
	newTab->PrevTab=Session->LastTab;
	Session->LastTab->NextTab=newTab;
	Session->LastTab=newTab;

	newTab->NextTab=Session->FirstTab;
	Session->FirstTab->PrevTab=newTab;
	Session->CurrTab=newTab;

	newTab->FirstSite=newSite;
	newTab->CurrSite=newSite;

	// Handle bonus
	newTab->BonusTab=NULL;
	newTab->BonusSite=NULL;

	// Handle site
	newSite->UpTab=newTab;
	newSite->PrevSite=NULL;
	newSite->NextSite=NULL;

	strcpy( newSite->Address , Session->OpeningAddress);

	message=2;
	return;
}

void SessionTabShow(InfoSessionPtr Session){
	printf("%s\n", Session->CurrTab->CurrSite->Address);
	return;
}

void SessionTabPrev(InfoSessionPtr Session){
	Session->CurrTab=Session->CurrTab->PrevTab;
	message=4;
	return;
}

void SessionTabNext(InfoSessionPtr Session){
	Session->CurrTab=Session->CurrTab->NextTab;
	message=5;
	return;
}

void SessionTabMoveLeft(InfoSessionPtr Session){
	TabNodePtr tmp1, tmp2;

	if(Session->CurrTab==Session->FirstTab){ // case its first it cant be moved left
		message= -6; // Failure message
		return;
	}

	// case there are only two tabs just switch the first and last tab pointers
	if(Session->CurrTab==Session->LastTab&&Session->CurrTab->PrevTab==Session->FirstTab){
		Session->LastTab=Session->FirstTab;
		Session->FirstTab=Session->CurrTab;
		message=6; // Success message
		return;
	}

	// we have the target at currtab
	Session->AuxTab=Session->CurrTab->PrevTab; // we save the other target at auxtab
	tmp1=Session->AuxTab->PrevTab; // we save the one end at tmp1
	tmp2=Session->CurrTab->NextTab; // we save the other end at tmp2

	// one way connection
	tmp1->NextTab=Session->CurrTab;
	Session->CurrTab->NextTab=Session->AuxTab;
	Session->AuxTab->NextTab=tmp2;

	// other way connection
	tmp2->PrevTab=Session->AuxTab;
	Session->AuxTab->PrevTab=Session->CurrTab;
	Session->CurrTab->PrevTab=tmp1;

	// Case one of them is an edge, update First/Last tabs
	if(Session->AuxTab==Session->FirstTab){
		Session->FirstTab=Session->CurrTab;
	}
	if(Session->CurrTab==Session->LastTab){
		Session->LastTab=Session->AuxTab;
	}

	// reset AuxTab
	Session->AuxTab=NULL;

	message=6; // Success message
	return;
}

void SessionTabMoveRight(InfoSessionPtr Session){
	TabNodePtr tmp1, tmp2;

	if(Session->CurrTab==Session->LastTab){ // case its first it cant be moved right
		message= -7;
		return;
	}

	// case there are only two tabs
	if(Session->CurrTab==Session->FirstTab&&Session->CurrTab->NextTab==Session->LastTab){
		Session->FirstTab=Session->LastTab;
		Session->LastTab=Session->CurrTab;
		message=7;
		return;
	}

	// we have the target at currtab
	Session->AuxTab=Session->CurrTab->NextTab; // we save the other target at auxtab
	tmp1=Session->CurrTab->PrevTab; // we save the other end at tmp1
	tmp2=Session->AuxTab->NextTab; // we save the one end at tmp2
	
	// one way connection
	tmp1->NextTab=Session->AuxTab;
	Session->AuxTab->NextTab=Session->CurrTab;
	Session->CurrTab->NextTab=tmp2;

	// other way connection
	tmp2->PrevTab=Session->CurrTab;
	Session->CurrTab->PrevTab=Session->AuxTab;
	Session->AuxTab->PrevTab=tmp1;

	// Case one of them is an edge, update First/Last tabs
	if(Session->AuxTab==Session->LastTab){
		Session->LastTab=Session->CurrTab;
	}
	if(Session->CurrTab==Session->FirstTab){
		Session->FirstTab=Session->AuxTab;
	}

	// reset AuxTab
	Session->AuxTab=NULL;

	message=7;
	return;
}

void SessionNewOpeningAddress(InfoSessionPtr Session, char *string){
	free(Session->OpeningAddress); // Free the previous one

	// Allocate memory for the next one
	if( (Session->OpeningAddress=malloc(sizeof(strlen(string)+1)))==NULL){
		message= -1;
		return;
	}
	strcpy(Session->OpeningAddress, string); // copy the new address to the Session

	message=8;
	return;
}

void SessionShowOpeningAddress(InfoSessionPtr Session){
	printf("%s\n", Session->OpeningAddress);
	return;
}

void SessionSiteNext(InfoSessionPtr Session){
	// Check if there is a next site
	if(Session->CurrTab->CurrSite->NextSite==NULL){
		message= -10;
		return;
	}
	// Make it curren
	Session->CurrTab->CurrSite=Session->CurrTab->CurrSite->NextSite;

	message=10;
	return;
}

void SessionSitePrev(InfoSessionPtr Session){
	// Check if there is a prev site
	if(Session->CurrTab->CurrSite->PrevSite==NULL){
		message= -11;
		return;
	}
	// Make it current
	Session->CurrTab->CurrSite=Session->CurrTab->CurrSite->PrevSite;

	message=11;
	return;
}

void SessionSiteShow(InfoSessionPtr Session){
	printf("%s\n", Session->CurrTab->CurrSite->Address);
	return;
}

void SessionTabClose(InfoSessionPtr Session){
	TabNodePtr tmp1;
	SiteNodePtr tmp2;

	// Delete all the sites on that tab
	tmp2=Session->CurrTab->FirstSite; // Get the address of the first site of the tab
	while( (tmp2=tmp2->NextSite)!=NULL){ // while there are sites available, move to the next site 
		free(tmp2->PrevSite); // free the previous one
	}
	free(tmp2); // delete the last one


	if(Session->FirstTab==Session->LastTab){ // is it the only tab left? Delete the whole session
		flag=1; // To send a message that session pointer needs to be turnd back to null to not print ui 

		// free whatever is left
		free(Session->CurrTab); 
		free(Session);

		message=131; // Full delete message
		return;
	}

	// link back the rest
	Session->CurrTab->NextTab->PrevTab=Session->CurrTab->PrevTab;
	if(Session->CurrTab==Session->LastTab){ // In case currtab is last, fix the last pointer
		Session->LastTab=Session->CurrTab->PrevTab;
	}

	Session->CurrTab->PrevTab->NextTab=Session->CurrTab->NextTab;
	if(Session->CurrTab==Session->FirstTab){ // In case curtab is first, fix the first pointer
		Session->FirstTab=Session->CurrTab->NextTab;
	}

	// change currtab to its new value
	tmp1=Session->CurrTab; // temporarily save the value for later free

	if(Session->CurrTab->BonusTab!=NULL){ // Is this a tab that was opened by following a link on a site (BONUS) ? Go back to that tab + site
		// Use the stored pointers
		Session->CurrTab->CurrSite=Session->CurrTab->BonusSite;
		Session->CurrTab=Session->CurrTab->BonusTab;	

		// free the deleted tab
		free(tmp1);

		message=132; // Bonus message
		return;
	}

	Session->CurrTab=Session->CurrTab->NextTab; // Just point it to the next in a circle tab 
	
	free(tmp1); // free the old one

	message=13;
	return;
}

void SessionClose(InfoSessionPtr Session){
	TabNodePtr tmp1, del;
	SiteNodePtr tmp2;

	Session->LastTab->NextTab=NULL; // break the circle to be able to go from start to finish
	
	tmp1=Session->FirstTab; // Go to the first tab
	while( tmp1!=NULL){ // move one tab at a time and delete the sites

		tmp2=tmp1->FirstSite; // Go to the first site
		while( (tmp2=tmp2->NextSite)!=NULL){ // while there are more move on
			free(tmp2->PrevSite); // and free the previous one
		}
		free(tmp2); // free the last one

		// Move to the next tab and free the current one
		del=tmp1;
		tmp1=tmp1->NextTab;
		free(del);
	}

	free(Session); // free the whole session 
	return;
}

void SessionNewAddress(InfoSessionPtr Session, char *string){
	SiteNodePtr newSite;
	SiteNodePtr lim, tmp;

	// Allocate the needed space
	if( (newSite=malloc(sizeof(struct SiteNode)))==NULL){
		message= -1;
		return;
	}

	// If there are sites saved after the current one
	if((lim=Session->CurrTab->CurrSite->NextSite)!=NULL){ 
		// delete them
		while(lim!=NULL){
			tmp=lim;
			lim=lim->NextSite;
			free(tmp);
		}
	}

	// Link the new site
	newSite->NextSite=NULL;
	newSite->PrevSite=Session->CurrTab->CurrSite;
	newSite->UpTab=Session->CurrTab;

	// Update the currtab
	Session->CurrTab->CurrSite->NextSite=newSite;
	Session->CurrTab->CurrSite=newSite;

	// Allocate memory for the address
	if( (newSite->Address=malloc(sizeof(strlen(string)+1)))==NULL){
		message= -1;
		return;
	}
	strcpy(newSite->Address, string); // Copy the address

	message=15;
	return;
}

void SessionOpenNewTab(InfoSessionPtr Session, char *string){
	TabNodePtr newTab;
	SiteNodePtr newSite;

	// Allocate needed memory
	if( (newTab=malloc(sizeof(struct TabNode)))==NULL ||
		(newSite=malloc(sizeof(struct SiteNode)))==NULL ||
		(newSite->Address=malloc(strlen(string)+1)) ==NULL ){
		message= -1;
		return;
	}
	// Update UI info
	Session->TotalTabsOpened++;
	newTab->TabID=Session->TotalTabsOpened;

	// Handle bonus
	newTab->BonusTab=Session->CurrTab;
	newTab->BonusSite=Session->CurrTab->CurrSite;

	// Handle tab
	newTab->PrevTab=Session->LastTab;
	Session->LastTab->NextTab=newTab;

	Session->LastTab=newTab;

	newTab->NextTab=Session->FirstTab;
	Session->FirstTab->PrevTab=newTab;

	Session->CurrTab=newTab;

	newTab->FirstSite=newSite;
	newTab->CurrSite=newSite;

	// Handle site
	newSite->UpTab=newTab;
	newSite->PrevSite=NULL;
	newSite->NextSite=NULL;

	strcpy( newSite->Address , string);

	message=16;
	return;
}

int GetFlag(void){
	return flag;
}

void ZeroFlag(void){
	flag=0;
}

int messageHandler(void){
	switch(message){
		case 0:	// Nothing went wrong do nothing
			break;
		case -1:	// If a malloc fails
			printf(" >Fatal memory error: Failed to allocate memory.\n");
			printf(" >Terminating program...\n");
			return 1;

		case 1:
			printf(" >New Session created!\n");
			break;

		case 2:
			printf(" >New Tab created!\n");
			break;

		case 4:
			printf(" >Moved to the prev Tab\n");
			break;

		case 5:
			printf(" >Moved to the next Tab\n");
			break;

		case -6:	// If move tab left fails cause currtab==firstab
			printf(" >Could not move current tab left cause it is currently first.\n");
			printf(" Please try something else.\n");
			break;
		case 6:
			printf(" >Switched position of the current tab with it's left one\n");
			break;

		case -7:
			printf(" >Could not move current tab right cause it is currently last.\n");
			printf(" Please try something else.\n");
			break;
		case 7:
			printf(" >Switched position of the current tab with it's right one\n");
			break;

		case 8:
			printf(" >Opening address changed!\n");
			break;

		case -10:
			printf(" >There is no next site to go.\n");
			break;
		case 10:
			printf(" >Moved to next site.\n");

		case -11:
			printf(" >There is no previous site to go.\n");
			break;
		case 11:
			printf(" >Moved to previous  site.\n");
			break;

		case 13:
			printf(" >Closed tab\n");
			break;
		case 131:
			printf(" >Closed the last tab of the current session, closing the whole session.\n");
			break;
		case 132:
			printf(" >Closed a bonus tab, going back to the source site.\n");
			break;

		case 15:
			printf(" >New address opened on current tab.\n");
			break;

		case 16:
			printf(" >New address opened on new tab.\n");
			break;

		case 18:
			printf(" >Could not find any session please create one to move on\n");
			break;

		default:
			printf(" Unknown error: we suggest exiting and restarting the app to avoid unexpected behavior.\n");
			break;

	}
	message=0; // Reset message to prepare for the next message
	return 0;
}

void PrintUI(InfoSessionPtr Session){
	TabNodePtr temp;
	SiteNodePtr tmp;
	if(Session==NULL){
		message=18;
		return;
	}
	printf(" ________________________________________________\n");
	printf("|                 Infosession                    |\n");
	printf("| OpeningAddress: %s        |\n", Session->OpeningAddress);
	printf("| FirstTab:  %p                      |\n", Session->FirstTab);
	printf("| LastTab:   %p                      |\n", Session->LastTab);
	printf("| CurrTab:   %p                      |\n", Session->CurrTab);
	printf("|________________________________________________|\n");

	printf(" ___________________________\n");
	printf("|       TabID: %4d         |\n", Session->FirstTab->TabID);
	if(Session->FirstTab==Session->CurrTab){
		printf("|        > CurrTab <        |\n");
	}
	printf("| PrevTab:   %p |\n", Session->FirstTab->PrevTab);
	printf("| NextTab:   %p |\n", Session->FirstTab->NextTab);
	printf("| FirstSite: %p |\n", Session->FirstTab->FirstSite);
	printf("| CurrSite:  %p |\n", Session->FirstTab->CurrSite);
	printf("| Sites:    ");
		tmp=Session->FirstTab->FirstSite;
		printf(" %p ->", tmp);
		while((tmp=tmp->NextSite)!=NULL){
			printf(" %p ->", tmp);
		}
	printf("\n| Adresses:");
		tmp=Session->FirstTab->FirstSite;
		printf(" %s ->", tmp->Address);
			while((tmp=tmp->NextSite)!=NULL){
				printf(" %s ->", tmp->Address);
			}
	printf("\n|___________________________|\n");

	if( Session->FirstTab->NextTab==Session->FirstTab){
		return;
	}
	temp=Session->FirstTab;
	while( (temp=temp->NextTab)!=Session->FirstTab){
		printf(" ___________________________\n");
		printf("|       TabID: %4d         |\n",temp->TabID);
		if(temp==Session->CurrTab){
			printf("|        > CurrTab <        |\n");
		}
		printf("| PrevTab:   %p |\n", temp->PrevTab);
		printf("| NextTab:   %p |\n", temp->NextTab);
		printf("| FirstSite: %p |\n", temp->FirstSite);
		printf("| CurrSite:  %p |\n", temp->CurrSite);
		printf("| Sites:    ");
			tmp=temp->FirstSite;
			printf(" %p ->", tmp);
			while((tmp=tmp->NextSite)!=NULL){
				printf(" %p ->", tmp);
			}
		printf("\n| Adresses:");
			tmp=temp->FirstSite;
			printf(" %s ->", tmp->Address);
				while((tmp=tmp->NextSite)!=NULL){
					printf(" %s ->", tmp->Address);
				}
		printf("\n|___________________________|\n");
	}

	return;
}

void PrintSessionActivity(InfoSessionPtr 	*MySessions, int ActiveSession){
	printf(" ____________________________________________________________________________________________\n");
	printf("| <Sessions> |        Session 1: %s %s     |        Session 2: %s %s     |\n", MySessions[0]==NULL ? "Closed" : "Open  ", ActiveSession ? "        " : "(Active)", MySessions[1]==NULL ? "Closed" : "Open  ", !ActiveSession ? "        " : "(Active)");
	printf("|____________|_______________________________________|_______________________________________|\n");
}