#include "sb_connection.h"
#include "bt_addr.h"
#include <ios>
#include <iostream>

main(int argc, const char* argv[]) {
	SbConnection connection(BtAddr("00:80:25:21:19:CA"));
	std::vector<uint8_t> init = connection.read();
	for (uint8_t byte : init) {
		std::cout << std::hex << byte << " ";
	}
	std::cout << std::endl;
}


