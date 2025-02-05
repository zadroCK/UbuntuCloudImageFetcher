#ifndef UBUNTU_CLOUD_IMAGE_FETCHER_IMPL_H
#define UBUNTU_CLOUD_IMAGE_FETCHER_IMPL_H

#include "ubuntu_cloud_image_fetcher.h"

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>


class UbuntuCloudImageFetcherImpl : public UbuntuCloudImageFetcher {
public:
    UbuntuCloudImageFetcherImpl(const std::string& url);
    ~UbuntuCloudImageFetcherImpl() override = default;

    std::vector<std::string> get_supported_releases() const override;
    std::string get_current_lts_version() const override;
    std::string get_sha256_for_release(const std::string& release) const override;

private:
    Poco::JSON::Object::Ptr root_object;

    std::string fetch_json_data(const std::string& url);
};

#endif // UBUNTU_CLOUD_IMAGE_FETCHER_IMPL_H
