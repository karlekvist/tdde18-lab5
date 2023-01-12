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
std::map<std::string, int> get_frequency_map(std::list<std::string> &text);
int reverse_compare_value(std::pair<std::string, int> left,  std::pair<std::string, int> right);
int compare_word_length_v(std::pair<std::string, int> left, std::pair<std::string, int> right);
int get_max_length(std::vector<std::pair<std::string, int>>);


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

    //we make sure that we don't pass faulty flags into the switch
    //to avoid crashes.
    if(flags.count(flag) == 1) {
        switch(flags.at(flag)){
            case 0:
                print(text);
                break;
            
            case 1:
                table(text);
                break;

            case 2:
                frequency(text);
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

void print(std::list<std::string> &text){
    std::copy(text.begin(), text.end(), 
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
}

void table(std::list<std::string> &text){
    std::map<std::string, int> frequency_m = get_frequency_map(text);
}

void frequency(std::list<std::string> &text){
    std::map<std::string, int> frequency_m = get_frequency_map(text);
    std::vector<std::pair<std::string,int>> frequency_v{frequency_m.begin(), frequency_m.end()};
    std::sort(frequency_v.begin(), frequency_v.end(), reverse_compare_value);

    int max_length = get_max_length(frequency_v);

    std::for_each(frequency_v.begin(), frequency_v.end(),[&frequency_v, &max_length](std::pair<std::string, int> p){
        std::cout << std::setw(max_length) << p.first << " " << p.second << std::endl;

    });
}

void substitute(std::string flag, std::list<std::string> &text){
    size_t index{0};
    index = flag.find('+');
    std::string old_word = flag.substr(0, index); 
    std::string new_word = flag.erase(0, index + 1);
    std::replace(text.begin(), text.end(), old_word, new_word);
}

void remove(std::string const word, std::list<std::string> &text){
    auto it = std::remove(text.begin(), text.end(), word);
    text.erase(it, text.end());
    return;
}

int reverse_compare_value(std::pair<std::string, int> left,  std::pair<std::string, int> right){
    return right.second < left.second;
}

int compare_word_length_v(std::pair<std::string, int> left, std::pair<std::string, int> right){
    return left.first.length() <  right.first.length();
}

int get_max_length(std::vector<std::pair<std::string, int>> in_v){ 
    std::vector<std::pair<std::string, int>>::iterator it = std::max_element(
        in_v.begin(), in_v.end(), compare_word_length_v);
    return it->first.length();
}
std::map<std::string, int> get_frequency_map(std::list<std::string> &text){   
    std::map<std::string, int> frequency_map;
    std::for_each(text.begin(), text.end(), 
    [&frequency_map](std::string word){++frequency_map[word];});
    return frequency_map;
}