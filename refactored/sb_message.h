#pragma once
#include "bt_addr.h"
#include <vector>
#include <iostream>

class SbMessage {
public:
    SbMessage(uint16_t command, const BtAddr& addr1, const BtAddr& addr2);

    void finalize();

    void push(const std::vector<uint8_t>& bytes);
    void push(uint8_t value);
    void push(uint16_t value);
    
    const std::vector<uint8_t>& get() const;

    friend std::ostream& operator<< (std::ostream& os, const SbMessage& message);

private:
    std::vector<uint8_t> m_message;
};

