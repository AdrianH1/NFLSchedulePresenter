#include <iostream>
#include <thread>
#include <vector>

#include <chrono>
using namespace std::chrono_literals;

#define ASIO_STANDALONE
#include <asio.hpp>

#include "libs/nlohmann/json.hpp"

std::vector<char> vBuffer(20 * 1024);


void grabSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "\n\nRead " << length << " bytes\n\n";

                for (int i = 0; i < length; i++)
                {
                    std::cout << vBuffer[i];

                    grabSomeData(socket);
                }
            }
        }
    );
}

int main(int argc, char const *argv[])
{
    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&]() { context.run(); });

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("77.109.136.75", ec), 80);
    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.215.14", ec), 80);
    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec)
    {
        std::cout << "Connected" << std::endl;
    }
    else
    {
        std::cout << "not connected" << std::endl;
    }

    if (socket.is_open())
    {
        grabSomeData(socket);

        std::string sRequest =
            "GET /apis/site/v2/sports/football/nfl/scoreboard?dates=2023&seasontype=2&week=1 HTTP/1.1\r\n"
            "Host: site.api.espn.com\r\n"
            // "GET /index.html HTTP/1.1\r\n"
            // "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
    }

    std::this_thread::sleep_for(2000ms);

    context.stop();
    if (thrContext.joinable()) thrContext.join();
}