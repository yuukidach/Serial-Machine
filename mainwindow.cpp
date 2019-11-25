#include <QShortcut>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPortUi = new Ui::SerialPort(serial,
                                      ui->portBox,
                                      ui->rcvEdit);
    serialPortUi->update_port_combobox();

    ui->portBox->installEventFilter(this);
    ui->dataBitsBox->setCurrentIndex(3);
    ui->stampCkBox->setCheckState(Qt::Checked);
    ui->rcvEdit->setReadOnly(true);

    baudRateOpt = new QMap<QString, QSerialPort::BaudRate>;
    baudRateOpt->insert("9600", QSerialPort::Baud9600);
    baudRateOpt->insert("115200", QSerialPort::Baud115200);

    dataBitsOpt = new QMap<QString, QSerialPort::DataBits>;
    dataBitsOpt->insert("5", QSerialPort::Data5);
    dataBitsOpt->insert("6", QSerialPort::Data6);
    dataBitsOpt->insert("7", QSerialPort::Data7);
    dataBitsOpt->insert("8", QSerialPort::Data8);

    parityOpt = new QMap<QString, QSerialPort::Parity>;
    parityOpt->insert("None", QSerialPort::NoParity);
    parityOpt->insert("Even", QSerialPort::EvenParity);
    parityOpt->insert("Odd", QSerialPort::OddParity);

    stopBitsOpt = new QMap<QString, QSerialPort::StopBits>;
    stopBitsOpt->insert("1", QSerialPort::OneStop);
    stopBitsOpt->insert("2", QSerialPort::TwoStop);

    ui->sendButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->portBox) {
        if (event->type() == QEvent::MouseButtonPress) {
            serialPortUi->update_port_combobox();
        }
    }
    return false;
}

void MainWindow::read_rcv_data()
{
    QByteArray buf;

    buf = serial->readAll().replace("\r", "");
    qDebug() << buf;
    if(buf.isEmpty()) {
        return;
    }

    if (ui->stampCkBox->checkState() == Qt::Checked) {
        ui->rcvEdit->append(QDateTime::currentDateTime().toString("[yy-MM-dd HH:mm:ss]:"));
    }
    ui->rcvEdit->append(buf);
    buf.clear();
}


void MainWindow::lock_setting(bool state)
{
    state = !state;
    ui->portBox->setEnabled(state);
    ui->baudBox->setEnabled(state);
    ui->dataBitsBox->setEnabled(state);
    ui->parityBox->setEnabled(state);
    ui->stopBitsBox->setEnabled(state);
    ui->sendButton->setEnabled(!state);
    if (state) {
        ui->openButton->setText(tr("Open Port"));
    } else {
        ui->openButton->setText(tr("Close Port"));
    }
}


void MainWindow::on_openButton_clicked()
{
    serial = new QSerialPort;
    if (ui->openButton->text()==tr("Open Port")) {
        serial->setPortName(ui->portBox->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(baudRateOpt->value(ui->baudBox->currentText()));
        serial->setDataBits(dataBitsOpt->value(ui->dataBitsBox->currentText()));
        serial->setParity(parityOpt->value(ui->parityBox->currentText()));
        serial->setStopBits(stopBitsOpt->value(ui->stopBitsBox->currentText()));
        serial->setFlowControl(QSerialPort::NoFlowControl);

        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::read_rcv_data);
        lock_setting(true);
    } else {
        serial->clear();
        serial->close();
        serial->deleteLater();
        lock_setting(false);
    }
}

void MainWindow::on_clearInButton_clicked()
{
    ui->rcvEdit->clear();
}

void MainWindow::on_clearOutButton_clicked()
{
    ui->sendEdit->clear();
}

void MainWindow::on_sendButton_clicked()
{
    QString sendStr = ui->sendEdit->toPlainText();
#ifdef __APPLE__
    sendStr.replace("\n", "\r\n");
#endif
    serial->write(sendStr.toUtf8());
}


void MainWindow::on_stampCkBox_toggled(bool checked)
{
    if (checked) {

    }
}


void MainWindow::on_hexCkBox_toggled(bool checked)
{
    QByteArray rcvBuffer = ui->rcvEdit->toPlainText().toUtf8();
    if (checked) {
        ui->rcvEdit->setText(rcvBuffer.toHex(' '));
    } else {
        ui->rcvEdit->setText(QByteArray::fromHex(rcvBuffer));
    }
}
