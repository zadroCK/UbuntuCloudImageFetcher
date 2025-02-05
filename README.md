# Ubuntu Cloud Image Fetcher

Ubuntu Cloud Image Fetcher is a simple tool for retrieving and displaying information about the latest Ubuntu Cloud images from the official Ubuntu cloud website. The tool uses the Simplestreams data format to fetch details about various Ubuntu releases, including supported releases, the current LTS (Long-Term Support) version, and the SHA256 hash for specific images.

## Requirements

This project uses the **Poco Libraries** for networking and JSON parsing. To build this project, you'll need to install the Poco library.

## Features

The project implements the following functionalities through the `UbuntuCloudImageFetcher` interface:

### 1. get_supported_releases()
   This function returns a list of all currently supported Ubuntu releases. It returns a vector of strings containing the names of the releases.

### 2. get_current_lts_version()
   This function returns the current Ubuntu LTS (Long-Term Support) version. LTS versions are releases that receive extended support and are often used in production environments.

### 3. get_sha256_for_release(const std::string& release)
   This function returns the SHA256 hash for a specific Ubuntu release image. The hash is used to verify the integrity of the image. The function's argument is the release name (e.g., "20.04", "22.04").

## Build the Project

#### Linux

To build and run the project on Linux, use the following script:
```bash
mkdir -p build

cd build

cmake ..

make

./main
```


## CLI Usage

When you run the program, you will be prompted to choose one of the following options:

1. Print the list of all supported Ubuntu releases.
2. Print the current LTS version.
3. Print the SHA256 hash for a specific release.

If you choose option 3, you will be asked to enter the name of the Ubuntu release (e.g., "20.04", "22.04").

After completing any of the options, the program will return to the initial menu.

