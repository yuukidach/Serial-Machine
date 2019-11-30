#include <QDebug>
#include <QDateTime>
#include "mainpresenter.h"

MainPresenter::MainPresenter(UartSerial& uart_serial, DataHandler& data_handler):
    uart_serial_(uart_serial),
    data_handler_(data_handler)
{
//    connect(&uart_serial_, SIGNAL(PortNameChanged(QString)),
//            this, SLOT(SetPortName(QString)));
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
    rcv_data_ = "";
    QByteArray real_data = uart_serial_.readLastRcv();

    if (getTimestampNeed()) {
        rcv_data_ = QDateTime::currentDateTime().toString("[yy-MM-dd HH:mm:ss:zzz]:\n").toUtf8();
    }
    if (getHexModeNeed()) {
        real_data = real_data.toHex(' ').toUpper();
    }
    rcv_data_.append(real_data);
    emit rcvDataArrived();
}


QByteArray MainPresenter::getRcvData()
{
    return rcv_data_;
}


bool MainPresenter::getTimestampNeed()
{
    return is_timestamp_needed_;
}


void MainPresenter::setTimestampNeed(bool is_need)
{
    is_timestamp_needed_ = is_need;
}


bool MainPresenter::getHexModeNeed()
{
    return is_hex_mode_needed_;
}


void MainPresenter::setHexModeNeed(bool is_need)
{
    is_hex_mode_needed_ = is_need;
}


void MainPresenter::saveData(QString fileurl, QByteArray data)
{
    // FileDialog return the url of the file.
    // eg. file:///Users/who/test.txt.
    // We should remove the first 7 charactors.
    QString file_loc = fileurl.remove(0, 7);
    data_handler_.saveData(file_loc, data);
}



