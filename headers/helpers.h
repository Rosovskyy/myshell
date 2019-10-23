//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#ifndef MYSHELL_HELPERS_H
#define MYSHELL_HELPERS_H

#include <boost/tokenizer.hpp>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

void get_current_path(string *str);
bool is_number(const std::string& s);
void msetenv(std::map<string, string>& value, const string& line);

#endif //MYSHELL_HELPERS_H
