cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER $ENV{CC})
set(CMAKE_CXX_COMPILER $ENV{CXX})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

#set(BOOST_ROOT ~/Document/boost/boost)


set(EXECUTABLE_OUTPUT_PATH "out/sample")

include_directories("src")
include_directories("third-party/websocketpp/")
include_directories("third-party/boost/")
#link_directories("third-party/websocketpp/")

#link_directories("/web/src/out/Develop/obj")

# Linux
find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-macro-redefined -fno-lto -std=c++11 -pthread -DWEBRTC_POSIX -DOPENSLL_IS_BORINGSSL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

pkg_search_module(X11 REQUIRED x11)
#list(APPEND webrtc_libs ${X11_LIBRARIES})
#list(APPEND webrtc_libs "dl")
#list(APPEND webrtc_libs "pthread")
#list(APPEND webrtc_libs "-Wl,--no-whole-archive")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1" )

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g") # for debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MMD -MP")

# Disable RTTI
#set_source_files_properties(main.cpp PROPERTIES
#  COMPILE_FLAGS " -fno-rtti "
#  )

add_executable(sample
  src/main.cc
  )
add_executable(client
  src/one_client.cc
  src/ws/websocket_endpoint.cc
  src/ws/websocket_endpoint.h
  src/ws/websocket_meta.cc
  src/ws/websocket_meta.h

  )
add_executable(example
  src/example.cc
  )
# add_executable(echo_client
#   src/echo_client.cc
#   )
target_link_libraries(sample
#  ${X11_LIBRARIES}
  crypto
  dl
  expat
  nspr4
  nss3
  nssutil3
  plc4
  plds4
  pthread
  rt
  ssl
  X11
  Xau
  xcb
  Xdmcp
  Xext
  z
  )
target_link_libraries(client
#  ${X11_LIBRARIES}
  crypto
  dl
  expat
  nspr4
  nss3
  nssutil3
  plc4
  plds4
  pthread
  rt
  ssl
  X11
  Xau
  xcb
  Xdmcp
  Xext
  z
  )
target_link_libraries(example
#  ${X11_LIBRARIES}
  crypto
  dl
  expat
  nspr4
  nss3
  nssutil3
  plc4
  plds4
  pthread
  rt
  ssl
  X11
  Xau
  xcb
  Xdmcp
  Xext
  z
  )