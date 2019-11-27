#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <filesystem>

typedef std::filesystem::path path;

inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}


void copyFile(std::string& src, std::string& target, bool q){
    if (q || !exists(target)){
        std::filesystem::copy_file(path(src), path(target), std::filesystem::copy_options::overwrite_existing);
    }
}

void Copy(std::string& src, std::string& target, bool f) noexcept{
    try{
        std::string p = (std::filesystem::is_directory(path(target)))? target+"/"+src:target;
        if(!f){

            if(exists(p)){
                std::cout<<"Do you want to overwrite "<<src<<"?\nY/N?"<<std::endl;
                char q;
                std::cin>>q;
                if(!std::filesystem::is_directory(path(src))) copyFile(std::ref(src), std::ref(p), q=='Y' || q=='y');
                else if(q=='N' || q=='n') std::filesystem::copy(path(src), path(p), std::filesystem::copy_options::skip_existing | std::filesystem::copy_options::recursive);
                else std::filesystem::copy(path(src), path(p), std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
            }
            else{
                if(!std::filesystem::is_directory(path(src))) copyFile(std::ref(src), std::ref(p), true);
                else{
                    std::filesystem::create_directory(path(p));
                    std::filesystem::copy(path(src), path(p), std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
                }
            }
        }
        else{
            if(!std::filesystem::is_directory(path(src))) copyFile(std::ref(src), std::ref(p), true);
            else{
            std::filesystem::create_directory(path(p));
            std::filesystem::copy(path(src), path(p), std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
            }
        }
    }

    catch (std::exception& e){
        std::cout << e.what();
    }
}

int main(int argc, char** argv) {
    bool f = false;
    bool R = false;
    bool lastDir = false;
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    for(auto i=1;i<argc;i++){
        if(strcmp("-h", argv[i])==0 || strcmp("--help", argv[i])==0){
            std::cout<<"mycp [-h|--help] [-f] -R  <dir_or_file_1> <dir_or_file_2> <dir_or_file_3>... <dir>\n"
                       "-f -- allow overwriting\n"
                       "-R -- to copy files from dirs recursively(may be used only with dirs)"<<std::endl;
            return 0;
        }
        else if(strcmp("-f", argv[i])==0) f = true;
        else if(strcmp("-R", argv[i])==0) R = true;
        else if(!std::filesystem::is_directory(path(argv[i])) && i==argc-1 && !dirs.empty()){
            std::cerr<<"The last argument must be a dir if there are dirs in arguments"<<std::endl;
            return -1;
        }
        else if(std::filesystem::is_directory(path(argv[i]))){
            dirs.emplace_back(argv[i]);
            if(i==argc-1) lastDir = true;
        }
        else files.emplace_back(argv[i]);
    }
    if(files.size()!=2 && !lastDir){
        std::cerr<<"Wrong number of args"<<std::endl;
        return -1;
    }
    if (dirs.size()!=0 && !lastDir){
        std::cerr<<"Can`t copy dir into file"<<std::endl;
        return -1;
    }
    if(!R && dirs.size()>1){
        std::cerr<<"-R is missing, there are dirs in passed list of files"<<std::endl;
        return -1;
    }
    if(!lastDir) Copy(std::ref(files[0]), std::ref(files[1]), f);
    else{
        for(auto i=0;i<files.size();i++){
            Copy(std::ref(files[i]), std::ref(dirs.back()), f);
        }
        if(R){
            for(auto i=0;i<dirs.size()-1;i++){
                Copy(std::ref(dirs[i]), std::ref(dirs.back()), f);
            }
        }
    }
    return 0;
}