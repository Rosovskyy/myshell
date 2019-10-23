
#include "functions.h"

#include <cstdio>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>


void execute(std::vector<std::string>& args) {
    int err = 0;
    std::string cmd = args[0];
    if (cmd == "merrno") {
        std::cout << err << std::endl;
    } else if (cmd == "mpwd") {
        err = mpwd(args);
    } else if (cmd == "mcd") {
        err = mcd(args);
    } else if (cmd == "mexit") {
        mexit(args);
    } else if (cmd == "mecho") {
        mexec(args);
    } else if (cmd == "mexport") {
        std::cout << "export" << std::endl;
    } else if (cmd == "help") {
            std::cout << "Program MyShell. version 1.0 beta release\n" << std::endl;
            std::cout << "merrno [-h|--help] \t returns exit status of the command" << std::endl;
            std::cout << "mpwd [-h|--help] \t returns current directory path" << std::endl;
            std::cout << "mcd <path> [-h|--help] \t change dir to <path>" << std::endl;
            std::cout << "mexit [exit code] [-h|--help] \t exit myshell\n" << std::endl;
    }
}

int main(int argc, char *argv[]) {

    std::string separator1("");
    std::string separator2(" ");
    std::string separator3("\"\'");

    std::string s;
    while (true) {
        std::string command;
        std::vector<std::string> args;
        get_current_path(&s);
        std::cout << s << " $ ";
        getline(std::cin, command);
        if (std::cin.fail() || std::cin.eof()) {
            std::cin.clear();
            break;
        } else if (s.empty()) {
            exit(-15);
        } else {
            boost::escaped_list_separator<char> els(separator1,separator2,separator3);
            boost::tokenizer<boost::escaped_list_separator<char>> tok(command, els);
            for (auto &t : tok) {
                args.push_back(t);
            }
            execute(args);
        }
    }

    return 0;
}

//#include <functional>
//#include <unordered_map>
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>

//#include <fstream>
//#include <sstream>
//#include <map>
//#include <errno.h>
//#include <fcntl.h>
