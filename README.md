OOOCode-Cache
=============

OOOCode Cache interface for named lumps of data.

## Features

- Should expose a cache interface
- Should implement a test cache
- OOOTestCache should return the same data pointer that was set in the cache

## API

OOOTestCache class

```C
#include "OOOTestCache.h"

unsigned char aMyData[] =
{
  ...
};
size_t uMyDataSize = sizeof(aMyData)

OOOTestCache * pCache = OOOConstruct(OOOTestCache);
OOOICache * iCache = OOOCast(OOOICache, pCache);

/* set cached data by name */
OOOICall(iCache, set, "MyData", aMyData, uMyDataSize);

...

unsigned char * pData;
size_t uDataSize;

/* get cached data by name */
OOOICall(iCache, get, "MyData", &pData, &uDataSize);
);
```

## Roadmap

- Should notify the owner when the original data is no longer needed
- Should support asynchronous implementations

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