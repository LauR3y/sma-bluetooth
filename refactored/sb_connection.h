#include "bt_addr.h"
#include <vector>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

class SbConnection {
public:
    SbConnection(const BtAddr& addr);
    ~SbConnection();

    void write(const std::vector<uint8_t>& payload);
    std::vector<uint8_t> read();

private:
    BtAddr m_addr;
    int    m_socket;
    int m_connected;
};

