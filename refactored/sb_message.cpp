#include "sb_message.h"
#include <iostream>
#include <iomanip>

SbMessage::SbMessage(uint16_t command, const BtAddr& addr1, const BtAddr& addr2) {
    m_message.push_back(0x7e); // Always 0x7e
    m_message.push_back(0x00); // Length sent in finish
    m_message.push_back(0x00);
    m_message.push_back(0x00); // XOR of bytes 0..3
    push(addr1.asBytes());
    push(addr2.asBytes());
    push(command);
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

void SbMessage::push(uint16_t value) {
    uint16_t v = htons(value);
    m_message.push_back((v&0xff00)>>8);
    m_message.push_back((v&0x0ff));
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
