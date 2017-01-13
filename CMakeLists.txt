cmake_minimum_required(VERSION 3.6)
project(UdpSocketLib)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

# Bring the header files here
include_directories(include)

# Add the source files
file(GLOB SOURCES "src/*.cpp" "src/*.c")

#file(GLOB SOURCES "src/*.cChecksum.cpp")

#Generate the shared library from the sources
add_library(UdpSocketLib SHARED ${SOURCES} include/UdpLibGlobaldefs.h src/RawUdpSocket.cpp include/RawUdpSocket.h include/AddressInfo.h)

#set(SOURCE_FILES main.cpp)
#add_executable(UdpSocketLib ${SOURCE_FILES})