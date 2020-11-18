#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"

BedSerialport::BedSerialport(QString portPath, PrintScheduler *sched):
m_standardOutput(stdout), _sched(sched)
{

    m_serialPort = new QSerialPort(portPath);
    m_serialPort->setPortName(portPath);
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    //    m_timer.start(5000);
}

void BedSerialport::setBedControl(BedControl *ctrl)
{
    _bedControl = ctrl;
}

void BedSerialport::serialClose()
{
    m_serialPort->close();
}

void BedSerialport::serialOpen()
{
    if(!m_serialPort->open(QIODevice::ReadWrite)){
        qDebug() << "usb open error";
        Logger::GetInstance()->write("usb open error");
    }else{
        qDebug() << "usb open sucess";
        Logger::GetInstance()->write("usb open sucess");
        m_serialPort->readAll();

        connect(m_serialPort, &QSerialPort::readyRead, this, &BedSerialport::handleReadyRead);
        connect(m_serialPort, &QSerialPort::errorOccurred, this, &BedSerialport::handleError);
    }
}

void BedSerialport::handleReadyRead()
{
    uint8_t checkSum = 0;
    if(!m_readAvaiable)
        return;

    arr.append(m_serialPort->readAll());
    ResponseData_t data;
    QByteArray temp;
    while(arr.contains(0x02) && arr.contains(0x03)){
//    if(arr.contains(0x02) && arr.contains(0x03)){
        for(int i = arr.indexOf(0x02,0)+1 ; i < arr.indexOf(0x03,0) - 1 ; i++){
            checkSum += arr[i];
        }
        if(checkSum != (uint8_t)arr[arr.indexOf(0x03,0) - 1]){
            arr = arr.right(arr.size() - arr.indexOf(0x03,0) - 1);
            return;
        }

        temp = arr.left(arr.indexOf(0x03,0) + 1);
        temp = temp.right(temp.size() - arr.indexOf(0x02,0));

        data.bed = (uint8_t)temp[1];
        data.command = (uint8_t)temp[2];
        data.response = (uint8_t)temp[3];

        switch(data.command){
        case 100:
            qDebug() << "transmit error";
            Logger::GetInstance()->write(QString("receive Data error"));
            temp.clear();
            sendByteCommand(lastcommand);
            break;
        case 101:
            qDebug() << "receive Data : move ok";
            Logger::GetInstance()->write(QString("receive Data : move ok"));
            _bedControl->receiveFromBedSerialPort();
            _sched->receiveFromSerialPort(MOVE_OK);
            break;
        case 111:
            qDebug() << "receive Data : auto reboot";
            _sched->sendAutoReboot(true);
            break;
        case 200:
            qDebug() << "receive Data : shutdown";
            _sched->receiveFromSerialPort(SHUTDOWN);
            break;
        case 91:
            qDebug() << "receive Data : LCD " << data.response;
            if(data.response){
                _sched->receiveFromSerialPort(LCD_ON);
            }else {
                _sched->receiveFromSerialPort(LCD_OFF);
            }
            break;
        }
        arr = arr.right(arr.size() - arr.indexOf(0x03,0) - 1);
    }
}

void BedSerialport::handleTimeout()
{
    if (m_readData.isEmpty()) {
        m_standardOutput << QObject::tr("No data was currently available "
                                        "for reading from port %1")
                            .arg(m_serialPort->portName())
                         << endl;
    } else {
        m_standardOutput << QObject::tr("Data successfully received from port %1")
                            .arg(m_serialPort->portName())
                         << endl;
        m_standardOutput << m_readData << endl;
    }

}

void BedSerialport::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
    }
}

void BedSerialport::parsingResponse(QByteArray array){

    if(array.endsWith("OK")){
        _bedControl->receiveFromBedSerialPort();
    }
    qDebug() << array;
    return;
}
void BedSerialport::sendByteCommand(QByteArray buffer){

//    qDebug() << "BedSerialPort byte length" << buffer.size();
    lastcommand.clear();
    lastcommand.append(buffer);
    m_serialPort->write(buffer);
    m_serialPort->waitForBytesWritten();
//    m_serialPort->waitForReadyRead();

    return;
}
void BedSerialport::sendCommand(QString command){

    QString buff(command);
    QStringList parts = buff.split(' ');
    commandFormat_t data = {0};
    for(int i = 0; i < parts.size();i++){
        switch(parts[i].toLocal8Bit()[0]){
        case 'G':
            data.G = parts[i].remove('G').toUInt();
            break;
        case 'H':
            data.H = parts[i].remove('H').toUInt();
            break;
        case 'A':
            data.A.int32 = parts[i].remove('A').toInt();
            break;
        case 'B':
            data.B.int32 = parts[i].remove('B').toInt();
            break;
        case 'C':
            data.C.int32 = parts[i].remove('C').toInt();
            break;
        case 'M':
            data.M.int32 = parts[i].remove('M').toInt();
            break;
        case 'P':
            data.P.int32 = parts[i].remove('P').toInt();
            break;
        }
    }
    Logger::GetInstance()->write("send command : " + buff);
//    qDebug() << "send command : " + buff;
    sendByteCommand(transData(data));
}
QByteArray BedSerialport::transData(commandFormat_t command){
    uint8_t buf[50] = {0};
    uint8_t checksum = 0;

    buf[0] = 0x02;
        buf[1] = command.G;
        buf[2] = command.H;

        buf[3] = command.A.ch[0];
        buf[4] = command.A.ch[1];
        buf[5] = command.A.ch[2];
        buf[6] = command.A.ch[3];

        buf[7] = command.B.ch[0];
        buf[8] = command.B.ch[1];
        buf[9] = command.B.ch[2];
        buf[10] = command.B.ch[3];

        buf[11] = command.C.ch[0];
        buf[12] = command.C.ch[1];
        buf[13] = command.C.ch[2];
        buf[14] = command.C.ch[3];

        buf[15] = command.M.ch[0];
        buf[16] = command.M.ch[1];
        buf[17] = command.M.ch[2];
        buf[18] = command.M.ch[3];

        buf[19] = command.P.ch[0];
        buf[20] = command.P.ch[1];
        buf[21] = command.P.ch[2];
        buf[22] = command.P.ch[3];

    for(int i = 1 ; i < 23; i++){
//    for(int i = 1 ; i < 23; i++){
        checksum += buf[i];
    }
    buf[23] = checksum;
    buf[24] = 0x03;

    qDebug() << "BedSerialPort send massage - G: " << command.G << " H: " << command.H << " A: " << command.A.int32 << " B: " << command.B.int32 << " C: " << command.C.int32 << " M: " << command.M.int32;
//    QThread::sleep(1);
    QByteArray data((char*)buf,25);
    return data;
}

bool BedSerialport::getReadAvaiable() const
{
    return m_readAvaiable;
}

void BedSerialport::setReadAvaiable(bool value)
{
    m_readAvaiable = value;
}
