cmake_minimum_required(VERSION 3.10)
project(UbuntuCloudFetcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Poco REQUIRED COMPONENTS Foundation Net NetSSL Crypto Util JSON)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main ubuntu_cloud_fetcher Poco::Foundation Poco::Net Poco::NetSSL Poco::Crypto Poco::Util Poco::JSON)

target_include_directories(main PRIVATE include)
