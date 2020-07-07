import QtQuick 2.0
import QtQuick.Controls 2.5
Item {
    id: mainMenu

    width: 480
    height: 320
//    property alias rectangleWidth: rectangle.width

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }

    Rectangle{
        id: selectFile
        radius: 10
        color: "#00C6EA"
        width: 255
        height: 255

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25

        Rectangle{
            id: rectangle
            width: selectFileText.width
            height: selectFileImage.height + selectFileText.height
            anchors.centerIn: parent
            color: "#00000000"

            Image {
                id: selectFileImage

                anchors.horizontalCenter: selectFileText.horizontalCenter
                scale: 0.7
                source: "qrc:/image/file.png"
            }
            Text {
                id: selectFileText

                anchors.top: selectFileImage.bottom

                text: qsTr("Select File")
                color: "#ffffff"
                font.family: openSansSemibold.name
                font.weight: Font.Bold
                font.letterSpacing: 2
                font.pixelSize: 32
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                scheduler.receiveFromQmlBusySet(true)
                stackView.push(Qt.resolvedUrl("qrc:/Qml/FileSelectList.qml"),StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: setting
        radius: 5
        color: "#DCEAF3"

        width: 155
        height: 120

        anchors.top: selectFile.top
        anchors.right: parent.right
        anchors.rightMargin: 25

        Rectangle{
            width: settingText.width
            height: settingImage.height + settingText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: settingImage
                x: 0
                y: 0
                sourceSize.height: 60
                sourceSize.width: 65
                anchors.horizontalCenterOffset: 0
                source: "qrc:/image/settings.svg"

                scale: 0.85
                anchors.horizontalCenter: settingText.horizontalCenter
            }

            Text {
                id: settingText
                text: qsTr("setting")
                color: "#666666"

                anchors.top: settingImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                scheduler.receiveFromQmlBusySet(true)
                stackView.push(Qt.resolvedUrl("qrc:/Qml/SettingMenu.qml"),StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: resinUpdate
        radius: 5
        color: "#DCEAF3"

        width: 155
        height: 120

        anchors.right: parent.right
        anchors.rightMargin: 25

        anchors.bottom: selectFile.bottom
        Rectangle{
            width: updateText.width
            height: updateImage.height + updateText.height
            anchors.centerIn: parent

            color: "#00000000"
            Image {
                id: updateImage
                source: "qrc:/image/update.png"

                scale: 0.6
                anchors.horizontalCenter: updateText.horizontalCenter
            }
            Text {
                id: updateText
                text: qsTr("resin update")
                color: "#666666"
                anchors.top: updateImage.bottom

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
    ResinUpdatePopup{
        id: resinUpdatePopup
        onCancel: {
            resinUpdatePopup.close()
        }
        onResinUpdate: {
            resinUpdater.update()
        }
    }

    Connections{
        id: schedulerConnection
        target: scheduler
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
    }
}
