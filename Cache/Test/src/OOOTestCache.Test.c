#include "OOOUnitTestDefines.h"
#include "OOOTestCache.h"

static char * szHelloWorld = "Hello, world!";
static char * szGoodbyeWorld = "Goodbye, world!";
static char * szApple = "Apple";
static char * szBanana = "Banana";
static char * szPear = "Pear";

OOOTest(OOOTestCache)
{
	char * szBuffer;
	size_t uSize;
	OOOTestCache * pCache = OOOConstruct(OOOTestCache);
	OOOICache * iCache = OOOCast(OOOICache, pCache);

	/* Should be able to set and get cached data by name */
	OOOICall(iCache, set, "HelloWorld", (unsigned char *) szHelloWorld, O_strlen(szHelloWorld) + 1);
	OOOICall(iCache, set, "GoodbyeWorld", (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);
	OOOICall(iCache, set, "Apple", (unsigned char *) szApple, O_strlen(szApple) + 1);
	OOOICall(iCache, set, "Banana", (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	OOOICall(iCache, set, "Pear", (unsigned char *) szPear, O_strlen(szPear) + 1);

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
	OOOICall(iCache, set, "Apple", (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	OOOICall(iCache, set, "Pear", (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);

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
	OOOICall(iCache, set, "HelloWorld", NULL, 0);
	OOOICall(iCache, set, "Banana", NULL, 0);

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
