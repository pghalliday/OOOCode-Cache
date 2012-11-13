OOOCode-Cache
=============

OOOCode Cache interface for named lumps of data.

## Features

OOOICache interface

- Should provide a set method to add data to a cache
- Should support asynchronous implementations

OOOTestCache implementation

- Should implement a get method that returns the same data pointer and size that was set

## API

### To implement an OOOICache

MyCache.h

```C
#ifndef OOOMyCache_H
#define OOOMyCache_H

#include "OOOICache.h"

#define OOOClass OOOMyCache
OOODeclare()
	OOOImplements
		OOOImplement(OOOICache)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
```

MyCache.c

```C
#include "OOOMyCache.h"

#define OOOClass OOOMyCache

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, set, OOOICacheData * iCacheData)
{
	/* TODO: Add to the cache */

	/* Notify the cache data instance that caching is complete */
	OOOICall(iCacheData, cached, NULL);
}
OOOMethodEnd

OOOConstructor()
{
#define OOOInterface OOOICache
	OOOMapVirtuals
		OOOMapVirtual(set)
	OOOMapVirtualsEnd
#undef OOOInterface
}
OOOConstructorEnd

#undef OOOClass
```

## Roadmap

- Should be possible to notify the original owner of the data pointer the original data is no longer needed

## Contributing

In lieu of a formal styleguide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality.

## Prerequisites

- OpenTV SDK C2.2 from http://community.opentv.com

## Initialising

This project references sub-modules so after cloning the repository...

```
git submodule init
git submodule update
```

Then the easiest way to work with the project in the OpenTV IDE...

1. Create a new workspace in the root of the project
1. In the IDE choose **File/Import...**
1. In the resulting dialog choose **General/Existing Projects Into Workspace** and press **Next**
1. Choose the **Select Root Directory:** Radio button and **Browse...** to the root of the project
1. A number of projects may be listed under **Projects**
1. Select the projects in the root, deselect those under the submodules folder and then click **Finish**
1. You should then be able to build the OpenTV projects by choosing **Project/Build All**

After you have built the projects at least once run the test application in the Virtual Set top box by...

1. Choosing the **CacheFlow** project on the left
1. Pressing the green **Run** button at the top
1. In the resulting dialog choose **Local OpenTV Application** and press **OK**

## Release History
_(Nothing yet)_

## License
Copyright (c) 2012 Peter Halliday  
Licensed under the MIT license.