#ifndef OOOICacheData_H
#define OOOICacheData_H

#include "OOOCode.h"
#include "OOOIError.h"

#define OOOInterface OOOICacheData
OOOVirtuals
	OOOVirtual(char *, getName)
	OOOVirtual(unsigned char *, getData)
	OOOVirtual(size_t, getSize)
	OOOVirtual(void, cached, OOOIError * iError)
OOOVirtualsEnd
#undef OOOInterface

#endif
