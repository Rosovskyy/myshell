#include "../headers/helpers.h"
#include "../headers/functions.h"
#include "../headers/wildcards.h"

void execute(std::vector<std::string>& args, std::map<std::string, std::string>& vars) {
    int err = 0;
    std::string cmd = args[0];
    if (cmd == "merrno") {
        std::cout << err << std::endl;
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
            std::cout << "* merrno [-h|--help] - print the end code of the last program or command\n"
                    "* mpwd [-h|--help] - print the current path\n"
                    "* mcd [-h|--help] - move the\n"
                    "* mexit [end code] [-h|--help] - exit myshell\n"
                    "* mecho [text|$<var_name>] [text|$<var_name>] [text|$<var_name>] - print arguments or value of variable\n"
                    "* mexport <var_name>[=VAL] - add global variable" << std::endl;
    } else {
        mecho(args, vars);
    }
}

bool findQuotes(std::string command) {
    std::vector<int> indexes;
    int number = 0;
    for (int i = 0; i < command.size(); i++) {
        if (command[i] == '"') {
            if (number % 2 == 1 && (i + 1) < command.size()) {
                if (command[i + 1] != ' ') {
                    return false;
                }
            }
            number++;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::string nun(""), space(" "), slash("\"\'");
    std::map<std::string, std::string> globalVariables;
    std::string s;
    get_current_path(&s);
    std::cout << s;
    char* buf;
    while ((buf = readline(" $ ")) != nullptr) {
        std::vector<std::string> args;
        if (strlen(buf) > 0) {
            add_history(buf);
        }
        std::string command(buf);
        if (!findQuotes(command)) {
            std::cerr << "Bad string format. Use space after quotes!" << std::endl;
            std::cout << s;
            continue;
        }
        boost::escaped_list_separator<char> separators(nun,space,slash);
        boost::tokenizer<boost::escaped_list_separator<char>> arguments(command, separators);
        for (auto &t : arguments) {
            args.push_back(t);
        }

        std::vector<std::string> all_args(args.begin() + 1, args.begin() + args.size()), wild_args;
        std::copy_if (all_args.begin(), all_args.end(), std::back_inserter(wild_args), [](const std::string &str)
        {return (str.find('*') != std::string::npos ||
                 str.find('?') != std::string::npos ||
                 str.find('[') != std::string::npos) ||
                str.find(']') != std::string::npos;} );
        if (!wild_args.empty()) {
            std::vector<std::string> neww = parse_args(wild_args);
            std::copy_if (all_args.begin(), all_args.end(), std::back_inserter(neww), [](const std::string &str)
            {return (str.find('*') == std::string::npos &&
                     str.find('?') == std::string::npos &&
                     str.find('[') == std::string::npos) &&
                    str.find(']') == std::string::npos;} );
            neww.insert(neww.begin(), 1, args[0]);
            execute(neww, globalVariables);
        } else {
            execute(args, globalVariables);
        }

        free(buf);
        get_current_path(&s);
        std::cout << s;
    }
    return 0;
}
