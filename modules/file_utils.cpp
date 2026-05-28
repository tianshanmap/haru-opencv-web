#include <filesystem>
#include <iostream>
#include <random>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;
namespace haru {
    void move_file(std::string source,std::string parent){
        fs::path filePath = source;
        fs::path destination;
        if (filePath.extension() == ".jpg") {
            destination = parent + "/" + filePath.stem().string() + ".jpeg";
        } else {
            destination = parent + "/" + filePath.filename().string();
        }
        std::cout << "move_file::" << source << " to " << destination << std::endl;
        fs::rename(source, destination);
    }
    void clear_folder(std::string path) {
        fs::path folderPath(path);
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            fs::remove(entry.path());
        }  
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
    std::string create_folder_under(std::string pathname,std::string name){
        fs::path filePath(pathname);
        std::string target = filePath.parent_path().string() + "/" + name;
        clear_folder(target);
        create_folder(target);
        return target;
    }
    int process_filesystem_file(std::string path,std::string destination){
        // std::cout << "process_filesystem_file::" << path << std::endl;
        fs::path filePath(path);
        // Get the parent path
        fs::path parent = filePath.parent_path().filename();
        std::string target = destination + "/" + parent.string() + "/jpeg";
        if (path.ends_with(".jpeg") || path.ends_with(".jpg")){
            // std::cout << "process_filesystem_file::jpeg" << path << std::endl;
            std::string target = destination + "/" + parent.string() + "/jpeg";
            create_folder(target);
            move_file(filePath.string(),target);
        } else if (path.ends_with(".mov") || path.ends_with(".mp4")){
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
    void find_image_directory(std::string path,std::vector<std::string> &files) {
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory() && entry.path().filename() == "jpeg") {
                files.push_back(entry.path().string());
            } else if (entry.is_directory()){
                find_image_directory(entry.path().string(),files);
            }
        }
    }
    int scan_directory(const std::string path,std::vector<std::string> &files,const std::string extension) {
        // std::string path = "/Users/developer/T9/travels/2026-01-14_2026-03-25/2026-01-16-2026-01-23-singapore-maleka";
        std::cout << "scan_filesystem_directory::" << path << std::endl;
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
                scan_directory(entry.path(),files,extension);
            } else {
                if (entry.path().extension() == extension) {
                    files.push_back(entry.path().string());
                }
            }
        }
        return 0;
    }
    void write_to_file(std::string &path,std::ostringstream &buffer) {
        std::ofstream myfile;
        myfile.open (path + "/mov.txt");
        myfile << buffer.str();
        myfile.close();
        buffer.str("");
        buffer.clear();
        std::cout << "write_to_file::" << path << std::endl;
    }
    std::vector<std::string> create_textfile_for_merge(std::vector<std::string> &files) {
        std::vector<std::string> files_parent;
        std::vector<std::string> files_with_same_parent;
        std::filesystem::path currentFilePath(files[0]);
        std::string current_parent = currentFilePath.parent_path().string();
        std::ostringstream buffer;
        for (int i = 0; i < files.size(); i++) {
            std::filesystem::path filePath(files[i]);
            std::string parent = filePath.parent_path().string();
            if (parent != current_parent) {
                files_parent.push_back(parent);
                if (!buffer.str().empty()) {
                    write_to_file(current_parent,buffer);
                }
                current_parent = parent;
            }
            buffer << "file " << "'" << files[i] << "'" << std::endl;
        }
        if (!buffer.str().empty()) {
            write_to_file(current_parent,buffer);
        }
        return files_parent;
    }
}
