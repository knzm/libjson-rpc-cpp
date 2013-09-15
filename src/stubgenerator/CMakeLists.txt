file(GLOB_RECURSE jsonrpcstub_source *.cpp)

add_executable(jsonrpcstub ${jsonrpcstub_source})
target_link_libraries(jsonrpcstub jsonrpccommon)

install(TARGETS jsonrpcstub LIBRARY DESTINATION lib
                      ARCHIVE DESTINATION lib
                      RUNTIME DESTINATION bin)
