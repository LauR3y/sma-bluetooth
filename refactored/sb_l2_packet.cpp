#include "sb_l2_packet.h"

SbL2Packet::SbL2Packet(const BtAddr& to, const BtAddr& from, const MessageBytes& mySusyId, const MessageBytes& mySerial) {
    push(std::vector<uint8_t>({0x7E, 0x54, 0x00, 0x2A}));
    push(to.asBytes());
    push(from.asBytes());
    pushByte(0x7E);
    pushByte(0x0E);
    push(0xFF, 0x03, 0x60, 0x65);
    pushByte(0xA0);
    push(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    pushByte(0x00);
    pushByte(0x01);
    push(mySusyId);
    push(mySerial);
    push(0x00, 0x01); // ??
    pushByte(0x00);                               // Ack 0x00
    pushByte(0x00);                               // ??
    pushByte(0x00);                               // Telegram Number
    pushByte(0x00);                               // ??
    pushByte(0x00);                               // $CNT Counter
    pushByte(0x80);                               // Command Group 1
    pushByte(0x0C);                               // Command Group 2
    pushByte(0x04);                               // Command Group 3
    push(0xFD, 0xFF);  // Command = Login
        push(0x07, 0x00, 0x00, 0x00, 0x84, 0x03);
        push(0x00, 0x00);
        time_t t = time(NULL);
        push((uint32_t)t);
        push(0x00, 0x00, 0x00, 0x00);  // ??
    //   $PASSWORD   12 chars xored with 0x88
    //   $CRC
    pushByte(0x7E);                               // Termination
}
