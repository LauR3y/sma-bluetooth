#pragma once
#include "bt_addr.h"
#include "message_bytes.h"
#include <iostream>

enum Command {
    L2Packet  = 0x0001,
    Ping      = 0x0002,
    Request   = 0x0003,
    Response  = 0x0004,
    Login1    = 0x0005,
    Error     = 0x0007,
    L2Segment = 0x0008,
    Login2    = 0x000A,
    Login3    = 0x000C,
    Unknown   = 0xFFFF
};

class SbMessage : public MessageBytes {
public:
    static Command getCommandFromBytes(const std::vector<uint8_t>& bytes);
    static SbMessage fromBytes(const std::vector<uint8_t>& bytes);

    SbMessage(Command command, const BtAddr& to, const BtAddr& from);
    SbMessage(const std::vector<uint8_t>& bytes);
    SbMessage(): MessageBytes() {}

    void finalize();

    const BtAddr& getFrom() const { return m_from; }
    const BtAddr& getTo() const { return m_to; }
    const Command& getCommand() const { return m_command; }

private:
    Command m_command = Unknown;
    BtAddr m_to;
    BtAddr m_from;
};

