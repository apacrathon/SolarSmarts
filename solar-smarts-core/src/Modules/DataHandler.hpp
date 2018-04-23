#pragma once

namespace SolarSmarts
{
	class DataHandler : public Module
	{
	public:
		DataHandler();
		std::string ModuleName() { return "DataHandler"; }

	private:
		SS_INLINE static void UpdateWeatherData(const std::string & apikey, const std::string & latitude, const std::string & longitude, const std::time_t & date_max, const std::time_t & date_min);
		SS_INLINE static void UpdatePredictionData(const std::string& apikey, const std::string& latitude, const std::string& longitude, const std::time_t & date_max, const std::time_t & date_min);

		static std::unique_ptr<Http> m_request_handler;
		static std::unique_ptr<Database> m_database;
	};
}