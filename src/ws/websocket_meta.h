#ifndef AOI_WEBSOCKET_META
#define AOI_WEBSOCKET_META

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>


#include <iostream>
#include <map>
#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;
class Connection_meta {
 public:
     typedef websocketpp::lib::shared_ptr<Connection_meta> ptr;

     Connection_meta(int id, websocketpp::connection_hdl hdl, std::string uri);

     void on_open(client * c, websocketpp::connection_hdl hdl);

     void on_fail(client * c, websocketpp::connection_hdl hdl);

     void on_close(client * c, websocketpp::connection_hdl hdl);

     void on_message(websocketpp::connection_hdl, client::message_ptr msg);

     websocketpp::connection_hdl get_hdl() const;

     int get_id() const;

     std::string get_status() const;
     //  新しい接続を作っていいかにつかう。"connecting" "Open"で真
     bool is_running() const;

     void record_sent_message(std::string message);


 private:
     int m_id;
     websocketpp::connection_hdl m_hdl;
     std::string m_status;
     std::string m_uri;
     std::string m_server;
     std::string m_error_reason;
     std::vector<std::string> m_messages;
 };

#endif  // AOI_WEBSOCKET_META