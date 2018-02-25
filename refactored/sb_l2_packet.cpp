#include "sb_l2_packet.h"

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

SbL2Packet::SbL2Packet(const MessageBytes& mySusyId, const MessageBytes& mySerial, const std::string& password) {
    pushByte(0x7E);
    push(0xFF, 0x03, 0x60, 0x65);
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
    pushByte(0x05);    // $CNT Counter   TODO
    pushByte(0x80);    // Command Group 1
    pushByte(0x0C);    // Command Group 2
    pushByte(0x04);    // Command Group 3
    pushWord(0xFFFD);  // Command = Login
        push(0x07, 0x00, 0x00, 0x00, 0x84, 0x03);
        push(0x00, 0x00);
        time_t t = time(NULL);
        pushLong((uint32_t)t);
        push(0x00, 0x00, 0x00, 0x00);   // ??
        for (int i = 0; i < 12; ++ i) { // $PASSWORD   12 chars xored with 0x88
            uint8_t byte = i < password.length() ? password[i] : 0;
            push(byte ^ 0x88);
        }
        pushWord(calculateFCS());       // $CRC
    pushByte(0x7E);                     // Termination
}

uint16_t SbL2Packet::calculateFCS() {
    return Fcs16::instance().calculateFCS(m_message.data(), m_message.size());
}
