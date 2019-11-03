#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();
    void on_clearInButton_clicked();
    void on_clearOutButton_clicked();
    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    Ui::SerialPort *serialPortUi;
    QSerialPort *serial;
    QMap<QString, QSerialPort::BaudRate> *baudRateOpt;
    QMap<QString, QSerialPort::DataBits> *dataBitsOpt;
    QMap<QString, QSerialPort::Parity> *parityOpt;
    QMap<QString, QSerialPort::StopBits> *stopBitsOpt;

    void lock_setting(bool state);
    bool eventFilter(QObject *watched, QEvent *event);

    void read_rcv_data();
};
#endif // MAINWINDOW_H
