#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include<algorithm>

void handleArgument(std::string arg);
void print();
void table();
void frequency();
void substitute(std::string word);
void remove(std::string word);

int main(int argc, char* argv[]){
//step 1
    std::string file_name = argv[1];
    std::ifstream file{file_name};

//step 2
    std::vector<std::string> full_args{argv, argv + argc};
    std::list<std::string> arguments;
    std::copy(full_args.cbegin()+2, full_args.cend(), back_inserter(arguments));

//step 3
    
    std::string word;
    std::list<std::string> text;
    
    while(file >> word) {
        text.push_back(word);
    }

//step 4
    std::for_each(arguments.cbegin(), arguments.cend(),[&](std::string argument){handleArgument(argument);});

}

void handleArgument(std::string arg)
{
    //todo:handle exception if flag is invalid.
    //Setting up a map to be able to do a switch later.
    std::map<std::string, int> flags{
        {"--print", 0},
        {"--table", 1},
        {"--frequency", 2},
        {"--substitute", 3},
        {"--remove", 4}
    };

    size_t index{0};
    std::string flag;
    std::string parameter;
    if(arg.find('=') != std::string::npos){
        index = arg.find('=');
        flag = arg.substr(0, index);
        arg.erase(0, index + 1);
        parameter = arg;
    } else {
        flag = arg; 
    }


    if(flags.count(flag) == 1) //check that argument is correct to be able to throw exception if not.
    {
        switch(flags.at(flag)){
            case 0:
                print();
                break;
            
            case 1:
                //table();
                break;

            case 2:
                //frequency();
                break;
        
            case 3:
                //substitute(parameter);
                break;

            case 4:
                //remove(parameter);
                break;
        }
    } 
    else 
    {
        //todo: set up an exception here. atm not doing anything.
        return;
    }
}

void print()
{
    std::cout << "it works?" << std::endl;
}
