#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#include <curl/curl.h>
#include <string>
#include <unordered_map>
#include <structures.h>
using payload = std::unordered_map<std::string, std::string>;
static const /*const*/ char* USER_AGENT = 
 	"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36";



namespace Requests {

	static size_t WriteCallback(
		void* contents, size_t size, size_t nmemb, void* userp
	);

	Structures::Response Requests(
		std::string&& url,
		const payload&& params = {}
	);

}
#endif // #ifndef _REQUESTS_H_