#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>


typedef struct flags_strct{
    bool i_flg=false,
            v_flg=false,
            reg_flg=false,
            file_flg= false;
} flags_strct;

void mygrep(std::vector<std::string> &args);
void check_flags(const std::string &line, std::string &str_filter, flags_strct &flags, std::regex &reg);

int main(int argc, char *argv[]) {
    std::vector<std::string> args{"-i", "lak", "--file=../file.txt"};
//    std::vector<std::string> args(argv+1, argv + argc);
    mygrep(args);
    return 0;
}

void mygrep(std::vector<std::string> &args){
    if ((std::find_if(args.begin(), args.end(), [](auto &arg){ return arg == "-h" || arg == "--help";})) != args.end()){
        std::cout << "grep [-h|--help] [-v|--invert-match] [-i|--ignore-case] "
                     "[--file=<filename>] [--regexp=’<regexpression>’ | string] Press Cmd+D or Ctrl+Z for exit";
        exit(0);
    }

    flags_strct flags;
    std::string filename, str_filter;
    std::regex reg;
    for (auto & arg : args){
        if (arg == "-v"){
            flags.v_flg = true;
        } else if (arg == "-i"){
            flags.i_flg = true;
        } else if (arg.find("--file") != std::string::npos){
            flags.file_flg= true;
            int tmp_pos = arg.find('=');
            filename = arg.substr(tmp_pos+1, arg.size() - tmp_pos - 1);
        } else if (arg.find("--regexp") != std::string::npos){
            int tmp_pos = arg.find('=');
            std::string slice = arg.substr(tmp_pos+1, arg.size() - tmp_pos-1);
            reg.assign(slice);
            flags.reg_flg=true;
        } else{
           str_filter = arg;
        }
    }
    if (flags.i_flg){
        std::transform(str_filter.begin(), str_filter.end(), str_filter.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    }

    std::string line;
    if (!flags.file_flg){
        while (std::getline(std::cin, line)) {
            check_flags(line, str_filter, flags, reg);
        }
    }
    else {
        std::ifstream file;
        file.open (filename);
        if (!file.is_open()) {
            std::cerr << "Couldn't open file\n";
            exit(1);
        }

        while (file >> line)
        {
            check_flags(line, str_filter, flags, reg);
        }
    }

}

void check_flags(const std::string &line, std::string &str_filter, flags_strct &flags,  std::regex &reg){
    std::string line_copy = line;
    if (flags.reg_flg && std::regex_match(line,reg)){
        std::cout << line << "\n";
    }
    else if (!flags.reg_flg) {
        if (flags.i_flg){
            std::transform(line.begin(), line.end(), line_copy.begin(),
                           [](unsigned char c){ return std::tolower(c); });
        }
        if (flags.v_flg){
            if (line_copy.find(str_filter) == std::string::npos){
                std::cout << line  << "\n";;
            }
        }
        else{
            if (line_copy.find(str_filter) != std::string::npos){
                std::cout << line << "\n";;
            }
        }
    }
}