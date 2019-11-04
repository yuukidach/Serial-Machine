#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

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
