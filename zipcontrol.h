#ifndef ZIPCONTROL_H
#define ZIPCONTROL_H

#include <QObject>

class ZipControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
//    Q_PROPERTY(QStringList childList READ getChildList)

public:
    explicit ZipControl(QObject *parent = nullptr);

    QString path();
    void setPath(QString path);

//    QStringList getChildList();

    Q_INVOKABLE bool hasFile(QString target) const;
    Q_INVOKABLE QString getFileString(QString target) const;

signals:
    void pathChanged();

public slots:

private:
    QString _path;
    QStringList _childList;
};

#endif // ZIPCONTROL_H
