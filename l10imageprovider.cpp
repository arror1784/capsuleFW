#include "l10imageprovider.h"
#include "transimagergb.h"
#include <QDebug>
const QString printFilePath = "/opt/capsuleFW/print/printFilePath";
L10ImageProvider::L10ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage L10ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 540;
    int height = 2560;
    qDebug() << "asdasd";
    if (size)
       *size = QSize(width, height);
    return _img;
}

void L10ImageProvider::transImage(QString path,int id)
{
    qDebug() << "transimage start" << path;
    _id = id;
    _img = TransImageRGB::L10transImage(path.toStdString()).value();
    qDebug() << "transimage finish";
}

