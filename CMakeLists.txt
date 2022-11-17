CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)
PROJECT(server)

SET(CMAKE_CXX_STANDARD 17)
include_directories(prj/include)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.71.0 REQUIRED)


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(server
        ## src/main.cpp
        # src/big_file.cpp
        # src/mime_types.cpp
        ## src/sync_client.cpp
        # src/request_parser.cpp
        prj/src/main.cpp
        prj/src/connection.cpp
        prj/include/connection.hpp
        prj/src/connection_manager.cpp
        prj/include/connection_manager.hpp
        prj/include/header.hpp
        prj/src/mime_types.cpp
        prj/include/mime_types.hpp
        prj/src/reply.cpp
        prj/include/reply.hpp
        prj/include/request.hpp
        prj/src/request_handler.cpp
        prj/include/request_handler.hpp
        prj/src/request_parser.cpp
        prj/include/request_parser.hpp
        prj/src/server.cpp
        prj/include/server.hpp
        prj/src/database_manager.cpp
        prj/include/database_manager.hpp
        prj/src/database.cpp
        prj/include/database.hpp
        prj/include/json.hpp
)

target_link_libraries(server ${Boost_LIBRARIES})
