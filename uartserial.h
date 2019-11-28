#ifndef UARTSERIAL_H
#define UARTSERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMap>
#include <QList>

class UartSerial: public QObject
{
    Q_OBJECT

private:
    QSerialPort port_;
    QString name_;
    QSerialPort::BaudRate baud_;
    QSerialPort::DataBits data_bits_;
    QSerialPort::Parity parity_;
    QSerialPort::StopBits stop_bits_;
    QByteArray rcv_data_ = "";

    QMap<QString, QSerialPort::BaudRate> baud_map_;
    QMap<QString, QSerialPort::DataBits> data_bits_map_;
    QMap<QString, QSerialPort::Parity> parity_map_;
    QMap<QString, QSerialPort::StopBits> stop_bits_map_;

public:
    QList<QString> baud_list;
    QList<QString> data_bits_list;
    QList<QString> parity_list;
    QList<QString> stop_bits_list;

private:
    void InitBaudOpt();
    void InitStopBitsOpt();
    void InitParityOpt();
    void InitDataBitsOpt();

public:
    explicit UartSerial(QObject *parent = nullptr);
    QStringList GetAllPortOpt();
    QStringList GetAllBaudOpt();
    QStringList GetAllStopBitsOpt();
    QStringList GetAllParityOpt();
    QStringList GetAllDataBitsOpt();
    QString GetPortName();
    void setPortName(QString name);
    void setBaudRate(QString baud);
    void setDataBits(QString data_bits);
    void setParity(QString parity);
    void setStopBits(QString stop_bits);
    void Open();
    void Close();
    void send(QString msg);
    QByteArray readLastRcv();

signals:
    void PortNameChanged(QString name);
    void BaudChanged();
    void StopBitsChanged();
    void ParityChanged();
    void DataBitsChanged();
    void rcvDataArrived();

public slots:
    void readByInt();

};

#endif // UARTSERIAL_H
