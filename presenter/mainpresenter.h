#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

#include <QObject>
#include <QString>
#include "uartserial.h"
#include "model/datahandler.h"

class MainPresenter: public QObject
{
    Q_OBJECT

private:
    UartSerial& uart_serial_;
    DataHandler& data_handler_;

    QByteArray rcv_data_;
    bool is_timestamp_needed_ = false;
    bool is_hex_mode_needed_ = false;

    Q_PROPERTY(QStringList name_list READ GetAllPortOpt)
    Q_PROPERTY(QStringList baud_list READ GetAllBaudOpt)
    Q_PROPERTY(QStringList data_bits_list READ GetAllDataBitsOpt)
    Q_PROPERTY(QStringList parity_list READ GetAllParityOpt)
    Q_PROPERTY(QStringList stop_bits_list READ GetAllStopBitsOpt)
    Q_PROPERTY(QByteArray rcv_data READ getRcvData)

public:
    MainPresenter(UartSerial& uart_serial, DataHandler& data_handler);
    Q_INVOKABLE void openPort(QString name,
                              QString baud,
                              QString data_bits,
                              QString parity,
                              QString stop_bits_list);
    Q_INVOKABLE void closePort();
    Q_INVOKABLE void sendMsg(QString msg);
    Q_INVOKABLE void setTimestampNeed(bool is_need);
    Q_INVOKABLE void setHexModeNeed(bool is_need);

    Q_INVOKABLE void saveData(QString fileurl, QByteArray data);

    QStringList GetAllPortOpt();
    QStringList GetAllBaudOpt();
    QStringList GetAllStopBitsOpt();
    QStringList GetAllParityOpt();
    QStringList GetAllDataBitsOpt();

    QString GetPortName();
    bool getTimestampNeed(void);
    bool getHexModeNeed(void);

signals:
    void PortNameChanged();
    void rcvDataArrived();

public slots:
    void updateRcvData();
    QByteArray getRcvData();
};

#endif // MAINPRESENTER_H
