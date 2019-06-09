#pragma once
#include "message_bytes.h"
#include "bt_addr.h"

class SbL2Packet : public MessageBytes {
public:
    SbL2Packet(const MessageBytes& mySusyId, const MessageBytes& mySerial, const std::string& password);   
    SbL2Packet& finalize();

private:
    void addEscapes();
    uint16_t calculateFCS();
};
