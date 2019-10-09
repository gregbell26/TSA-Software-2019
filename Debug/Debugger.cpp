//
// Created by Corbin Estes on 10/2/19.
//

#include <iostream>
#include <map>
#include <functional>


#if defined(MACOS) || defined(LINUX)
#define COLOR_INFO "\033[34m" //
#define COLOR_WARNING "\033[33m"
#define COLOR_ERROR "\033[31;1m"
#define COLOR_RESET "\033[0m"

#elif defined(WINDOWS)

#include <Windows.h>

#undef ERROR
// blue
#define COLOR_INFO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1) // 1325ED
// yellow
#define COLOR_WARNING SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6) // EDE613
// red
#define COLOR_ERROR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12) // FF0000
// reset
#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) // FFFFFF

#endif

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

