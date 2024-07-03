#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include <string>

class IO {
    std::fstream file_stream;
public:
    IO(const std::string& file_path);
    ~IO();
    std::fstream getFileStream();
};

#endif