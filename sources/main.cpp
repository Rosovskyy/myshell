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
        mecho(args, vars);
    } else if (cmd == "mexport") {
        mexport(args, vars);
    } else if (cmd == "help") {
            cout << "* merrno [-h|--help] - print the end code of the last program or command\n"
                    "* mpwd [-h|--help] - print the current path\n"
                    "* mcd [-h|--help] - move the\n"
                    "* mexit [end code] [-h|--help] - exit myshell\n"
                    "* mecho [text|$<var_name>] [text|$<var_name>] [text|$<var_name>] - print arguments or value of variable\n"
                    "* mexport <var_name>[=VAL] - add global variable" << endl;
    } else {
        mecho(args, vars);
    }
}

#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[]) {
    string nun(""), space(" "), slash("\"\'");
    map<string, string> globalVariables;
    string s;
    get_current_path(&s);
    cout << s;
    char* buf;
    while ((buf = readline(" $ ")) != nullptr) {
        vector<string> args;
        get_current_path(&s);
        if (strlen(buf) > 0) {
            add_history(buf);
        }
        string command(buf);
        boost::escaped_list_separator<char> separators(nun,space,slash);
        boost::tokenizer<boost::escaped_list_separator<char>> arguments(command, separators);
        for (auto &t : arguments) {
            cout << "value: " << t << endl;
            args.push_back(t);
        }
        execute(args, globalVariables);
        free(buf);
        cout << s;
    }
    return 0;
}
