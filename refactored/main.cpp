#include "sb_context.h"
#include "sb_message.h"
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
	SbContext context(addr);
	context.connect();
	context.ping();
	SbMessage login1 = context.waitFor(Login1);
	context.updateMyAddr(login1);
	context.request();
	SbMessage response = context.waitFor(Response);
	context.request();
	response = context.waitFor(Response);
	// Send L2 Packet

	// // Read first message
	// std::vector<uint8_t> init = context.receive();
	// std::cout << "Received:" << std::endl;
	// dump(init);

	// // E $INVCODE
	// uint8_t invcode = init[22];

	// std::cout << "invcode = " << (int)invcode << std::endl;

	// // S 7E 1F 00 61 00 00 00 00 00 00 $ADDR 02 00 00 04 70 00 $INVCODE 00 00 00 00 01 00 00 00 $END;
	// SbMessage message({ 
	// 	0x7E, 0x1F, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 	// });
	// message += addrAsBytes(); 
	// message += std::vector<uint8_t>({0x02, 0x00, 0x00, 0x04, 0x70, 0x00, invcode, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00});
	// std::cout << "Sending:" << std::endl;
	// std::cout << message;
	// connection.send(message.get());

	// // R 7E 22 00 5C $ADDR 00 00 00 00 00 00 05 00 $ADDR $END;
	// bool found = false;
	// std::vector<uint8_t> response;
	// while(!found) {
	// 	response = connection.receive();
	// 	std::cout << "Received:" << std::endl;
	// 	dump(response);
	// 	found = (response[3] == 0x5C);
	// }
	
	// // E $ADD2 $END;
	// BtAddr addr2(response, 26);
	// std::cout << "E $ADD2: " << addr2.toString() << std::endl;

	// Login
	// S 7E 14 00 6A 00 00 00 00 00 00 $ADDR 03 00 05 00 $END;
	// R 7E 18 00 66 $ADDR 00 00 00 00 00 00 04 00 05 00 00 00 $END;
	// E $SIGNAL $END;
	// S 7E 14 00 6A 00 00 00 00 00 00 $ADDR 03 00 05 00 $END;
	// R 7E 18 00 66 $ADDR 00 00 00 00 00 00 04 00 05 00 00 00 $END;
	// S 7E 14 00 6A 00 00 00 00 00 00 $ADDR 03 00 05 00 $END;
	// R 7E 18 00 66 $ADDR 00 00 00 00 00 00 04 00 05 00 00 00 $END;
	// #S 7E 3F 00 41 $ADD2 FF FF FF FF FF FF 01 00 7E FF 03 60 65 09 A0 FF FF FF FF FF FF 00 00 $MYSUSYID $MYSERIAL 00 00 00 00 00 00 $CNT 80 00 02 00 00 00 00 00 00 00 00 00 00 $CRC 7E $END;
	// #S 7E 3B 00 45 $ADD2 FF FF FF FF FF FF 01 00 7E FF 03 60 65 08 A0 FF FF FF FF FF FF 00 03 $MYSUSYID $MYSERIAL 00 03 00 00 00 00 00 80 0E 01 FD FF FF FF FF FF $CRC 7E $END;
	// S 7E 54 00 2A $ADD2 FF FF FF FF FF FF 01 00 7E FF 03 60 65 0E A0 FF FF FF FF FF FF 00 01 $MYSUSYID $MYSERIAL 00 01 00 00 00 00 $CNT 80 0C 04 FD FF 07 00 00 00 84 03 00 00 $TIME 00 00 00 00 $PASSWORD $CRC 7E $END;
	// R 7E 69 00 17 $ADDR $END;
	// E $LOGIN $END;
}


// Received:
// 0x7e 0x1f 0x00 0x61 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x02 0x00 0x00 0x04 0x70 0x00 0x02 0x00
// 0x00 0x00 0x00 0x01 0x00 0x00 0x00
// invcode = 2
// Sending:
// 0x7e 0x1f 0x00 0x61 0x00 0x00 0x00 0x00
// 0x00 0x00 0xca 0x19 0x21 0x25 0x80 0x00
// 0x02 0x00 0x00 0x04 0x70 0x00 0x02 0x00
// 0x00 0x00 0x00 0x01 0x00 0x00 0x00
// Received:
// 0x7e 0x1f 0x00 0x61 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x0a 0x00 0xca 0x19 0x21 0x25 0x80 0x00
// 0x01 0xdf 0xbc 0xeb 0xeb 0x27 0xb8
// Received:
// 0x7e 0x14 0x00 0x6a 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x0c 0x00 0x02 0x00
// Received:
// 0x7e 0x22 0x00 0x5c 0xca 0x19 0x21 0x25
// 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// 0x05 0x00 0xca 0x19 0x21 0x25 0x80 0x00
// 0x01 0x01 0xdf 0xbc 0xeb 0xeb 0x27 0xb8
// 0x02 0x01


