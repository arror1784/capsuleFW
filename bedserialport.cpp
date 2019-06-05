#include "bedserialport.h"

BedSerialport::BedSerialport(QString portPath) :
    m_standardOutput(stdout)
{

    m_serialPort = new QSerialPort(portPath);
    m_serialPort->setPortName(portPath);
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->open(QIODevice::ReadWrite);

    connect(m_serialPort, &QSerialPort::readyRead, this, &BedSerialport::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &BedSerialport::handleError);
    connect(&m_timer, &QTimer::timeout, this, &BedSerialport::handleTimeout);
    //m_timer.start(5000);
}

void BedSerialport::handleReadyRead()
{
    uint8_t checkSum = 0;
    arr.append(m_serialPort->readAll());
    qDebug() << arr;
    logger->write(QString("receive Data: ") + QString::fromStdString(arr.toStdString()));
    if(arr.contains(0x02) == true && arr.contains(0x03)){
        for(int i = arr.indexOf(0x02,0) + 1;i < arr.indexOf(0x03,0)-1;i++){
            checkSum += arr[i];
        }
        if(checkSum != arr[arr.indexOf(0x03,0) - 1]){
            arr = arr.right(arr.size() - arr.indexOf(0x03,0) - 1);
            return;
        }
        QByteArray temp = arr.left(arr.indexOf(0x03,0) + 1);
        temp = temp.right(temp.size() - arr.indexOf(0x02,0));

        if(temp.contains("OK")){
//            parsingResponse(arr);
            emit sendSignalToBedControl(arr[arr.indexOf("OK") - 2]);
//            arr.clear();
        }else if(temp.contains("error")){
            qDebug() << "transmit error";
            temp.clear();
            sendByteCommand(lastcommand);
        }else if(temp.contains("start")){
            temp.clear();
            emit sendToPrintScheduler('A',START_FLAG);
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
        emit sendSignalToBedControl(array[5]);
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
void BedSerialport::sendCommand(char *command){

    serialMutex.lock();
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
            data.A.db = parts[i].remove('A').toFloat();
            break;
        case 'B':
            data.B.db = parts[i].remove('B').toFloat();
            break;
        case 'C':
            data.C.db = parts[i].remove('C').toFloat();
            break;
        case 'M':
            data.M.db = parts[i].remove('M').toFloat();
            break;
        case 'P':
            data.P.db = parts[i].remove('P').toFloat();
            break;
        }
    }
    logger->write("send command : " + buff);
    sendByteCommand(transData(&data));
    serialMutex.unlock();
}
QByteArray BedSerialport::transData(commandFormat_P command){
    uint8_t buf[50] = {0};
    uint8_t checksum = 0;
    commandFormat_t temp;
    temp.G = command->G;
    temp.H = command->H;
    temp.CheckSum = command->CheckSum;
    temp.A.db = command->A.db * 1000.0f;
    temp.B.db = command->B.db * 1000.0f;
    temp.C.db = command->C.db * 1000.0f;
    temp.M.db = command->M.db * 1000.0f;
    temp.P.db = command->P.db * 1000.0f;

    buf[0] = 0x02;
    buf[1] = temp.G;
    buf[2] = temp.H;

    buf[3] = temp.A.ch[0];
    buf[4] = temp.A.ch[1];
    buf[5] = temp.A.ch[2];
    buf[6] = temp.A.ch[3];
    buf[7] = temp.A.ch[4];
    buf[8] = temp.A.ch[5];
    buf[9] = temp.A.ch[6];
    buf[10] = temp.A.ch[7];

    buf[11] = temp.B.ch[0];
    buf[12] = temp.B.ch[1];
    buf[13] = temp.B.ch[2];
    buf[14] = temp.B.ch[3];
    buf[15] = temp.B.ch[4];
    buf[16] = temp.B.ch[5];
    buf[17] = temp.B.ch[6];
    buf[18] = temp.B.ch[7];

    buf[19] = temp.C.ch[0];
    buf[20] = temp.C.ch[1];
    buf[21] = temp.C.ch[2];
    buf[22] = temp.C.ch[3];
    buf[23] = temp.C.ch[4];
    buf[24] = temp.C.ch[5];
    buf[25] = temp.C.ch[6];
    buf[26] = temp.C.ch[7];

    buf[27] = temp.M.ch[0];
    buf[28] = temp.M.ch[1];
    buf[29] = temp.M.ch[2];
    buf[30] = temp.M.ch[3];
    buf[31] = temp.M.ch[4];
    buf[32] = temp.M.ch[5];
    buf[33] = temp.M.ch[6];
    buf[34] = temp.M.ch[7];

    buf[35] = temp.P.ch[0];
    buf[36] = temp.P.ch[1];
    buf[37] = temp.P.ch[2];
    buf[38] = temp.P.ch[3];
    buf[39] = temp.P.ch[4];
    buf[40] = temp.P.ch[5];
    buf[41] = temp.P.ch[6];
    buf[42] = temp.P.ch[7];

    for(int i = 1 ; i < 43; i++){
//    for(int i = 1 ; i < 23; i++){
        checksum += buf[i];
    }
    buf[43] = checksum;
    buf[44] = 0x03;

    qDebug() << "BedSerialPort send massage - G: " << command->G << " H: " << command->H << " A: " << command->A.db;

    QByteArray data((char*)buf,45);
    return data;
}
