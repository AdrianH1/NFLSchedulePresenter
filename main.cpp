#include <iostream>
#include <thread>

#define ASIO_STANDALONE
#include <asio.hpp>

int main(int argc, char const *argv[])
{
    asio::error_code ec;

    asio::io_context context;

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
        std::string sRequest =
            "GET /apis/site/v2/sports/football/nfl/scoreboard?dates=2023&seasontype=2&week=1 HTTP/1.1\r\n"
            // "Host: example.com\r\n"
            "Host: site.api.espn.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);

        size_t bytes = socket.available();
        std::cout << "Bytes available: " << bytes << std::endl;

        if (bytes > 0)
        {
            std::vector<char> vBuffer(bytes);
            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

            for (auto c : vBuffer)
            {
                std::cout << c;
            }
        }

    }
}