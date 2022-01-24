#include "c10imageprovider.h"
#include "imagescaler.h"

#include <QDebug>
#include <QImageReader>

C10ImageProvider::C10ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage C10ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 540;
    int height = 2560;
    qDebug() << "asdasd";
    if (size)
       *size = QSize(width, height);
    return _img;
}

void C10ImageProvider::transImage(QString path, int id,int delta, float yMult)
{
    qDebug() << "transimage start C10" << path;
    _id = id;
    QImageReader ir(path);

    if(ir.canRead()){
        auto oriImg = ir.read();

        _img = ImageScaler::transImage(oriImg,delta,yMult,_imageBuf);
        qDebug() << "transimage finish C10";

        return;
    }else{
        qDebug() << path << " is not available " << ir.errorString();
    }
}
