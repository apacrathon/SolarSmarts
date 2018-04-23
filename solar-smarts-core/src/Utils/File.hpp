#pragma once
/*
namespace SolarSmarts
{
	SS_INLINE static double TryGetValue(const std::string& data)
	{
		try { return std::stod(data); }
		catch (std::invalid_argument) { PRINT("unable to parse value: %s", data.c_str()); return 0; }
		catch (std::out_of_range) { PRINT("argument out of range"); return 0; }
	}

	SS_INLINE static mwArray ReadFile(const std::string& filename)
	{
		std::vector<double> ghi, solar_irradiance, temperature, humidity, input;	

		std::ifstream file("X:\\Users\\raj\\Documents\\Spring 2018\\Capstone\\SolarSmarts\\solar-smarts-core\\src\\" + filename);

		if (file.is_open() && file.good())
		{
			PRINT("File is open.");
			while (file.good())
			{
				std::string data = std::string();

				for (std::uint32_t i = 0; i < 4; i++)
					std::getline(file, data, ',');

				double GHIVal = TryGetValue(data);
				if (GHIVal != -1) ghi.push_back(GHIVal);

				for (std::uint32_t i = 0; i < 6; i++)
					std::getline(file, data, ',');

				double SolarIrr = TryGetValue(data);
				if (SolarIrr != -1) solar_irradiance.push_back(SolarIrr);

				for (std::uint32_t i = 0; i < 9; i++)
					std::getline(file, data, ',');

				double Temp = TryGetValue(data);
				if (Temp != -1) temperature.push_back(Temp);

				for (std::uint32_t i = 0; i < 3; i++)
					std::getline(file, data, ',');

				double Humidity = TryGetValue(data);
				if (Humidity != -1) humidity.push_back(Humidity);

				std::getline(file, data, '\n');
			}
			file.close();
		}
		else
		{
			std::cout << "Could not open " + filename;
		}

		input.insert(input.end(), ghi.begin(), ghi.end());
		input.insert(input.end(), temperature.begin(), temperature.end());
		input.insert(input.end(), humidity.begin(), humidity.end());
		input.insert(input.end(), solar_irradiance.begin(), solar_irradiance.end());

		mwArray C(input.size() / 4, 4, mxDOUBLE_CLASS, mxREAL); // matrix constructor
		C.SetData(&input[0], input.size());

		Regression r;
		r.SetInput(C);

		std::cout << ghi.size() << std::endl;

		std::cout << C(1, 1) << std::endl;
		std::cout << C(1, 2) << std::endl;
		std::cout << C(1, 3) << std::endl;
		std::cout << C(1, 4) << std::endl;
		std::cout << C(2, 1) << std::endl;
		std::cout << C(2, 2) << std::endl;
		std::cout << C(2, 3) << std::endl;
		std::cout << C(2, 4) << std::endl;


		r.run_main(0, NULL);	
		mwArray result = r.GetOutput();
		std::cout << "Result dimension: " << result.GetDimensions();
			
		return mwArray(0, 0);
	}
}*/