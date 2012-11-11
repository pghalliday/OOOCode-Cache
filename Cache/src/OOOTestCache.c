#include "OOOTestCache.h"
#include "OOOError.h"

#define OOOClass OOOTestCache

typedef struct _Entry Entry;
struct _Entry
{
	char * szName;
	unsigned char * pData;
	size_t uSize;
	Entry * pNext;
};

OOOPrivateData
	Entry * pEntries;
OOOPrivateDataEnd

OOODestructor
{
	Entry * pEntry = OOOF(pEntries);
	Entry * pLast = NULL;
	while (pEntry)
	{
		pLast = pEntry;
		pEntry = pEntry->pNext;
		O_free(pLast->szName);
		O_free(pLast);
	}
}
OOODestructorEnd

OOOMethod(void, set, OOOICacheData * iCacheData)
{
	Entry * pEntry = OOOF(pEntries);
	char * szName = OOOICall(iCacheData, getName);
	unsigned char * pData = OOOICall(iCacheData, getData);
	size_t uSize = OOOICall(iCacheData, getSize);

	if (szName == NULL)
	{
		OOOError * pError = OOOConstruct(OOOError, "INVALID NAME");
		OOOICall(iCacheData, cached, OOOCast(OOOIError, pError));
		OOODestroy(pError);
	}
	else
	{
		if (pData == NULL)
		{
			/* Delete */
			Entry * pLast = NULL;
			while (pEntry)
			{
				if (O_strcmp(pEntry->szName, szName) == 0)
				{
					if (pLast)
					{
						pLast->pNext = pEntry->pNext;
					}
					else
					{
						OOOF(pEntries) = pEntry->pNext;
					}
					O_free(pEntry->szName);
					O_free(pEntry);
					break;
				}
				pLast = pEntry;
				pEntry = pEntry->pNext;
			}
		}
		else
		{
			/* Set */
			while (pEntry)
			{
				if (O_strcmp(pEntry->szName, szName) == 0)
				{
					break;
				}
				pEntry = pEntry->pNext;
			}

			if (!pEntry)
			{
				/* Add */
				pEntry = O_malloc(sizeof(Entry));
				pEntry->pNext = OOOF(pEntries);
				OOOF(pEntries) = pEntry;
				pEntry->szName = O_strdup(szName);
				pEntry->pData = NULL;
				pEntry->uSize = 0;
			}

			pEntry->pData = pData;
			pEntry->uSize = uSize;
		}
		OOOICall(iCacheData, cached, NULL);
	}
}
OOOMethodEnd

OOOMethod(void, get, char * szName, unsigned char ** ppData, size_t * pSize)
{
	Entry * pEntry = OOOF(pEntries);
	*ppData = NULL;
	*pSize = 0;
	while (pEntry)
	{
		if (O_strcmp(pEntry->szName, szName) == 0)
		{
			*pSize = pEntry->uSize;
			*ppData = pEntry->pData;
			break;
		}
		pEntry = pEntry->pNext;
	}
}
OOOMethodEnd

OOOConstructor()
{
#define OOOInterface OOOICache
	OOOMapVirtuals
		OOOMapVirtual(set)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(get)
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
