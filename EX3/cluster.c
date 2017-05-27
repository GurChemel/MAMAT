#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "list.h"
#include "point.h"
#include "cluster.h"

typedef struct Cluster_{
	PList 	pointsList;
	int 	dimension;
} Cluster;

PCluster ClusterCreate(int dim){
	//checking input
	if (dim <= 0) return NULL;
	PCluster newCluster = (PCluster)malloc(sizeof(Cluster));
	if (newCluster == NULL) return NULL;
	newCluster->dimension = dim;
	newCluster->pointsList = ListCreate(clonePoint,destroyPoint,comparePoint,printPoint);
	if (newCluster->pointsList == NULL) return NULL;
	return newCluster;
}// End Of ClusterCreate

void ClusterDestroy(PCluster killCluster){
	//checking input
	if (killCluster == NULL) return;
	ListDestroy(killCluster->pointsList);
	free(killCluster);
}// End Of Point Destroy

void	printPoint(void* point_){
	//checking input
	if (point_ == NULL) return;
	PPoint point = (PPoint)point_;
	PointPrint(point);

} // End Of printPoint

void	destroyPoint(void* point_){
	//checking input
	if (point_ == NULL) return;
	PPoint point = (PPoint)point_;
	PointDestroy(point);
	return;
}// End Of destroyPoint

PElement 	clonePoint(void* source_){
	//checking input
	if (source_ == NULL) return NULL;
	//casting
	PPoint source = (PPoint)source_;
	//allocating memory
	PPoint newPoint = PointCreate(PointGetDimension(source));
	if (newPoint == NULL) return NULL;
	int dimension  = PointGetDimension(source);
	int coordinate = PointGetFirstCoordinate(source);
	Result Status = SUCCESS; // variable for validating PoinAddCoordinate operation
	int i = 0;
	for (i = 0; i<dimension; i++){
		Status = PointAddCoordinate(newPoint,coordinate);
		if (Status == FAIL){
			return NULL;
		}
		else{
			coordinate = PointGetNextCoordinates(newPoint); // moving to the next point
		}

	}
	return (PElement)newPoint;

}// End Of clonePoint

BOOL	comparePoint(void* srcA, void* srcB){
	//checking input
	if (srcA == NULL || srcB == NULL) return FALSE;
	//casting
	PPoint sourceA = (PPoint)srcA;
	PPoint sourceB = (PPoint)srcB;
	// checking the numbers of coordinates
	int coordinatesNumA = PointNumCoordinates(sourceA);
	int coordinatesNumB = PointNumCoordinates(sourceB);
	if (coordinatesNumA == -1 || coordinatesNumB == -1) return FALSE;
	if (coordinatesNumA != coordinatesNumB) return FALSE;
	//comparing points
	if (PointGetFirstCoordinate(sourceA)!= PointGetFirstCoordinate(sourceB)) return FALSE; // checking first coordinate
	int i;
	for (i = 1; i<coordinatesNumA ; i++ ){
		if (PointGetNextCoordinates(sourceA) != PointGetNextCoordinates(sourceB)) return FALSE;
	}
	return TRUE;// all coordinates are equal


}

