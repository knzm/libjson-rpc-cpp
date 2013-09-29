file(GLOB_RECURSE jsonrpcstub_source *.cpp)

find_package(Argtable REQUIRED)

add_executable(jsonrpcstub ${jsonrpcstub_source})
target_link_libraries(jsonrpcstub jsonrpccommon ${Argtable_LIBRARY})

install(TARGETS jsonrpcstub LIBRARY DESTINATION lib
                      ARCHIVE DESTINATION lib
                      RUNTIME DESTINATION bin)
