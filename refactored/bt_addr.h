#pragma once
#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <vector>

class BtAddr {
public:
    BtAddr(uint8_t fill = 0);
    BtAddr(const std::string& addr);
    BtAddr(const std::vector<uint8_t>& buffer, size_t offset=0);

    std::string toString() const;
    void getSockAddr(struct sockaddr_rc& addr, uint8_t channel=1) const;
    std::vector<uint8_t> asBytes() const;
    
private:
    bdaddr_t m_addr;
};
