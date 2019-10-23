//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#include "../headers/helpers.h"
#include <stdio.h>
#include <unistd.h>

void execute(vector<string>& args) {
    int err = 0;
    string cmd = args[0];
    if (cmd == "merrno") {
        cout << err << endl;
    } else if (cmd == "mpwd") {
        err = mpwd(args);
    } else if (cmd == "mcd") {
        err = mcd(args);
    } else if (cmd == "mexit") {
        mexit(args);
    } else if (cmd == "mecho") {
        mexec(args);
    } else if (cmd == "mexport") {
        cout << "export" << endl;
    } else if (cmd == "help") {
            cout << "Program MyShell. version 1.0 beta release\n" << endl;
            cout << "merrno [-h|--help] \t returns exit status of the command" << endl;
            cout << "mpwd [-h|--help] \t returns current directory path" << endl;
            cout << "mcd <path> [-h|--help] \t change dir to <path>" << endl;
            cout << "mexit [exit code] [-h|--help] \t exit myshell\n" << endl;
    }
}

int main(int argc, char *argv[]) {

    string separator1("");
    string separator2(" ");
    string separator3("\"\'");

    string s;
    while (true) {
        string command;
        vector<string> args;
        get_current_path(&s);
        cout << s << " $ ";
        getline(cin, command);
        if (cin.fail() || cin.eof()) {
            cin.clear();
            break;
        } else if (s == "") {
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