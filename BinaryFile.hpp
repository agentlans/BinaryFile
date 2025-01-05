#ifndef BINARYFILE_HPP
#define BINARYFILE_HPP

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

class BinaryFile {
public:
    enum class Mode {
        READ,
        WRITE,
        APPEND,
        READ_WRITE
    };

    BinaryFile();
    
    bool open(const std::string& filename, Mode mode);
    void close();
    
    std::streamoff get_offset();
    std::streamsize size();
    
    std::vector<char> read(size_t n);
    void read(char* buffer, size_t n);
    
    void write(const char* data, size_t n);
    void write(const std::vector<char>& data);
    
    void seek(std::streamoff offset, bool relative);
    
    bool eof() const;
    bool is_writable_mode() const;

private:
    std::fstream fileStream;

    void check_open() const; // Checks if the file is open
};

#endif // BINARYFILE_HPP
