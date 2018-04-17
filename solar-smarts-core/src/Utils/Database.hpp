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

namespace Utils
{
	class Database
	{
	public:
		// Constructor
		SS_INLINE Database()
		{
			this->m_driver.reset(get_mysql_driver_instance());
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
				PRINT("Connection successfully established.");
			}
			catch(sql::SQLException e) 
			{ 
				PRINT("%s", e.getSQLStateCStr());
			}

			if (this->m_connection->isValid()) PRINT("IM VALID!");
		}

		SS_INLINE void Disconnect()
		{
			this->m_connection->close();
		}

		SS_INLINE std::unique_ptr<ResultSet> ExecuteQuery(const std::string& query)
		{
			if (!m_connection->isValid()) return nullptr;
		
			this->m_statement.reset(this->m_connection->createStatement());
			this->m_statement->execute("USE " + this->m_database);;

			return nullptr;
		}		
	private:
		std::unique_ptr<sql::mysql::MySQL_Driver> m_driver;
		std::unique_ptr<Connection> m_connection;
		std::unique_ptr<Statement> m_statement;

		std::string m_database;
		std::string m_host;
		std::string m_user;
		std::string m_password;
	};
}
