cmake_minimum_required(VERSION 3.27.0)
project(NFLSchedulePresenter VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories("libs/asio-1.28.0/include")

set(HEADERS
    CApiDataCompiler.hpp
    CApiDataReader.hpp
    CHttpClient.hpp
    Data/CGame.hpp
    Data/CWeek.hpp
    )
    
    set(SOURCES
    CApiDataCompiler.cpp
    CApiDataReader.cpp
    CHttpClient.cpp
    InternalDb.hpp
    main.cpp
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
