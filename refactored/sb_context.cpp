#include "sb_context.h"
#include "sb_message_ping.h"

class SbContext {
public:
SbContext::SbContext(const BtAddr& addr): m_sbAddr(addr), m_connection(m_sbAddr) {
}

SbContext::SbContext(const std::string& addr): m_sbAddr(addr), m_connection(m_sbAddr) {
}


SbContext SbContext::connect() {
    std::vector<uint8_t> received = receive();

    m_invCode = received[22];
    // send(buildMessage61());

    // received = waitFor(0x5C);

    // m_myAddr = BtAddr(received, 26);

    // send(buildMessage6A());

    // received = waitFor(0x66);
    // double strength = (received[22] * 100.0) / 0xff;
    // std::cout << "Bluetooth signal strength" << std::dec << strength << std::endl;

    // send(buildMessage2A()); 
}

SbContext SbContext::ping() {
    SbMessagePing ping(m_sbAddr, m_invCode);
    send(ping);
}

// std::ostream SbContext::dump(const std::vector<uint8_t>& msg, std::ostream& os) {
// 	int i = 0;
// 	for (uint8_t byte :  msg) {
// 		os << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)byte << " ";
// 		++ i;
// 		if (i%8 == 0) os << std::endl;
// 	}
// 	if (i%8 != 0) os << std::endl;
//     return os;
// }

void SbContext::send(const SbMessage& message) {
	std::cout << "Sending:" << message;
    m_connection.send(message.get());
}

std::vector<uint8_t> SbContext::receive() {
    std::vector<uint8_t> received = m_connection.receive();
	std::cout << "Received:" << std::endl;
    dump(received, std::cout);
    return received;
}

// SbMessage SbContext::buildMessage61() {
// 	std::vector<uint8_t> message = { 
// 		0x7E, 0x1F, 0x00, 0x61,
//         0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00
//  	}; 
// 	m_sbAddr.addToMsg(message);
// 	return append(message, std::vector<uint8_t> last({
//         0x02, 0x00, 0x00, 0x04,
//         0x70, 0x00, invcode, 0x00,
//         0x00, 0x00, 0x00, 0x01,
//         0x00, 0x00, 0x00
//     }));
// }

// std::vector<uint8_t> SbContext::buildMessage6A() {
// 	std::vector<uint8_t> message = { 
// 		0x7E, 0x1F, 0x00, 0x6A,
//         0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00
//  	}; 
// 	m_sbAddr.addToMsg(message);
// 	return append(message, std::vector<uint8_t> last({
//         0x03, 0x00, 0x05, 0x04
//     }));
// }

// std::vector<uint8_t> SbContext::buildMessage2A() {
//     std::vector<uint8_t> message = {
//         0x7E, 0x54, 0x00, 0x2A
//     };
//     m_myAddr.addToMsg(message);//  $ADD2
//     append(message, std::vector<uint8_t> last({
//         0xFF, 0xFF, 0xFF, 0xFF,
//         0xFF, 0xFF, 0x01, 0x00, 
//         0x7E, 0xFF, 0x03, 0x60,
//         0x65, 0x0E, 0xA0, 0xFF,
//         0xFF, 0xFF, 0xFF, 0xFF,
//         0xFF, 0x00, 0x01
//     }));

//     // $MYSUSYID
//     // case 29: // $MYSUSYID
//     // for (i = 0; i < 2; i++)
//     // {
//     //     fl[cc] = conf->MySUSyID[i];
//     //     cc++;
//     // }
//     // break;

//     // $MYSERIAL
//     // case 30: // $MYSERIAL
//     // for (i = 0; i < 4; i++)
//     // {
//     //     fl[cc] = conf->MySerial[i];
//     //     cc++;
//     // }
//     // printf("\n");
//     // break;
//     append(message, std::vector<uint8_t> last({
//         0x00, 0x01, 0x00, 0x00,
//         0x00, 0x00 
//     }));

//     // $CNT
//     // case 25: // $CNT send counter
//     // send_count++;
//     // fl[cc] = send_count;
//     // cc++;
//     // break;
 
//     append(message, std::vector<uint8_t> last({
//        0x80, 0x0C, 0x04, 0xFD,
//        0xFF, 0x07, 0x00, 0x00,
//        0x00, 0x84, 0x03, 0x00,
//        0x00 
//     }));

//     // $TIME 
//     time_t now = time(NULL);
//     // simply need to make this value the correct way around
//     // timestamp 0x5A7F6FCD is sent as CD 6F 7F 5A
//     // perhaps use htonl?

//     append(message, std::vector<uint8_t> last({
//         0x00, 0x00, 0x00, 0x00
//     }))

//     // $PASSWORD
//     // case 19: // $PASSWORD

//     // j = 0;
//     // for (i = 0; i < 12; i++)
//     // {
//     //     if (conf->Password[j] == '\0')
//     //         fl[cc] = 0x88;
//     //     else
//     //     {
//     //         pass_i = conf->Password[j];
//     //         fl[cc] = ((pass_i + 0x88) % 0xff);
//     //         j++;
//     //     }
//     //     cc++;
//     // }
//     // break;
 
//     // $CRC
//     // case 4: //$crc
//     // tryfcs16(flag, fl + 19, cc - 19, fl, &cc);
//     // add_escapes(fl, &cc);
//     // fix_length_send(flag, fl, &cc);
//     // break;
//     message.push_back(0x7E);
// }

// Needs to wait for command
std::vector<uint8_t> SbContext::waitFor(uint8_t type) {
	bool found = false;
	std::vector<uint8_t> message;
	while(!found) {
		message = connection.receive();
		std::cout << "Received:" << std::endl;
		dump(message, std::cout);
		found = (message[3] == type);
	}
    return message;
}


private:
    BtAddr       m_sbAddr;
    uint8_t      m_invCode;
    BtAddr       m_myAddr;
    SbConnection m_connection;
}
