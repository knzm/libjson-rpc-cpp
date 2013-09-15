set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/test)

set(COMMON_SOURCES server.cpp)

add_executable(helloworld helloworld.cpp ${COMMON_SOURCES})
target_link_libraries(helloworld jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(remotecounter remotecounter.cpp ${COMMON_SOURCES})
target_link_libraries(remotecounter jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(remotecalculator remotecalculator.cpp ${COMMON_SOURCES})
target_link_libraries(remotecalculator jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(errorhandling errorhandling.cpp ${COMMON_SOURCES})
target_link_libraries(errorhandling jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(jsonrpcprotocol jsonrpcprotocol.cpp ${COMMON_SOURCES})
target_link_libraries(jsonrpcprotocol jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(specification specification.cpp ${COMMON_SOURCES})
target_link_libraries(specification jsonrpcclient jsonrpcserver jsonrpccommon)

add_executable(parametervalidation parametervalidation.cpp)
target_link_libraries(parametervalidation jsonrpcclient jsonrpcserver jsonrpccommon)
