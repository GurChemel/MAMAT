#ifndef _POINT_H_
#define _POINT_H_

typedef struct Point_* PPoint;

PPoint	 	PointCreate(int Dimension);
void 		PointDestroy(PPoint killPoint);
Result 		PointAddCoordinate(PPoint addToPoint, int coordinate);
int 		PointGetFirstCoordinate(PPoint point);
int 		PointGetNextCoordinates(PPoint point);
void 		PointPrint(PPoint printPoint);
int 		PointGetDimension(PPoint point);
int 		PointNumCoordinates(PPoint point);
BOOL		PointCompare(PPoint, PPoint);
int 		PointsDistance(PPoint,PPoint);
//for using with List (Point section)
PElement 	cloneCoordinate(void*);
void 		destroyCoordinate(void*);
BOOL		compareCoordinate(void*, void*);
void		printCoordinate(void*);


#endif
