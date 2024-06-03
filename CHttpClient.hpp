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

    std::string address_;
    int port_;
    asio::error_code ec_;
    asio::io_context context_;
    asio::ip::tcp::endpoint endpoint_;
    asio::ip::tcp::socket socket_;
    std::vector<std::string> vBuffer_Body_{ 20 * 1024 };
    std::queue<std::pair<std::string, std::string>> requests_;
    std::pair<std::string, std::string> currentRequest_;
    bool headerProcessed_ = false;
    std::string headerBuffer_;
};