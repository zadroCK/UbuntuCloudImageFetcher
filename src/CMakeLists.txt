add_library(ubuntu_cloud_fetcher ubuntu_cloud_image_fetcher_impl.cpp)

target_link_libraries(ubuntu_cloud_fetcher Poco::Foundation Poco::Net Poco::NetSSL Poco::Crypto Poco::Util)

target_include_directories(ubuntu_cloud_fetcher PRIVATE ../include)
