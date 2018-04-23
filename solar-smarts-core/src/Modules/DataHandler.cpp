#include <stdafx.hpp>
#include "DataHandler.hpp"

namespace SolarSmarts
{
	std::unique_ptr<Database> DataHandler::m_database;
	std::unique_ptr<Http> DataHandler::m_request_handler;

	void DataHandler::UpdateWeatherData(const std::string& apikey, const std::string& latitude, const std::string& longitude, const time_t& date_max, const std::time_t& date_min)
	{
		PRINT("Updating weather data...");
		std::string temp = stime(date_min);
		std::cout << "Date min " << temp << std::endl;

		// storage vectors
		std::vector<std::int64_t> datetime = {};
		std::vector<double> humidity = {};
		std::vector<std::int64_t> temperature = {};

		// Populate API request paramaters
		std::string darksky_uri = "https://api.darksky.net/forecast/[KEY]/[LONGITUDE],[LATITUDE],[TIME]?exclude=currently,minutely,daily,alerts,flags";
		
		boost::replace_first(darksky_uri, "[KEY]", apikey);
		boost::replace_first(darksky_uri, "[LATITUDE]", latitude);
		boost::replace_first(darksky_uri, "[LONGITUDE]", longitude);
		
		for (std::time_t date_current = date_min; date_current < date_max; date_current += 86400)
		{
			std::string dyn_darksky_uri = darksky_uri;
			boost::replace_first(dyn_darksky_uri, "[TIME]", std::to_string(date_current));

			std::cout << dyn_darksky_uri << std::endl;

			// Make the HTTP request
			m_request_handler->HttpGet(dyn_darksky_uri);
			std::string result_json = m_request_handler->GetData();
			m_request_handler->ResetData();	// reset to avoid buffer overflow

			// Use a stringstream to emulate file reading to load JSON into ptree
			std::stringstream ss(result_json);
			pt::ptree pt;
			pt::read_json(ss, pt);

			// Traverse Json
			pt::ptree dataArray = pt.get_child("hourly.data");

			for (pt::ptree::iterator it = dataArray.begin(); it != dataArray.end(); it++)
			{
				pt::ptree arrayObject = it->second;
				if (arrayObject.get<double>("time", -1) > date_min)
				{
					datetime.push_back(arrayObject.get<time_t>("time", -1));
					humidity.push_back(arrayObject.get<double>("humidity", -1));
					temperature.push_back(arrayObject.get<double>("temperature", -1));
				}
			}
		}
		
		// Store in SQL
		auto darksky_max_date = m_database->ExecuteQuery("SELECT Date FROM DarkSky WHERE Date = (SELECT MAX(Date) FROM DarkSky)");
		m_database->InsertWeather(datetime, temperature, humidity);

		PRINT("The database has been updated with new weather data");
	}

	void DataHandler::UpdatePredictionData(const std::string& apikey, const std::string& latitude, const std::string& longitude)
	{
		// This stuff is just split from the weather predictions - Needs to be modified to work like the weather update
		/*
		std::string solcast_uri = "https://api.solcast.com.au/radiation/forecasts?longitude=[LONGITUDE]&latitude=[LATITUDE]&api_key=[KEY]&format=json";

		// Populate API request paramaters
		boost::replace_first(solcast_uri, "[KEY]", apikey);
		boost::replace_first(solcast_uri, "[LONGITUDE]", longitude);
		boost::replace_first(solcast_uri, "[LATITUDE]", latitude);

		// Make the HTTP request
		m_request_handler->HttpGet(solcast_uri);
		std::string result_json = m_request_handler->GetData();

		pt::ptree pt = ParseJson(result_json);

		// storage vector
		std::vector<double> future_ghi = {};

		// Traverse Json
		pt::ptree forecastArray = pt.get_child("forecasts");

		for (pt::ptree::iterator it = forecastArray.begin(); it != forecastArray.end(); it++)
		{
			pt::ptree object = it->second;
			future_ghi.push_back(object.get<double>("ghi", -1));
		}
		*/
	}

	DataHandler::DataHandler()
	{
		m_database.reset(new Database);
		m_request_handler.reset(new Http);

		std::time_t current_time = std::time(nullptr);

		m_database->Connect("solarsmarts.cwspsvjaweae.us-east-2.rds.amazonaws.com", "solar", "solarsmarts", "SolarSmarts");
		
		auto darksky_max_date = m_database->ExecuteQuery("SELECT Date FROM DarkSky WHERE Date = (SELECT MAX(Date) FROM DarkSky)");

		if (darksky_max_date)
		{
			if (darksky_max_date->next())	// only one result is expected from a MAX query
			{
				std::time_t last_time = str_to_time_t(darksky_max_date->getString("Date"));

				if (!IsDateCurrent(last_time))
				{
					PRINT("Weather data is out of date since %s", darksky_max_date->getString("Date").c_str());
					UpdateWeatherData("412208de88616c3f6dae1a522da9b7f5", "-74.435656", "40.526044", current_time, last_time);
				}
				else
				{
					PRINT("Weather data is up to date until %s", darksky_max_date->getString("Date").c_str());
				}
			}
		}
		else
		{
			PRINT("Error getting result.");
		}
	
		auto solcast_max_date = m_database->ExecuteQuery("SELECT Date FROM Solcast_Forecast WHERE Date = (SELECT MAX(Date) FROM Solcast_Forecast)");

		if (solcast_max_date)
		{
			// @TODO!
			// solcast api key Q47SrBjYcpmpOle4__48T4w7bwQ5xaVe
		}
		else
		{
			PRINT("Error getting result.");
		}

		m_database->Disconnect();
	}
}