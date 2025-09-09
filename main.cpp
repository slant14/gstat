#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userdata) {

    size_t total_size = size * nmemb;
    static_cast<std::string*>(userdata)->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = ""; // TODO: fetch from env file, for testing only here

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user/followers");

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Accept: application/vnd.github+json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        headers = curl_slist_append(headers, "X-GitHub-Api-Version: 2022-11-28");
        headers = curl_slist_append(headers, "User-Agent: My-CPP-App"); 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
           std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                nlohmann::json data = nlohmann::json::parse(readBuffer);
                std::cout << "Number of followers: " << data.size() << std::endl;

                for (const auto& follower : data) {
                    std::string username = follower["login"];
                    std::string url = follower["html_url"];
                    std::cout << " - " << username << " (" << url << ")" << std::endl;
                }
            
            } catch (const std::exception& e) {
                std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
            }


        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return 0;
}
