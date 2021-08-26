#include "transimagergb.h"

#include <QImageReader>
#include <QImageWriter>
#include <QImage>
#include <QColor>
#include <QMatrix>
#include <QDebug>


QImage TransImageRGB::L10transImage(QImage &img)
{
    if(img.width() != 1620 || img.height() != 2560){
        return img;
    }
    QImage imgE(540, 2560, QImage::Format_RGB32);

    int sourceWidth = img.width();
    int sourceHeight = img.height();

    int targetWidth = 540;
//    int targetheight = 2560;

    for(int x = 0; x < sourceWidth; x++){
        int y = 1;
        for(int i = 0; i < sourceHeight;i+=3){

            uint32_t transRed = 0;
            uint32_t transGreen = 0;
            uint32_t transBlue = 0;

            for(int j = 0; j < 3; j++){
                if(i + j > sourceWidth){
                    break;
                }
                auto col = img.pixel(x,i + j);
                uint32_t total = col & 0x000000ff;
                if(j == 0){
                    transRed = total;
                }else if(j == 1){
                    transGreen = total;
                }else{
                    transBlue = total;
                }
            }
            QRgb rgb = RGB_MASK & (transBlue << 16 | transGreen << 8 | transRed);
            imgE.setPixel(targetWidth - y++,x, rgb);
        }
    }
    return imgE;
}
