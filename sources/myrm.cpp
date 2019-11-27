#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

void dir_remove(std::string file) {
    if (boost::filesystem::exists(file)) {
        try {
            boost::filesystem::remove_all(file);
        } catch (...) {
            exit(-1);
        }
    } else {
        exit(-1);
    }
}

void remove_force(std::string file) {
    if (boost::filesystem::exists(file)) {
        if (!boost::filesystem::is_directory(file)) {
            try {
                boost::filesystem::remove(file);
            } catch (...) {
                exit(-1);
            }
        } else {
            exit(-1);
        }
    } else {
        exit(-1);
    }
}

int main(int argc, const char * argv[]) {
    bool force = false, dirRemove = false;
    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            std::cout << "myrm [-h|--help] [-f] [-R] <file1> <file2> <file3>\n"
                         "-f - just delete\n"
                         "-R - delete directories" << std::endl;
            exit(0);
        } else if (strcmp(argv[i], "-f") == 0) {
            force = true;
        } else if (strcmp(argv[i], "-R") == 0) {
            dirRemove = true;
        } else {
            files.push_back(argv[i]);
        }
    }

    for (int i = 0; i < files.size(); i++) {
        if (force && !dirRemove) {
            remove_force(files[i]);
        } else if (force) {
            dir_remove(files[i]);
        } else {
            std::string answer;
            std::cout << "Delete the " << files[i] << "? [Y/n] ";
            std::cin >> answer;
            boost::to_lower(answer);
            if (answer.at(0) == 'y') {
                if (dirRemove) {
                    dir_remove(files[i]);
                } else {
                    remove_force(files[i]);
                }
            } else if (answer.at(0) == 'a') {
                continue;
            } else if (answer.at(0) == 'c') {
                break;
            } else {
                exit(-1);
            }
        }
    }
    return 0;
}