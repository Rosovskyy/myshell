//
// Created by Serhiy Rosovskyy on 10/23/19.
//

#include "../headers/variables.h"
#include "../headers/helpers.h"

void splitValues(map<string, string>& variables, const string& command) {
    vector<string> variable;
    boost::split(variable, command, boost::is_any_of("="));
    variables[variable.front()] = variable.back();
}

void msetenv(string command, map<string, string>& value) {
    if (command.find('=') != string::npos) {
        vector<string> variable;
        boost::split(variable, command, boost::is_any_of("="));
        setenv(variable.front().c_str(), variable.back().c_str(), 1);
    } else {
        if (value.count(command) > 0) {
            setenv(command.c_str(), value[command].c_str(), 0);
        }
    }
}