file(GLOB_RECURSE jsonrpc_source_common common/*.c*)
file(GLOB_RECURSE jsonrpc_source_client client/*.c*)
file(GLOB_RECURSE jsonrpc_source_server server/*.c*)

file(GLOB jsonrpc_header_common common/*.h)
file(GLOB jsonrpc_header_client client/*.h)
file(GLOB jsonrpc_header_server server/*.h)
file(GLOB jsonrpc_header *.h)

include_directories("${PROJECT_SOURCE_DIR}/src/")

add_library(jsonrpccommon SHARED ${jsonrpc_source_common})
add_library(jsonrpccommonStatic STATIC ${jsonrpc_source_common})
target_link_libraries(jsonrpccommon ${JSONCPP_LIBRARY})
target_link_libraries(jsonrpccommonStatic ${JSONCPP_LIBRARY})
set_target_properties(jsonrpccommonStatic PROPERTIES OUTPUT_NAME jsonrpccommon)

add_library(jsonrpcclient SHARED ${jsonrpc_source_client})
add_library(jsonrpcclientStatic STATIC ${jsonrpc_source_client})
target_link_libraries(jsonrpcclient jsonrpccommon ${CURL_LIBRARIES})
target_link_libraries(jsonrpcclientStatic jsonrpccommonStatic ${CURL_LIBRARIES})
set_target_properties(jsonrpcclientStatic PROPERTIES OUTPUT_NAME jsonrpcclient)

<<<<<<< HEAD
add_library(jsonrpcserver SHARED ${jsonrpc_source_server} ${jsonrpc_header_server})
add_library(jsonrpcserverStatic STATIC ${jsonrpc_source_server} ${jsonrpc_header_server})
target_link_libraries(jsonrpcserver jsonrpccommon ${CMAKE_DL_LIBS})
target_link_libraries(jsonrpcserverStatic jsonrpccommonStatic ${CMAKE_DL_LIBS})
set_target_properties(jsonrpcserverStatic PROPERTIES OUTPUT_NAME jsonrpcserver)

set(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
set_target_properties(jsonrpccommon jsonrpccommonStatic jsonrpcclient jsonrpcclientStatic jsonrpcserver jsonrpcserverStatic PROPERTIES VERSION "${VERSION_STRING}" SOVERSION "${VERSION_MAJOR}")
=======
target_link_libraries(jsonrpc pthread dl ${CURL_LIBRARIES})
target_link_libraries(jsonrpcStatic pthread dl ${CURL_LIBRARIES})
>>>>>>> master

install(FILES ${jsonrpc_header}        DESTINATION include/jsonrpc)
install(FILES ${jsonrpc_header_common} DESTINATION include/jsonrpc/common)
install(FILES ${jsonrpc_header_client} DESTINATION include/jsonrpc/client)
install(FILES ${jsonrpc_header_server} DESTINATION include/jsonrpc/server)

install(TARGETS jsonrpccommon jsonrpccommonStatic jsonrpcclient jsonrpcclientStatic jsonrpcserver jsonrpcserverStatic
                      LIBRARY DESTINATION lib
                      ARCHIVE DESTINATION lib
                      RUNTIME DESTINATION bin)
