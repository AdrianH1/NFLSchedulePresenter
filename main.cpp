#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>

#include <chrono>
using namespace std::chrono_literals;

#define ASIO_STANDALONE
#include <asio.hpp>

#include "libs/nlohmann/json.hpp"

std::vector<char> vBuffer(20 * 1024);
std::vector<std::string> vBuffer_Body(20 * 1024);

// void grabSomeData(asio::ip::tcp::socket& socket)
// {
//     // asio::async_read_until(socket, asio::dynamic_buffer(vBuffer), "\r\n\r\n",
//     //     [&](std::error_code ec, std::size_t length)
//     //     {
//     //         if (!ec)
//     //         {
//     //             std::cout << "\n\nRead " << length << " bytes\n\n";

//     //             for (int i = 0; i < length; i++)
//     //             {
//     //                 std::cout << vBuffer[i];
//     //             }
//     //         }
//     //     }
//     // );


//     socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
//         [&](std::error_code ec, std::size_t length)
//         {
//             if (!ec)
//             {
//                 std::cout << "\n\nRead " << length << " bytes\n\n";

//                 for (int i = 0; i < length; i++)
//                 {
//                     // std::cout << vBuffer[i];
//                     grabSomeData(socket);
//                 }
//             }
//         }
//     );
// }

void grabSomeData(asio::ip::tcp::socket& socket);

void handleRead(asio::ip::tcp::socket& socket, std::vector<char>& vBuffer, std::size_t length) {
    std::string data(vBuffer.data(), length);
    static bool headerProcessed = false;
    static std::string headerBuffer;

    if (!headerProcessed) {
        headerBuffer += data;
        std::size_t headerEnd = headerBuffer.find("\r\n\r\n");
        if (headerEnd != std::string::npos) {
            headerProcessed = true;
            std::string body = headerBuffer.substr(headerEnd + 4);
            // std::cout << "Header:\n" << headerBuffer.substr(0, headerEnd) << "\n";
            // std::cout << "Bodyy:\n" << body << "\n";
            vBuffer_Body.emplace_back(body);
            // Handle the body data as needed, or start processing subsequent reads directly as body.
        }
    }
    else {
        // std::cout << "Body:\n" << data << "\n";
        vBuffer_Body.emplace_back(data);
        // Handle the body data as needed.
    }

    grabSomeData(socket);
}

void grabSomeData(asio::ip::tcp::socket& socket) {
    auto vBuffer = std::make_shared<std::vector<char>>(1024);
    socket.async_read_some(asio::buffer(vBuffer->data(), vBuffer->size()),
        [vBuffer, &socket](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "\n\nRead " << length << " bytes\n\n";
                handleRead(socket, *vBuffer, length);
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

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("54.71.61.211", ec), 80);
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
            "GET /v2/sports/football/leagues/nfl/events HTTP/1.1\r\n"
            "Host: sports.core.api.espn.com\r\n"
            // "GET /index.html HTTP/1.1\r\n"
            // "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
    }

    std::this_thread::sleep_for(2000ms);

    // std::string json_string(vBuffer_Body.begin(), vBuffer_Body.end());

    std::ofstream myfile;
    myfile.open("filename.json");
    for (auto s : vBuffer_Body)
    {
        myfile << s;
    }
    myfile.close();

    std::ifstream ifs("filename.json");
    nlohmann::json json_stream = nlohmann::json::parse(ifs);

    std::cout << json_stream.at("$meta");

    context.stop();
    if (thrContext.joinable()) thrContext.join();
}