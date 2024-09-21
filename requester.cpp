#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://localhost:5556");

    for (int i = 0; i < 10; ++i) {
        std::string request = "Hello " + std::to_string(i);
        socket.send(zmq::buffer(request), zmq::send_flags::none);
        std::cout << "Sent: " << request << std::endl;

        zmq::message_t reply;
        auto result = socket.recv(reply, zmq::recv_flags::none);
        if (result) {
            std::cout << "Received: " << reply.to_string() << std::endl;
        }
    }

    return 0;
}