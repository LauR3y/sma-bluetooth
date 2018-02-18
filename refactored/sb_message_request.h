#include "bt_addr.h"
#include "sb_message.h"

class SbMessageRequest : public SbMessage {
public:
    SbMessageRequest(const BtAddr& to);
    SbMessageRequest(const std::vector<uint8_t>& bytes) : SbMessage(bytes) {}
};
