//
// Created by Serhiy Rosovskyy on 10/23/19.
//

#ifndef OS_MYSHELL_VARIABLES_H
#define OS_MYSHELL_VARIABLES_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <map>

using namespace std;

void splitValues(std::map<string, string>& vars, const string& line);
void msetenv(string line, std::map<string, string>& vars);

#endif //OS_MYSHELL_VARIABLES_H
