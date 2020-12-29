#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include <iostream>

class Scanner {
public:
    Scanner(std::string input){
        _input = input;
        std::string str = "";

        for(int i = 0; i<_input.length(); ++i){
            char now = _input.at(i);
            if(' ' == now){
                continue;
            }else if('(' == now || ')' == now || ',' == now\
                || '{' == now || '}' ==  now){
                if(!str.empty()){
                    _resultVector.push_back(str);
                    str.clear();
                }
                str.push_back(now);
                _resultVector.push_back(str);
                str.clear();
            }else {
                str+=now;
            }
        }
    }

    std::string nextToken(){
        if(!_resultVector.empty()){
            std::string result;
            result = _resultVector.front();
            _resultVector.erase(_resultVector.begin());
            return result;
        }else{
            throw (std::string)"next char doesn't exist.";
        }
    }

private:
    std::string _input;
    std::vector<std::string> _resultVector;
};
#endif
