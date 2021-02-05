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
    void sendToQmlImageScale(double scale);
    void sendToQmlImageRotate(int rotate);
    void sendToQmlImageWidhtHeight(int width,int height);

public slots:
    void imageWrote();
public:
    void imageChange(QString path);
    void imageScale(double scale);
    void imageRotate(int rotate);
    void imageWidhtHeight(int width,int height);
    void waitImageWrote();

private:
    std::condition_variable _cv_image;
    std::mutex _cv_image_m;
    bool _imageWrote = true;
};

#endif // PRINTIMAGE_H
