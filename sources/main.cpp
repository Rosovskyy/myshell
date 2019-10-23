#include "../headers/helpers.h"
#include "../headers/functions.h"

void execute(vector<string>& args, std::map<string, string>& vars) {
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
        mexec(args, vars);
    } else if (cmd == "mexport") {
        mexport(args, vars);
    } else if (cmd == "help") {
            cout << "* merrno [-h|--help] - print the end code of the last program or command\n"
                    "* mpwd [-h|--help] - print the current path\n"
                    "* mcd [-h|--help] - move the\n"
                    "* mexit [end code] [-h|--help] - exit myshell\n"
                    "* mecho [text|$<var_name>] [text|$<var_name>] [text|$<var_name>] - print arguments or value of variable\n"
                    "* mexport <var_name>[=VAL] - add global variable" << endl;
    }
}

int main(int argc, char *argv[]) {
    string nun(""), space(" "), slash("\"\'");
    map<string, string> globalVariables;
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
        } else if (s.empty()) {
            exit(-15);
        } else {
            boost::escaped_list_separator<char> separators(nun,space,slash);
            boost::tokenizer<boost::escaped_list_separator<char>> arguments(command, separators);
            for (auto &t : arguments) {
                args.push_back(t);
            }
            execute(args, globalVariables);
        }
    }

    return 0;
}
