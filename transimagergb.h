#ifndef TRANSIMAGERGB_H
#define TRANSIMAGERGB_H

#include <string>

class TransImageRGB
{
public:
    TransImageRGB();

    static bool transImage(std::string target, std::string path,int rotate = 0);
};

#endif // TRANSIMAGERGB_H
