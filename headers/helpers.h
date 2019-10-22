//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#ifndef MYSHELL_HELPERS_H
#define MYSHELL_HELPERS_H

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <mach-o/dyld.h>
#include <functional>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
#include <map>
#include <errno.h>
#include <fcntl.h>
#include <boost/algorithm/string.hpp>

using namespace std;

void get_current_path(string *str);
int mpwd(vector<string>& cmd);
int mcd(vector<string>& cmd);
void mexec(vector<string>& args);

#endif //MYSHELL_HELPERS_H
