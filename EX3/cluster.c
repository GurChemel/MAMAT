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

Result	 ClusterAddPoint(PCluster cluster, PPoint point){
	//checking input
	if (cluster == NULL || point == NULL) return FAIL;
	int clusterDim = cluster->dimension;
	int pointDim = PointGetDimension(point);
	if (clusterDim != pointDim) return FAIL;
	PPoint clusterPoint = (PPoint)ListGetFirst(cluster->pointsList); //variable for the while loop, initialized to first point in cluster
	while (clusterPoint != NULL){
		if (PointCompare(clusterPoint, point) == TRUE) return FAIL; // point already exist
		clusterPoint = (PPoint)ListGetNext(cluster->pointsList);
	}
	// if we got here the new point does not exist in the cluster
	Result status = ListAdd(cluster->pointsList, point);
	return status;
}// End of ClusterAddPoint

int		 ClusterGetMinDistance(PCluster cluster, PPoint point){
	if (cluster == NULL || point == NULL) return 1000;
	if (cluster->dimension != PointGetDimension(point)) return 1000; // point has different dimension from cluster
	// initializing variables
	int Distance 	= 1001;
	int minDistance = 1000;
	PPoint clusterPoint = (PPoint)ListGetFirst(cluster->pointsList);
	while (clusterPoint != NULL){
		Distance = PointsDistance(clusterPoint, point);
		if (Distance == 1000) return 1000; // fail to compute distance between two points
		if (Distance < minDistance) minDistance = Distance;
		clusterPoint = (PPoint)ListGetNext(cluster->pointsList);
	}
	return minDistance;
}// End Of ClusterGetMinDistance

void 	 ClusterPrint(PCluster cluster){
	if (cluster == NULL) return;
	int dim = cluster->dimension;
	int minDist = 1000;
	int distance = 1001;
	//initialize pointers
	PPoint pointA = (PPoint)ListGetFirst(cluster->pointsList);
	PPoint pointB = (PPoint)ListGetNext(cluster->pointsList);
	int pointsNumber = ListNumElements(cluster->pointsList);//number of points in cluster
	int pointProgress = 0; // variable to keep track on progress
	while (pointProgress < pointsNumber){
		pointA = (PPoint)ListGetFirst(cluster->pointsList);// reseting the iterator in the list
		int i = 0;
		for (i=0 ; i<pointProgress; i++){
			pointA = (PPoint)ListGetNext(cluster->pointsList); // moving pointA to rellevant location
		}
		pointB = (PPoint)ListGetNext(cluster->pointsList);// setting pointB to one point ahead of pointA
		while (pointB != NULL){
			distance = PointsDistance(pointA,pointB);
			if(distance < minDist) minDist = distance;
			pointB = (PPoint)ListGetNext(cluster->pointsList);
		}
		pointProgress ++ ;
	}// from here minDist should hold the minimum distance value


	printf("Cluster's dimension: %d\n", dim);
	int i =0;
	pointA = (PPoint)ListGetFirst(cluster->pointsList);
	for (i=0;i<pointsNumber;i++){
		printPoint(pointA);
		pointA = (PPoint)ListGetNext(cluster->pointsList);
	}
	printf("\nMinimum Square Distance: %d\n", minDist);

	return;
}

////////// functions for creating  List /////////

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
			coordinate = PointGetNextCoordinates(source); // moving to the next point
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
	return PointCompare(sourceA,sourceB);
}// End of comparePoint




/*BOOL	comparePoint(void* srcA, void* srcB){
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


}*/

