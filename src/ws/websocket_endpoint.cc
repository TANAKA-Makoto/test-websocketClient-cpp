#include "websocket_endpoint.h"

websocket_endpoint::websocket_endpoint() : m_next_id(0) {
  std::cout << __FUNCTION__ << std::endl;
  m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
  m_endpoint.clear_error_channels(websocketpp::log::elevel::all);
  m_endpoint.init_asio();
  m_endpoint.start_perpetual();
  m_thread.reset(new websocketpp::lib::thread(&client::run, &m_endpoint));
}

websocket_endpoint::~websocket_endpoint(){
  m_endpoint.stop_perpetual();

  std::cout << "> Closing connection " << one_con->get_id() << std::endl;
  websocketpp::lib::error_code ec;
    m_endpoint.close(one_con->get_hdl(), websocketpp::close::status::going_away, "", ec);
    if (ec) {
      std::cout << "> Error closing connection " << one_con->get_id() << ": "
                << ec.message() << std::endl;
    }

  m_thread->join();
}

int websocket_endpoint::connect(std::string const & uri) {
  websocketpp::lib::error_code ec;
  client::connection_ptr con = m_endpoint.get_connection(uri, ec);
  if (ec) {
    std::cout << "> Connect initialization error: " << ec.message() << std::endl;
    return -1;
  }
  //int new_id = m_next_id++;
  Connection_meta::ptr metadata_ptr(new Connection_meta(1, con->get_handle(), uri));
  //m_connection_list[new_id] = metadata_ptr;
  one_con = metadata_ptr;
  con->set_open_handler(websocketpp::lib::bind(
    &Connection_meta::on_open,
    metadata_ptr,
    &m_endpoint,
    websocketpp::lib::placeholders::_1
  ));
  con->set_fail_handler(websocketpp::lib::bind(
    &Connection_meta::on_fail,
    metadata_ptr,
    &m_endpoint,
    websocketpp::lib::placeholders::_1
  ));
  con->set_close_handler(websocketpp::lib::bind(
    &Connection_meta::on_close,
    metadata_ptr,
    &m_endpoint,
    websocketpp::lib::placeholders::_1
  ));
  con->set_message_handler(websocketpp::lib::bind(
    &Connection_meta::on_message,
    metadata_ptr,
    websocketpp::lib::placeholders::_1,
    websocketpp::lib::placeholders::_2
  ));
  m_endpoint.connect(con);
  return 1;
}

void websocket_endpoint::close(websocketpp::close::status::value code, std::string reason){
  websocketpp::lib::error_code ec;
  //Connection_meta::ptr metadata_ptr(new Connection_meta(1, con->get_handle(), uri));
  //one_con = metadata_ptr;
/*  if (metadata_it == m_connection_list.end()){
    std::cout << "> No connection found with id " << id << std::endl;
    return;
  }*/
  std::cout << one_con->get_id() << std::endl;
  m_endpoint.close(one_con->get_hdl(), code ,reason, ec);
  if (ec){
    std::cout << "> Error initiating close: " << ec.message() << std::endl;
  }
  //one_con = nullptr;
}

void websocket_endpoint::send(std::string message){
  websocketpp::lib::error_code ec;

  /*con_list::iterator metadata_it = m_connection_list.find(id);
  if (metadata_it == m_connection_list.end()) {
    std::cout << "> No connection found with id " << id << std::endl;
    return;
  }*/

  m_endpoint.send(one_con->get_hdl(), message, websocketpp::frame::opcode::text, ec);
  if (ec) {
    std::cout << "> Error sending message: " << ec.message() << std::endl;
    return;
  }

  one_con->record_sent_message(message);
}

Connection_meta::ptr websocket_endpoint::get_metadata(int id) const {
    con_list::const_iterator metadata_it = m_connection_list.find(id);
    if (metadata_it == m_connection_list.end()) {
        return Connection_meta::ptr();
    } else {
        return metadata_it->second;
    }
}