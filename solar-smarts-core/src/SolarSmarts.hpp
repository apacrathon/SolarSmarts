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
#include <ctime>
#include <time.h>

// boost
#include <boost\foreach.hpp>
#include <boost\make_shared.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>

#include <boost\algorithm\string.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>

// mcr
#include "mclmcrrt.h"
#include "mclcppclass.h"

//#ifdef _DEBUG
#define PRINT(__fmt__,...) \
	printf("[" __FUNCTION__ "]: " __fmt__ "\n", __VA_ARGS__)
//#else
//#define PRINT(__fmt__,...)
//#endif

namespace SolarSmarts
{
	void Init();
	void MCR_Regress(std::shared_ptr<mwArray>, std::shared_ptr<mwArray>);
}

namespace pt = boost::property_tree;