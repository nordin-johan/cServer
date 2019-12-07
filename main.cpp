#include <iostream>
#include "server.cpp"

/**
 * main
 *
 * Initialises the server
 */
int main(void) {

	Server server;

	int port;
	std::cout << "Select server port" << std::endl;

	std::cin >> port;

	// fail case
	if (std::cin.fail())
		port = 1000;

	server.init(port);
	return 0;

}