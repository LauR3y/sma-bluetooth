#pragma once
#include <string>
#include <bluetooth/bluetooth.h>

class BtAddr {
public:
    BtAddr(const std::string& addr);

    struct sockaddr_rc getSockAddr(uint8_t channel=1) const;
    
private:
    bdaddr_t m_addr;
};
