
#include "../headers/helpers.h"

#define WRONG_TXT "Command has been improperly used. Use "

void get_current_path(std::string *str) {
    *str = boost::filesystem::current_path().string();
}

int mpwd(std::vector<std::string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.empty()) {
        std::string path;
        get_current_path(&path);
        std::cout << path << std::endl;
        return 0;
    }
    if ((cmd.size() == 1) && (cmd[0].at(0) == '-')) {
        cout << "The command returns the current path." << endl;
    } else {
        cerr << "It is not such options. Use [-h, --help]." << endl;
    }
    return -1;
}

int mcd(std::vector<std::string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.empty()){
        std::exit(0);
    }
    std::cout << cmd.size();
    if (cmd.size() == 1 && chdir(cmd[0].c_str()) == 0) {
        return 0;
    } else if (cmd.size() == 1 && !(cmd[0] != "-h" || cmd[0] != "--help")){
        std::cout << "No such directory\n";
        return -1;
    } else if (cmd.size() == 1 ){
        std::cout << "The command changes the directory to the <path>\n" << std::endl;
        return 0;
    }
    if (cmd.size() == 2 && (cmd[1] == "-h" || cmd[1] == "--help")){
        std::cout << "The command changes the directory to the "<< cmd[0] << std::endl;
        return 0;
    }

    std::cerr << WRONG_TXT << "mcd <path> [-h, --help].\n" << std::endl;
    return -1;
}

void mexec(std::vector<std::string>& args) {
    if (args[0].at(0) == 'm') {
        args[0] = args[0].replace(0, 1, "");
    }
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Error: cannot fork" << std::endl;
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        std::vector<const char*> c_func_args;
        for (int i = 0; i < args.size(); i++) {
            const char *c_val = args[i].c_str();
            c_func_args.push_back(c_val);
            if (i == args.size() - 1) {
                c_func_args.push_back(nullptr);
            }
        }
        char* const* args_data = const_cast<char* const*>(c_func_args.data());
        const char* cmd = args[0].c_str();
        execvp(cmd, args_data);
        cerr << "Bad arguments" << endl;
        exit(EXIT_FAILURE);
    }
}

void mexit(std::vector<std::string>& args){
    args.erase(args.begin());
    if (args.empty()){
        std::exit(0);
    }
    else if (args.size() == 1){
        if (args[0] == "-h" || args[0] == "--help"){
            std::cout << "Exits the shell with return code <code> \n";
            return;
        }
        else if ( std::all_of(args[0].begin(), args[0].end(), ::isdigit)){
            std::stringstream tmp(args[0]);
            int x = 0;
            tmp >> x;
            std::exit(x);
        }
    }
    else if (args.size() == 2 && (args[1] == "-h" || args[1] == "--help") &&
            std::all_of(args[0].begin(), args[0].end(), ::isdigit)){
                std::cout << "Mexit exits the program with " << args[0] << " exit code\n";
                return;
    }
    std::cout << WRONG_TXT << " mexit <exit_code> [-h, --help]";
}