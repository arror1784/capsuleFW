#ifndef IMAGESCALER_H
#define IMAGESCALER_H

#include <QImage>

namespace ImageScaler
{
    QImage transImage(QImage& img,int delta,float yMult);
};

#endif // IMAGESCALER_H
