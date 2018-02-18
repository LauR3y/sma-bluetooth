#include "sb_message.h"
#include "sb_message_ping.h"
#include "sb_message_request.h"
#include <iostream>
#include <iomanip>

Command SbMessage::getCommandFromBytes(const std::vector<uint8_t>& bytes) {
    return static_cast<Command>((bytes[16] << 8) + bytes[17]);
}

SbMessage SbMessage::fromBytes(const std::vector<uint8_t>& bytes) {
    Command cmd = getCommandFromBytes(bytes);
    switch(cmd) {
        case Ping: return SbMessagePing(bytes);
        case Request: return SbMessageRequest(bytes);
        default: return SbMessage(bytes);
    }
}

SbMessage::SbMessage(Command command, const BtAddr& to, const BtAddr& from) : m_command(command), m_to(to), m_from(from) {
    m_message.push_back(0x7e); // Always 0x7e
    m_message.push_back(0x00); // Length sent in finish
    m_message.push_back(0x00);
    m_message.push_back(0x00); // XOR of bytes 0..3
    push(from.asBytes());
    push(to.asBytes());
    push(command);
}

SbMessage::SbMessage(const std::vector<uint8_t>& bytes) : m_message(bytes) {
    m_command = getCommandFromBytes(bytes);
    m_to = BtAddr(bytes, 4);
    m_from = BtAddr(bytes, 10);
}

void SbMessage::finalize() {
    m_message[1] = m_message.size();
    m_message[3] = m_message[0] ^ m_message[1] ^ m_message[2];
}

void SbMessage::push(const std::vector<uint8_t>& bytes) {
    m_message.insert(m_message.end(), bytes.begin(), bytes.end());
}

void SbMessage::push(uint8_t byte) {
    m_message.push_back(byte);
}

void SbMessage::push(Command command) {
    m_message.push_back((command&0xff00)>>8);
    m_message.push_back((command&0x0ff));
}

const std::vector<uint8_t>& SbMessage::get() const {
    return m_message;
}

std::ostream& operator<<(std::ostream& os, const SbMessage& message) {
    int i = 0;
    for (uint8_t byte : message.get()) {
	    os << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)byte << " ";
	    ++ i;
	    if (i%8 == 0) os << std::endl;
    }
    if (i%8 == 0) os << std::endl;
    return os;
}
