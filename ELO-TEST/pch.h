//
// pch.h
// Header for standard system include files.
// 
//

#pragma once

#include "gtest/gtest.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

extern "C" {
#include "Lua542/include/lua.h"
#include "Lua542/include/lauxlib.h"
#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua542/liblua54.a")
#endif // _WIN32

using namespace std;

using EloScore = int;
using IDPlayer = int;
using PositionClassification = int;
