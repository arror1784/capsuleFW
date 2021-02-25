import QtQuick 2.0
import QtQuick.Controls 2.5


DefaultCalibration{
    id: heightCalibration

    property double maxLEDBrightness: 150.0
    property double minLEDBrightness: 50.0

    title: qsTr("Calibration")
    text: qsTr("UV LED Brightness (%)")
    firstCalibrationValue: 1
    secondCalibrationValue: 0.1
    calibrationValue: 0

    onCalibrationBTNClicked: {
        calibrationValue = Math.round(calibrationValue * 10) / 10

        if(value === DefaultCalibration.BTNCalibration.FirstPlus){
            calibrationValue = Math.min(calibrationValue,maxLEDBrightness)
        }else if(value === DefaultCalibration.BTNCalibration.FirstMinus){
            calibrationValue = Math.max(calibrationValue,minLEDBrightness)
        }else if(value === DefaultCalibration.BTNCalibration.SecondPlus){
            calibrationValue = Math.min(calibrationValue,maxLEDBrightness)
        }else if(value === DefaultCalibration.BTNCalibration.SecondMinus){
            calibrationValue = Math.max(calibrationValue,minLEDBrightness)
        }
    }

    BackBTN{
        id: backButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        onClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    AcceptBTN{
        id: saveButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        text: qsTr("Save LED Offset")

        onClicked: {
            connection.receiveFromQmlSetLedOffset(calibrationValue)
            stackView.pop(StackView.Immediate)
        }
    }
    Connections{
        target: connection
        onSendToQmlLEDOffset:{
            calibrationValue = offset
        }
    }
    Component.onCompleted: {
        connection.receiveFromQmlGetLedOffset()
    }
}
