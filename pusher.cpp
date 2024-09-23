#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::push);
    socket.connect("tcp://localhost:5556");

    for (int i = 0; i < 10; ++i) {
        std::string request = "Hello " + std::to_string(i);
        socket.send(zmq::buffer(request), zmq::send_flags::none);
        std::cout << "Sent: " << request << std::endl;

         std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}