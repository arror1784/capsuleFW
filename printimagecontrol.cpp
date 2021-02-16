#include "printimagecontrol.h"

#include <QDebug>
PrintImageControl::PrintImageControl(int width, int height, int rotate) :
     _width(width), _height(height), _rotate(rotate)
{

}
void PrintImageControl::imageWrote()
{
    qDebug() << "image worte";
    _imageWrote = true;
    _cv_image.notify_all();
}

void PrintImageControl::imageScale(double scale)
{
    _scale = scale;
    emit sendToQmlImageScale(_scale);
}

void PrintImageControl::imageRotate(int rotate)
{
    _rotate = rotate;
    emit sendToQmlImageRotate(_rotate);
}

void PrintImageControl::imageWidhtHeight(int width, int height)
{
    _width = width;
    _height = height;
    emit sendToQmlImageWidhtHeight(_width,_height);
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

void PrintImageControl::reset()
{
    emit sendToQmlImageScale(_scale);
    emit sendToQmlImageRotate(_rotate);
    emit sendToQmlImageWidhtHeight(_width,_height);

}
