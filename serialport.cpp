#include "serialport.h"

SerialPort::SerialPort()
{
    return;
}


void SerialPort::update_port_combobox(QComboBox *portBox)
{
    QString curText = portBox->currentText();
    portBox->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        portBox->addItem(info.portName());
    }
    portBox->setCurrentText(curText);
}
