#include "httplib.h"

void getHandler(const httplib::Request &req, httplib::Response &res) {
    std::cout << req.body << '\n';
    res.set_content(req.body + "Hello World", "text/plain");
}

void postHandler(const httplib::Request &req, httplib::Response &res) {
}

void start_server(int port) {
    httplib::Server server;

    server.Get("/", &getHandler);
    server.Post("/", &postHandler);

    std::cout << std::format("Server up and running on port: %d\n", port);
    server.listen("0.0.0.0", port);
}

// [](const httplib::Request &req, httplib::Response &res){} : (req, res) => {}
