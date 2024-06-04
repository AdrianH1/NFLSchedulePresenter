#include "CHttpClient.hpp"
#include "libs/nlohmann/json.hpp"
#include <asio.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <regex>
#include <chrono>

//------------------------------------------------------------------
CHttpClient::CHttpClient(const std::string& address, int port)
    : address_(address), port_(port), endpoint_(asio::ip::make_address(address, ec_), port),
    socket_(context_) {}

//------------------------------------------------------------------
void CHttpClient::start() {
    if (!requests_.empty()) {
        processNextRequest();
        context_.run();
    }
}

//------------------------------------------------------------------
void CHttpClient::addRequest(const std::string& url, const std::string& filename) {
    requests_.emplace(url, filename);
}

//------------------------------------------------------------------
void CHttpClient::processNextRequest() {
    if (requests_.empty()) {
        return;
    }

    currentRequest_ = requests_.front();
    requests_.pop();

    vBuffer_Body_.clear();
    headerProcessed_ = false;
    headerBuffer_.clear();

    // Ensure the socket is closed before starting a new request
    if (socket_.is_open()) {
        socket_.close();
    }

    socket_ = asio::ip::tcp::socket(context_);
    socket_.connect(endpoint_, ec_);

    if (!ec_) {
        std::string sRequest =
            "GET " + currentRequest_.first + " HTTP/1.1\r\n"
            "Host: sports.core.api.espn.com\r\n"
            "Connection: close\r\n\r\n";

        socket_.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec_);
        grabSomeData();
    }
    else {
        std::cout << "Failed to connect: " << ec_.message() << std::endl;
    }
}

//------------------------------------------------------------------
void CHttpClient::grabSomeData() {
    auto vBuffer = std::make_shared<std::vector<char>>(1024);
    socket_.async_read_some(asio::buffer(vBuffer->data(), vBuffer->size()),
        [this, vBuffer](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "\n\nRead " << length << " bytes\n\n";
                handleRead(*vBuffer, length);
            }
            else if (ec == asio::error::eof) {
                // Connection closed cleanly by peer
                std::cout << "Connection closed by server.\n";
                saveToFile();
                processNextRequest();
            }
            else {
                std::cout << "Error: " << ec.message() << std::endl;
            }
        }
    );
}

//------------------------------------------------------------------
void CHttpClient::handleRead(const std::vector<char>& vBuffer, std::size_t length) {
    std::string data(vBuffer.data(), length);

    if (!headerProcessed_) {
        headerBuffer_ += data;
        std::size_t headerEnd = headerBuffer_.find("\r\n\r\n");
        if (headerEnd != std::string::npos) {
            headerProcessed_ = true;
            std::string body = headerBuffer_.substr(headerEnd + 4);
            vBuffer_Body_.emplace_back(body);
            headerBuffer_ = headerBuffer_.substr(0, headerEnd);
        }
    }
    else {
        vBuffer_Body_.emplace_back(data);
    }

    grabSomeData();
}

//------------------------------------------------------------------
void CHttpClient::saveToFile() {
    std::ofstream tempFile(currentRequest_.second);
    for (const auto& s : vBuffer_Body_) {
        tempFile << s;
    }
    tempFile.close();


    // Load the file and extract the JSON content
    std::ifstream ifs(currentRequest_.second);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string fileContent = buffer.str();

    if (currentRequest_.second.find("eventDetails") != std::string::npos)
    {
        std::size_t start = fileContent.find('{');
        std::size_t end = fileContent.rfind('}');
        std::string jsonString = fileContent.substr(start, end + 1);
        try
        {
            auto json_stream = nlohmann::json::parse(jsonString);
            std::cout << json_stream.at("name") << std::endl;
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cout << "exception in " << currentRequest_.second << std::endl;
            std::cerr << e.what() << '\n';
        }

        return;
    }

    std::ofstream finalFile(currentRequest_.second);
    // Extract JSON using regex (assuming JSON starts with '{' and ends with '}')
    std::regex jsonRegex(R"(\{.*\})", std::regex::extended);
    std::smatch match;
    if (std::regex_search(fileContent, match, jsonRegex)) {
        std::string jsonString = match.str();
        auto json_stream = nlohmann::json::parse(jsonString);
        finalFile << json_stream;
        std::cout << json_stream.at("$meta") << std::endl;
    }
    else {
        std::cout << "No JSON content found in the response." << std::endl;
    }
}