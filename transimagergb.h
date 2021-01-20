#ifndef TRANSIMAGERGB_H
#define TRANSIMAGERGB_H

#include <string>

//#include <optional>
#include <QImage>

namespace  TransImageRGB
{
    bool transImage(std::string target, std::string path, int width, int height, int rotate = 30);
    QImage L10transImage(std::string target);
};

#endif // TRANSIMAGERGB_H
