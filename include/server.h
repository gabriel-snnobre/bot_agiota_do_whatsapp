#pragma once

#include "httplib.h"

void postHandler(const httplib::Request &req, httplib::Response &res);
void getHandler(const httplib::Request &req, httplib::Response &res);
void start_server(int port);
