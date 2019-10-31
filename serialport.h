#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_mainwindow.h"

//namespace Ui {
//    class SerialPort;
//}

class SerialPort
{
public:
    SerialPort();
    ~SerialPort();

    void update_port_combobox(QComboBox * portBox);
};



#endif // SERIALPORT_H
