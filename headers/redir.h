//
// Created by Serhiy Rosovskyy on 11/9/19.
//

#ifndef MYSHELL_REDIR_H
#define MYSHELL_REDIR_H

#include <fcntl.h>
#include "../headers/functions.h"

void redirect(std::string from, std::string to, std::map<string, string>& vars, bool stdout, bool stdin);

#endif //MYSHELL_REDIR_H
