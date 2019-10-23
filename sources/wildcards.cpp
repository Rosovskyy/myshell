#include <iostream>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool wildcard_matches(const std::string &pattern, const std::string &filename);
std::vector<std::string> parse_args(std::vector<std::string> &wildcards);

int main(int argc, char *argv[]) {
    std::vector<std::string> all_args(argv + 2, argv + argc);
    std::vector<std::string> neww = parse_args(all_args);

    return 0;
}


std::vector<std::string> parse_args(std::vector<std::string> &wildcards){
    std::vector<std::string> files, final_ar;
    std::string path, file_name;
    bool found = false;

    for (auto &wildcard: wildcards) {
        int slash_inx = wildcard.find_last_of('/');
        if (slash_inx != std::string::npos){  // if path is absolute or ../ or ./
            path = wildcard.substr(0,slash_inx+1);
            file_name = wildcard.substr(slash_inx+1);
        }else{ // if only file name
            path = "./";
            file_name = wildcard;
        }

        for (const auto & entry : fs::directory_iterator(path)){
            files.emplace_back(entry.path());
        }

        for (auto &file: files) {
            std::string file_no_path = file.substr(file.find_last_of('/')+1);
            if (wildcard_matches(" " + file_name, " " + file_no_path)) { // dynamic alg doesnt work if * is a first sign so add ' '
                final_ar.emplace_back(path+file_no_path);
                found = true;
//                std::cout << file_no_path << " " << file_name << "\n";
            }
        }
        if (!found){
            std::cerr << "For wildcard " << wildcard << " nothing is found\n";
            // make global error flag = -1;
            return std::vector<std::string>();
        }
        found = false;
    }
    return final_ar;
}

bool wildcard_matches(const std::string &pattern, const std::string &filename){
    bool ar[filename.size()+1][pattern.size()+1];
    for (int i = 0; i < filename.size()+1; i++){
        for (int j = 0; j < pattern.size()+1; j++){
            if (i == 0){
                ar[i][j] = j == 0;
            }
            else if (j == 0 & i != 0){
                ar[i][j] = false;
            }
            else if (filename[i-1] == pattern[j-1] || pattern[j-1] == '?')
                ar[i][j] = ar[i-1][j-1];
            else if (pattern[j-1] == '*')
                ar[i][j] = ar[i][j-1] || ar[i-1][j];
            else ar[i][j] = false;
        }
    }
    return ar[filename.size()][pattern.size()];
}