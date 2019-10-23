//
// Created by Serhiy Rosovskyy on 10/23/19.
//

#ifndef OS_MYSHELL_FUNCTIONS_H
#define OS_MYSHELL_FUNCTIONS_H

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

int mpwd(vector<string>& cmd);
int mcd(vector<string>& cmd);
void mexec(vector<string>& args);
void mexit(vector<string>& args);
void mexport(std::vector<std::string>& args);

#endif //OS_MYSHELL_FUNCTIONS_H
