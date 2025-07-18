#include "SerialHelper.h"

void SerialHelper::ReceiveAcraInit(void) {
    receiveAera = new QPlainTextEdit(this);
    receiveAera->setFixedSize(800, 400); // 这些都是像素,这个区域的大小
    receiveAera->move(30, 20);
    receiveAera->setReadOnly(true);

    QPushButton* clearReceive = new QPushButton("清空接收区", this);
    clearReceive->setFixedSize(150, 50);
    clearReceive->move(680, 430);
    connect(clearReceive, &QPushButton::clicked, [&]() {
        receiveAera->clear();
        });
}

void SerialHelper::SendAcraInit(void) {
    sendAera = new QPlainTextEdit(this);
    sendAera->setFixedSize(800, 100); // 这些都是像素,这个区域的大小
    sendAera->move(30, 500);
    sendButton = new QPushButton("发送", this);
    sendButton->setFixedSize(150, 50);
    sendButton->move(500, 630);
    sendButton->setDisabled(true);

    connect(sendButton, &QPushButton::clicked, [&]() {
        QString data = sendAera->toPlainText();
        if (sendMode->currentText() == "HEX") {
            QByteArray arr;
            for (int i = 0;i < data.size();++i) {
                if (data[i] == ' ') continue;
                int num = data.mid(i, 2).toUInt(nullptr, 16);
                ++i;
                arr.append(num);
            }
            serialPort->write(arr);
        }
        else
        {
            serialPort->write(data.toLocal8Bit().data());
        }
        });

    QPushButton* clearSend = new QPushButton("清空发送区", this);
    clearSend->setFixedSize(150, 50);
    clearSend->move(680, 630);
    connect(clearSend, &QPushButton::clicked, [&]() {
        sendAera->clear();
        });
}

void SerialHelper::SetupInit(void) {
    this->portNumber = new QComboBox(this);
    this->baudRate = new QComboBox(this);
    this->dataSize = new QComboBox(this);
    this->stopSize = new QComboBox(this);
    this->check = new QComboBox(this);
    this->receiveMode = new QComboBox(this);
    this->sendMode = new QComboBox(this);

    this->baudRate->addItem("4800");
    this->baudRate->addItem("9600");
    this->baudRate->addItem("19200");
    this->baudRate->addItem("115200");
    this->dataSize->addItem("8");
    this->stopSize->addItem("1");
    this->stopSize->addItem("1.5");
    this->stopSize->addItem("2");
    this->check->addItem("无校验");
    this->check->addItem("奇校验");
    this->check->addItem("偶校验");
    this->receiveMode->addItem("HEX");
    this->sendMode->addItem("HEX");
    this->receiveMode->addItem("文本");
    this->sendMode->addItem("文本");

    QLabel* portLabel = new QLabel("串口号",this);
    QLabel* baudLabel = new QLabel("波特率",this);
    QLabel* dataLabel = new QLabel("数据位",this);
    QLabel* stopLabel = new QLabel("停止位",this);
    QLabel* checkLabel = new QLabel("校验位",this);
    QLabel* receiveLabel = new QLabel("接受格式",this);
    QLabel* sendLabel = new QLabel("发送格式",this);

    QVector<QComboBox*> setups;
    setups.push_back(portNumber);
    setups.push_back(baudRate);
    setups.push_back(dataSize);
    setups.push_back(stopSize);
    setups.push_back(check);
    setups.push_back(receiveMode);
    setups.push_back(sendMode);

    QVector<QLabel*> labels;
    labels.push_back(portLabel);
    labels.push_back(baudLabel);
    labels.push_back(dataLabel);
    labels.push_back(stopLabel);
    labels.push_back(checkLabel);
    labels.push_back(receiveLabel);
    labels.push_back(sendLabel);

    for (int i = 0; i < setups.size(); ++i) {
        setups[i]->setFixedSize(200, 50);
        setups[i]->move(850, 20 + i * 80);
        labels[i]->move(1080, 25 + i * 80);
    }
}

void SerialHelper::BeginUSART(void)
{
    starUSART = new QPushButton("串口连接", this);
    endUSART = new QPushButton("串口断开", this);
    starUSART->setFixedSize(150, 50);
    endUSART->setFixedSize(150, 50);
    starUSART->move(850, 600);
    endUSART->move(1000, 600);

    endUSART->setDisabled(true);
    connect(endUSART, &QPushButton::clicked, [&]() {
        sendButton->setDisabled(true);

        starUSART->setDisabled(false);
        endUSART->setDisabled(true);
        serialPort->close();


        });
    connect(starUSART, &QPushButton::clicked, [&]() {

        if (portNumber->currentText() != ""){
            starUSART->setDisabled(true);
        endUSART->setDisabled(false);
        sendButton->setDisabled(false);
        USART();
        }
        else {
            QMessageBox::critical(this, "串口打开失败", "请确认串口是否连接正确");
        }
       

        });

}

void SerialHelper::USART(void)
{
    QSerialPort::BaudRate Baud;
    QSerialPort::DataBits Data;
    QSerialPort::StopBits Stop;
    QSerialPort::Parity Check ;

    QString port = portNumber->currentText();
    QString baud = baudRate->currentText();
    QString data = dataSize->currentText();
    QString stop = stopSize->currentText();
    QString ch = check->currentText();

    if (baud == "4800") Baud = QSerialPort::Baud4800;
    else if (baud == "9600") Baud = QSerialPort::Baud9600;
    else if (baud == "19200") Baud = QSerialPort::Baud19200;
    else if (baud == "115200") Baud = QSerialPort::Baud115200;
    

    if (data == "8")Data = QSerialPort::Data8;

    if (stop == "1")Stop = QSerialPort::OneStop;
    else if(stop == "1.5")Stop = QSerialPort::OneAndHalfStop;
    else if (stop == "2")Stop = QSerialPort::TwoStop;


    if (ch == "无校验") Check = QSerialPort::NoParity;
    else if (ch == "奇校验") Check = QSerialPort::OddParity;
    else if (ch == "偶校验") Check = QSerialPort::EvenParity;

    serialPort = new QSerialPort(this);
    serialPort->setBaudRate(Baud);
    serialPort->setDataBits(Data);
    serialPort->setParity(Check);
    serialPort->setStopBits(Stop);
    serialPort->setPortName(port);

    if (serialPort->open(QSerialPort::ReadWrite)) {
        connect(serialPort, &QSerialPort::readyRead, [&]() {
            auto data = serialPort->readAll();
            if (receiveMode->currentText() == "HEX") {
                QString hex = data.toHex(' ');
                receiveAera->appendPlainText(hex);
            }
            else {
                QString str = QString(data);
                receiveAera->appendPlainText(data);
            }
            });

    }
    else {
        QMessageBox::critical(this, "串口打开失败", "请确认串口是否连接正确");
    
    }

   

    
    




}
void SerialHelper::timerEvent(QTimerEvent* e) {
    QVector<QString>temp;

    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        temp.push_back(info.portName());
    }
    std::sort(temp.begin(), temp.end());
    if (temp != ports) {
        this->portNumber->clear();
        this->ports = temp;
        for (auto& a : ports) this->portNumber->addItem(a);
    }

}

SerialHelper::SerialHelper(QWidget* parent)
    : QMainWindow(parent)
{
    this->setFixedSize(1200, 750);
    this->setWindowTitle("串口助手");

    ReceiveAcraInit();
    SendAcraInit();
    SetupInit();
    BeginUSART();
    this->startTimer(1000);
}

SerialHelper::~SerialHelper()
{}
