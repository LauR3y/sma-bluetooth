#include "sb_connection.h"
#include "bt_addr.h"
#include <ios>
#include <iostream>
#include <iomanip>

void dump(const std::vector<uint8_t>& msg) {
	int i = 0;
	for (uint8_t byte : init) {
		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)byte << " ";
		++ i;
		if (i%8 == 0) std::cout << std::endl;
	}
	if (i%8 != 0) std::cout << std::endl;
}

main(int argc, const char* argv[]) {
	BtAddr addr("00:80:25:21:19:CA")
	SbConnection connection(addr);

	// Read first message
	std::vector<uint8_t> init = connection.read();
	dump(init);

	// E $INVCODE
	int invdode = init[22];

    // S 7E 1F 00 61 00 00 00 00 00 00 $ADDR 02 00 00 04 70 00 $INVCODE 00 00 00 00 01 00 00 00 $END;
	std::vector<uint8_t> message = { 
		0x7E, 0x1F, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 	}; 
	addr.addToMsg(message);
	message.push_back({0x02, 0x00, 0x00, 0x04, 0x70, 0x00, invcode, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00});
	connection.write(message);

    // R 7E 22 00 5C $ADDR 00 00 00 00 00 00 05 00 $ADDR $END;
	std::vector<uint8_t> response = connection.read();
	dump(response);
	
    // E $ADD2 $END;

	// Login
	// 7E 1F 00 61 00 00 00 00 00 00 $ADDR 02 00 00 04 70 00 $INVCODE 00 00 00 00 01 00 00 00

}


// 0x7e 0x1f 0x00 0x61 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x02 0x00 0x00 0x04 0x70 0x00 0x02 0x00
// 0x00 0x00 0x00 0x01 0x00 0x00 0x00

