#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userdata) {

    size_t total_size = size * nmemb;
    static_cast<std::string*>(userdata)->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int main() {



}
