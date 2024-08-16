cmake_minimum_required(VERSION 3.20)

project(SocketTesting)

add_executable(Server src/server.cpp)

add_executable(Client src/client.cpp)