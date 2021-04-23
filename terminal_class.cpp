//
// Created by os on 20.4.2021.
//

#include "terminal_class.h"
#include <iostream>
#include <list>
#include <iterator>

terminal::terminal(){
    using namespace std;
    list_last.resize(1);
    list_hist.resize(50);

};

terminal::~terminal(){
/*
    list_last.clear();
    list_hist.clear();
*/
}

void terminal::push_hist(const char *new_cmd){
    list_hist.push_front(new_cmd);

}

void terminal::push_last_cwd(char *last_cwd){
    list_last.push_front(last_cwd);
}
/**
 * make sure what "auto" is!!!
 */
void terminal::print_hist(){
    for (auto it = list_hist.cbegin(); it != list_hist.cend(); it++) {
        std::cout << *it << std::endl;
    }
}

