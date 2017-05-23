#ifndef _RUNWAY_H
#define _RUNWAY_H

#include "ex2.h"
#include "flight.h"

typedef struct _FLIGHTS_LIST {
	PFLIGHT					pFlight;
	struct _FLIGHTS_LIST*	pNext;
}FLIGHTS_LIST;

typedef struct _RUNWAY {
	int 			runway_num;
	FlightType 		runway_type;
	FLIGHTS_LIST*	runway_list;
}RUNWAY;

RUNWAY* createRunway(int runway_num, FlightType runway_type);
void destroyRunway(RUNWAY* pRunway);
BOOL isFlightExist(RUNWAY* pRunway, int flightCode);
int getFlightNum(RUNWAY* pRunway);
Result addFlight(RUNWAY* pRunway, PFLIGHT pFlight);
Result removeFlight(RUNWAY* pRunway, int flightCode);
Result depart(RUNWAY* pRunway);
void printRunway(RUNWAY* pRunway);

#endif
