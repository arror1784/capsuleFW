#include "l10printimage.h"

#include <QDebug>
L10PrintImage::L10PrintImage(int width, int height, int rotate, QString filePath, L10ImageProvider* l10imageProvider) :
    PrintImageControl (width,height,rotate), _l10imageProvider(l10imageProvider), _filePath(filePath)
{

}
void L10PrintImage::imageChange(int number)
{
    qDebug() << "L10";
    _imageWrote = false;
    if(number == 0){
        requestTransImage(0);
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(1);
    }else{
        emit sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(number + 1);
    }
//    emit sendToQmlChangeImage(_rootPath + QString::number(number));
}
void L10PrintImage::requestTransImage(int number){

    _imageTransfuture = std::async([this](int number) {
        QString imagePath = _rootPath + QString::number(number);
        QString filePath = _filePath + QString::number(number) + ".png";

        Logger::GetInstance()->write("print image path : " + imagePath);

        _l10imageProvider->transImage(filePath,number);
        return imagePath;
    },number);

}
