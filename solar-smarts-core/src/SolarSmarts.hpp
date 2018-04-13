#pragma once

// std
#include <map>
#include <array>
#include <mutex>
#include <random>
#include <string>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include <unordered_map>

// boost
#include <boost\make_shared.hpp>

//#ifdef _DEBUG
#define PRINT(__fmt__,...) \
	printf("[" __FUNCTION__ "]: " __fmt__ "\n", __VA_ARGS__)
//#else
//#define PRINT(__fmt__,...)
//#endif

//using namespace Utils;

namespace SolarSmarts
{
	void Init();
}