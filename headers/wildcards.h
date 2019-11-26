//
// Created by arelav on 01.11.19.
//

#ifndef MYSHELL_WILDCARDS_H
#define MYSHELL_WILDCARDS_H

#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <algorithm>

std::vector<std::string> parse_args(std::vector<std::string> &wildcards);
bool wildcard_matches(const std::string &pattern, const std::string &filename);

#endif //MYSHELL_WILDCARDS_H
