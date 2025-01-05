#include "BinaryFile.hpp"

// Default constructor
BinaryFile::BinaryFile() : fileStream() {}

// Open a binary file with the specified mode
bool BinaryFile::open(const std::string& filename, Mode mode) {
    std::ios_base::openmode openMode = std::ios::binary;
    
    switch (mode) {
        case Mode::READ:
            openMode |= std::ios::in;
            break;
        case Mode::WRITE:
            openMode |= std::ios::out | std::ios::trunc;
            break;
        case Mode::APPEND:
            openMode |= std::ios::out | std::ios::app;
            break;
        case Mode::READ_WRITE:
            openMode |= std::ios::in | std::ios::out;
            break;
    }

    fileStream.open(filename, openMode);
    return fileStream.is_open();
}

// Close the binary file
void BinaryFile::close() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

// Get the current offset in the file
std::streamoff BinaryFile::get_offset() {
    check_open();
    return fileStream.tellg();
}

// Get the size of the file
std::streamsize BinaryFile::size() {
    check_open();
    std::streamoff currentPos = get_offset();
    
    // Seek to the end to get the size
    fileStream.seekg(0, std::ios::end);
    std::streamsize fileSize = fileStream.tellg();
    
    // Restore original position
    seek(currentPos, true);
    
    return fileSize;
}

// Read 'n' bytes into a vector and return it
std::vector<char> BinaryFile::read(size_t n) {
    check_open();
    std::vector<char> buffer(n);
    read(buffer.data(), n);
    return buffer;
}

// Read 'n' bytes into a provided buffer
void BinaryFile::read(char* buffer, size_t n) {
    check_open();
    if (!fileStream.read(buffer, n)) {
        throw std::runtime_error("Failed to read from binary file.");
    }
}

// Write 'n' bytes from a char array
void BinaryFile::write(const char* data, size_t n) {
    check_open();
    if (!fileStream.write(data, n)) {
        throw std::runtime_error("Failed to write to binary file.");
    }
}

// Write data from a vector
void BinaryFile::write(const std::vector<char>& data) {
    write(data.data(), data.size());
}

// Seek to a specific offset; relative means offset is relative to current position
void BinaryFile::seek(std::streamoff offset, bool relative) {
    check_open();
    if (relative) {
        fileStream.seekg(offset, std::ios_base::cur);
        fileStream.seekp(offset, std::ios_base::cur);
    } else {
        fileStream.seekg(offset, std::ios_base::beg);
        fileStream.seekp(offset, std::ios_base::beg);
    }
}

// Check if end-of-file has been reached
bool BinaryFile::eof() const {
    return fileStream.eof();
}

// Check if the current mode allows writing
bool BinaryFile::is_writable_mode() const {
    return (fileStream.flags() & std::ios_base::out) != 0;
}

// Check if the file is open; throws an exception if not
void BinaryFile::check_open() const {
    if (!fileStream.is_open()) {
        throw std::runtime_error("The binary file is not open.");
    }
}
