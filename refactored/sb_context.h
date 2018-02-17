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

    void send(const SbMessage& message);
    std::vector<uint8_t> receive();

    // Needs to wait for command
    std::vector<uint8_t> waitFor(uint8_t type);
        
private:
    BtAddr       m_sbAddr;
    uint8_t      m_invCode;
    BtAddr       m_myAddr;
    SbConnection m_connection;
};

