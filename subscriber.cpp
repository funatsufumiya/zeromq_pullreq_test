#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://localhost:5555");

    while (true) {
        zmq::message_t message;
        auto result = socket.recv(message, zmq::recv_flags::none);
        if (result) {
            std::cout << "Received: " << message.to_string() << std::endl;
        }
    }

    return 0;
}