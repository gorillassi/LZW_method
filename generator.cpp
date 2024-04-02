#include <iostream>
#include <fstream>
#include <string>

void generateInputData(const std::string& filePath, int dataSize) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        return;
    }

    // Генерируем повторяющиеся последовательности символов
    std::string pattern = "ABCD";
    for (int i = 0; i < dataSize; i++) {
        outFile << pattern;
        // Добавляем немного вариативности
        if (i % 5 == 0) outFile << "XYZ";
        if (i % 10 == 0) outFile << "\n";
    }

    outFile.close();
    std::cout << "Generated input data in " << filePath << std::endl;
}

int main() {
    std::string filePath = "source.txt";
    int dataSize = 1000; // Размер данных, который определяет, сколько раз будет напечатана последовательность

    generateInputData(filePath, dataSize);

    return 0;
}
