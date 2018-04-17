#pragma once

namespace SolarSmarts
{
	namespace Utils
	{
		static void ReadFile(const std::string& filename)
		{
			std::vector<double> data =
			{
				573,		736,		856,		930,
				477.289,	660.436,	798.072,	883.815,
				76.24,		79.23,		83.22,		85.93,
				0.75,		0.68,		0.62,		0.58,
			};
				
			mwArray C(4, 4, mxDOUBLE_CLASS, mxREAL); // matrix constructor
			C.SetData(&data[0], data.size());
			
			Regression r;
			r.SetInput(C);
			r.run_main(0, NULL);	
			mwArray result = r.GetOutput();
			
			std::cout << "Result dimension: " << result.GetDimensions();
		}
	}
}
