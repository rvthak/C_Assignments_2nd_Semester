/*************************************************************************
Implementation File	: controller.c
Author Date			: I. Rovithakis sdi1800164 20/03/2019
Purpose				: ATD controller - functions
**************************************************************************/

#include "controller.h"

void ControllerDimiourgia(TController *controller){
	controller->TimeBusy=0;
	controller->TimeInactive=0;
	controller->ArithmoPelaton=0;
	controller->enapomenonXronos=0;
	controller->TimeOff=0;
	return;
}

void ControllerNewCustomer(TController *controller){
	controller->ArithmoPelaton++;
	controller->TimeBusy++;
	return;
}

void ControllerSetXrono(TController *controller, int xronosEksipiretisis){
	controller->enapomenonXronos=xronosEksipiretisis;
	return;
}

void ControllerNoWork(TController *controller){
	controller->TimeInactive++;
	return;
}

void ControllerBusy(TController *controller){
	controller->TimeBusy++;
	controller->enapomenonXronos--;
	return;
}

int ControllerFree(TController controller){
	if(controller.enapomenonXronos==0){
		return 1;
	}
	return 0;
}

unsigned int ControllerGetArithmosPelatwn(TController controller){
	return controller.ArithmoPelaton;
}

unsigned int ControllerGetEnapomenonXronos(TController controller){
	return controller.enapomenonXronos;
}

unsigned int ControllerGetInactiveXronos(TController controller){
	return controller.TimeInactive;
}

unsigned int ControllerGetBusyXronos(TController controller){
	return controller.TimeBusy;
}

void ControllerOff(TController *controller){
	controller->TimeOff++;
	return;
}

unsigned int ControllerGetTimeOff(TController controller){
	return controller.TimeOff;
}