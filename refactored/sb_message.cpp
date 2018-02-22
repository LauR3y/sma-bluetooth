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
    push(0x7e); // Always 0x7e
    push(0x00); // Length sent in finish
    push(0x00);
    push(0x00); // XOR of bytes 0..3
    push(from.asBytes());
    push(to.asBytes());
    push(command);
}

SbMessage::SbMessage(const std::vector<uint8_t>& bytes) : MessageBytes(bytes) {
    m_command = getCommandFromBytes(bytes);
    m_to = BtAddr(bytes, 4);
    m_from = BtAddr(bytes, 10);
}

void SbMessage::finalize() {
    m_message[1] = m_message.size();
    m_message[3] = m_message[0] ^ m_message[1] ^ m_message[2];
}

void SbMessage::push(Command command) {
    push((uint16_t) command);
}
