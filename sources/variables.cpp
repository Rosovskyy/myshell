//
// Created by Serhiy Rosovskyy on 10/23/19.
//

#include "../headers/variables.h"
#include "../headers/helpers.h"

void splitValues(std::map<string, string>& variables, const string& line) {
    vector<string> res;
    std::size_t current, previous = 0;
    std::string delim = "=";
    current = line.find(delim);
    while (current != std::string::npos) {
        res.push_back(line.substr(previous, current - previous));
        previous = current + 1;
        current = line.find(delim, previous);
    }
    res.push_back(line.substr(previous, current - previous));
    variables[res.front()] = res.back();
}

void msetenv(string line, map<string, string>& value) {
    if (line.find('=') != string::npos) {
        vector<string> res;

        std::size_t current, previous = 0;
        std::string delim = "=";
        current = line.find(delim);
        while (current != std::string::npos) {
            res.push_back(line.substr(previous, current - previous));
            previous = current + 1;
            current = line.find(delim, previous);
        }
        res.push_back(line.substr(previous, current - previous));

        setenv(res.front().c_str(), res.back().c_str(), 1);
    } else {
        if (value.count(line) > 0) {
            setenv(line.c_str(), value[line].c_str(), 0);
        }
    }
}