CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
PROJECT(hsm)

ADD_EXECUTABLE(hsm)
TARGET_SOURCES(hsm
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hsm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/hsm.cpp
)
TARGET_INCLUDE_DIRECTORIES(hsm
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)