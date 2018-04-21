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
	
	SS_INLINE void TestHttpRequests()
	{
		PRINT("Testing HTTP module...");
		// Test curl to see if it works
		Utils::Http http;
		http.HttpGet("https://api.darksky.net/forecast/412208de88616c3f6dae1a522da9b7f5/40.526044,-74.435656");
		std::string data = http.GetData();

		// Initialize stringstream with the data
		std::stringstream ss(data);

		// Create an alias for this namespace to reduce length
		namespace pt = boost::property_tree;

		// Create a root
		pt::ptree root;

		// Load the JSON file into the property tree
		pt::read_json(ss, root);

		// Test the result data
		PRINT("latitude is %lf", root.get<double>("latitude", 0));

		PRINT("Done.");
	}

	SS_INLINE void Init()
	{
		PRINT("Initializing SolarSmart backend...");	
		
		//TestDatabase();
		//TestMATLAB();
		TestHttpRequests();	
	}
}

