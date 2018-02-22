#include "message_bytes.h"
#include <iostream>
#include <iomanip>

MessageBytes::MessageBytes(const std::vector<uint8_t>& bytes) : m_message(bytes) {
}

MessageBytes::MessageBytes(uint8_t value) {
    push(value);
}

MessageBytes::MessageBytes(uint8_t value1, uint8_t value2) {
    push(value1, value2);
}

MessageBytes::MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3) {
    push(value1, value2, value3);
}

MessageBytes::MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4) {
    push(value1, value2, value3, value4);
}

MessageBytes::MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5) {
    push(value1, value2, value3, value4, value5);
}

MessageBytes::MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5, uint8_t value6) {
    push(value1, value2, value3, value4, value5, value6);
} 

MessageBytes::MessageBytes(uint16_t value) {
    push(value);
}

void MessageBytes::push(const std::vector<uint8_t>& bytes) {
    m_message.insert(m_message.end(), bytes.begin(), bytes.end());
}

void MessageBytes::push(uint8_t byte) {
    m_message.push_back(byte);
}

void MessageBytes::push(uint8_t value1, uint8_t value2) {
    push(std::vector<uint8_t>({value1, value2}));
}

void MessageBytes::push(uint8_t value1, uint8_t value2, uint8_t value3) {
    push(std::vector<uint8_t>({value1, value2, value3}));
}

void MessageBytes::push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4) {
    push(std::vector<uint8_t>({value1, value2, value3, value4}));
}

void MessageBytes::push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5) {
    push(std::vector<uint8_t>({value1, value2, value3, value4, value5}));
}

void MessageBytes::push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5, uint8_t value6) {
    push(std::vector<uint8_t>({value1, value2, value3, value4, value5, value6}));
}

void MessageBytes::push(uint16_t word) {
    m_message.push_back((word&0xff00)>>8);
    m_message.push_back((word&0x0ff));
}

void MessageBytes::push(uint32_t word) {
    m_message.push_back((uint8_t)((word&0xff000000)>>24));
    m_message.push_back((uint8_t)((word&0x00ff0000)>>16));
    m_message.push_back((uint8_t)((word&0x0000ff00)>>8));
    m_message.push_back((uint8_t)((word&0x000000ff)));
}

const std::vector<uint8_t>& MessageBytes::get() const {
    return m_message;
}

std::ostream& operator<<(std::ostream& os, const MessageBytes& message) {
    int i = 0;
    for (uint8_t byte : message.get()) {
	    os << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)byte << " ";
	    ++ i;
	    if (i%8 == 0) os << std::endl;
    }
    if (i%8 == 0) os << std::endl;
    return os;
}
