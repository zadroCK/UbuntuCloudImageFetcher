#ifndef UBUNTU_CLOUD_IMAGE_FETCHER_H
#define UBUNTU_CLOUD_IMAGE_FETCHER_H

#include <string>
#include <vector>

class UbuntuCloudImageFetcher {
public:
    virtual ~UbuntuCloudImageFetcher() = default;

    virtual std::vector<std::string> get_supported_releases() const = 0;

    virtual std::string get_current_lts_version() const = 0;

    virtual std::string get_sha256_for_release(const std::string& release) const = 0;
};

#endif // UBUNTU_CLOUD_IMAGE_FETCHER_H
