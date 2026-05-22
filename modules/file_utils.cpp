#include <filesystem>
#include <iostream>
#include <random>

namespace fs = std::filesystem;
namespace haru {
    void move_file(std::string source,std::string parent){
        fs::path filePath = source;
        fs::path destination(parent + "/" + filePath.filename().string());
        std::cout << "move_file::" << source << " to " << destination << std::endl;
        fs::rename(source, destination);
    }

    void create_folder(std::string name){
        try {
            if (fs::create_directories(name)) {
                std::cout << "Directories created successfully\n";
            } else {
                // std::cout << "Directories already exist\n";
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    void create_folder(std::string parent,std::string name){
        create_folder(parent + "/" + name);
    }
    int process_filesystem_file(std::string path,std::string destination){
        // std::cout << "process_filesystem_file::" << path << std::endl;
        fs::path filePath(path);
        // Get the parent path
        fs::path parent = filePath.parent_path().filename();
        std::string target = destination + "/" + parent.string() + "/jpeg";
        if (path.ends_with(".jpeg")){
            // std::cout << "process_filesystem_file::jpeg" << path << std::endl;
            std::string target = destination + "/" + parent.string() + "/jpeg";
            create_folder(target);
            move_file(filePath.string(),target);
        } else if (path.ends_with(".mov")){
            std::cout << "process_filesystem_file::mov=>" << path << std::endl;
            std::string target = destination + "/" + parent.string() + "/mov";
            create_folder(target);
            move_file(filePath.string(),target);
        }
        return 1;
    }

    int process_filesystem_directory(std::string path,std::string destination) {
        // std::string path = "/Users/developer/T9/travels/2026-01-14_2026-03-25/2026-01-16-2026-01-23-singapore-maleka";
        std::cout << "process_filesystem_directory::" << path << std::endl;
        // Validate path

        std::error_code ec; // To handle errors without exceptions
         fs::path folderPath(path);
        std::cout << "\nContents of folder:\n";
        for (const auto& entry : fs::directory_iterator(folderPath, ec)) {
            if (ec) {
                std::cerr << "Error reading directory: " << ec.message() << "\n";
                return 1;
            }
            if (fs::is_directory(entry.path())){
                process_filesystem_directory(entry.path(),destination);
            } else {
                process_filesystem_file(entry.path(),destination);
            }
        }

        return 0;
    }

    int process_filesystem(std::string path,std::string destination){
        // Validate path
        create_folder(destination);
        fs::path folderPath(path);
        if (!fs::exists(folderPath)) {
            std::cerr << "Error: Path does not exist.\n";
            return 1;
        }
        if (fs::is_directory(folderPath)) {
            process_filesystem_directory(path,destination);
        } else {
            process_filesystem_file(path,destination);
        }
        return 1;
    }
    std::vector<std::string> getFiles(std::string path,std::string extension) {
        std::vector<std::string> files;
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == extension) {
                files.push_back(entry.path().string());
            }
        }
        return files;
    }
}
