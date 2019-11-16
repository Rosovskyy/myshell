#include <iostream>
#include <unistd.h>
#include <cstring>
#include <wait.h>

#include "pipeline.h"
void pipeline(std::vector<const char *> &progs){
    int  pipes[progs.size() * 4];

    for (int i = 0; i < progs.size() * 2; i++) {
        pipe(&pipes[2*i]);
    }

    for (auto j = 0; j < progs.size() * 4; j+=4){
        pid_t pid = fork();
        if (pid == 0){
            char output[100] = {'\0'};
            close(pipes[j+1]);
            if (j != 0){
                int end = read(pipes[j], output, 100);
                output[end] = '\0';
            }
            close(pipes[j]);

            close(pipes[j+2]);
            dup2(pipes[j+3], STDOUT_FILENO);
            dup2(pipes[j+3], STDERR_FILENO);
            close(pipes[j+3]);

            std::string cur_cmd = (std::string) progs[j/4];
            std::cout << "|" <<cur_cmd <<"|";
            size_t pos;

            if ((pos = cur_cmd.find(' ')) != std::string::npos){
                std::string cmd{cur_cmd.substr(0,pos)};
                std::string args{cur_cmd.substr(pos+1)};
                char *argv[]= {(char*)cmd.c_str(),(char *)args.c_str(),output, NULL};
                execvp(cmd.c_str(), argv);
            }
            else{
                if (strlen(output) > 0){
                    char *argv[]= {(char*)progs[j/4], output, NULL};
                    execvp(progs[j/4], argv);
                }else {
                    char *argv[] = { (char*)progs[j/4], NULL };
                    execvp(progs[j/4], argv);
                }
            }
            exit(0);
        }
    }

    char buf[100];
    for (int i=0; i < progs.size() * 4; i+=4){
        close(pipes[i]);
        if (i != 0){
            write(pipes[i+1], buf, strlen(buf) + 1);
        }
        close(pipes[i+1]);


        close(pipes[i+3]);
        int end = read(pipes[i+2],buf, 100);
        buf[end] = '\0';
        close(pipes[i+2]);

        std::cout << buf<< " ";
        wait(NULL);
    }

}

//
//
//
//int main(int argc, char **argv)
//{
//    std::vector<const char *> progs{"../test/one","../test/two -t", "../test/three -m"};
//    pipeline(progs);
//
//
//    return 0;
//}


