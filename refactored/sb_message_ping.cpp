#include "sb_message_ping.h"

SbMessagePing::SbMessagePing(const BtAddr& addr, uint8_t invCode):SbMessage(0x0200, BtAddr(), addr) {
	*this += std::vector<uint8_t>({0x00, 0x04, 0x70, 0x00, invcode, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00});
    finalize();
}
