#include "bt_addr.h";
#include <vector>;
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

class SbConnection {
public:
    SbConnection(const BtAddr& addr);
    ~SbConnection();

    std::vector<uint8_t read();
    int write(const std::vector<uint8_t>& payload);

private:
    BtAddr m_addr;
    int    m_socket;
}