#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include<algorithm>

void handleArgument(std::string arg, std::list<std::string> &text);
void print(std::list<std::string> &text);
void table(std::list<std::string> &text);
void frequency(std::list<std::string> &text);
void substitute(std::string flag, std::list<std::string> &text);
void remove(std::string word, std::list<std::string> &text);
std::vector<std::string> get_frequency_vector(std::list<std::string> &text);

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
    std::for_each(arguments.cbegin(), arguments.cend(),[&](std::string argument){handleArgument(argument, text);});

}

void handleArgument(std::string arg, std::list<std::string> &text)
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
                print(text);
                break;
            
            case 1:
                table(text);
                break;

            case 2:
                //frequency();
                break;
        
            case 3:
                substitute(flag, text);
                break;

            case 4:
                remove(parameter, text);
                break; 
        }
    } 
    else 
    {
        //todo: set up an exception here. atm not doing anything.
        return;
    }
}

void print(std::list<std::string> &text)
{
    std::copy(text.begin(), text.end(), 
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
}

void table(std::list<std::string> &text)
{
    get_frequency_vector(text);
}

void frequency(std::list<std::string> &text)
{
}

void substitute(std::string flag, std::list<std::string> &text)
{
    size_t index{0};
    index = flag.find('+');
    std::string old_word = flag.substr(0, index); 
    std::string new_word = flag.erase(0, index + 1);
    std::replace(text.begin(), text.end(), old_word, new_word);
}

void remove(std::string const word, std::list<std::string> &text)
{
    auto it = std::remove(text.begin(), text.end(), word);
    text.erase(it, text.end());
    return;
}

/*
* 
*/
std::vector<std::string> get_frequency_vector(std::list<std::string> &text)
{   
    std::vector<std::string> frequency_v{text.begin(), text.end()};
    std::sort(frequency_v.begin(), frequency_v.end());

    std::copy(frequency_v.begin(), frequency_v.end(), 
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;


}