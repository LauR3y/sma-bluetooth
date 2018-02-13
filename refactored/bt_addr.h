#pragma once
#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <vector>

class BtAddr {
public:
    BtAddr(const std::string& addr);

    void getSockAddr(struct sockaddr_rc& addr, uint8_t channel=1) const;
    void addToMsg(std::vector<uint8_t>& message);
    
private:
    bdaddr_t m_addr;
};
