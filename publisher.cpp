#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::push);
    socket.bind("tcp://*:5555");

    for (int i = 0; ; ++i) {
        std::string msg = "Message " + std::to_string(i);
        zmq::message_t message(msg.data(), msg.size());
        socket.send(message, zmq::send_flags::none);
        std::cout << "Sent: " << msg << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}