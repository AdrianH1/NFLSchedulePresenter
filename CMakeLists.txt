cmake_minimum_required(VERSION 3.27.0)
project(NFLSchedulePresenter VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories("libs/asio-1.28.0/include")

set(HEADERS
    CApiReader.hpp
)
    
    set(SOURCES
    main.cpp
    CApiReader.cpp
)

add_executable(NFLSchedulePresenter ${HEADERS} ${SOURCES} )

target_link_libraries(
    NFLSchedulePresenter 
    wsock32 
    ws2_32
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
