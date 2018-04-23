#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn\build_config.h>
#include <cppconn\config.h>
#include <cppconn\connection.h>
#include <cppconn\datatype.h>
#include <cppconn\driver.h>
#include <cppconn\exception.h>
#include <cppconn\metadata.h>
#include <cppconn\parameter_metadata.h>
#include <cppconn\prepared_statement.h>
#include <cppconn\resultset.h>
#include <cppconn\resultset_metadata.h>
#include <cppconn\sqlstring.h>
#include <cppconn\statement.h>
#include <cppconn\variant.h>
#include <cppconn\version_info.h>
#include <cppconn\warning.h>

using namespace sql;
using namespace sql::mysql;

namespace SolarSmarts
{
	class Database
	{
	public:
		// Constructor
		SS_INLINE Database()
		{
			this->m_driver.reset(get_mysql_driver_instance());
		}

		SS_INLINE ~Database()
		{
			m_driver.release();
			m_connection.release();
			m_statement.release();
			m_prepared_statement.release();
		}

		SS_INLINE void Connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
		{
			PRINT("Connecting to database...");

			this->m_host = host;
			this->m_user = user;
			this->m_password = password;
			this->m_database = database;

			try 
			{ 
				this->m_connection.reset(this->m_driver->connect(this->m_host, this->m_user, this->m_password));
				if (this->m_connection->isValid()) PRINT("Connection successfully established!");
			}
			catch(sql::SQLException e) 
			{ 
				PRINT("%s", e.getSQLStateCStr());
			}
		}

		SS_INLINE void Disconnect()
		{
			this->m_connection->close();
		}

		SS_INLINE std::shared_ptr< sql::ResultSet > ExecuteQuery(const std::string& query)
		{
			std::shared_ptr< sql::ResultSet > res;
			try
			{
				if (!m_connection->isValid()) return nullptr;

				this->m_statement.reset(this->m_connection->createStatement());
				this->m_statement->execute("USE " + this->m_database);
				res.reset(this->m_statement->executeQuery(query));
			}
			catch (SQLException &e) 
			{
				std::cout << "# ERR: SQLException in " << __FILE__;
				std::cout << "(" << __FUNCTION__ << ") on line " \
					<< __LINE__ << std::endl;
				std::cout << "# ERR: " << e.what();
				std::cout << " (MySQL error code: " << e.getErrorCode();
				std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
			}

			m_statement->close();

			return res;
		}		

		SS_INLINE void InsertWeather(std::vector<std::int64_t> datetime, std::vector<std::int64_t> temperature, std::vector<double> humidity)
		{
			if (temperature.size() != humidity.size() || temperature.size() != datetime.size()) return;

			m_prepared_statement.reset(m_connection->prepareStatement("INSERT INTO DarkSky(Date, Temperature, Humidity) VALUES (?, ?, ?)"));
			
			for (auto i = 0; i < datetime.size(); i++)
			{
				m_prepared_statement->setDateTime(1, stime(datetime.at(i)));
				m_prepared_statement->setDouble(2, temperature.at(i));
				m_prepared_statement->setDouble(3, humidity.at(i));

				m_prepared_statement->executeUpdate();
			}
		}

		SS_INLINE void InsertPrediction(std::vector<std::int64_t> datetime, std::vector<double> future_ghi)
		{
			m_prepared_statement.reset(m_connection->prepareStatement("INSERT INTO Solcast_Forecast(Date, ghi) VALUES (?,?)"));

			for (auto i = 0; i < datetime.size(); i++)
			{
				if (i % 2 != 0)
				{
					m_prepared_statement->setDateTime(1, stime(datetime.at(i)));
					m_prepared_statement->setDouble(2, future_ghi.at(i));

					m_prepared_statement->executeUpdate();
				}
			}
		}
	private:
		std::unique_ptr<sql::mysql::MySQL_Driver> m_driver;
		std::unique_ptr<Connection> m_connection;
		std::unique_ptr<Statement> m_statement;
		std::unique_ptr<PreparedStatement> m_prepared_statement;

		std::string m_database;
		std::string m_host;
		std::string m_user;
		std::string m_password;
	};
}
