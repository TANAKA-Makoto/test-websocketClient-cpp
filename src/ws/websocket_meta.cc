#include "websocket_meta.h"

Connection_meta::Connection_meta(int id, websocketpp::connection_hdl hdl, std::string uri)
  : m_id(id)
  , m_hdl(hdl)
  , m_status("Connecting")
  , m_uri(uri)
  , m_server("N/A"){}

void Connection_meta::on_open(client * c, websocketpp::connection_hdl hdl) {
    m_status = "Open";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
}
void Connection_meta::on_fail(client * c, websocketpp::connection_hdl hdl) {
    m_status = "Failed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_error_reason = con->get_ec().message();
}
void Connection_meta::on_close(client * c, websocketpp::connection_hdl hdl) {
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
      << websocketpp::close::status::get_string(con->get_remote_close_code())
      << "), close reason: " << con->get_remote_close_reason();
    m_error_reason = s.str();
}
void Connection_meta::on_message(websocketpp::connection_hdl, client::message_ptr msg) {
   std::cout << __FUNCTION__ << ":" << msg->get_opcode() << std::endl;
   std::cout << websocketpp::frame::opcode::text << std::endl;
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        m_messages.push_back("<< " + msg->get_payload());
    } else {
        m_messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));
    }
}
websocketpp::connection_hdl Connection_meta::get_hdl() const {
    return m_hdl;
}
int Connection_meta::get_id() const {
    return m_id;
}
std::string Connection_meta::get_status() const {
    return m_status;
}
void Connection_meta::record_sent_message(std::string message) {
    m_messages.push_back(">> " + message);
}