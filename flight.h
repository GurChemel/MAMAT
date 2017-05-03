

#include "ex2.h"
#ifndef _FLIGHT_H
#define _FLIGHT_H

/* flight struct declaration & implementation */

typedef struct _FLIGHT {
	int 		flight_num;
	FlightType 	flight_type;
	char		flight_dest[4];
	BOOL		flight_emrgncy;

}FLIGHT, *PFLIGHT;

/* interface functions declaration*/

PFLIGHT	creatFlight(int, FlightType, char*, BOOL);
void 	destroyFlight(PFLIGHT);
void	printFlight(PFLIGHT);

#endif

