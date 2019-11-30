#include <QtDebug>
#include <QDir>
#include "datahandler.h"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
}


void DataHandler::saveData(QString fullpath_filename, QByteArray data)
{
    QFile file(fullpath_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << file.errorString() << fullpath_filename;
        return;
    }

    QTextStream out(&file);
    out << data;

    file.close();
}



