#pragma once
#include "bt_addr.h"
#include "sb_connection.h"
#include "sb_message.h"

class SbContext {
public:
    SbContext(const BtAddr& addr);
    SbContext(const std::string& addr);

    SbContext connect();
    SbContext ping();
    SbContext request();

    void updateMyAddr(const SbMessage& message);

    void send(const SbMessage& message);
    SbMessage receive();
    SbMessage waitFor(Command command);
        
private:
    BtAddr       m_sbAddr;
    uint8_t      m_invCode;
    BtAddr       m_myAddr;
    SbConnection m_connection;
};

