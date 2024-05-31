#include "CApiReader.hpp"
#include "libs/nlohmann/json.hpp"
#include <asio.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>

CApiReader::CApiReader(const std::string& address, int port)
    : endpoint_(asio::ip::make_address(address, ec_), port),
    socket_(context_) {
    if (!ec_) {
        socket_.connect(endpoint_, ec_);
        if (!ec_) {
            std::cout << "Connected" << std::endl;
        }
        else {
            std::cout << "Not connected: " << ec_.message() << std::endl;
        }
    }
    else {
        std::cout << "Error in address: " << ec_.message() << std::endl;
    }
}

void CApiReader::start() {
    if (socket_.is_open()) {
        grabSomeData();

        std::string sRequest =
            "GET /v2/sports/football/leagues/nfl/events HTTP/1.1\r\n"
            "Host: sports.core.api.espn.com\r\n"
            "Connection: close\r\n\r\n";

        socket_.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec_);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::ofstream myfile("filename.json");
    for (const auto& s : vBuffer_Body_) {
        myfile << s;
    }
    myfile.close();

    std::ifstream ifs("filename.json");
    auto json_stream = nlohmann::json::parse(ifs);
    std::cout << json_stream.at("$meta");

    context_.stop();
    if (thrContext_.joinable()) thrContext_.join();
}

void CApiReader::grabSomeData() {
    auto vBuffer = std::make_shared<std::vector<char>>(1024);
    socket_.async_read_some(asio::buffer(vBuffer->data(), vBuffer->size()),
        [this, vBuffer](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "\n\nRead " << length << " bytes\n\n";
                handleRead(*vBuffer, length);
            }
        }
    );
}

void CApiReader::handleRead(const std::vector<char>& vBuffer, std::size_t length) {
    std::string data(vBuffer.data(), length);
    static bool headerProcessed = false;
    static std::string headerBuffer;

    if (!headerProcessed) {
        headerBuffer += data;
        std::size_t headerEnd = headerBuffer.find("\r\n\r\n");
        if (headerEnd != std::string::npos) {
            headerProcessed = true;
            std::string body = headerBuffer.substr(headerEnd + 4);
            vBuffer_Body_.emplace_back(body);
        }
    }
    else {
        vBuffer_Body_.emplace_back(data);
    }

    grabSomeData();
}