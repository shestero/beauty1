#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>

#include <CLI/CLI.hpp>
#include <beauty/beauty.hpp>
#include <boost/asio/ip/address.hpp>

#include "GetParams.hpp"

// Business logic example: generate greeting message
std::string logic(std::string_view name) {
    return std::format("Hello, {}!", name);
}

// Log request and response into stdout
void report(const beauty::request& req, std::string_view response) {
    const auto tstamp = std::format("[{:%Y-%m-%d %H:%M:%S}]\t", std::chrono::system_clock::now());
    std::osyncstream cout(std::cout);
    cout << tstamp << " Request: " << req.target() << std::endl;
    cout << tstamp << "Response: " << response << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    // === Command-line / environment configuration ===========================

    CLI::App app{"Beauty server example (above Boost.Beast)"};

    std::string host { "127.0.0.1" };
    app.add_option("-H,--host", host, "Default binding host")
            ->envname("SERVER_HOST")
            ->check([](const std::string& s) -> std::string {
                if (s == "localhost" || s == "0.0.0.0" || s == "::")
                    return {};
                boost::system::error_code ec;
                boost::asio::ip::make_address(s, ec);
                if (ec)
                    return "Invalid IP address";
                return {};
            });
    int port = 8080;
    std::string default_name { "Anonymous" };
    app.add_option("-p,--port", port, "Port number")
            ->envname("SERVER_PORT")
            ->check(CLI::Range(1024, 65535));

    app.add_option("-a,--anonymous", default_name, "Default name")
            ->envname("DEFAULT_NAME");

    CLI11_PARSE(app, argc, argv);

    // === Server setup =======================================================

    beauty::server server;

    // Root endpoint
    server.add_route("/")
            .get([](const auto& /* req */, auto& res) {
                res.body() = "Hi!";
            });

    // Greeting endpoint: /greeting?name=...
    server.add_route("/greeting")
            .get([&default_name](const auto& req, auto& res) {
                GetParams params(req);
                auto name = params.get("name").value_or(default_name);

                auto resp = logic(name);
                report(req, resp);
                res.body() = resp;
            });

    // === Run server =========================================================

    std::cout << "Starting server at " << host << ":" << port << " ..." << std::endl;

    server.listen(port, host);
    server.wait();
}
