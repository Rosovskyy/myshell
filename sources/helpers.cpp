//
// Created by Serhiy Rosovskyy on 10/19/19.
//

#include "../headers/helpers.h"

void get_current_path(string *str) {
    *str = boost::filesystem::current_path().string();
}
