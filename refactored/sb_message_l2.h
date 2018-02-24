#include "bt_addr.h"
#include "sb_l2_packet.h"
#include "sb_message.h"

class SbMessageL2 : public SbMessage {
public:
    SbMessageL2(const BtAddr& to, const SbL2Packet& packet);
    SbMessageL2(const std::vector<uint8_t>& bytes): SbMessage(bytes) {}
};
