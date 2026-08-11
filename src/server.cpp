#include "httplib.h"

void getHandler(const httplib::Request &req, httplib::Response &res) {
    auto mode = req.get_param_value("hub.mode");
    auto token = req.get_param_value("hub.verify_token");
    auto challenge = req.get_param_value("hub.challenge");

    if (mode == "subscribe" && token == "letitrip") {
        std::cout << "Webhook verified!" << std::endl
                  << std::flush;
        res.status = 200;
        res.set_content(challenge, "text/plain");
        return;
    }

    std::cout << "Failed request" << std::endl << std::flush;
    res.status = 403;
}

void postHandler(const httplib::Request &req, httplib::Response &res) {
    std::cout << req.body << std::endl << std::flush;

    res.status = 200;
}

void start_server(int port) {
    httplib::Server server;

    server.Get("/", getHandler);
    server.Post("/", postHandler);

    std::cout << std::format("Server up and running on port: {}\n", port) << std::flush;

    server.listen("0.0.0.0", port);
}

// [](const httplib::Request &req, httplib::Response &res){} : (req, res) => {}
