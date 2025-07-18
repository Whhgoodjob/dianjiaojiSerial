#pragma once

#include <QtWidgets/QMainWindow>
#include<QPlainTextEdit>
#include<QPushButton>
#include<QComboBox>
#include<QLabel>
#include<QDebug>
#include<QSerialPort>
#include<QSerialPortInfo>
#include <algorithm>
#include <QList>
#include <QString>
#include<QMessageBox>

class SerialHelper : public QMainWindow
{
    Q_OBJECT

public:
    SerialHelper(QWidget *parent = nullptr);
    ~SerialHelper();

    void ReceiveAcraInit(void);
    void SendAcraInit(void);
    void SetupInit(void);
    void BeginUSART(void);
    void USART(void);
    void timerEvent(QTimerEvent* e);


private:
    QPlainTextEdit* sendAera;
    QPlainTextEdit* receiveAera;

    QPushButton* sendButton;
    QPushButton* starUSART;
    QPushButton* endUSART;

    QComboBox* portNumber;
    QComboBox* baudRate;
    QComboBox* dataSize;
    QComboBox* stopSize;
    QComboBox* check;
    QComboBox* receiveMode;
    QComboBox* sendMode;


    QSerialPort* serialPort;
    QVector<QString>ports;
   

  
};

