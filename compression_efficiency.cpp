#include <iostream>
#include <fstream>

long getFileSize(const std::string& fileName) {
    std::ifstream file(fileName, std::ifstream::binary | std::ifstream::ate);
    if (!file) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return -1;
    }
    return file.tellg();
}

int main() {
    std::string originalFilePath = "source.txt";
    std::string lzwCompressedFilePath = "compressed.txt";
    std::string zstdCompressedFilePath = "zstandart.txt";

    long originalSize = getFileSize(originalFilePath);
    long lzwCompressedSize = getFileSize(lzwCompressedFilePath);
    long zstdCompressedSize = getFileSize(zstdCompressedFilePath);

    double lzwCompressionEfficiency = (1.0 - double(lzwCompressedSize) / originalSize) * 100;
    double zstdCompressionEfficiency = (1.0 - double(zstdCompressedSize) / originalSize) * 100;

    std::cout << "Original file size: " << originalSize << " bytes" << std::endl;
    std::cout << "LZW Compressed file size: " << lzwCompressedSize << " bytes" << std::endl;
    std::cout << "Zstandard Compressed file size: " << zstdCompressedSize << " bytes" << std::endl;
    std::cout << "LZW Compression efficiency: " << lzwCompressionEfficiency << "%" << std::endl;
    std::cout << "Zstandard Compression efficiency: " << zstdCompressionEfficiency << "%" << std::endl;

    return 0;
}
