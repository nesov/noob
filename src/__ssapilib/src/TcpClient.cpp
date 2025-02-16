

#include "utils.h"
#include "Message.h"

#include "TcpClient.h"

TcpClient::TcpClient(const char *host, int port) :m_host(host), m_port(port) {
    init(m_host, m_port);
}

TcpClient::~TcpClient() {
    close(m_client_fd);
}

inline int TcpClient::connect_() {
    m_connection_status = connect(this->m_client_fd,
                                  (sockaddr *)&m_serv.server_address, sizeof(m_serv.server_address));
    if (m_connection_status < 0) {
        std::cerr << "Connection error\n";
        close(m_client_fd);
        return -1;
    } else {
        std::cerr << "Connected!!!\n";
    }
    return 0;
}

inline void TcpClient::receiveMessage(Message &message) {
    int bytes{0};
    while (bytes != sizeof(message)) {
        bytes = read(m_client_fd, &message, sizeof(message));
    }
}

inline void TcpClient::sendMessage(Message &message) {
    int bytes{0};
    while (bytes != sizeof(message)) {
        bytes = send(m_client_fd, &message, sizeof(message), 0);
    }
}

int TcpClient::init(const char *host, const int port)
{
    m_client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_client_fd == -1)
    {
        std::cerr << "Crearing socket Error\n";
        return -1;
    }

    std::memset(&m_serv.server_address, 0, sizeof(m_serv.server_address));
    m_serv.server_address.sin_family = AF_INET;
    m_serv.server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &m_serv.server_address.sin_addr) <= 0)
    {
        std::cerr << "Converting address error\n";
        close(m_client_fd);
        return -1;
    }
    return 0;
}
