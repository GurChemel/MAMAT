#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"

typedef void* PElement;
typedef struct List_* PList;

typedef PElement (*clone)(PElement);
typedef void (*destroy)(PElement);
typedef BOOL (*compare)(PElement, PElement);
typedef void (*print)(PElement);

PList		ListCreate(clone clFun, destroy deFun, compare coFun, print prFun);
Result		ListAdd(PList list, PElement element);
Result		ListRemove(PList list, PElement element);
void		ListDestroy(PList list);
PElement	ListGetFirst(PList list);
PElement	ListGetNext(PList list);
BOOL		ListCompare(PList list_a, PList list_b);
void		ListPrint(PList list);

#endif
