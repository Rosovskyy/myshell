#include "helpers.h"
#include "functions.h"
#include "wildcards.h"
#include "redir.h"
#include "pipeline.h"

void get_current_path(string *str) {
    *str = boost::filesystem::current_path().string();
}

std::string strip(std::string str){
    if (str.back() == ' '){
        str = str.substr(0, str.size() - 1);
    }
    if (str.at(0) == ' '){
        str = str.substr(1, str.size() - 1);
    }
    return str;
}

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
        mexec(args, vars, false, -1, -1, false);
    } else if (cmd == "mexport") {
        mexport(args, vars);
    }
    else if (cmd[0] == '.' && std::find(args.begin(), args.end(), "|") == args.end()) {
            args[0] = args[0].replace(0, 1, "");
            mexec(args, vars, false, -1, -1, false);
    } else if (args[args.size() - 1] == "&") {
            mexec(args, vars, true, -1, -1, false);
    } else if (cmd == "help") {
            std::cout << "* merrno [-h|--help] - print the end code of the last program or command\n"
                    "* mpwd [-h|--help] - print the current path\n"
                    "* mcd [-h|--help] - move the\n"
                    "* mexit [end code] [-h|--help] - exit myshell\n"
                    "* mecho [text|$<var_name>] [text|$<var_name>] [text|$<var_name>] - print arguments or value of variable\n"
                    "* mexport <var_name>[=VAL] - add global variable" << std::endl;
    } else if (args.size() > 2) {
        if (std::find(args.begin(), args.end(), "|") != args.end()){
            std::vector<std::string> pipe_args;
            std::string buf;
            for (int j = 0; j != args.size(); ++j){
                if (args[j] != "|"){
                    buf += (args[j] + " ");
                }
                else {
                    pipe_args.emplace_back(strip(buf));
                    buf.erase();
                }
            }
            pipe_args.emplace_back(strip(buf));

            std::vector<const char *> pipe_args_n;
            for (auto &i: pipe_args) {
                pipe_args_n.emplace_back(i.c_str());
            }
            pipeline(pipe_args_n);
        }
        for (int i = 1; i < args.size() - 1; i++) {
            if (args[i] == ">") {
                redirect(args[i - 1], args[i + 1], vars, true, false);
            } else if (args[i] == "2>") {
                redirect(args[i - 1], args[i + 1], vars, false, false);
            } else if (args[i] == "<") {
                redirect(args[i - 1], args[i + 1], vars, false, true);
            } else if (args[i] == "2>&1") {
                redirect(args[0], args[2], vars, true, false);
                redirect(args[0], args[2], vars, false, false);
            }
        }
    } else {
        mexec(args, vars, false, -1, -1, false);
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

    std::map<std::string, std::string> globalVariables;

    if (argc > 1) {
        std::vector<std::string> args;
        for (int i = 1; i < argc; i++) {
            args.push_back(argv[i]);
        }
        exec_file(args, globalVariables);
        exit(0);
    }

    std::string nun(""), space(" "), slash("\"\'");
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
