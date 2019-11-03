#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_mainwindow.h"

namespace Ui {
    class SerialPort;
}

class Ui::SerialPort
{
public:
    QSerialPort *port;
    QComboBox *portBox;
    QTextEdit *rcvEdit;

public:
    SerialPort(QSerialPort *port,
               QComboBox *comboBox,
               QTextEdit *rcvEdit);
    ~SerialPort();

    void update_port_combobox();
};



#endif // SERIALPORT_H
