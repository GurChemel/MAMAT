/*
 * flight.c
 *  Created on: May 3, 2017
 */
#include "ex2.h"
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

PFLIGHT creatFlight(int flight_num, FlightType flight_type, char* flight_dest,BOOL flight_emrgncy) {
	/* create new flight and initialize parameters */
	//checking if flight num is valid
	if ((flight_num > MAX_ID)||(is_DestLegal(flight_dest)==0)) {
		return NULL;
	}
	PFLIGHT pFlight;
	//allocating memory
	pFlight = (PFLIGHT) malloc(sizeof(FLIGHT));
	if (pFlight == NULL) {
		return NULL;
	}
	// initializing flight
	pFlight->flight_num = flight_num;
	pFlight->flight_type = flight_type;
	strcpy(pFlight->flight_dest, flight_dest);
	pFlight->flight_emrgncy = flight_emrgncy;

	return pFlight;
}

void destroyFlight(PFLIGHT pFlight) {
	/* free memory of flight */
	if (pFlight != NULL) {
		free(pFlight);
	}
}

void printFlight(PFLIGHT pFlight) {
	/* print flight data according to instructions */
	char type, emergency;
	if (pFlight->flight_type == DOMESTIC) {
		type = 'D';
	} else {
		type = 'I';
	}
	if (pFlight->flight_emrgncy == TRUE) {
		emergency = 'E';
	} else {
		emergency = 'R';
	}
	printf("Flight %d %c %s %c\n", pFlight->flight_num, type,
			pFlight->flight_dest, emergency);
}

PFLIGHT copyFlight(PFLIGHT flight_src, PFLIGHT flight_copied) {
	/* int copyFlight( source, destination) copies from source to new FLIHT by value,
	 * Return NULL if fails, Return flight_copied if succeed
	 */

	flight_copied = (PFLIGHT)malloc(sizeof(FLIGHT));
	if(flight_copied==NULL){
		return NULL;
	}
	//flight_copied = flight_src;
	memcpy(flight_copied, flight_src, sizeof(FLIGHT));
	if (memcmp(flight_copied, flight_src, sizeof(FLIGHT))==0){
		return flight_copied;
	}else{
		return NULL;
	}
	return flight_copied;
}

// Check if a sting contain legally writen destination:
int is_DestLegal(char* str) {
	int i;
	int len = strlen(str);
	if (len != 3) {
		return 0;
	}
	for (i = 0; i < len; i++) {
		if (!isupper(str[i])) {
			return 0;
		}
	}
	return 1;
}
