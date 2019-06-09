#include "sb_message_request.h"

SbMessageRequest::SbMessageRequest(const BtAddr& to): SbMessage(Request, to, BtAddr()) {
    push(0x05, 0x00);
    finalize();
}
