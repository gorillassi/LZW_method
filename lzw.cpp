#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>

// Функция для сжатия данных алгоритмом LZW
std::vector<int> compressLZW(const std::string& input, std::unordered_map<std::string, int>& dictionary) {
    int dictSize = dictionary.size();
    std::string w;
    std::vector<int> result;

    for (char c : input) {
        std::string wc = w + c;
        if (dictionary.count(wc)) {
            w = wc;
        } else {
            result.push_back(dictionary[w]);
            // Добавляем новую последовательность в словарь
            dictionary[wc] = dictSize++;
            w = std::string(1, c);
        }
    }

    // Добавляем оставшуюся последовательность
    if (!w.empty()) {
        result.push_back(dictionary[w]);
    }

    return result;
}

// Функция для записи сжатых данных в файл
void writeCompressedData(const std::string& filePath, const std::vector<int>& data) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int value : data) {
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    outFile.close();
}

int main() {
    const std::string inputFilePath = "source.txt";
    const std::string outputFilePath = "compressed.txt";

    // Загружаем содержимое файла
    std::ifstream inFile(inputFilePath);
    std::string data((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());
    inFile.close();

    // Инициализация словаря
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[std::string(1, char(i))] = i;
    }

    auto compressedData = compressLZW(data, dictionary);
    writeCompressedData(outputFilePath, compressedData);

    std::cout << "Compression completed successfully. Output file: " << outputFilePath << std::endl;

    return 0;
}
