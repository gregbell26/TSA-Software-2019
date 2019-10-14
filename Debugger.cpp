//
// Created by Corbin Estes on 10/2/19.
//

#include <iostream>
#include <map>
#include <functional>
#include <string>


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
T readVar(){

}

void process(std::string *in) {
    std::string command = in->substr(0, in->find(' '));
    if (command == "run") {
        run();
    } else if(command == "call") {
        call(in -> substr(in->find(' ') + 1, in->size() - 1));
    } else if (command == "increment") {
        incrementVar(std::stoi(in -> substr(in->find(' ') + 1, in->size() - 1)));
    } else if (command == "setVar"){
        std::string str = in -> substr(in->find(' ') + 1, in->size() - 1);
        replaceVar(str.substr(0, str.find(' ')), std::stoi(str.substr(str.find(' ') + 1, str.size() - 1)));
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

