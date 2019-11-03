#include <QString>
#include "serialport.h"

Ui::SerialPort::SerialPort(QSerialPort *port,
                           QComboBox *portBox,
                           QTextEdit *rcvEdit)
{
    this->port = port;
    this->portBox = portBox;
    this->rcvEdit = rcvEdit;
}


void Ui::SerialPort::update_port_combobox()
{
    QString curText = portBox->currentText();
    portBox->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        portBox->addItem(info.portName());
    }
    portBox->setCurrentText(curText);
}

