#ifndef OOOICache_H
#define OOOICache_H

#include "OOOCode.h"
#include "OOOICacheData.h"

#define OOOInterface OOOICache
OOOVirtuals
	OOOVirtual(void, set, OOOICacheData * iCacheData)
OOOVirtualsEnd
#undef OOOInterface

#endif
