#include "printimagecontrol.h"

PrintImageControl::PrintImageControl()
{

}
void PrintImageControl::imageWrote()
{
    _imageWrote = true;
    _cv_image.notify_all();
}

void PrintImageControl::imageScale(double scale)
{
    emit sendToQmlImageScale(scale);
}

void PrintImageControl::imageRotate(int rotate)
{
    emit sendToQmlImageRotate(rotate);
}

void PrintImageControl::imageWidhtHeight(int width, int height)
{
    emit sendToQmlImageWidhtHeight(width,height);
}
void PrintImageControl::waitImageWrote()
{
    std::unique_lock<std::mutex> lk(_cv_image_m);
    _cv_image.wait(lk,[this]{return this->_imageWrote;});
}

void PrintImageControl::setRootPath(QString path)
{
    _rootPath = path;
}

void PrintImageControl::imageSetBlack()
{
    _imageWrote = false;
    emit sendToQmlChangeImage("qrc:/image/defaultBlackImage.png");
}
