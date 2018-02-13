#include "bt_addr.h"
#include <iostream>

BtAddr::BtAddr(const std::string& addr) {
    str2ba(addr.c_str(), &m_addr);
}

void BtAddr::getSockAddr(struct sockaddr_rc& sockaddr, uint8_t channel) const {
    sockaddr.rc_family = AF_BLUETOOTH;
    sockaddr.rc_channel = channel;
    memcpy(&sockaddr.rc_bdaddr, &m_addr, sizeof(sockaddr.rc_bdaddr));
}

void BtAddr::addToMsg(std::vector<uint8_t>& message) {
    for (size_t i = 0; i < sizeof(bdaddr_t); ++i) {
        message.push_back(m_addr.b[i]);
    }
}
