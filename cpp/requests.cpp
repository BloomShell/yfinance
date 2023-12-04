#include <requests.h>
#include <structures.h>


namespace Requests {

	static size_t WriteCallback(
		void* contents, 
		size_t size, 
		size_t nmemb, 
		void* userp
	)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	};

	Structures::Response Requests(
		std::string&& url,
		const payload&& params
	) {
		CURL* curl = curl_easy_init();
		std::string responseBuffer;
		long response_code;
		if (params.size() > 0) {
			url += '?';
			for (auto& [key, val] : params)
				url += '&' + key + '=' + val;
		}
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
			curl_easy_perform(curl);
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_cleanup(curl);
		};

		return Structures::Response(
			std::move(responseBuffer), 
			std::move(response_code)
		);
	}

}