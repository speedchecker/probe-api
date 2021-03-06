// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------

#include "compiler.h"

#include <stdint.h>
#include <string.h>		// for memcmp
#include <assert.h>
#include <stdlib.h>		// for strtoul

#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <chrono>
#include <limits>		// for numeric_limits

#include <sstream>
#define OSSFMT(expr)	(static_cast<std::ostringstream&>(std::ostringstream() << expr).str())

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

//------------------------------------------------------

// TODO: reference additional headers your program requires here
