#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userdata) {

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
            std::cout << "Received data:\n" << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return 0;
}
