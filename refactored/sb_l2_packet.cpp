#include "sb_l2_packet.h"
#include <iomanip>

class Fcs16 {
public:
    static Fcs16& instance() {
        if (!m_instance) {
            m_instance = new Fcs16();
        }
        return *m_instance;
    }

    uint16_t calculateFCS(uint8_t* ptr, size_t len) {
        uint16_t fcs = 0xffff; // Initial Fcs
        while(len --) {
            fcs = (fcs >> 8) ^ m_table[(fcs ^ *ptr++) & 0xff];
        }
        return fcs;
    }

private:
    Fcs16() {
        uint16_t v = 0;
        for (int b = 0; b < 256; ++b) {
            v = b;
            for (int i = 8; i > 0; --i) {
                v = v & 1 ? (v >> 1) ^ 0x8408 : (v >> 1);
            }
            m_table[b] = v;
        }
    }

    uint16_t m_table[256];
    static Fcs16* m_instance;
};

Fcs16* Fcs16::m_instance = 0;

SbL2Packet::SbL2Packet(
	const MessageBytes& mySusyId,
       	const MessageBytes& mySerial,
       	const std::string& password
) {
    // See RFC 1662 for details of basic frame format
    // +--------+--------+--------+----------------+------+------+---------+--------+
    // |  FLAG  |  ADDR  |  CTRL  |     PROTOCOL   | Info | Padd |   FCS   |  FLAG  |
    // |01111110|11111111|00000011|     16 bits    |  **  |  **  | 16 bits |01111110|
    // +--------+--------+--------+----------------+------+------+---------+--------+
    pushByte(0x7E);
    push(0xFF, 0x03, 0x60, 0x65); // Protocol 0x6560 -> no assocaited Network Control Protocol (RFC 1661)
    pushByte(0x0E);    // length   TODO
    pushByte(0xA0);
    push(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    pushByte(0x00);
    pushByte(0x01);
    push(mySusyId);
    push(mySerial);
    push(0x00, 0x01);  // ??
    pushByte(0x00);    // Ack 0x00
    pushByte(0x00);    // ??
    pushByte(0x00);    // Telegram Number
    pushByte(0x00);    // ??
    pushByte(0x03);    // $CNT Counter   TODO
    pushByte(0x80);    // Command Group 1
    pushByte(0x0C);    // Command Group 2
    pushByte(0x04);    // Command Group 3
    pushWord(0xFFFD);  // Command = Login
        push(0x07, 0x00, 0x00, 0x00, 0x84, 0x03);
        push(0x00, 0x00);
        time_t t = time(NULL);
        pushLong((uint32_t)t);
        pushLong(0x00);   // ??
        for (int i = 0; i < 12; ++ i) { // $PASSWORD   12 chars xored with 0x88
            uint8_t byte = i < password.length() ? password[i] : 0;
            push(byte ^ 0x88);
        }
}

SbL2Packet& SbL2Packet::finalize() {
    uint16_t fcsCheck = calculateFCS();
    pushWord(fcsCheck);       // $CRC
    addEscapes();
    pushByte(0x7E);           // Termination
    return *this;
}

void SbL2Packet::addEscapes() {
    for (size_t i = 1; i < m_message.size(); ++ i) {
        switch(m_message[i]) {
            case 0x7d:
            case 0x7e:
            case 0x11:
            case 0x12:
            case 0x13:
                m_message[i] = m_message[i] ^ 0x20;
                m_message.insert(i, (uint8_t)0x7d);
                ++ i;
                break;
        }
    }
}

uint16_t SbL2Packet::calculateFCS() {
    // RFC 1662 FCS is calculated over all bits of Address, Control, 
    // Protocol, Information and Padding fields (so NOT FLAG at start)
    return Fcs16::instance().calculateFCS(m_message.data() + 1, m_message.size() - 1);
}
