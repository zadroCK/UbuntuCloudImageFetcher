#include<iostream>
#include "ubuntu_cloud_image_fetcher_impl.h"

UbuntuCloudImageFetcherImpl::UbuntuCloudImageFetcherImpl(const std::string& url){
    std::string json_data = fetch_json_data(url);
    Poco::JSON::Parser parser;
    auto result = parser.parse(json_data);
    root_object = result.extract<Poco::JSON::Object::Ptr>();
}

std::string UbuntuCloudImageFetcherImpl::fetch_json_data(const std::string& url){
    Poco::URI uri(url);
    Poco::Net::Context::Ptr context = new Poco::Net::Context(
        Poco::Net::Context::CLIENT_USE,
        "",
        "",
        "", 
        Poco::Net::Context::VERIFY_NONE,
        9,
        false
    );
    Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);

    Poco::Net::HTTPResponse response;
    session.sendRequest(request);

    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        throw std::runtime_error("Failed to fetch JSON data: " + std::to_string(response.getStatus()));
    }

    std::istream& rs = session.receiveResponse(response);    
    std::string response_data;
    Poco::StreamCopier::copyToString(rs, response_data);

    return response_data;
}

std::vector<std::string> UbuntuCloudImageFetcherImpl::get_supported_releases() const{
    std::vector<std::string> releases;
    auto products = root_object->getObject("products");
    for (const auto& key : *products){
        const auto& product = products->getObject(key.first);
        if (product->has("arch") && product->getValue<std::string>("arch") == "amd64" && product->getValue<std::string>("os") == "ubuntu") {
            releases.push_back(product->getValue<std::string>("release_title") + ", " + product->getValue<std::string>("release_codename"));
        }
    }
    return releases;
}

std::string UbuntuCloudImageFetcherImpl::get_current_lts_version() const{
    auto products = root_object->getObject("products");
    std::string current_version = "Unknown";
    for (const auto& key : *products) {
        const auto& product = products->getObject(key.first);
        if (product->has("arch") && product->getValue<std::string>("arch") == "amd64" && product->getValue<std::string>("release_title").find("LTS") != std::string::npos) {
            current_version = product->getValue<std::string>("release_title") + ", " + product->getValue<std::string>("release_codename");
        }
    }
    return current_version;
}

std::string UbuntuCloudImageFetcherImpl::get_sha256_for_release(const std::string& release) const{
    auto products = root_object->getObject("products");
    for (const auto& key : *products) {
        const auto& product = products->getObject(key.first);
        if(product->has("arch") && product->getValue<std::string>("arch") == "amd64" && product->getValue<std::string>("release_title").find(release) != std::string::npos){
            const auto& versions = product->getObject("versions");
            auto latest_version_key = versions->begin()->first;
            for(const auto& version : *versions){
                if(latest_version_key < version.first){
                    latest_version_key = version.first;
                }
            }
            const auto& version_object = versions->getObject(latest_version_key);
            const auto& items = version_object->getObject("items");
            if (items->has("disk1.img")) {
                return items->getObject("disk1.img")->getValue<std::string>("sha256");
            }
        }
    }
    return "Unknown";
}
