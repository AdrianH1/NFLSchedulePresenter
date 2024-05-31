#pragma once

#include <vector>
#include <string>

#define ASIO_STANDALONE
#include <asio.hpp>

class CApiReader
{
public:
    CApiReader(const std::string& address, int port);
    void start();

private:
    void grabSomeData();
    void handleRead(const std::vector<char>& vBuffer, std::size_t length);

    asio::error_code ec_;
    asio::io_context context_;
    asio::io_context::work idleWork_{ context_ };
    std::thread thrContext_{ [this]() { context_.run(); } };
    asio::ip::tcp::endpoint endpoint_;
    asio::ip::tcp::socket socket_;
    std::vector<std::string> vBuffer_Body_{ 20 * 1024 };
};