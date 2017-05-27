#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "list.h"
#include "point.h"

typedef struct Point_ {
	PList	coordsList;
	int 	dimension;
} POINT;

PPoint PointCreate(int Dimension){
	//checking input
	if (Dimension <= 0) return NULL;
	PPoint newPoint = (PPoint)malloc(sizeof(POINT));
	if (newPoint == NULL) return NULL;
	newPoint->coordsList = ListCreate(cloneCoordinate,destroyCoordinate,compareCoordinate,printCoordinate);
	if (newPoint->coordsList == NULL)return NULL;
	newPoint->dimension = Dimension;
	return newPoint;
}// End Of PointCreate

void PointDestroy(PPoint killPoint){
	//checking input
	if (killPoint == NULL) return;
	ListDestroy(killPoint->coordsList);
	free(killPoint);
}// End Of Point Destroy

Result PointAddCoordinate(PPoint addToPoint, int coordinate){
	//checking input
	if (addToPoint == NULL) return FAIL;
	//checking if there is "room" for more coordinates
	if (ListNumElements(addToPoint->coordsList) < addToPoint->dimension){
		return ListAdd(addToPoint->coordsList, &coordinate);
	}
	else{
		return FAIL;
	}

} // End Of PointAddCoordinate


int PointGetFirstCoordinate(PPoint point){
	//checking input
	if (point == NULL) return 0;
	if (point->coordsList == NULL) return 0;
	//checking for empty point
	if (ListIsEmpty(point->coordsList)) return 0;

	int* firstCoordinate = (int*)ListGetFirst(point->coordsList);
	return *firstCoordinate;
}// End Of PointGetFirstCoordinate


int PointGetNextCoordinates(PPoint point){
	//checking input
	if (point == NULL) return 0;
	if (point->coordsList == NULL) return 0;
	//checking for empty point
	if (ListIsEmpty(point->coordsList)) return 0;

	int* nextCoordinate = (int*)ListGetNext(point->coordsList);
	if (nextCoordinate == NULL){
		return 0;// there is no next point
	}
	else{
		return *nextCoordinate;
	}
}// End Of PointGetNextCoordinates


void PointPrint(PPoint point){
	//checking input
	if (point == NULL || point->coordsList == NULL ) return;
	if (ListIsEmpty(point->coordsList)) return;
	printf("Point Dimension: %d, Size: %d, Coordinates:",point->dimension, ListNumElements(point->coordsList));
	ListPrint(point->coordsList);
}



PElement cloneCoordinate(void* source_){
	//check input
	if (source_ == NULL) return NULL;
	//casting
	int* source = (int*)source_;
	//allocating memory
	int* newCoord = (int*)malloc(sizeof(int));
	if (newCoord == NULL) return NULL;
	*newCoord = *source;
	return (PElement)newCoord;
} //END OF cloneCoordinate


void destroyCoordinate(void* coordToKill_){
	//checking input
	if (coordToKill_ == NULL) return;
	//casting
	int* coordToKill = (int*)coordToKill_;

	free(coordToKill);

}// END OF destroyCoordinate

BOOL compareCoordinate(void* srcA, void* srcB){
	//checking input
	if (srcA ==NULL || srcB == NULL) return FALSE;
	//casting
	int sourceA = *(int*)srcA;
	int sourceB = *(int*)srcB;
	return (sourceA == sourceB) ? TRUE : FALSE;
}// END OF compareCoordinate

void printCoordinate(void* coordPrint){
	//checking input
	if (coordPrint == NULL) return;
	int toPrint = *(int*)coordPrint;
	printf("%d",toPrint);
}// END OF printCoordinate

int		PointGetDimension(PPoint point){
	//checking input
		if (point == NULL) return 0;
		return point->dimension;
}// End Of PointGetDimension

int 	PointNumCoordinates(PPoint point){
	if (point == NULL) return -1;
	return ListNumElements(point->coordsList);
}// End Of PointNumCoordinates

///////////////////////////////////////////////////////////


