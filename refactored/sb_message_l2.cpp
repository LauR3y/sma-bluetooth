#include "sb_message_l2.h"

SbMessageL2::SbMessageL2(const BtAddr& to, const SbL2Packet& packet) : SbMessage(L2Packet, to, BtAddr(0xff)) {
    push(packet);
    finalize();
}
