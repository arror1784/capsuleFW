#include "c10printimage.h"

#include <QDebug>
C10PrintImage::C10PrintImage(int width, int height, int rotate) :
    PrintImageControl (width,height,rotate)
{

}

void C10PrintImage::imageChange(int number)
{
    qDebug() << "C10";
    _imageWrote = false;
    emit sendToQmlChangeImage(_rootPath + QString::number(number) + ".png");
}
