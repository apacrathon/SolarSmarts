#include "stdafx.hpp"

// application entry point
int main()
{
	SolarSmarts::Init();
	return 0;
}

namespace SolarSmarts
{
	void Init()
	{
		PRINT("Initializing SolarSmart backend...");	

		
		std::shared_ptr<Database> database(new Database);	
		database->Connect("solarsmarts.cwspsvjaweae.us-east-2.rds.amazonaws.com", "solar", "solarsmarts", "SolarSmarts");
		PRINT("SUCCESS");
		database->Disconnect();
		
		
		//// Test MATLAB shenanigans
		//mclmcrInitialize();	//init matlab environment
		//mwArray t = Utils::ReadFile("3YearModelDataFinal.csv");

		// Test curl to see if it works
		Utils::Http h;
		h.Test();

		PRINT("DONE");
	}
}

