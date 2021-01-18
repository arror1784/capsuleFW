#ifndef TRANSIMAGERGB_H
#define TRANSIMAGERGB_H

#include <string>

class TransImageRGB
{
public:
    TransImageRGB();

    static bool transImage(std::string target, std::string path, int width, int height, int rotate = 0);
    static bool L10transImage(std::string target, std::string path);

};

#endif // TRANSIMAGERGB_H
