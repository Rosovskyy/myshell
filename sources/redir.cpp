//
// Created by Serhiy Rosovskyy on 11/9/19.
//

#include "../headers/redir.h"

void redirect(std::string from, std::string to, std::map<string, string>& vars, bool stdout, bool stdin) {
    int fd = open(to.c_str(), O_TRUNC | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        std::cerr << "Some troubles while opening file" << std::endl;
        exit(17);
    }
    std::vector<std::string> arg(1, from);
    if (stdin) {
        mexec(arg, vars, false, fd, -1, stdout);
    } else {
        mexec(arg, vars, false, -1, fd, stdout);
    }
    close(fd);
}
