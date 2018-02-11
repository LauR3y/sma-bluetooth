#include "bt_addr.h";
#include "sb_connection.h";

class SbContext {
public:
    SbContext(const BtAddr& addr);

private:
    BtAddr       m_addr;
    SbConnection m_connection;
}
