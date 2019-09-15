#ifndef AOI_WEBSOCKET_ENDPOINT_H
#define AOI_WEBSOCKET_ENDPOINT_H

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include "websocket_meta.h"

typedef websocketpp::client<websocketpp::config::asio_client> client;
class websocket_endpoint {
public:
    websocket_endpoint ();
    ~websocket_endpoint();
    int connect(std::string const & uri);
    void close(websocketpp::close::status::value code, std::string reason);
    void send(std::string message);
    Connection_meta::ptr get_metadata() const;
private:
    typedef std::map<int,Connection_meta::ptr> con_list;
    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
    con_list m_connection_list;
    Connection_meta::ptr one_con;
    int m_next_id;
};


#endif  // AOI_WEBSOCKET_ENDPOINT_H