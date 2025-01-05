#include <iostream>
#include "BinaryFile.hpp"

int main() {
    BinaryFile binaryFile;
    const std::string filename = "example.bin";

    // Write data to the file
    {
        if (binaryFile.open(filename, BinaryFile::Mode::WRITE)) {
            std::vector<char> data = {'H', 'e', 'l', 'l', 'o', ' ', 'B', 'i', 'n', 'a', 'r', 'y', ' ', 'F', 'i', 'l', 'e'};
            binaryFile.write(data);
            binaryFile.close();
        }
    }

    // Read data from the file
    {
        if (binaryFile.open(filename, BinaryFile::Mode::READ)) {
            auto readData = binaryFile.read(10); // Read 10 bytes
            std::cout << "Data read from file: ";
            std::cout.write(readData.data(), readData.size()); // Output the read data
            std::cout << std::endl;
            binaryFile.close();
        }
    }

    return 0;
}
