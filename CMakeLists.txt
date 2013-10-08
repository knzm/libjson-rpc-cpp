cmake_minimum_required(VERSION 2.6)
project(libjson-rpc-cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/dev/")

find_package(CURL REQUIRED)
find_package(JSONCPP REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/src/deps)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out)

SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Wall --coverage")
SET(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -Wall --coverage")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lgcov")

SET(MAJOR_VERSION 0)
SET(MINOR_VERSION 3)
SET(PATCH_VERSION 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/jsonrpc/version.h.in"
  "${PROJECT_BINARY_DIR}/version.h"
)
install(FILES ${PROJECT_BINARY_DIR}/version.h DESTINATION include/jsonrpc) 

add_subdirectory(src/jsonrpc)
add_subdirectory(src/stubgenerator)
add_subdirectory(src/example)

find_package(Boost COMPONENTS unit_test_framework)
IF(Boost_FOUND)
    message(STATUS "Found Bosst Unit Suite -> Enabling test cases")
    ENABLE_TESTING()
    set(CTEST_OUTPUT_ON_FAILURE TRUE)
    add_subdirectory(src/test)
ENDIF(Boost_FOUND)


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/dev/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_NAME "libjsonrpccpp-dev")
SET(CPACK_SET_DESTDIR "on")


SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")
SET(CPACK_RESOURCE_FILE_README  "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(CPACK_GENERATOR "PackageMaker")
	SET(CPACK_PACKAGING_INSTALL_PREFIX "/opt/local")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET(CPACK_GENERATOR "DEB")
	SET(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

SET(CPACK_PACKAGE_DESCRIPTION "jsonrpc framework for C++, including server and client support and a stubgenerator for several languages.")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "jsonrpc framework for C++")
SET(CPACK_PACKAGE_VENDOR "Peter Spiess-Knafl")
SET(CPACK_PACKAGE_CONTACT "Peter Spiess-Knafl <peter.knafl@gmail.com>")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4-nss-dev, libjsoncpp-dev, libargtable2-dev")

SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

SET(CPACK_COMPONENTS_ALL jsonrpccommon jsonrpccommonStatic jsonrpcserver jsonrpcserverStatic jsonrpclient jsonrpcclientStatic jsonrpcstub)
INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")


