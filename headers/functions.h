//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#ifndef MYSHELL_FUNCTIONS_H
#define MYSHELL_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>


void get_current_path(std::string *str);
int mpwd(std::vector<std::string>& cmd);
int mcd(std::vector<std::string>& cmd);
void mexec(std::vector<std::string>& args);
void mexit(std::vector<std::string>& args);

#endif //MYSHELL_FUNCTIONS_H
