#include "ubuntu_cloud_image_fetcher_impl.h"
#include <iostream>

void print_menu() {
    std::cout << "\nSelect an option:\n";
    std::cout << "1. List all currently supported Ubuntu releases\n";
    std::cout << "2. Display the current Ubuntu LTS version\n";
    std::cout << "3. Get the SHA256 hash for a specific Ubuntu release\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    try {
        const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
        UbuntuCloudImageFetcherImpl fetcher(url);

        while (true) {
            print_menu();

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    auto releases = fetcher.get_supported_releases();
                    std::cout << "\nSupported Ubuntu Releases:\n";
                    for (const auto& release : releases) {
                        std::cout << "  - " << release << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::cout << "\nCurrent LTS Version: " << fetcher.get_current_lts_version() << std::endl;
                    break;
                }
                case 3: {
                    std::string release;
                    std::cout << "\nEnter the release version (e.g., 23.10): ";
                    std::cin >> release;
                    try {
                        std::cout << "SHA256 for " << release << ": " 
                                  << fetcher.get_sha256_for_release(release) << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Error fetching SHA256 for release " << release << ": " << e.what() << std::endl;
                    }
                    break;
                }
                case 4: {
                    std::cout << "Exiting. Goodbye!" << std::endl;
                    return 0;
                }
                default: {
                    std::cerr << "Invalid choice. Please enter a valid option (1-4)." << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
