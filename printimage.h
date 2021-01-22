#ifndef PRINTIMAGE_H
#define PRINTIMAGE_H

#include <QObject>
#include <mutex>
#include <condition_variable>

class PrintImage : public QObject
{
    Q_OBJECT
public:
    PrintImage();

signals:
    void sendToQmlChangeImage(QString path);
    void sendToQmlImageScale(double value);
public slots:
    void imageWrote();
public:
    void imageChange(QString path);
    void imageScale(double value);
    void waitImageWrote();

private:
    std::condition_variable _cv_image;
    std::mutex _cv_image_m;
    bool _imageWrote = true;
};

#endif // PRINTIMAGE_H
