#pragma once

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

#ifdef _DEBUG
#define PRINT(__fmt__,...) \
	printf("[" __FUNCTION__ "]: " __fmt__, __VA_ARGS__)
#else
#define PRINT(__fmt__,...)
#endif

namespace SolarSmarts
{
	void Init();
}