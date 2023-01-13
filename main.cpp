#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

void handleArgument(std::string &arg, std::list<std::string> &text);

void print(std::list<std::string>const &text);
void table(std::list<std::string> &text);
void frequency(std::list<std::string> &text);
void substitute(std::string &parameter, std::list<std::string> &text);
void remove(std::string &parameter, std::list<std::string> &text);

std::map<std::string, int> get_frequency_map(std::list<std::string> &text);
int reverse_compare_value(std::pair<std::string, int> const &left,  std::pair<std::string, int> const &right);
int compare_word_length_v(std::pair<std::string, int> const &left, std::pair<std::string, int> const &right);
int get_max_length(std::vector<std::pair<std::string, int>> &in_v);
int get_max_length(std::map<std::string, int> &in_m);


int main(int argc, char* argv[]){
//step 1
    std::string file_name = argv[1];
    std::ifstream file{file_name};

//step 2
    std::vector<std::string> full_args{argv, argv + argc};
    std::list<std::string> arguments;
    std::copy(full_args.cbegin() + 2, full_args.cend(), back_inserter(arguments));

//step 3
    std::list<std::string> text{std::istream_iterator<std::string>(file),
              std::istream_iterator<std::string>{}};

    if(text.size() < 1) {
        std::cout << "File empty" << std::endl;
        return -1;
    }
    
//step 4
    try{
        std::for_each(arguments.cbegin(), arguments.cend(), [&](std::string argument){handleArgument(argument, text);});
    } catch(char const* c) {
        std::cout << c << std::endl;
        return -1;
    } 
    catch(...) {
        std::cout << "Warning, invalid use.  Proper flags are: \n" 
                  << "--print --table --frequency --substitute=<oldWord>+<newWord> --remove=<word>"
                  << std::endl;
        return -1;
    }
}

void handleArgument(std::string &arg, std::list<std::string> &text)
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

    try{
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
                substitute(parameter, text);
                break;

            case 4:
                remove(parameter, text);
                break; 
        }
    } 
    catch(char const* c){
        throw c;
    }
    catch(...){
        throw;
    }
}

void print(std::list<std::string> const &text) {
    std::copy(text.begin(), text.end(), 
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
}

void table(std::list<std::string> &text){
    std::map<std::string, int> frequency_m = get_frequency_map(text);

    int max_length = get_max_length(frequency_m);

    std::for_each(frequency_m.begin(), frequency_m.end(), [&max_length](std::pair<std::string, int> p){
        std::cout << std::setw(max_length) << std::left << p.first << " " << p.second << std::endl;
    });
}

void frequency(std::list<std::string> &text){
    std::map<std::string, int> frequency_m = get_frequency_map(text);
    std::vector<std::pair<std::string,int>> frequency_v{frequency_m.begin(), frequency_m.end()};
    std::sort(frequency_v.begin(), frequency_v.end(), reverse_compare_value);

    int max_length = get_max_length(frequency_v);

    std::for_each(frequency_v.begin(), frequency_v.end(),[&max_length](std::pair<std::string, int> p){
        std::cout << std::setw(max_length) << p.first << " " << p.second << std::endl;
    });
}

//not taking parameter as &(ref) due to it being changed internally.
void substitute(std::string &parameter, std::list<std::string> &text){
    if(parameter.find('+')==std::string::npos){
        throw "Invalid parameter. correct use --substitute=<oldWord>+<newWord>";
    }
    size_t index{0};
    index = parameter.find('+');
    std::string old_word = parameter.substr(0, index); 
        if(old_word.size() < 1){
        throw "no <oldWord>. correct use correct use --substitute=<oldWord>+<newWord>";
    }
    std::string new_word = parameter.erase(0, index + 1);
    if(new_word.size() < 1){
        throw "no <newWord>. correct use --substitute=<oldWord>+<newWord>";
    }
    std::replace(text.begin(), text.end(), old_word, new_word);
}

void remove(std::string &parameter, std::list<std::string> &text){
    auto it = std::remove(text.begin(), text.end(), parameter);
    if(parameter.size() < 1){
        throw "no <word>";
    }
    text.erase(it, text.end());
    return;
}

int reverse_compare_value(std::pair<std::string, int> const &left,  std::pair<std::string, int> const &right){
    return right.second < left.second;
}

int compare_word_length_v(std::pair<std::string, int> const &left, std::pair<std::string, int> const &right){
    return left.first.length() <  right.first.length();
}

int get_max_length(std::map<std::string, int> &in_m){ 
    std::map<std::string, int>::iterator it = std::max_element(
        in_m.begin(), in_m.end(), compare_word_length_v);
    return it->first.length();
}

int get_max_length(std::vector<std::pair<std::string, int>> &in_v){ 
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