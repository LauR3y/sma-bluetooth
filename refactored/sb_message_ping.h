#include "bt_addr.h"
#include "sb_message.h"

class SbMessagePing : public SbMessage {
public:
    SbMessagePing(const BtAddr& to);
    SbMessagePing(const std::vector<uint8_t>& bytes);
};
