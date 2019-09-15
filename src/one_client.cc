#define BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_SYSTEM_NO_LIB

#include <iostream>
#include <chrono>

#include "ws/websocket_meta.h"
#include "ws/websocket_endpoint.h"

int main() {
  std::string uri = "ws://localhost:9000" ;

  std::cout << "point 0" <<std::endl;
  websocket_endpoint endpoint;
  endpoint.connect(uri);
  sleep(1);
  endpoint.send("hoge");
  sleep(1);
  endpoint.close(1000,"test");
}