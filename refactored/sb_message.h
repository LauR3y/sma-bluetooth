#include "bt_addr.h"
#include <vector>
#include <iostream>

class SbMessage {
public:
    SbMessage(uint16_t command, const BtAddr& addr1, const BtAddr& addr2);

    void finalize();

    SbMessage operator+=(const std::vector<uint8_t> bytes);
    SbMessage operator+=(const SbMessage& message);
    SbMessage operator+=(const uint8_t byte);
    SbMessage operator+=(const uint16_t short);
    
    const std::vector<uint8_t>& get() const;

    friend std::ostream& operator<< (std::ostream& os, const SbMessage& message);

private:
    std::vector<uint8_t> m_message;
};

SbMessage operator+(SbMessage lhs, const std::vector<uint8_t> bytes);
SbMessage operator+(SbMessage lhs, const SbMessage& message);
SbMessage operator+(SbMessage lhs, const uint8_t byte);