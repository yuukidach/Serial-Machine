#include "uartserial.h"
#include <QtCore>

UartSerial::UartSerial(QObject *parent) : QObject(parent)
{
    this->GetAllPortOpt();
    this->InitBaudOpt();
    this->InitDataBitsOpt();
    this->InitParityOpt();
    this->InitStopBitsOpt();
};


void UartSerial::InitBaudOpt()
{
    this->baud_map_.insert("1200", QSerialPort::Baud1200);
    this->baud_map_.insert("2400", QSerialPort::Baud2400);
    this->baud_map_.insert("4800", QSerialPort::Baud4800);
    this->baud_map_.insert("9600", QSerialPort::Baud9600);
    this->baud_map_.insert("19200", QSerialPort::Baud19200);
    this->baud_map_.insert("38400", QSerialPort::Baud38400);
    this->baud_map_.insert("57600", QSerialPort::Baud57600);
    this->baud_map_.insert("115200", QSerialPort::Baud115200);
    this->baud_list.append({"1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"});
}


void UartSerial::InitDataBitsOpt()
{
    this->data_bits_map_.insert("5", QSerialPort::Data5);
    this->data_bits_map_.insert("6", QSerialPort::Data6);
    this->data_bits_map_.insert("7", QSerialPort::Data7);
    this->data_bits_map_.insert("8", QSerialPort::Data8);
    this->data_bits_list.append({"5", "6", "7", "8"});
}


void UartSerial::InitParityOpt()
{
    this->parity_map_.insert("None", QSerialPort::NoParity);
    this->parity_map_.insert("Even", QSerialPort::EvenParity);
    this->parity_map_.insert("Odd", QSerialPort::OddParity);
    this->parity_map_.insert("Space", QSerialPort::SpaceParity);
    this->parity_map_.insert("Mark", QSerialPort::MarkParity);
    this->parity_list.append({"None", "Even", "Odd", "Space", "Mark"});
}


void UartSerial::InitStopBitsOpt()
{
    this->stop_bits_map_.insert("1", QSerialPort::OneStop);
    this->stop_bits_map_.insert("1.5", QSerialPort::OneAndHalfStop);
    this->stop_bits_map_.insert("2", QSerialPort::TwoStop);
    this->stop_bits_list.append({"1", "1.5", "2"});
}


/**
 * @brief Find all available ports
 * @return port_list: String list of all port names.
 */
QStringList UartSerial::GetAllPortOpt()
{
    QStringList port_list;
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        port_list.append(port.portName());
    }
    return port_list;
}


QStringList UartSerial::GetAllBaudOpt()
{
    return this->baud_list;
}


QStringList UartSerial::GetAllDataBitsOpt()
{
    return this->data_bits_list;
}


QStringList UartSerial::GetAllParityOpt()
{
    return this->parity_list;
}


QStringList UartSerial::GetAllStopBitsOpt()
{
    return this->stop_bits_list;
}


QString UartSerial::GetPortName()
{
    return name_;
}


void UartSerial::setPortName(QString name)
{
    name_ = name;
}


void UartSerial::setBaudRate(QString baud)
{
    baud_ = baud_map_.value(baud);
}


void UartSerial::setDataBits(QString data_bits)
{
    data_bits_ = data_bits_map_.value(data_bits);
}


void UartSerial::setParity(QString parity)
{
    parity_ = parity_map_.value(parity);
}


void UartSerial::setStopBits(QString stop_bits)
{
    stop_bits_ = stop_bits_map_.value(stop_bits);
}


void UartSerial::Open() {
    port_.setPortName(name_);
    port_.setBaudRate(baud_);
    port_.setDataBits(data_bits_);
    port_.setParity(parity_);
    port_.setStopBits(stop_bits_);
    port_.setFlowControl(QSerialPort::NoFlowControl);
    port_.open(QIODevice::ReadWrite);
    connect(&port_, SIGNAL(readyRead()),
            this, SLOT(readByInt()));
}


void UartSerial::Close() {
    port_.clear();
    port_.close();
}


void UartSerial::send(QString msg){
    if(port_.isOpen()) {
        port_.write(msg.toUtf8());
    }
}


void UartSerial::readByInt()
{
    rcv_data_ = port_.readAll().replace("\r", "");
    emit rcvDataArrived();
}


QByteArray UartSerial::readLastRcv()
{
    return rcv_data_;
}



