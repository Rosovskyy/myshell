#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>

int main(int argc, const char * argv[]) {
    bool transition = false;
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            std::cout << "mymkdir [-h|--help] [-p]  <dirname>" << std::endl;
            std::cout << "-p - create all directories in the path" << std::endl;
            exit(0);
        } else if (strcmp(argv[i], "-p") == 0) {
            transition = true;
        } else {
            args.push_back(argv[i]);
        }
    }

    if (transition) {
        try {
            for (int i = 0; i < args.size(); i++) {
                boost::filesystem::path path(args[i]);
                boost::filesystem::create_directories(path);
            }
        } catch (...) {
            exit(-1);
        }
    } else {
        try {
            for (int i = 0; i < args.size(); i++) {
                boost::filesystem::path path(args[i]);
                if (boost::filesystem::exists(path)) {
                    std::cerr << "The directory with the same name already exists" << std::endl;
                    exit(-1);
                } boost::filesystem::create_directory(path);
            }
        } catch (...) {
            exit(-1);
        }
    }
    return 0;
}