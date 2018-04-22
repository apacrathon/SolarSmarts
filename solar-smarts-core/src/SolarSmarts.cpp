#include "stdafx.hpp"

// application entry point
int main()
{
	SolarSmarts::Init();
	return 0;
}

namespace SolarSmarts
{
	SS_INLINE void TestDatabase()
	{
		PRINT("Testing MATLAB module...");
		std::shared_ptr<Database> database(new Database);
		database->Connect("solarsmarts.cwspsvjaweae.us-east-2.rds.amazonaws.com", "solar", "solarsmarts", "SolarSmarts");
		database->Disconnect();
		PRINT("Done.");
	}
	
	SS_INLINE void TestMATLAB()
	{
		PRINT("Testing MATLAB module...");
		// Test MATLAB shenanigans
		mclmcrInitialize();	//init matlab environment
		mwArray t = Utils::ReadFile("3YearModelDataFinal.csv");
		PRINT("Done.");
	}
	
	SS_INLINE void TestHttpRequests(std::string DarkSKY_APIKEY, std::string solCast_APIKEY, std::string longitude, std::string latitude)
	{
		PRINT("Testing HTTP module...");

		//Get current UNIX time (We will run this once every morning)
		std::time_t result = std::time(nullptr);
		std::string current_time = std::to_string(result);
		
		//API URLs
		std::string darkSkyURL = "https://api.darksky.net/forecast/[KEY]/[LONGITUDE],[LATITUDE],[TIME]?exclude=currently,minutely,daily,alerts,flags";
		std::string solCastURL = "https://api.solcast.com.au/radiation/forecasts?longitude=[LONGITUDE]&latitude=[LATITUDE]&api_key=[solCast_APIKEY]&format=json";

		//Replacing darkSkyURL with key and time values + coordinates
		size_t key_index = darkSkyURL.find("[KEY]");
		darkSkyURL.replace(key_index, 5, DarkSKY_APIKEY);
		size_t time_index = darkSkyURL.find("[TIME]");
		darkSkyURL.replace(time_index, 6, current_time);
		size_t longitudeIndex = darkSkyURL.find("[LONGITUDE]");
		darkSkyURL.replace(longitudeIndex, 11, longitude);
		size_t latitudeIndex = darkSkyURL.find("[LATITUDE]");
		darkSkyURL.replace(latitudeIndex, 10, latitude);

		//Replacing solCastURL with key value and coordinates
		size_t solCast_APIKEYIndex = solCastURL.find("[solCast_APIKEY]");
		solCastURL.replace(solCast_APIKEYIndex, 16, solCast_APIKEY);
		size_t longitudeIndex2 = solCastURL.find("[LONGITUDE]");
		solCastURL.replace(longitudeIndex2, 11, longitude);
		size_t latitudeIndex2 = solCastURL.find("[LATITUDE]");
		solCastURL.replace(latitudeIndex2, 10, latitude);
	
		//DarkSky Data
		std::vector<double> humidity = {};
		std::vector<double> temperature = {};

		//SolCast Data
		std::vector<double> futureGHI = {};

		//HTTP module for DarkSky
		Utils::Http httpDarkSky;
		httpDarkSky.HttpGet(darkSkyURL);
		std::string DarkSkyData = httpDarkSky.GetData();

		//HTTP module for Solcast
		Utils::Http httpSolCast;
		httpSolCast.HttpGet(solCastURL);
		std::string SolCastData = httpSolCast.GetData();

		// Initialize stringstream with the data
		std::stringstream ssDarkSky(DarkSkyData);
		std::stringstream ssSolCast(SolCastData);

		// Create an alias for this namespace to reduce length
		//namespace pt = boost::property_tree; //Mit: Had to remove this because BOOST_FOREACH does not accept a namespace parameter

		// Create a root for both data sources
		boost::property_tree::ptree DarkSkyroot;
		boost::property_tree::ptree SolCastroot;

		// Load the JSON file into the property tree
		boost::property_tree::read_json(ssDarkSky, DarkSkyroot);
		boost::property_tree::read_json(ssSolCast, SolCastroot);

		//DarkSky Data Retrieval
		boost::property_tree::ptree dataArray = DarkSkyroot.get_child("hourly.data");
		
		for (boost::property_tree::ptree::iterator it = dataArray.begin(); it != dataArray.end(); it++)
		{
			boost::property_tree::ptree arrayObject = it->second;

			humidity.push_back(arrayObject.get<double>("humidity", -1));
			temperature.push_back(arrayObject.get<double>("temperature", -1));
		}

		//SolCast Data Retrieval
		boost::property_tree::ptree forecastArray = SolCastroot.get_child("forecasts");

		for (boost::property_tree::ptree::iterator it = forecastArray.begin(); it != forecastArray.end(); it++)
		{
			boost::property_tree::ptree object = it->second;

			futureGHI.push_back(object.get<double>("ghi", -1));

		}
		
		
		//Print DarkSky Result
		for (int i = 0; i < humidity.size(); i++)
		{
			std::cout << "Humidity : " << humidity[i];
			std::cout << " Temperature : " << temperature[i] << std::endl;
		}

		//Print SolCast Data
		std::cout << "SIZE OF SOLCAST DATA IS" << futureGHI.size() << std::endl;
		for (int i = 0; i < futureGHI.size(); i++)
		{
			std::cout << "GHI : " << futureGHI[i] << std::endl;
		}
		

		PRINT("Done.");
	}

	SS_INLINE void Init()
	{
		PRINT("Initializing SolarSmart backend...");	
		
		//TestDatabase();
		//TestMATLAB();

		std::string DarkSKY_APIKEY = "412208de88616c3f6dae1a522da9b7f5";
		std::string solCast_APIKEY = "Q47SrBjYcpmpOle4__48T4w7bwQ5xaVe";
		std::string longitude = "40.526044";
		std::string latitude = "-74.435656";

		TestHttpRequests(DarkSKY_APIKEY,solCast_APIKEY,longitude,latitude);	
	}
}

