/*
 * runway.c
 *
 *  Created on: May 3, 2017
 *      Author: gur
 */

#include <stdio.h>
#include "runway.h"

RUNWAY* createRunway(int runway_num, FlightType runway_type) {
	// Check for valid inputs:
	if (runway_num > MAX_ID) {
		return NULL;
	}
	
	// Allocate memory:
	RUNWAY* pRunway = (RUNWAY*)malloc(sizeof(RUNWAY));
	if (printRunway == NULL) {
		return NULL;
	}
	
	// Set parameters:
	pRunway->runway_num = runway_num;
	pRunway->runway_type = runway_type;
	pRunway->runway_list = NULL;

	// Return Runway pointer:
	return pRunway;

}	// ***  End of: createRunway  ***


void destroyRunway(RUNWAY* pRunway) {
	// Set default pointers:
	FLIGHTS_LIST* pList = pRunway->runway_list;
	FLIGHTS_LIST* next = NULL;
	
	// Free flight list:
	while (pList != NULL) {
		next = pList->pNext;
		free(pList);
		pList = next;
	}

	//Free runway:
	free(pRunway)

}	// ***  End of: destroyRunway  ***


BOOL isFlightExist(RUNWAY* pRunway, int flightCode) {
	// Check for valid inputs:
	if ((flightCode > MAX_ID) || (pRunway == NULL)) {
		return FALSE;
	}
	
	// Set default pointers:
	FLIGHTS_LIST* pList = pRunway->runway_list;

	// Find flight:
	while (pList != NULL) {
		if (flightCode == pList->pFlight->flight_num) {
			return TRUE;
		}
		pList = pList->pNext;
	}
	
	// If search didn't find anything:
	return FALSE;

}	// ***  End of: isFlightExist  ***


int getFlightNum(RUNWAY* pRunway){
	// Check for valid inputs:
	if (pRunway == NULL) {
		return -1;
	}

	// Set Parameters:
	int counts = 0;
	FLIGHTS_LIST* pList = pRunway->runway_list;

	// Count flights:
	while (pList != NULL) {
		counts++;
		pList = pList->pNext;
	}
	return counts;

}	// ***  End of: getFlightNum  ***


Result addFlight(RUNWAY* pRunway, FLIGHT* pFlight);
Result removeFlight(RUNWAY* pRunway, int flightCode);
Result depart(RUNWAY* pRunway);
void printRunway(RUNWAY* pRunway);

