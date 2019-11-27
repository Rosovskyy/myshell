#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <filesystem>

typedef std::filesystem::path path;

inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void moveFile(std::string& src, std::string& target, bool q){
    if (q || !exists(target)){
        std::filesystem::rename(path(src), path(target));
    }
}


void moveDir(std::string sorc, std::string dst) {

    for(std::filesystem::path p: std::filesystem::directory_iterator(sorc)){
        std::filesystem::path destFile = dst/p.filename();

        if (std::filesystem::is_directory(p)) {
            std::filesystem::create_directory(destFile);
            moveDir(p.string().c_str(), destFile.string().c_str());
        } else {
            std::filesystem::rename(p, destFile);
        }
    }
}


void Move(std::string& src, std::string& target, bool f) noexcept{
    try{
        std::string p = (std::filesystem::is_directory(path(target)))? target+"/"+src:target;
        if(!f){
            if(exists(p)){
                std::cout<<"Do you want to overwrite "<<src<<"?\nY/N?"<<std::endl;
                char q;
                std::cin>>q;
                if(std::filesystem::is_directory(path(p))) moveDir(src, p);
                else moveFile(std::ref(src), std::ref(p), q=='Y' || q=='y');
            }
            else{
                moveFile(std::ref(src), std::ref(p), true);
            }
        }
        else{
            moveFile(std::ref(src), std::ref(p), f);
        }
    }

    catch (std::exception& e){
        std::cout << e.what();
    }
}

int main(int argc, char** argv) {
    bool f = false;
    bool lastDir = false;
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    for(auto i=1;i<argc;i++){
        if(strcmp("-h", argv[i])==0 || strcmp("--help", argv[i])==0){
            std::cout<<"mymv [-h|--help] [-f] <oldfile> <newfile>\nmymv [-h|--help] [-f] <oldfile_or_dir_1> "
                       "<oldfile_or_dir_oldfile2> <oldfile_or_dir_oldfile3>.... <dir>"<<std::endl;
            return 0;
        }
        else if(strcmp("-f", argv[i])==0) f = true;
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

    if(!lastDir) Move(std::ref(files[0]), std::ref(files[1]), f);
    else{
        for(auto i=0;i<files.size();i++){
            Move(std::ref(files[i]), std::ref(dirs.back()), f);
        }
        for(auto i=0;i<dirs.size()-1;i++){
                Move(std::ref(dirs[i]), std::ref(dirs.back()), f);
        }
    }
    return 0;
}