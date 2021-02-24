import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultCalibration{
    id: heightCalibration

    property bool goHome: false
    property bool goMaxheight: false
    property bool goMicro: false
    property bool goAutoHome: false

    title: qsTr("Calibration")
    text: qsTr("Bed height offset (㎛)")
    firstCalibrationValue: -100
    secondCalibrationValue: -10
    calibrationValue: 0

    onCalibrationBTNClicked: {
        if(value === DefaultCalibration.BTNCalibration.FirstPlus){
            buttonEnabled = false
            goMicro = true
            connection.receiveFromQmlMoveMotor("moveMicro",firstCalibrationValue)
        }else if(value === DefaultCalibration.BTNCalibration.FirstMinus){
            buttonEnabled = false
            goMicro = true
            connection.receiveFromQmlMoveMotor("moveMicro",-firstCalibrationValue)
        }else if(value === DefaultCalibration.BTNCalibration.SecondPlus){
            buttonEnabled = false
            goMicro = true
            connection.receiveFromQmlMoveMotor("moveMicro",secondCalibrationValue)
        }else if(value === DefaultCalibration.BTNCalibration.SecondMinus){
            buttonEnabled = false
            goMicro = true
            connection.receiveFromQmlMoveMotor("moveMicro",-secondCalibrationValue)
        }
    }

    BackBTN{
        id: backButton

        onBackClicked: {
            goHome = true
            waitPopup.open()
            connection.receiveFromQmlMoveMotor("goHome",0)
        }
    }
    AcceptBTN{
        id: saveButton

        enabled: buttonEnabled

        text: qsTr("Save Height Offset")

        onAcceptClicked: {
            goHome = true
            waitPopup.open()
            connection.receiveFromQmlMoveMotor("goHome",0)
            connection.receiveFromQmlSetHeightOffset(calibrationValue)
        }
    }
    WaitPopup{
        id: waitPopup
    }
    Connections{
        target: connection
        onSendToQmlMoveOk:{
            if(goHome){
                goHome = false
                waitPopup.close()
                stackView.pop(StackView.Immediate)
            }else if(goMaxheight){
                goMaxheight = false
                buttonEnabled = true
                waitPopup.close()
            }else if(goMicro){
                goMicro = false
                buttonEnabled = true
            }else if(goAutoHome){
                goAutoHome = false
                goMaxheight = true
                connection.receiveFromQmlMoveMotor("moveMaxHeight",0)
            }
        }
        onSendToQmlHeightOffset:{
            calibrationValue = offset
        }
    }

    Component.onCompleted: {
        buttonEnabled = false
        goHome = false
        goMaxheight = false
        goMicro = false
        goAutoHome = true

        connection.receiveFromQmlMoveMotor("autoHome",0)
        connection.receiveFromQmlGetHeightOffset()

        waitPopup.open()
    }
}
