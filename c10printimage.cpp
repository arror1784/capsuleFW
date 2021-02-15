#include "c10printimage.h"

C10PrintImage::C10PrintImage()
{

}

void C10PrintImage::imageChange(int number)
{
    _imageWrote = false;
    emit sendToQmlChangeImage(_rootPath + number + ".png");
}
