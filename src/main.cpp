#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/system/error_code.hpp>

#include <iomanip>
#include <iostream>
#include <thread>

namespace beast = boost::beast;
using tcp = boost::asio::ip::tcp;

void Log(std::string where, boost::system::error_code ec)
{
    std::cerr << "[" << std::setw(20) << where << "] "
              << (ec ? "Error: " : "OK")
              << (ec ? ec.message() : "")
              << std::endl;
}

int main()
{
    std::string url {"ltnm.learncppthroughprojects.com"};
    std::string port {"80"};
    std::string message {"Hello Websocket"};
    
    // Always start with an I/O context object.
    boost::asio::io_context ioc {};
    
    // Under the hood, socket.connect uses I/O context to talk to the socket
    // and get a response back. The response is saved in ec.
    boost::system::error_code ec {};

    // Resolve the endpoint.
    tcp::resolver resolver {ioc};
    auto resolveIt {
        resolver.resolve(url, port, ec)
    };
    if (ec) {
        Log("resolver.resolve", ec);
        return -1;
    }
    
    // Connect TCP socket.
    tcp::socket socket {ioc};
    socket.connect(*resolveIt, ec);
    if (ec) {
        Log("socket.connect", ec);
        return -2;
    }
    
    // Tie the socket object to the WebSocket stream and attempt an handshake.
    beast::websocket::stream<boost::beast::tcp_stream> ws {std::move(socket)};
    ws.handshake(url, "/echo", ec);
    if (ec) {
        Log("ws.handshake", ec);
        return -3;
    }

    // Tell the WebSocket object to exchange messages in text format.
    ws.text(true);
    
    // Send a message to the connected WebSocket server.
    boost::asio::const_buffer wbuffer {message.c_str(), message.size()};
    ws.write(wbuffer, ec);
    if (ec) {
        Log("ws.write", ec);
        return -4;
    }
    
    boost::beast::flat_buffer rbuffer {};
    ws.read(rbuffer, ec);
    if (ec) {
        Log("ws.read", ec);
        return -5;
    }
    
    // Print the echoed message.
    std::cout << "ECHO: "
              << boost::beast::make_printable(rbuffer.data())
              << std::endl;

    Log("returning", ec);

    return 0;
}
