#include "stdafx.hpp"

// application entry point
int main()
{
	SolarSmarts::Init();
	return 0;
}

namespace SolarSmarts
{
	SS_INLINE void TestMATLAB()
	{
		PRINT("Testing MATLAB module...");
		// Test MATLAB shenanigans
		mclmcrInitialize();	//init matlab environment
		//mwArray t = ReadFile("3YearModelDataFinal.csv");
		PRINT("Done.");
	}
	
	SS_INLINE void Init()
	{
		PRINT("Initializing SolarSmart backend...");
		LoadModule<DataHandler>();
	}
}

