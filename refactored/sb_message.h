#include <vector>
#include <iostream>

class SbMessage {
public:
    SbMessage(uint8_t type);

    SbMessage operator+=(const std::vector<uint8_t> bytes);
    SbMessage operator+=(const SbMessage& message);
    SbMessage operator+=(const uint8_t byte);
    
    const std::vector<uint8_t>& get();

    friend std::ostream& operator<< (std::ostream& os, const SbMessage& message);

private:
    std::vector<uint8_t> m_message;
};

SbMessage operator+(SbMessage lhs, const std::vector<uint8_t> bytes);
SbMessage operator+(SbMessage lhs, const SbMessage& message);
SbMessage operator+(SbMessage lhs, const uint8_t byte);