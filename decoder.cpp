#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

// Функция для чтения сжатых данных из файла
std::vector<int> readCompressedData(const std::string& filePath) {
    std::vector<int> compressedData;
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        compressedData.push_back(value);
    }

    inFile.close();
    return compressedData;
}

// Функция для распаковки данных алгоритмом LZW
std::string decompressLZW(const std::vector<int>& compressedData) {
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = std::string(1, char(i));
    }

    std::string w(1, char(compressedData[0]));
    std::string result = w;
    std::string entry;
    int dictSize = 256;

    for (size_t i = 1; i < compressedData.size(); i++) {
        int k = compressedData[i];
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictSize) {
            entry = w + w[0];
        } else {
            throw std::runtime_error("Bad compressed k");
        }

        result += entry;
        
        // Добавляем новую последовательность в словарь
        if (!w.empty()) {
            dictionary[dictSize++] = w + entry[0];
        }
        
        w = entry;
    }

    return result;
}

// Основная функция
int main() {
    const std::string compressedFilePath = "compressed.txt";
    const std::string decompressedFilePath = "sourceNew.txt";

    auto compressedData = readCompressedData(compressedFilePath);
    std::string decompressedData = decompressLZW(compressedData);

    std::ofstream outFile(decompressedFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << decompressedFilePath << std::endl;
        exit(EXIT_FAILURE);
    }

    outFile << decompressedData;
    outFile.close();

    std::cout << "Decompression completed successfully. Check " << decompressedFilePath << std::endl;

    return 0;
}
