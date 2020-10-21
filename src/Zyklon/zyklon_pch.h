#ifndef __ZYKLON_PCH_H__
#define __ZYKLON_PCH_H__

/*
 * precompiled header header for zyklon implemented with cmake
 */

//--------------------------------------
// STL HEADERS AND DATA STRUCTURES
//--------------------------------------
#include <memory>

#include <utility>

#include <algorithm>

#include <functional>

#include <string>

#include <vector>

#include <unordered_map>

#include <unordered_set>

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Log.h"

// ------------------------------------------
// VENDOR FILES
// ------------------------------------------
#include <debugbreak.h>

#ifdef ZYKLON_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#endif // __ZYKLON_PCH_H__