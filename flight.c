/*
 * flight.c
 *  Created on: May 3, 2017
 */
#include "ex2.h"
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PFLIGHT	creatFlight(int flight_num, FlightType flight_type , char* flight_dest, BOOL flight_emrgncy){
	/* create new flight and initialize parameters */
	if (flight_num > MAX_ID){
		return NULL;
	}
	PFLIGHT pFlight;
	pFlight = (PFLIGHT)malloc(sizeof(FLIGHT));
	if (pFlight == NULL){
		return NULL;
	}
	//FLIGHT flight = *pFlight;
	pFlight->flight_num = flight_num;
	pFlight->flight_type = flight_type;
	strcpy(pFlight->flight_dest, flight_dest);
	pFlight->flight_emrgncy = flight_emrgncy;

	return pFlight;
}


void destroyFlight(PFLIGHT pFlight){
	/* free memory of flight */
	if(pFlight!=NULL){
		free(pFlight);}
}

void printFlight(PFLIGHT pFlight){
	/* print flight data according to instructions */
	char type, emergency;
	if (pFlight->flight_type==DOMESTIC){
		type ='D';
	}else{
		type ='I';
	}
	if (pFlight->flight_emrgncy==TRUE){
		emergency ='E';
	}else{
		emergency ='R';
		}
	printf("Flight %d %c %s %c \n", pFlight->flight_num, type, pFlight->flight_dest  ,emergency );
}
