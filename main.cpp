#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include "../src/app/processes/ProcessManagement.hpp"
#include "../src/app/processes/Task.hpp"



int main(int argc, char* argv[]) {
    std::string directory;
    std::string action;

    std::cout << "ENTER THE DIRECTORY PATH : ";
    std::getline(std::cin, directory);

    std::cout << "(ENCRYPT/ DECRYPT)? : ";
    std::getline(std::cin, action);

    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            ProcessManagement processManagement;

            for (const auto& entry : fs::recursive_directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    std::string filePath = entry.path().string();
                    IO io(filePath);
                    std::fstream f_stream = std::move(io.getFileStream());

                    if(f_stream.is_open()){
                        Action taskAction = (action == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
                        auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filePath);
                        processManagement.submitToQueue(std::move(task));
                    } 
                    else{
                        std::cout << "FILE : " << filePath<<" CAN'T BE OPENED" << std::endl;
                    }
                }
            }

            processManagement.executeTasks();
        } 
        else{
            std::cout << "INVALID DIRECTORY PATH" << std::endl;
        }
    } 
    catch (const fs::filesystem_error& ex) {
        std::cout << "FILESYSTEM ERROR: " << ex.what() << std::endl;
    }
    return 0;
}