#include "l10printimage.h"

L10PrintImage::L10PrintImage()
{

}
void L10PrintImage::imageChange(int number)
{
    _imageWrote = false;
    if(number == 0){
        requestTransImage(0);
        sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(1);
    }else{
        sendToQmlChangeImage(_imageTransfuture.get());
        requestTransImage(number + 1);
    }
    emit sendToQmlChangeImage(_rootPath + QString::number(number));
}
void L10PrintImage::requestTransImage(int number){

    _imageTransfuture = std::async([this](int number) {
        QString imagePath = _rootPath + QString::number(number);
        QString path = _rootPath + QString::number(number);

        Logger::GetInstance()->write("print image path : " + imagePath);

        _l10imageProvider->transImage(path,number);
        return imagePath;
    },number);

}
