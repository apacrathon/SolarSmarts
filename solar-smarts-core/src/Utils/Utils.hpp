#pragma once

namespace SolarSmarts
{
	SS_INLINE bool IsDateCurrent(const std::time_t & time)
	{
		auto clock_now = std::chrono::system_clock::now();
		std::time_t current_time = std::chrono::system_clock::to_time_t(clock_now);
		
		std::array<int, 8> time_parts;

		struct tm *current_time_parts = std::localtime(&current_time);
		
		time_parts[0] = current_time_parts->tm_year;
		time_parts[1] = current_time_parts->tm_mon;
		time_parts[2] = current_time_parts->tm_mday;
		time_parts[3] = current_time_parts->tm_hour;

		struct tm *_time_parts = std::localtime(&time);
		
		time_parts[4] = _time_parts->tm_year;
		time_parts[5] = _time_parts->tm_mon;
		time_parts[6] = _time_parts->tm_mday;
		time_parts[7] = _time_parts->tm_hour;


		if (time_parts[0] == time_parts[4])
			if (time_parts[1] == time_parts[5])
				if (time_parts[2] == time_parts[6])
					if (time_parts[3] == time_parts[7])
						return true;
		
		return false;
	}

	SS_INLINE pt::ptree ParseJson(const std::string& input)
	{
		// Use a stringstream to emulate file reading to load JSON into ptree
		std::stringstream ss(input);
		pt::ptree pt;
		pt::read_json(ss, pt);
		return pt;
	}

	SS_INLINE std::time_t str_to_time_t(const std::string & date) 
	{
		struct tm tm;
		std::istringstream iss(date);
		iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		return mktime(&tm);
	}

	SS_INLINE std::string stime(const time_t & t) {
		std::tm tm = *std::localtime(&t);
		std::stringstream ss;
		ss << std::put_time(&tm, "%F %T");
		return ss.str();
	}
}