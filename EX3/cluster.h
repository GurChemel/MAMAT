#ifndef _CLUSTER_H_
#define _CLUSTER_H_

typedef struct Cluster_* PCluster;

PCluster ClusterCreate(int dim);
void	 ClusterDestroy(PCluster);
Result	 ClusterAddPoint(PCluster, PPoint);
int		 ClusterGetMinDistance(PCluster, PPoint);
void 	 ClusterPrint(PCluster);

PElement 	clonePoint(void* source_);
void 		destroyPoint(void*);
BOOL		comparePoint(void*, void*);
void		printPoint(void*);


#endif
