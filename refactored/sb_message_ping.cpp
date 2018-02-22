#include "sb_message_ping.h"

SbMessagePing::SbMessagePing(const BtAddr& to, uint8_t invcode):SbMessage(Ping, to, BtAddr()) {
    push(0x00, 0x04, 0x70, 0x00, invcode, 0x00);
    push(0x00, 0x00, 0x00, 0x01, 0x00, 0x00);
    pushByte(0x00);
    finalize();
}
