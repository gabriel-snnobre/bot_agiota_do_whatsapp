#include "httplib.h"

void getHandler(const httplib::Request &req, httplib::Response &res) {
    auto mode = req.get_param_value("hub.mode");
    auto token = req.get_param_value("hub.verify_token");
    auto challenge = req.get_param_value("hub.challenge");

    std::cout << mode;
    std::cout << token;
    std::cout << challenge;
    std::cout << req.body << std::flush;

    res.set_content(req.body + "Hello World", "text/plain");
}

void postHandler(const httplib::Request &req, httplib::Response &res) {
}

void start_server(int port) {
    httplib::Server server;

    server.Get("/", getHandler);
    server.Post("/", postHandler);

    std::cout << std::format("Server up and running on port: {}\n", port) << std::flush;

    server.listen("0.0.0.0", port);
}

// [](const httplib::Request &req, httplib::Response &res){} : (req, res) => {}
