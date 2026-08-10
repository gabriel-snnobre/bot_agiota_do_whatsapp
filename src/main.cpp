#include "dotenv.h"
#include "httplib.h"
#include <curl/curl.h>
#include <iostream>
#include <cstdlib>

namespace Bot {
std::string URL = "https://graph.facebook.com/v25.0/1321969807657106/messages";
std::string DATA = "{\"messaging_product\": \"whatsapp\",\"to\": \"";
std::string DATA_1 = "\",\"type\": \"text\",\"text\": {\"body\": \"";
std::string DATA_END = "\"}}";

CURLcode send_message(CURL *curl, curl_slist *header, std::string number, std::string message) {
    std::string DATA_FINAL = DATA + number + DATA_1 + message + DATA_END;

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, DATA_FINAL.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    return curl_easy_perform(curl);
}
}  // namespace Bot

int main() {
    curl_slist *headers = NULL;
    CURL *curl = curl_easy_init();
    dotenv env(".env");
    httplib::Server svr;


    svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << req.body << '\n';
        res.set_content(req.body + "67", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    headers = curl_slist_append(headers, ("Authorization: Bearer " + env.get("WPP_TOKEN")).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    if (!curl) {
        return 1;
    }


    CURLcode result = Bot::send_message(curl, headers, env.get("NUMBER"), "Bom dia, ignore a próxima mensagem:");
    result = Bot::send_message(curl, headers, env.get("NUMBER"), "Teste hihihi");

    curl_easy_cleanup(curl);

    return 0;
}


