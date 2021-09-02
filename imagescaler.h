#ifndef IMAGESCALER_H
#define IMAGESCALER_H

#include <QImage>

namespace ImageScaler
{
    QImage transImage(QImage& img,int delta,float yMult, std::vector<uint8_t>& out);
};

#endif // IMAGESCALER_H
