//
// Created by Corbin Estes on 10/2/19.
//

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <typeinfo>
#include <map>


void run(){
    //start game
}

void call(std::string str){

}

void incrementVar(int i){

}
void replaceVar(std::string, int){

}

void findVar(std::string str){
    //find the thing

}

template <typename T>
std::map<T*, std::string> variables;


template <typename T>
void flagVar(T* var, std::string name){
    variables<T*>.insert(std::pair<T*, std::string>(&var, name));
}

template <typename T>
void showVar(std::string search_name){
    typename std::map<T*, std::string>::iterator itr;
    for (itr = variables<T*>.begin(); itr != variables<T*>.end(); ++itr) {
        if (itr->second == search_name) {
            std::cout << search_name << ": " << *itr->first << std::endl;
        }
    }
}

void process(std::string *in) {
    std::string command = in->substr(0, in->find(' '));
    if (command == "run") {
        run();
    } else if(command == "call") {
        call(in -> substr(in->find(' ') + 1, in->size() - 1));
    } else if (command == "increment") {
        incrementVar(std::stoi(in -> substr(in->find(' ') + 1, in->size() - 1)));
    } else if (command == "flag"){
        std::string str = in -> substr(in->find(' ') + 1, in->size() - 1);
//        flagVar( , str);
    } else if (command == "readVar"){
        findVar(in -> substr(in->find(' ') + 1, in->size() - 1));
    } else if (command == "close") {
        exit(0);//Sorry corbin
    } else {
        std::cout << "Command does not exist" << std::endl;
    }
}

int main() {
    std::string userin;
    while (userin != "end") {
        getline(std::cin, userin);
        process(&userin);
    }
    return 0;
}

