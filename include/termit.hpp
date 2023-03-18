#ifndef TERMIT
#define TERMIT


#include <string>
class Termit {

public:
    Termit();

private:
    std::string parseLine(std::string&);
};


#endif