#include "bt_addr.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

BtAddr::BtAddr(const std::string& addr) {
    str2ba(addr.c_str(), &m_addr);
}

struct sockaddr_rc BtAddr::getSockAddr(uint8_t channel) const {
    struct sockaddr_rc sockaddr = {0};
    sockaddr.rc_family = AF_BLUETOOTH;
    sockaddr.rc_channel = channel;
    sockaddr.rc_bdaddr = m_addr;
}
