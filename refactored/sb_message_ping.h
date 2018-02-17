#include "bt_addr.h"
#include "sb_message.h"

class SbMessagePing: SbMessage {
public:
    SbMessagePing(const BtAddr& addr, uint8_t invCode);
};
