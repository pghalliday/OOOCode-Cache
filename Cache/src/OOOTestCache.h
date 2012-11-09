#ifndef OOOTestCache_H
#define OOOTestCache_H

#include "OOOCode.h"
#include "OOOICache.h"

#define OOOClass OOOTestCache
OOODeclare()
	OOOImplements
		OOOImplement(OOOICache)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, get, char * szName, unsigned char ** ppData, size_t * pSize)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
