// Ioannis Rovithakis | sdi1800164

#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession *InfoSessionPtr;

InfoSessionPtr SessionNew(char *);
void SessionNewTab(InfoSessionPtr Session);

void SessionTabShow(InfoSessionPtr Session);

void SessionTabNext(InfoSessionPtr Session);
void SessionTabPrev(InfoSessionPtr Session);

void SessionTabMoveLeft(InfoSessionPtr Session);
void SessionTabMoveRight(InfoSessionPtr Session);

void SessionNewOpeningAddress(InfoSessionPtr, char *string);
void SessionShowOpeningAddress(InfoSessionPtr Session);

void SessionSiteNext(InfoSessionPtr Session);
void SessionSitePrev(InfoSessionPtr Session);
void SessionSiteShow(InfoSessionPtr Session);

void SessionTabClose(InfoSessionPtr Session);
void SessionClose(InfoSessionPtr Session);

void SessionNewAddress(InfoSessionPtr Session, char *string);

void SessionOpenNewTab(InfoSessionPtr Session, char *string);

int GetFlag(void); // returns the value of the flag variable
void ZeroFlag(void); // Sets flag value to 0

int messageHandler(void); // Gets the latest message from message variable and prints the correct output

void PrintUI(InfoSessionPtr Session); // Print the UI
void PrintSessionActivity(InfoSessionPtr *MySessions, int ActiveSessions); // Print the Current session state

#endif
