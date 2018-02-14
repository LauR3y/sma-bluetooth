#include "sb_connection.h"
#include <unistd.h>
#include <sys/socket.h>
#include <stdexcept>

SbConnection::SbConnection(const BtAddr& addr) : m_addr(addr) {
    struct sockaddr_rc a = {0};
    m_addr.getSockAddr(a);
    m_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (m_socket < 0) {
        throw std::runtime_error("Unable to create socket");
    }
    m_connected = connect(m_socket, (struct sockaddr*)(&a), sizeof(a));
    if (m_connected < 0) {
        throw std::runtime_error("Unable to connect");
    }   
}

SbConnection::~SbConnection() {
    //close(m_socket);
}

void SbConnection::send(const std::vector<unsigned char>& payload) {
    write(m_socket, &payload[0], payload.size());
}

std::vector<uint8_t> SbConnection::receive() {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    bool finished = false;
    int bytesToRead = 4;
    int bytesReadSoFar = 0;
    std::vector<uint8_t> buffer;
    buffer.resize(bytesToRead);

    while(bytesToRead > bytesReadSoFar) {
        FD_ZERO(&readfds);
        FD_SET(m_socket, &readfds);

        if (select(m_socket + 1, &readfds, NULL, NULL, &tv) < 0) {
            throw std::runtime_error("Error in select");
        }

        if (!FD_ISSET(m_socket, &readfds)) {
            throw std::runtime_error("Timeout waiting for data");
        }

        int bytesRead = recv(m_socket, &buffer[bytesReadSoFar], bytesToRead, 0);
        if (bytesRead < 0) {
            throw std::runtime_error("socket read error");
        }
        bytesReadSoFar += bytesRead;
        if (bytesReadSoFar >= 2 && bytesToRead == 4) {
            // Just finished reading the length :-)
            bytesToRead = buffer[1];
            buffer.resize(bytesToRead);
        }
    }

    return buffer;
} 
// R 7E 1F 00 61 $ADDR 00 00 00 00 00 00 02 00 00 04 70 00 $END;
// E $INVCODE $END;
