


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"


static RUNWAY_LIST airPort;

Result	addRunway‬‬(int new_num, FlightType runway_type){

	RUNWAY* 	 runway		 = airPort->thisRunway;
	RUNWAY_LIST* listElement = &airPort;
	RUNWAY_LIST* next		 = airPort->nextRunway;

	//adding first runway
	if (runway==NULL){
		listElement->thisRunway = createRunway(new_num, runway_type);
		return(runway == NULL)? FAILURE :SUCCESS;
	}

	while(next != NULL){
		//checking for runway with same number
		if (runway->runway_num==new_num){
			return FAILURE;
		}

		//updating values to move down the list
		listElement = next;
		runway 		= listElement->thisRunway;
		next 		= listElement->nextRunway;
	}

	//adding runway to the end of the list
	listElement->nextRunway = (RUNWAY_LIST*)malloc(sizeof(RUNWAY_LIST));

	if (listElement->nextRunway == NULL){return FAILURE;}

	listElement->nextRunway->thisRunway = createRunway(new_num, runway_type);

	return (listElement->nextRunway->thisRunway==NULL) ? FAILURE : SUCCESS;

}/* End Of addRunway‬‬ */

Result	removeRunway‬‬(int kill_num){

	RUNWAY* 	 runway		 = airPort->thisRunway;
	RUNWAY_LIST* listElement = &airPort;
	RUNWAY_LIST* next		 = airPort->nextRunway;

	if (runway==NULL){return FAILURE;} //in case there are no runways

	if (runway->runway_num==kill_num){// for the first runway on the list
		destroyRunway(listElement->thisRunway);
		&airPort = airPort->nextRunway;
		free(listElement);
	}

	while(next != NULL){
		if (next->thisRunway->runway_num == kill_num){
			destroyRunway(next->thisRunway);
			listElement->nextRunway = next->nextRunway;//patching the "hole" in the list
			free(next);
			return SUCCESS;
		}
		listElement = next;
		runway 		= listElement->thisRunway;
		next 		= listElement->nextRunway;
	} return FAILURE; // if there was no runway with number matching "kill_num"

}/* End Of removeRunway */

int		getRunwayNum(){
	//return the number of runways in airport
	int count=0;
	RUNWAY_LIST* listElement = &airPort;
	RUNWAY_LIST* next	= airPort->nextRunway;

	if (listElement->thisRunway==NULL){return 0;} //there are no runways
	count++; //counting first runway

	while(next != NULL){
		count++;
		listElement=next;
		next=listElement->nextRunway;
	} return count;

}/* End Of getRunwayNum */

Result	addFlightToAirport(int flight_code, FlightType flight_type, char dest[4],BOOL flight_emrgncy){

	if ((flight_code>MAX_ID) || (is_DestLegal(dest)==0)) {return FAILURE;}//validity of parameters

	RUNWAY* 	 runway		 	= airPort->thisRunway;
	RUNWAY_LIST* listElement 	= &airPort;
	RUNWAY_LIST* next			= airPort->nextRunway;
	int 		 minFlightsNum  = MAX_ID+1;
	int			 addtoRunwayNum = MAX_ID+1;
	RUNWAY_LIST* addtoRunway 	= NULL;

	if (runway==NULL){return FAILURE;}//airport is empty

	while (listElement != NULL){
		if(isFlightExist(runway, flight_code)==TRUE){return FAILURE;}//flight with the same number already exist

		int numFlights = getFlightNum(runway);

		if((runway->runway_type==flight_type) && (numFlights<=minFlightsNum)){//runway is matching by type and has minimal flights so far
			if((numFlights==minFlightsNum) && (runway->runway_num<addtoRunwayNum)){//if there is the same number of flights
				addtoRunway=listElement;
			}
			else if (numFlights < minFlightsNum){//in case this runway has minimal number of flights
				addtoRunway=listElement;
			}
		}

		listElement = next;
		runway 		= listElement->thisRunway;
		next 		= listElement->nextRunway;
	}

	if (addtoRunway == NULL){return FAILURE;}// no runway found fit
	PFLIGHT newflight = creatFlight(flight_code, flight_type, dest, flight_emrgncy);
	Result addFlightResult = addFlight(addtoRunway->thisRunway,newflight);
	return addFlightResult;
}/* End Of addFlightToAirport */

Result	departFromRunway(int runway_num, int num_of_flights){

	RUNWAY* 	 runway		 = airPort->thisRunway;
	RUNWAY_LIST* listElement = &airPort;
	RUNWAY_LIST* next		 = airPort->nextRunway;
	if (runway == NULL){return FAILURE;}//airport empty

	while(listElement != NULL){

		if((runway->runway_num == runway_num) && (getFlightNum(runway)>=num_of_flights)){//finding the correct runway and checking for enough flights
			for(int i = 0 ; i < num_of_flights ; i++){
				Result Resultdepart = depart(runway);
				if (Resultdepart == FAILURE){return FAILURE;}//some depart failed
			}
			return SUCCESS;
		}
	listElement = next;
	runway 		= listElement->thisRunway;
	next 		= listElement->nextRunway;
	}
	return FAILURE;

}/* End Of departFromRunway */

Result	changeDest(char origin_dest[4], char new_dest[4]){
	RUNWAY* 	 runway		 = airPort->thisRunway;
	RUNWAY_LIST* listElement = &airPort;
	RUNWAY_LIST* next		 = airPort->nextRunway;

	if((is_DestLegal(origin_dest)==0) || (is_DestLegal(new_dest)==0)){return FAILURE;}// illegal destination
	while(listElement != NULL){
		char*			destination 	= runway->runway_list->pFlight->flight_dest;
		FLIGHTS_LIST*	flightElement	= runway->runway_list;
		FLIGHTS_LIST*	nextflight		= runway->runway_list->pNext;
		while(flightElement != NULL){
			if (strcmp(destination, origin_dest)==0){
				int len=strlen(origin_dest);
				for(int i =0; i<=len; i++){
					runway->runway_list->pFlight->flight_dest[i]=new_dest[i];
				}
			}
			flightElement	= nextflight;
			destination		= flightElement->pFlight->flight_dest;
			nextflight		= flightElement->pNext;
		}
		listElement = next;
		runway 		= listElement->thisRunway;
		next 		= listElement->nextRunway;
	}
	return SUCCESS;

}

















