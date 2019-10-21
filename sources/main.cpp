//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#include "../headers/helpers.h"
#include <stdio.h>
#include <unistd.h>

int mpwd(vector<string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.size() == 0) {
        string path;
        get_current_path(&path);
        cout << path << endl;
        return 0;
    } else if ((cmd.size() == 1) && ((cmd[0] == "-h") || (cmd[0] == "--help"))) {
        cout << "The command returns the current path." << endl;
        return 0;
    } else {
        std::cerr << "It is not such options. Use [-h, --help]." << endl;
        return -1;
    }
}

int mcd(vector<string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.size() == 1 && chdir(cmd[0].c_str()) == 0) {
        return 0;
    } else if (cmd.size() == 2 && (cmd[1] == "-h" || cmd[1] == "--help")) {
        cout<< "The command changes the directory to the <path>" <<endl;
        return chdir(cmd[0].c_str());
    } else if(cmd.size() == 1 && (cmd[0] == "-h" || cmd[0] == "--help")) {
        cout << "The command changes the directory to the <path>" << endl;
        return 1;
    } else {
        std::cerr << "It is not such options. Use [-h, --help]." << endl;
        return -1;
    }
}

void execute(std::map<string, string>& vars, vector<string>& args) {
    int err_code = 0;
    if (args.empty()) {
        exit(-2);
    }
    string cmd = args[0];
    if (cmd == "merrno") {
        cout << err_code << endl;
    } else if (cmd == "mpwd") {
        err_code = mpwd(args);
    } else if (cmd == "mcd") {
        err_code = mcd(args);
    } else if (cmd == "help") {
        cout << "Program MyShell. version 1.0 beta release\n" << endl;
        cout << "merrno [-h|--help] \t returns exit status of the command" << endl;
        cout << "mpwd [-h|--help] \t returns current directory path" << endl;
        cout << "mcd <path> [-h|--help] \t change dir to <path>" << endl;
        cout << "mexit [exit code] [-h|--help] \t exit myshell\n" << endl;
    }
}

int main(int argc, char *argv[]) {

    std::map<string, string> variables;

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
        } else {
            boost::escaped_list_separator<char> els(separator1,separator2,separator3);
            boost::tokenizer<boost::escaped_list_separator<char>> tok(command, els);

            for (auto &t : tok) {
                args.push_back(t);
            }

            execute(variables, args);
        }
    }

    return 0;
}