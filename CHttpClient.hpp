#pragma once

#include <vector>
#include <string>
#include <queue>

#define ASIO_STANDALONE
#include <asio.hpp>

class CHttpClient
{
public:
    CHttpClient(const std::string& address, int port);
    void start();
    void addRequest(const std::string& url, const std::string& filename);

private:
    void grabSomeData();
    void handleRead(const std::vector<char>& vBuffer, std::size_t length);
    void processNextRequest();
    void saveToFile();

    std::string address;
    int port;
    asio::error_code ec;
    asio::io_context context;
    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::socket socket;
    std::vector<std::string> vBufferBody{ 20 * 1024 };
    std::queue<std::pair<std::string, std::string>> requests;
    std::pair<std::string, std::string> currentRequest;
    bool headerProcessed = false;
    std::string headerBuffer;
};