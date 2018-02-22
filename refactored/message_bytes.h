#pragma once
#include <vector>
#include <iostream>

class MessageBytes {
public:
    MessageBytes(const std::vector<uint8_t>& bytes);
    MessageBytes(uint8_t value);
    MessageBytes(uint8_t value1, uint8_t value2);
    MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3);
    MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4);
    MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5);
    MessageBytes(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5, uint8_t value6);
    MessageBytes(uint16_t value);

    void push(const std::vector<uint8_t>& bytes);
    void push(uint8_t value);
    void push(uint8_t value1, uint8_t value2);
    void push(uint8_t value1, uint8_t value2, uint8_t value3);
    void push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4);
    void push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5);
    void push(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4, uint8_t value5, uint8_t value6);
    void push(uint16_t value);
    void push(uint32_t value);
    
    const std::vector<uint8_t>& get() const;

    friend std::ostream& operator<< (std::ostream& os, const MessageBytes& message);

    uint8_t operator[](size_t i) const { return m_message[i]; }

private:
    std::vector<uint8_t> m_message;
};

