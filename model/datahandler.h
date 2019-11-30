#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class DataHandler : public QObject
{
    Q_OBJECT

private:

public:
    explicit DataHandler(QObject *parent = nullptr);

    void saveData(QString filename, QByteArray data);



signals:

public slots:
};

#endif // DATAHANDLER_H
