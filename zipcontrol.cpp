#include "zipcontrol.h"

#include "zip/zip.h"

ZipControl::ZipControl(QObject *parent) : QObject(parent)
{

}

bool ZipControl::hasFile(QString path, QString target) const
{
    auto val = path.toUtf8().toStdString();
    try {

        miniz_cpp::zip_file file(val);
        if(file.has_file(target.toStdString())){
            return true;
        }else{
            return false;
        }

    } catch (std::exception e) {
        return false;
    }
}

QString ZipControl::getFileString(QString path, QString target) const
{
    auto val = path.toUtf8().toStdString();
    auto member = target.toStdString();
    try {
        miniz_cpp::zip_file file(val);
        if(file.has_file(member)){
            return QString::fromUtf8(file.read(member).c_str());
        }else{
            return "";
        }

    } catch (std::exception e) {
        return "";
    }
}
