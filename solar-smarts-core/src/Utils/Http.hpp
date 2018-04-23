#pragma once

// temporarily included all for testing
#include <curl.h>
#include <curlver.h>
#include <easy.h>
#include <mprintf.h>
#include <multi.h>
#include <system.h>

namespace SolarSmarts
{
	class Http
	{
	public:
		SS_INLINE void HttpGet(const std::string& URL)	// @TODO: add result code checks
		{
			if (this->Init())
			{
				curl_easy_setopt(this->m_curl, CURLOPT_URL, URL.c_str());	// set url
				curl_easy_setopt(this->m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);	// set callback
				curl_easy_setopt(this->m_curl, CURLOPT_WRITEDATA, &result_buffer);	// set callback buffer
				m_result = std::make_shared<CURLcode>(curl_easy_perform(this->m_curl));

				if (*m_result != CURLE_OK)
					PRINT("%s", curl_easy_strerror(*m_result));

				// clean up	
				curl_easy_cleanup(this->m_curl);
				curl_global_cleanup();
			}
			else
			{
				PRINT("Internal http GET method failed.");
			}
		}
			
		SS_INLINE std::string GetData()
		{
			return result_buffer;
		}

		SS_INLINE void ResetData()
		{
			result_buffer = "";
		}
	private:
		std::string result_buffer;
		std::shared_ptr<CURLcode> m_result;
		CURL* m_curl;

		SS_INLINE bool Init()
		{
			curl_global_init(CURL_GLOBAL_DEFAULT); // Set up the program environment for libcurl
			this->m_curl = curl_easy_init();

			if (!this->m_curl) return false;
			//PRINT("Initialized v%s", curl_version());
			return true;
		}
			
		SS_INLINE static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string& data)
		{
			data.append((char*)ptr, size * nmemb);
			return size * nmemb;
		}
	};
}
