cmake_minimum_required (VERSION 2.6)
project (thermocracy-server)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.68.0 REQUIRED COMPONENTS system filesystem)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USER_MULITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(Boost_ROOT "/usr/local/Cellar/boost/1.68.0_1")
set(Boost_INLCUDE_DIR "/usr/local/Cellar/boost/1.68.0_1/include")
set(Boost_LIBRARY_DIR "/usr/local/Cellar/boost/1.68.0_1/lib")

set(JSON_INCLUDE_PATH "./3party/json")
set(JSON_CPP "./3party/jsoncpp.cpp")

set(SOURCES Source.cpp
        Server.h
        Server.cpp
        Thermocracy.h
        Thermocracy.cpp
        EchoJson.h
        EchoJson.cpp
        JsonMessageBase.h
        JsonMessageBase.cpp
        ${JSON_CPP}
        UserJson.h
        UserJson.cpp)

if(Boost_FOUND)
    include_directories("/usr/local/boost-1.68.0/include" "./")
    add_executable (thermocracy-server ${SOURCES})
    set_property(TARGET thermocracy-server PROPERTY CXX_STANDARD 14)
    target_include_directories(thermocracy-server PRIVATE ${Boost_INCLUDE_DIRS} ${JSON_INCLUDE_PATH})
    target_link_libraries(thermocracy-server ${Boost_FILESYSTEM_LIBRARIES}
            ${Boost_SYSTEM_LIBRARIES})
endif()