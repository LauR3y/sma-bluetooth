#include "sb_connection.h"
#include "bt_addr.h"
#include <ios>
#include <iostream>
#include <iomanip>

void dump(const std::vector<uint8_t>& msg) {
	int i = 0;
	for (uint8_t byte :  msg) {
		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)byte << " ";
		++ i;
		if (i%8 == 0) std::cout << std::endl;
	}
	if (i%8 != 0) std::cout << std::endl;
}

int main(int argc, const char* argv[]) {
	BtAddr addr("00:80:25:21:19:CA");
	SbConnection connection(addr);

	// Read first message
	std::vector<uint8_t> init = connection.read();
	std::cout << "Received:" << std::endl;
	dump(init);

	// E $INVCODE
	uint8_t invcode = init[22];

	std::cout << "invcode = " << (int)invcode << std::endl;

	// S 7E 1F 00 61 00 00 00 00 00 00 $ADDR 02 00 00 04 70 00 $INVCODE 00 00 00 00 01 00 00 00 $END;
	std::vector<uint8_t> message = { 
		0x7E, 0x1F, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 	}; 
	addr.addToMsg(message);
	std::vector<uint8_t> last({0x02, 0x00, 0x00, 0x04, 0x70, 0x00, invcode, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00});
	message.insert(message.end(), last.begin(), last.end());
	std::cout << "Sending:" << std::endl;
	dump(message);
	connection.write(message);

	// R 7E 22 00 5C $ADDR 00 00 00 00 00 00 05 00 $ADDR $END;
	bool found = false;
	std::vector<uint8_t> response;
	while(!found) {
		response = connection.read();
		std::cout << "Received:" << std::endl;
		dump(response);
		found = (response[3] == 0x5C);
	}
	
	// E $ADD2 $END;

	// Login
	// S 7E 1F 00 61 00 00 00 00 00 00 $ADDR 02 00 00 04 70 00 $INVCODE 00 00 00 00 01 00 00 00

}


// 0x7e 0x1f 0x00 0x61 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x02 0x00 0x00 0x04 0x70 0x00 0x02 0x00
// 0x00 0x00 0x00 0x01 0x00 0x00 0x00

