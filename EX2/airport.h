
#ifndef _AIRPORT_H
#define _AIRPORT_H

#include "ex2.h"
#include "flight.h"
#include "runway.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct _RUNWAY_LIST {
	RUNWAY*					thisRunway;
	struct _RUNWAY_LIST*	nextRunway;
}RUNWAY_LIST;

Result addRunway(int,FlightType);
Result removeRunway(int);
int		getRunwayNum();
Result	addFlightToAirport(int flight_code, FlightType flight_type, char dest[4],BOOL flight_emrgncy);
Result	departFromRunway(int runway_num, int num_of_flights);
Result	changeDest(char origin_dest[4], char new_dest[4]);
Result	delay(char dest_name[4]);
void	printAirport();
void	destroyAirport();


#endif
