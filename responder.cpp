#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5556");

    while (true) {
        zmq::message_t request;
        auto result = socket.recv(request, zmq::recv_flags::none);
        if (result) {
            std::cout << "Received: " << request.to_string() << std::endl;
            std::string reply = "World";
            socket.send(zmq::buffer(reply), zmq::send_flags::none);
        }
    }

    return 0;
}