
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "airport.h"
#include "runway.h"
#include "flight.h"
#include "ex2.h"

#define MAX_LINE_SIZE 256

// Check if a sting contain non-digit elements:
int isNonDigitInString(char* str) {
	int i;
	int len = strlen(str);
	for (i = 0; i < len; i++) {
		if (!isdigit(str[i])) {
			return 1;
		}
	}
	return 0;
}

// Check if a sting contain legally writen destination:
int isDestLegal(char* str) {
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


int main() {
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char *pCommand, *pArgA, *pArgB, *pArgC, *pArgD;

	// Initialize arguments:
	int runwayNumber, flightNumber, numOfFlights;
	BOOL emergency;
	FlightType intOrDom;

	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		//fprintf(stderr, szLine);
		// Parse arguments:
		pCommand = strtok(szLine, delimiters);
		pArgA = strtok(NULL, delimiters);
		pArgB = strtok(NULL, delimiters);
		pArgC = strtok(NULL, delimiters);
		pArgD = strtok(NULL, delimiters);
		// Skip empty line:
		if (pCommand == NULL) {
			continue;
		}

		// Find command:
		/*	*******************************
					Insert
		  	******************************* */
		if (strcmp(pCommand, "Insert") == 0) {
			// Validate inputs:
			if ((pArgA == NULL) || (pArgB == NULL)) {
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			if (isNonDigitInString(pArgA) || ((*pArgB != 'I') && (*pArgB != 'D'))) {
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
			// Set parameters:
			runwayNumber = atoi(pArgA);
			switch (*pArgB) {//----------------------- added break -------------------------------
				case 'I':
					intOrDom = INTERNATIONAL;
					break;
				case 'D':
					intOrDom = DOMESTIC;
					break;
			}
			// Execute command:
			if (FAILURE == addRunway(runwayNumber,intOrDom)) {
				fprintf(stderr, "Insert execution failed.\n");
			}
		}
		/*	*******************************
					Remove
			******************************* */
		else if (strcmp(pCommand, "Remove") == 0) {
			// Validate inputs:
			if (pArgA == NULL) {
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}
			if (isNonDigitInString(pArgA)) {
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
			// Set parameters:
			runwayNumber = atoi(pArgA);
			// Execute command:
			if (FAILURE == removeRunway(runwayNumber)) {
				fprintf(stderr, "Remove execution failed.\n");
			}
		}
		/*	*******************************
					Add
			******************************* */
		else if (strcmp(pCommand, "Add") == 0) {
			// Validate inputs:
			if ((pArgA == NULL) || (pArgB == NULL) || (pArgC == NULL) || (pArgD == NULL)) {
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			if ((isNonDigitInString(pArgA)) || ((*pArgB != 'I') && (*pArgB != 'D')) || (!isDestLegal(pArgC)) || ((*pArgD != 'R') && (*pArgD != 'E'))) {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			// Set parameters:
			flightNumber = atoi(pArgA);
			
			if ((flightNumber<1) || (flightNumber>MAX_ID)) {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			
			switch (*pArgB) {
				case 'I':
					intOrDom = INTERNATIONAL;
					break;
				case 'D':
					intOrDom = DOMESTIC;
					break;
			}
			// destination = *pArgC;
			switch (*pArgD) {
				case 'E':
					emergency = TRUE;
					break;
				case 'R':
					emergency = FALSE;
					break;
			}
			// Execute command:
			if (FAILURE == addFlightToAirport(flightNumber, intOrDom, pArgC, emergency)) {
				fprintf(stderr, "Add execution failed.\n");
			}
		}
		/*	*******************************
					Depart
			******************************* */
		else if (strcmp(pCommand, "Depart") == 0) {
			// Validate inputs:
			if ((pArgA == NULL) || (pArgB == NULL)) {
				fprintf(stderr, "Depart failed: not enough parameters.\n");
				continue;
			}
			if ((isNonDigitInString(pArgA)) || (isNonDigitInString(pArgB))) {
				fprintf(stderr, "Depart execution failed.\n");
				continue;
			}
			// Set parameters:
			runwayNumber = atoi(pArgA);
			numOfFlights = atoi(pArgB);
			// Execute command:
			if (FAILURE == departFromRunway(runwayNumber, numOfFlights)) {
				fprintf(stderr, "Depart execution failed.\n");
			}
		}
		/*	*******************************
					Change
			******************************* */
		else if (strcmp(pCommand, "Change") == 0) {
			// Validate inputs:
			if ((pArgA == NULL) || (pArgB == NULL)) {
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
			if ((!isDestLegal(pArgA)) || (!isDestLegal(pArgB))) {
				fprintf(stderr, "Change execution failed.\n");
				continue;
			}
			// destination = *pArgA;
			// newDestination = *pArgB;
			
			// Execute command:
			if (FAILURE == changeDest(pArgA, pArgB)) {
				fprintf(stderr, "Change execution failed.\n");
			}
		}
		/*	*******************************
					Delay
			******************************* */
		else if (strcmp(pCommand, "Delay") == 0) {
			// Validate inputs:
			if (pArgA == NULL) {
				fprintf(stderr, "Delay failed: not enough parameters.\n");
				continue;
			}
			if (!isDestLegal(pArgA)) {
				fprintf(stderr, "Delay execution failed.\n");
				continue;
			}
			// destination = *pArgA;
			
			// Execute command:
			if (FAILURE == delay(pArgA)) {
				fprintf(stderr, "Delay execution failed.\n");
			}
		}
		/*	*******************************
					Print
			******************************* */
		else if (strcmp(pCommand, "Print") == 0) {
			// Execute command:
			printAirport();
		}
		/*	*******************************
					Exit
			******************************* */
		else if (strcmp(pCommand, "Exit") == 0) {
			// Execute command:
			destroyAirport();
			return 0;
		}
		else {
			fprintf(stderr, "Command not found.\n");
		}
	}
	return 0;
}
