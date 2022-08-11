#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <tuple>

void stringToLowerCase(std::string &str){ // converts string to lower case string
    std::transform(str.begin(),
                   str.end(),
                   str.begin(),
                   [](unsigned char ch){return std::tolower(ch);});
}

void transformStringToBrackets(std::string &str){ // all symbols in string converts into '(' if char contains once and to ')' if not once

    std::vector<std::pair<unsigned char, int>> charAndPositions;
    bool foundFlag;

    for(int i = 0; i < str.size(); i++){
        foundFlag = false;
        if(charAndPositions.size() > 0){

            for(int j = 0; j < charAndPositions.size(); ++j){

                if(charAndPositions[j].first == str[i]){
                    foundFlag = true;
                    charAndPositions[j].second++;
                }
            }
            if(!foundFlag){
                    charAndPositions.push_back(std::make_pair(str[i], 1));
                }
        }
        else{
            charAndPositions.push_back(std::make_pair(str[i], 1));
        }
    }

    for(int i = 0; i < str.size(); ++i){

        for(int j = 0; j < charAndPositions.size(); ++j){

            if(charAndPositions[j].first == str[i]){
                if(charAndPositions[j].second == 1){
                    str[i] = '(';

                }
                else if(charAndPositions[j].second > 1){
                    str[i] = ')';

                }
            }
        }
    }

}

int main()
{
    std::string str;

    std::cin >> str;

    stringToLowerCase(str);
    transformStringToBrackets(str);

    std::cout << std::endl << str << std::endl;

    return 0;
}
