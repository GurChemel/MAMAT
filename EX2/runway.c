/*
 * runway.c
 *
 *  Created on: May 3, 2017
 *      Author: gur
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runway.h"

RUNWAY* createRunway(int runway_num, FlightType runway_type) {
	// Check for valid inputs:
	if (runway_num > MAX_ID) {
		return NULL;
	}
	
	// Allocate memory:
	RUNWAY* pRunway = (RUNWAY*)malloc(sizeof(RUNWAY));
	if (pRunway == NULL) {
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
		destroyFlight(pList->pFlight);
		free(pList);
		pList = next;
	}

	//Free runway:
	free(pRunway);

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


Result addFlight(RUNWAY* pRunway, FLIGHT* pFlight) {
	// Check for valid inputs:
	if ((pRunway == NULL) || (pRunway->runway_type != pFlight->flight_type) || (isFlightExist(pRunway,pFlight->flight_num) == TRUE)){
		return FAILURE;
	}
	
	// Copy flight:
	FLIGHT* pFlightCopied = NULL;
	pFlightCopied = copyFlight(pFlight, pFlightCopied);
	if (NULL == pFlightCopied) {
		return FAILURE;
	}
	
	FLIGHTS_LIST* pList = pRunway->runway_list;
	FLIGHTS_LIST* pLastList = pList;

	// Check if runway is empty:
	if (pList == NULL) {
		pRunway->runway_list = (FLIGHTS_LIST*)malloc(sizeof(FLIGHTS_LIST));
		if (NULL == pRunway->runway_list) {
			return FAILURE;
		}
		pRunway->runway_list->pFlight = pFlightCopied;
		pRunway->runway_list->pNext = NULL;
		return SUCCESS;
	}

	// Find a place to enter the new flight:
	// If the flight is an Emergency:
	if (TRUE == pFlight->flight_emrgncy) {		
		// If there is no Emergency Flights on the list:
		if (FALSE == pList->pFlight->flight_emrgncy) {
			pRunway->runway_list = (FLIGHTS_LIST*)malloc(sizeof(FLIGHTS_LIST));
			if (NULL == pRunway->runway_list) {
				return FAILURE;
			}
			pRunway->runway_list->pFlight = pFlightCopied;
			pRunway->runway_list->pNext = pList;
			return SUCCESS;
		}
		else {
			while ((pList != NULL) && (TRUE == pList->pFlight->flight_emrgncy)) {
				pLastList = pList;
				pList = pList->pNext;
			}
		}
	}
	else {
		while (pList != NULL) {
			pLastList = pList;
			pList = pList->pNext;
		}
	}

	// Enter the flight in the place:
	pLastList->pNext = (FLIGHTS_LIST*)malloc(sizeof(FLIGHTS_LIST));
	if (NULL == pLastList->pNext) {
		return FAILURE;
	}
	pLastList->pNext->pFlight = pFlightCopied;
	pLastList->pNext->pNext = pList;

	return SUCCESS;
}	// ***  End of: addFlight  ***


Result removeFlight(RUNWAY* pRunway, int flightCode) {
	// Check for valid inputs:
	if ((flightCode > MAX_ID) || (pRunway == NULL) || (pRunway->runway_list == NULL) || FALSE==(isFlightExist(pRunway, flightCode))) {
		return FAILURE;
	}
	
	// Set default pointers:
	FLIGHTS_LIST* pList = pRunway->runway_list;
	FLIGHTS_LIST* pLastList = pList;
	
	// If the flight is the first one:
	if (flightCode == pList->pFlight->flight_num) {
		destroyFlight(pList->pFlight);
		pRunway->runway_list = pList->pNext;
		free(pList);
		return SUCCESS;
	}

	// Find flight and remove:
	while (pList != NULL) {
		if (flightCode == pList->pFlight->flight_num) {
			destroyFlight(pList->pFlight);
			pLastList->pNext = pList->pNext;
			free(pList);
			return SUCCESS;
		}
		pLastList = pList;
		pList = pList->pNext;
	}

	return FAILURE;
}	// ***  End of: removeFlight  ***


Result depart(RUNWAY* pRunway) {
	// Check for valid inputs:
	if ((pRunway == NULL) || (pRunway->runway_list == NULL)) {
		return FAILURE;
	}

	return removeFlight(pRunway, pRunway->runway_list->pFlight->flight_num);
}	// ***  End of: depart  ***


void printRunway(RUNWAY* pRunway) {
	if (pRunway->runway_type == INTERNATIONAL) {
		printf("Runway %d international\n", pRunway->runway_num);
	}
	else {
		printf("Runway %d domestic\n", pRunway->runway_num);
	}
	printf("%d flights are waiting:\n", getFlightNum(pRunway));

	// Set default pointers:
	FLIGHTS_LIST* pList = pRunway->runway_list;

	// Find flight:
	while (pList != NULL) {
		printFlight(pList->pFlight);
		pList = pList->pNext;
	}

}	// ***  End of: printRunway  ***
