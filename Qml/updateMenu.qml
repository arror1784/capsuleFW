import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    Rectangle{
        id: resinUpdate
        radius: 5
        anchors.top: parent.top
        anchors.topMargin: 20
        color: "#DCEAF3"

        width: 215
        height: 110

        anchors.left: parent.left
        anchors.leftMargin: 15

        Rectangle{
            width: resinUpdateText.width
            height: resinUpdateImage.height + resinUpdateText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: resinUpdateImage
                source: "qrc:/image/fill.png"

                height: 67
                width: 67

                scale: 0.9
                anchors.horizontalCenter: resinUpdateText.horizontalCenter
            }

            Text {
                id: resinUpdateText
                text: qsTr("resin update")
                color: "#666666"

                anchors.top: resinUpdateImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                resinUpdater.checkUpdate()
                resinUpdatePopup.open()
            }
        }
    }
    Rectangle {
        id: firmwareUpdate
        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 15
        Rectangle{
            width: firmwareUpdateText.width
            height: firmwareUpdateImage.height + firmwareUpdateText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: firmwareUpdateImage

                width: 67
                height: 67

                source: "qrc:/image/download.png"

                scale: 0.8
                anchors.horizontalCenter: firmwareUpdateText.horizontalCenter
            }

            Text {
                id: firmwareUpdateText
                text: qsTr("software update")
                color: "#666666"

                anchors.top: firmwareUpdateImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
//                stackView.push(Qt.resolvedUrl("qrc:/Qml/FirmUpdateFileList.qml"),StackView.Immediate)
                swUpdatePopup.open()
                scheduler.checkUpdate()
            }
        }
    }
    Rectangle{
        id: backButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Back")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            antialiasing: false
            anchors.leftMargin: 0
            anchors.fill: parent
            onClicked: {
                scheduler.receiveFromQmlBusySet(false)
                stackView.pop(StackView.Immediate)
            }
        }
    }
    ResinUpdatePopup{
        id: resinUpdatePopup
        onCancel: {
            resinUpdatePopup.close()
        }
        onResinUpdate: {
            resinUpdater.update()
        }
    }
    SWUpdatePopup{
        id: swUpdatePopup
        onCancel: {
            swUpdatePopup.close()
        }
        onSwUpdate: {
            scheduler.update()
        }
    }

    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlSWUpdateAvailable:{
            swUpdatePopup.updateAvailable()
        }
        onSendToQmlSWUpdateNotAvailable:{
            swUpdatePopup.updateNotAvailable()
        }
        onSendToQmlSWUpdateFinished:{
            swUpdatePopup.updateFinished()
        }
        onSendToQmlSWUpdateError:{
            console.debug("update error")
            swUpdatePopup.updateError()
        }
    }
    Connections{
        id: resinUpdaterConnection
        target: resinUpdater
        onUpdateAvailable:{
            resinUpdatePopup.updateAvailable()
        }
        onUpdateNotAvailable:{
            resinUpdatePopup.updateNotAvailable()
        }
        onUpdateFinished:{
            resinUpdatePopup.updateFinished()
        }
        onUpdateError:{
            resinUpdatePopup.updateError()
        }
    }
//    Connections{
//        id: swUpdaterConnection
//        target: SWUpdater
//        onUpdateAvailable:{
//            swUpdatePopup.updateAvailable()
//        }
//        onUpdateNotAvailable:{
//            swUpdatePopup.updateNotAvailable()
//        }
//        onUpdateFinished:{
//            swUpdatePopup.updateFinished()
//        }
//        onUpdateError:{
//            console.debug("update error")
//            swUpdatePopup.updateError()
//        }
//    }
}
