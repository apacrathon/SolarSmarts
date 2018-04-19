#pragma once

// temporarily included all for testing
#include <curl.h>
#include <curlver.h>
#include <easy.h>
#include <mprintf.h>
#include <multi.h>
//#include <stdcheaders.h>
#include <system.h>
//#include <typecheck-gcc.h>

namespace SolarSmarts
{
	namespace Utils
	{
		class Http
		{
		public:
			void Test()
			{
				CURL* m_curl = curl_easy_init();
				if (m_curl)	
				{
					PRINT("Initialized %s", curl_version());
				}
			}
		private:
			// use smart pointers to manage curl instance similar to database class.
		};
	}
}