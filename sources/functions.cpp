//
// Created by Serhiy Rosovskyy on 10/23/19.
//

#include "../headers/helpers.h"

int mpwd(vector<string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.size() == 0) {
        string path;
        get_current_path(&path);
        cout << path << endl;
        return 0;
    }
    if ((cmd.size() == 1) && ((*cmd.begin() == "-h") || (*cmd.begin() == "--help"))) {
        cout << "The command returns the current path." << endl;
        return 0;
    }
    std::cerr << "It is not such options. Use [-h, --help]." << endl;
    return -1;
}

int mcd(vector<string>& cmd) {
    cmd.erase(cmd.begin());
    if (cmd.size() == 1 && chdir(cmd[0].c_str()) == 0) {
        return 0;
    }
    if (cmd.size() == 2 && (cmd[1] == "-h" || cmd[1] == "--help")) {
        cout<< "The command changes the directory to the <path>" <<endl;
        return chdir(cmd[0].c_str());
    }
    if(cmd.size() == 1 && (*cmd.begin() == "-h" || *cmd.begin() == "--help")) {
        cout << "The command changes the directory to the <path>" << endl;
        return 1;
    }
    std::cerr << "It is not such options. Use [-h, --help]." << endl;
    return -1;
}

void mexec(vector<string>& args) {
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
        vector<const char*> c_func_args;
        for (int i = 0; i < args.size(); i++) {
            const char *c_val = args[i].c_str();
            c_func_args.push_back(c_val);
            if (i == args.size() - 1) {
                c_func_args.push_back(nullptr);
            }
        }
        execvp(args[0].c_str(), const_cast<char* const*>(c_func_args.data()));
        std::cerr << "Bad arguments" << endl;
        exit(EXIT_FAILURE);
    }
}