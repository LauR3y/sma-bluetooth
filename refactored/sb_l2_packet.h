#pragma once
#include "message_bytes.h"
#include "bt_addr.h"

class SbL2Packet : public MessageBytes {
public:
    SbL2Packet(const BtAddr& to, const BtAddr& from, const MessageBytes& mySusyId, const MessageBytes& mySerial);    
};
