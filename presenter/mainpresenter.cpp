#include "mainpresenter.h"
#include <QDebug>

MainPresenter::MainPresenter(UartSerial& uart_serial):
    uart_serial_(uart_serial)
{
    connect(&uart_serial_, SIGNAL(PortNameChanged(QString)),
            this, SLOT(SetPortName(QString)));
    connect(&uart_serial_, SIGNAL(rcvDataArrived()),
            this, SLOT(updateRcvData()));
}


void MainPresenter::openPort(QString name,
                             QString baud,
                             QString data_bits,
                             QString parity,
                             QString stop_bits)
{
    uart_serial_.setPortName(name);
    uart_serial_.setBaudRate(baud);
    uart_serial_.setDataBits(data_bits);
    uart_serial_.setParity(parity);
    uart_serial_.setStopBits(stop_bits);
    uart_serial_.Open();
}


void MainPresenter::closePort()
{
    uart_serial_.Close();
}


void MainPresenter::sendMsg(QString msg)
{
    uart_serial_.send(msg);
}


QString MainPresenter::GetPortName()
{
    return uart_serial_.GetPortName();
}


QStringList MainPresenter::GetAllPortOpt()
{
    qDebug() << uart_serial_.GetAllPortOpt();
    return uart_serial_.GetAllPortOpt();
}


QStringList MainPresenter::GetAllBaudOpt()
{
    return uart_serial_.GetAllBaudOpt();
}


QStringList MainPresenter::GetAllDataBitsOpt()
{
    return uart_serial_.GetAllDataBitsOpt();
}


QStringList MainPresenter::GetAllParityOpt()
{
    return uart_serial_.GetAllParityOpt();
}


QStringList MainPresenter::GetAllStopBitsOpt()
{
    return uart_serial_.GetAllStopBitsOpt();
}


void MainPresenter::updateRcvData()
{
    rcv_data_ = uart_serial_.readLastRcv();
    emit rcvDataArrived();
}


QByteArray MainPresenter::getRcvData()
{
    return rcv_data_;
}




