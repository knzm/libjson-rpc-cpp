file(COPY spec.json ssl_cert.pem DESTINATION ${CMAKE_BINARY_DIR}/out)

add_custom_command(OUTPUT abstractstubserver.h
                   COMMAND jsonrpcstub ARGS -i ${CMAKE_CURRENT_SOURCE_DIR}/spec.json -s abstractsubserver.h -c Stub
                   MAIN_DEPENDENCY spec.json
                   DEPENDS jsonrpcstub
                   COMMENT Generating Stubfiles
                   VERBATIM)

add_executable(simpleserversample simpleserver.cpp)
target_link_libraries(simpleserversample jsonrpcserver)

add_executable(simpleclientsample simpleclient.cpp)
target_link_libraries(simpleclientsample jsonrpcclient)

add_executable(stubclientsample stubclient.cpp abstractstubserver.h)
target_link_libraries(stubclientsample jsonrpc)

#add_executable(stubserversample stubserver.cpp abstractmystubserver.h)
#target_link_libraries(stubserversample jsonrpc)

#add_executable(xbmcremote xbmcremote.cpp)
#target_link_libraries(xbmcremote jsonrpc)
