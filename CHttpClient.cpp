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
    : address(address), port(port), endpoint(asio::ip::make_address(address, ec), port),
    socket(context) {}

//------------------------------------------------------------------
void CHttpClient::start() {
    if (!requests.empty()) {
        processNextRequest();
        context.run();
    }
}

//------------------------------------------------------------------
void CHttpClient::addRequest(const std::string& url, const std::string& filename) {
    requests.emplace(url, filename);
}

//------------------------------------------------------------------
void CHttpClient::processNextRequest() {
    if (requests.empty()) {
        return;
    }

    currentRequest = requests.front();
    requests.pop();

    vBufferBody.clear();
    headerProcessed = false;
    headerBuffer.clear();

    // Ensure the socket is closed before starting a new request
    if (socket.is_open()) {
        socket.close();
    }

    socket = asio::ip::tcp::socket(context);
    socket.connect(endpoint, ec);

    if (!ec) {
        std::string sRequest =
            "GET " + currentRequest.first + " HTTP/1.1\r\n"
            "Host: sports.core.api.espn.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
        grabSomeData();
    }
    else {
        std::cout << "Failed to connect: " << ec.message() << std::endl;
    }
}

//------------------------------------------------------------------
void CHttpClient::grabSomeData() {
    auto vBuffer = std::make_shared<std::vector<char>>(1024);
    socket.async_read_some(asio::buffer(vBuffer->data(), vBuffer->size()),
        [this, vBuffer](std::error_code ec, std::size_t length) {
            if (!ec) {
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

    if (!headerProcessed) {
        headerBuffer += data;
        std::size_t headerEnd = headerBuffer.find("\r\n\r\n");
        if (headerEnd != std::string::npos) {
            headerProcessed = true;
            std::string body = headerBuffer.substr(headerEnd + 4);
            vBufferBody.emplace_back(body);
            headerBuffer = headerBuffer.substr(0, headerEnd);
        }
    }
    else {
        vBufferBody.emplace_back(data);
    }

    grabSomeData();
}

//------------------------------------------------------------------
void CHttpClient::saveToFile() {
    std::ofstream tempFile(currentRequest.second);
    for (const auto& s : vBufferBody) {
        tempFile << s;
    }
    tempFile.close();


    // Load the file and extract the JSON content
    std::ifstream ifs(currentRequest.second);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string fileContent = buffer.str();

    if (currentRequest.second.find("eventDetails") != std::string::npos)
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
            std::cout << "exception in " << currentRequest.second << std::endl;
            std::cerr << e.what() << '\n';
            addRequest(currentRequest.first, currentRequest.second);
        }

        return;
    }

    std::ofstream finalFile(currentRequest.second);
    // Extract JSON using regex (assuming JSON starts with '{' and ends with '}')
    std::regex jsonRegex(R"(\{.*\})", std::regex::extended);
    std::smatch match;
    if (std::regex_search(fileContent, match, jsonRegex)) {
        std::string jsonString = match.str();
        try
        {
            auto json_stream = nlohmann::json::parse(jsonString);
            finalFile << json_stream;
            std::cout << json_stream.at("$meta") << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "exception in " << currentRequest.second << std::endl;
            std::cerr << e.what() << '\n';
            addRequest(currentRequest.first, currentRequest.second);
        }

    }
    else {
        std::cout << "No JSON content found in the response." << std::endl;
    }
}