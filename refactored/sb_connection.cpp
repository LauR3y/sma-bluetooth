#include "sb_connection.h";

SbConnection::SbConnection(const BtAddr& addr) {
    m_addr = addr;
    struct sockaddr_rc a = m_addr.getSockAddr();
    m_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (m_socket < 0) {
        throw std::exeption("Unable to create socket");
    }
    m_connected = connect(m_socket, static_cast<struct sockaddr*>(a), sizeof(a));
    if (m_connected < 0) {
        throw std::exception("Unable to connect");
    }   
}

SbConnection::~SbConnection() {
    close(m_socket);
}

void SbConnection::send(const std::vector<uint8_t>& payload) {

}

std::vector<uint8_t> SbConnection::recv() {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    bool finished = false;
    int bytesToRead = sizeof(header);
    int bytesReadSoFar = 0;
    std::vector<uint8_t> buffer;
    buffer.reserve(bytesToRead);

    while(bytesToRead > bytesReadSoFar) {
        FD_ZERO(&readfds);
        FD_SET(m_socket, &readfds);

        if (select(m_socket + 1, &readfds, NULL, NULL, &tv) < 0) {
            throw std::exctption("Error in select");
        }

        if (!FD_ISSET(m_socket, &readFds)) {
            throw std::exception("Timeout waiting for data");
        }

        int bytesRead = recv(m_socket, &buffer[bytesReadSoFar], bytesToRead, 0);
        if (bytesRead < 0) {
            throw std::exception("socket read error");
        }
        bytesReadSoFar += bytesRead;
        if (bytesReadSoFar >= 2 && bytesToRead == 4) {
            // Just finished reading the length :-)
            bytesToRead = buffer[1];
            buffer.reserve(bytesToRead);
        }
    }

    return buffer;
} 
// R 7E 1F 00 61 $ADDR 00 00 00 00 00 00 02 00 00 04 70 00 $END;
// E $INVCODE $END;