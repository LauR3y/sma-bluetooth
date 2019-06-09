#include "sb_message_l2.h"

SbMessageL2::SbMessageL2(const BtAddr& to, const SbL2Packet& packet) : SbMessage(L2Packet, BtAddr(0xff), to) {
    push(packet);
    finalize();
}
