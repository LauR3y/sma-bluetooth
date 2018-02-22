#pragma once
#include "bt_addr.h"
#include "message_bytes.h"
#include <iostream>

enum Command {
    L2Packet  = 0x0100,
    Ping      = 0x0200,
    Request   = 0x0300,
    Response  = 0x0400,
    Login1    = 0x0500,
    Error     = 0x0700,
    L2Segment = 0x0800,
    Login2    = 0x0A00,
    Login3    = 0x0C00,
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

