#include "OOOUnitTestDefines.h"
#include "OOOTestCache.h"

static char * szHelloWorld = "Hello, world!";
static char * szGoodbyeWorld = "Goodbye, world!";
static char * szApple = "Apple";
static char * szBanana = "Banana";
static char * szPear = "Pear";

#define OOOClass TestData
OOODeclare(char * szName, char * szError, unsigned char * pData, size_t uSize)
	OOOImplements
		OOOImplement(OOOICacheData)
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, wasChecked)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	char * szName;
	char * szError;
	unsigned char * pData;
	size_t uSize;
	bool bChecked;
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(char *, getName)
	return OOOF(szName);
OOOMethodEnd

OOOMethod(unsigned char *, getData)
	return OOOF(pData);
OOOMethodEnd

OOOMethod(size_t, getSize)
	return OOOF(uSize);
OOOMethodEnd

OOOMethod(void, cached, OOOIError * iError)
	if (OOOF(szError))
	{
		if (OOOCheck(iError != NULL))
		{
			OOOCheck(O_strcmp(OOOICall(iError, toString), OOOF(szError)) == 0);
		}
	}
	else
	{
		OOOCheck(iError == NULL);
	}
	OOOF(bChecked) = TRUE;
OOOMethodEnd

OOOMethod(bool, wasChecked)
	return OOOF(bChecked);
OOOMethodEnd

OOOConstructor(char * szName, char * szError, unsigned char * pData, size_t uSize)
#define OOOInterface OOOICacheData
	OOOMapVirtuals
		OOOMapVirtual(getName)
		OOOMapVirtual(getData)
		OOOMapVirtual(getSize)
		OOOMapVirtual(cached)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(wasChecked)
	OOOMapMethodsEnd

	OOOF(szName) = szName;
	OOOF(szError) = szError;
	OOOF(pData) = pData;
	OOOF(uSize) = uSize;
OOOConstructorEnd
#undef OOOClass

static void set(OOOICache * iCache, char * szName, char * szError, unsigned char * pData, size_t uSize)
{
	TestData * pTestData = OOOConstruct(TestData, szName, szError, pData, uSize);
	OOOICall(iCache, set, OOOCast(OOOICacheData, pTestData));
	OOOCheck(OOOCall(pTestData, wasChecked));
	OOODestroy(pTestData);
}

OOOTest(OOOTestCache)
{
	char * szBuffer;
	size_t uSize;
	OOOTestCache * pCache = OOOConstruct(OOOTestCache);
	OOOICache * iCache = OOOCast(OOOICache, pCache);

	/* Should error if an invalid name is used */
	set(iCache, NULL, "INVALID NAME", (unsigned char *) szHelloWorld, O_strlen(szHelloWorld) + 1);

	/* Should be able to set and get cached data by name */
	set(iCache, "HelloWorld", NULL, (unsigned char *) szHelloWorld, O_strlen(szHelloWorld) + 1);
	set(iCache, "GoodbyeWorld", NULL, (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);
	set(iCache, "Apple", NULL, (unsigned char *) szApple, O_strlen(szApple) + 1);
	set(iCache, "Banana", NULL, (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	set(iCache, "Pear", NULL, (unsigned char *) szPear, O_strlen(szPear) + 1);

	OOOCall(pCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szHelloWorld);
	OOOCheck(uSize == O_strlen(szHelloWorld) + 1);

	OOOCall(pCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szGoodbyeWorld);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);

	OOOCall(pCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szApple);
	OOOCheck(uSize == O_strlen(szApple) + 1);

	OOOCall(pCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szBanana);
	OOOCheck(uSize == O_strlen(szBanana) + 1);

	OOOCall(pCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szPear);
	OOOCheck(uSize == O_strlen(szPear) + 1);

	/* Should be able to overwrite entries in the cache */
	set(iCache, "Apple", NULL, (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	set(iCache, "Pear", NULL, (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);

	OOOCall(pCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szHelloWorld);
	OOOCheck(uSize == O_strlen(szHelloWorld) + 1);

	OOOCall(pCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szGoodbyeWorld);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);

	OOOCall(pCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szBanana);
	OOOCheck(uSize == O_strlen(szBanana) + 1);

	OOOCall(pCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szBanana);
	OOOCheck(uSize == O_strlen(szBanana) + 1);

	OOOCall(pCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szGoodbyeWorld);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);

	/* Should return NULL when entry is not in the cache */
	OOOCall(pCache, get, "Nothing", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	/* Should be possible to delete an entry from the cache by passing in NULL */
	set(iCache, "HelloWorld", NULL, NULL, 0);
	set(iCache, "Banana", NULL, NULL, 0);

	OOOCall(pCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	OOOCall(pCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szGoodbyeWorld);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);

	OOOCall(pCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szBanana);
	OOOCheck(uSize == O_strlen(szBanana) + 1);

	OOOCall(pCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	OOOCall(pCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == szGoodbyeWorld);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);

	OOODestroy(pCache);
}
