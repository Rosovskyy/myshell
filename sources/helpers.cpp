//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#include "../headers/helpers.h"

void get_current_path(string *str) {
    *str = boost::filesystem::current_path().string();
}

bool is_number(const string& s)
{
    return !s.empty() && find_if(s.begin(),
                                      s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

vector<string> splitString(string line, string delim) {
    istringstream iss(line);
    vector<string> res((istream_iterator<string>(iss)),
                                 istream_iterator<string>());
    return res
}