#include "sb_l2_packet.h"

SbL2Packet::SbL2Packet(const BtAddr& to, const BtAddr& from, const MessageBytes& mySusyId, const MessageBytes& mySerial) {
    push(std::vector<uint8_t>({0x7E, 0x54, 0x00, 0x2A}));
    push(to.asBytes());
    push(from.asBytes());
    push(0x7E);
    push(0x0E);
    push(std::vector<uint8_t>({0xFF, 0x03, 0x60, 0x65}));
    push(0xA0);
    push(std::vector<uint8_t>({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}));
    push(0x00);
    push(0x01);
    push(mySusyId);
    push(mySerial);
    push(std::vector<uint8_t>({0x00, 0x01})); // ??
    push(0x00);                               // Ack 0x00
    push(0x00);                               // ??
    push(0x00);                               // Telegram Number
    push(0x00);                               // ??
    push(0x00);                               // $CNT Counter
    push(0x80);                               // Command Group 1
    push(0x0C);                               // Command Group 2
    push(0x04);                               // Command Group 3
    push(std::vector<unit8_t>({0xFD, 0xFF});  // Command = Login
        push(std::vector<uint8_t>({0x07, 0x00, 0x00, 0x00, 0x84, 0x03, 0x00, 0x00});
        time_t t = time(NULL);
        push((uint32_t)t);
        push(std::vector<uint8_t>({0x00, 0x00, 0x00, 0x00});  // ??
    //   $PASSWORD   12 chars xored with 0x88
    //   $CRC
    push(0x7E);                               // Termination
}
