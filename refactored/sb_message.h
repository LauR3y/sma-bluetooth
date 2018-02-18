#pragma once
#include "bt_addr.h"
#include <vector>
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
    Login3    = 0x0C00
};

class SbMessage {
public:
    static Command getCommandFromBytes(const std::vector<uint8_t>& bytes);
    static SbMessage fromBytes(const std::vector<uint8_t>& bytes);

    SbMessage(Command command, const BtAddr& to, const BtAddr& from);
    SbMessage(const std::vector<uint8_t> bytes);

    void finalize();

    void push(const std::vector<uint8_t>& bytes);
    void push(uint8_t value);
    void push(uint16_t value);
    
    const std::vector<uint8_t>& get() const;

    friend std::ostream& operator<< (std::ostream& os, const SbMessage& message);

    const BtAddr& getFrom() const { return m_from; }
    const BtAddr& getTo() const { return m_to; }
    const Command& getCommand() const { return m_command; }

private:
    std::vector<uint8_t> m_message;
    Command m_command;
    BtAddr m_to;
    BtAddr m_from;
};

