#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <forward_list>
#include<algorithm>

int main(int argc, char* argv[]){
//step 1
    std::string file_name = argv[1];
    std::ifstream file{file_name};
//step 2
    //keep this as forward list if we dont need to go backwards.
    std::forward_list<char*> arguments;
    //this should copy the arguments in order. double check.
    std::copy(argv[2], argv[sizeof(argv)-1], arguments);

//step 3
    //check char* vs string.
    std::string word;
    std::list<std::string> text;
    
    while(file >> word) {
        text.push_back(word);
    }

//step 4
    std::for_each(arguments.cbegin(), arguments.cend(), [](char* &c){
        std::cout << c << std::endl;
    });

}