#ifndef OOOICache_H
#define OOOICache_H

#include "OOOCode.h"

#define OOOInterface OOOICache
OOOVirtuals
	OOOVirtual(void, set, char * szName, unsigned char * pData, size_t uSize)
OOOVirtualsEnd
#undef OOOInterface

#endif
