#include "sb_message_request.h"

SbMessageRequest::SbMessageRequest(const BtAddr& to): SbMessage(Request, to, BtAddr()) {
    push(std::vector<uint8_t>({0x05, 0x00}));
}
