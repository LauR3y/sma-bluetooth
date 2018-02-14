#include "bt_addr.h"
#include "sb_connection.h"

class SbContext {
public:
    SbContext(const BtAddr& addr);
    SbContext(const std::string& addr);

    SbContext connect();

private:
    void send(const std::vector<uint8_t>& message);
    std::vector<uint8_t> receive();
    std::vector<uint8_t> waitFor(uint8_t type);
    
    std::ostream dump(const std::vector<uint8_t>& msg, std::ostream& os);
    std::vector<uint8_t> buildMessage61();
    std::vector<uint8_t> buildMessage6A();
    std::vector<uint8_t> buildMessage2A();
    std::vector<uint8_t> append(std::vector<uint8_t>& message, const std::vector<uint8_t>& toAppend);
    
    BtAddr       m_sbAddr;
    uint8_t      m_invCode;
    BtAddr       m_myAddr;
    SbConnection m_connection;
}
