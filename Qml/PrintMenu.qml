import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: printMenu
    width: 480
    height: 320

    property int time: 0
    property bool waitPopupOpened: false

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }
    Rectangle{

        width: fileName.width > remainingTime.width ? fileName.width : remainingTime.width
        height: fileName.height + remainingTime.height + 20
        anchors.left: parent.left
        anchors.leftMargin: 30 + 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -22

        color: "transparent"
        Column{
            id: fileName
            Text {
                text: qsTr("File name")
                font.family: openSansRegular.name
                font.pixelSize: 15
            }
            Text {
                id: fileNameText
                width: 200
                text: stackView.get(1).currentParentName
                font.family: openSansSemibold.name
                font.pixelSize: 27
                font.bold: true

                elide: Text.ElideRight
            }
        }
        Column{
            id: remainingTime
            anchors.top: fileName.bottom
            anchors.topMargin: 20
            Text {
                text: qsTr("time")
                font.family: openSansRegular.name
                font.pixelSize: 15
            }
            Text {
                text: Math.ceil((time + 1) / 60) - 1 + "min " + time % 60 + "sec"
                font.family: openSansSemibold.name
                font.pixelSize: 27
                font.bold: true
            }
        }
    }

    CircularProgressBar{
        id: progressBar

        width: 200
        height: 200

        anchors.top: parent.top
        anchors.topMargin: 35
        anchors.right: parent.right
        anchors.rightMargin: 25
    }
    Rectangle{
        id: printInfoButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Print info")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                fileInfoPopup.open()
                fileInfoPopup.setText(stackView.get(1).currentParentName,
                                      "***min",
                                      stackView.get(2).materialName,
                                      scheduler.receiveFromQmlGetMaterialOptionFromPath(stackView.get(1).currentPath,"layer_height"))
            }
        }
    }
    Rectangle{
        id: quitButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Quit")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                scheduler.receiveFromQmlBedPrintPause('A')
                quitPopup.open()
                quitPopup.setButtonEnabled(false)
            }
        }
    }
    FileInfoPopup{
        id: fileInfoPopup
    }
    WaitPopup{
        id: waitPopup
    }
    QuitPopup{
        id: quitPopup
        onPrintResume: {
            scheduler.receiveFromQmlBedPrintStart('A')
            close()
        }
        onPrintStop: {
            scheduler.receiveFromQmlBedPrintFinish('A')
            waitPopup.open()
            waitPopupOpened = true
            close()
        }
    }

    Timer{
        interval: 1000; running: true; repeat: true
        onTriggered: time++
    }
    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlUpdateProgress :{
            setProgressValue(Math.ceil((currentIndex - 1) /maxIndex * 100))
        }
        onSendToQmlPauseFinish :{
            quitPopup.setButtonEnabled(true)
        }
        onSendToQmlPrintFinish :{
            if(waitPopupOpened === true){
                waitPopupOpened = false
                waitPopup.close()
            }
            stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingCompleted.qml"),StackView.Immediate)
        }
    }
    function setProgressValue(value){
        progressBar.setCurrentValue(value)
    }
    function clear(){
        progressBar.setCurrentValue(0)
        time = 0
    }
}
