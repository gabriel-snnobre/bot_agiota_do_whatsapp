#include "httplib.h"

void getHandler(const httplib::Request &req, httplib::Response &res) {
    std::cout << req.body << '\n';
    res.set_content(req.body + "67", "text/plain");
}

void postHandler(const httplib::Request &req, httplib::Response &res) {
}

void start_server() {
    httplib::Server server;

    server.Get("/", &getHandler);
    server.Post("/", &postHandler);

    server.listen("0.0.0.0", 8080);
}

// [](const httplib::Request &req, httplib::Response &res){} : (req, res) => {}


