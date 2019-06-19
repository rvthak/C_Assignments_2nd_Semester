/*************************************************************************
Implementation File	: controller.h 
Author Date			: I. Rovithakis sdi1800164 20/03/2019
Purpose				: ATD controller header
**************************************************************************/

#ifndef Controller
#define Controller

typedef struct{
	unsigned int TimeBusy;
	unsigned int TimeInactive;
	unsigned int ArithmoPelaton;
	unsigned int enapomenonXronos;
	unsigned int TimeOff;
}TController;

void ControllerDimiourgia(TController *controller);
void ControllerNewCustomer(TController *controller);

void ControllerSetXrono(TController *controller, int xronosEksipiretisis);

void ControllerNoWork(TController *controller);
void ControllerBusy(TController *controller);

int ControllerFree(TController controller);

unsigned int ControllerGetArithmosPelatwn(TController controller);
unsigned int ControllerGetEnapomenonXronos(TController controller); 
unsigned int ControllerGetInactiveXronos(TController controller);
unsigned int ControllerGetBusyXronos(TController controller);

void ControllerOff(TController *controller);
unsigned int ControllerGetTimeOff(TController controller);

#endif