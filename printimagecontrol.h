#ifndef PRINTIMAGECONTROL_H
#define PRINTIMAGECONTROL_H

#include <QObject>
#include <mutex>
#include <condition_variable>

class PrintImageControl : public QObject
{
    Q_OBJECT

public:
    PrintImageControl();

signals:
    void sendToQmlChangeImage(QString path);
    void sendToQmlImageScale(double scale);
    void sendToQmlImageRotate(int rotate);
    void sendToQmlImageWidhtHeight(int width,int height);

public slots:
    void imageWrote();

public:
    virtual void imageChange(int number);
    void imageScale(double scale);
    void imageRotate(int rotate);
    void imageWidhtHeight(int width,int height);
    void waitImageWrote();

    void setRootPath(QString path);
    void imageSetBlack();

private:
    std::condition_variable _cv_image;
    std::mutex _cv_image_m;
protected:
    bool _imageWrote = true;

    QString _rootPath;
};

#endif // PRINTIMAGECONTROL_H
