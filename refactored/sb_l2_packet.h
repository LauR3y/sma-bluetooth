#pragma once
#include "message_bytes.h"
#include "bt_addr.h"

class SbL2Packet : public MessageBytes {
public:
    SbL2Packet(const MessageBytes& mySusyId, const MessageBytes& mySerial, const std::string& password);   
private:
    uint16_t calculateFCS();
};
