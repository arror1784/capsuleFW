import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: mainMenu

    width: 480
    height: 320

    property string version: ""
    property string modelNo: ""

    MenuBTN{
        id: selectFile

        radius: 10
        color: "#00C6EA"
        width: 255
        height: 255

        text: qsTr("Select File")

        imgSource: "qrc:/image/file.png"
        imgScale: 0.7

        selectedPosition: MenuBTN.BTNPosition.NONE

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25

        font.family: openSansSemibold.name
        font.weight: Font.Bold
        font.letterSpacing: 2
        font.pixelSize: 32
        fontColor: "#ffffff"

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/FileSelectList.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: setting

        width: 155
        height: 120

        text: qsTr("Settings")

        imgSource: "qrc:/image/settings.png"
        imgScale: 0.9
        imgHeight: 60
        imgWidth: 65

        selectedPosition: MenuBTN.BTNPosition.NONE

        anchors.top: selectFile.top
        anchors.right: parent.right
        anchors.rightMargin: 25

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/SettingMenu.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: info

        width: 155
        height: 120

        text: qsTr("Info")

        imgSource: "qrc:/image/info.png"
        imgScale: 0.6
        imgHeight: 67
        imgWidth: 67

        selectedPosition: MenuBTN.BTNPosition.NONE

        anchors.bottom: selectFile.bottom
        anchors.right: parent.right
        anchors.rightMargin: 25

        onClicked: {
            connection.receiveFromQmlGetProductInfo()
            infoPopup.open()
//          infoPopup.setText(version,modelNo)
        }
    }
    InfoPopup{
        id:infoPopup
    }
    Connections{
        target: wifi
        onConnectedChange:{
            infoPopup.setWifiConnectd(connected)
        }
    }
    Connections{
        target: connection
        onSendToQmlProductInfo:{
            var JsonString = json
            var JsonObject = JSON.parse(JsonString);
            version = JsonObject.version
            modelNo = JsonObject.modelNo
            infoPopup.setText(version,modelNo)
        }
    }
    Component.onCompleted: {
        wifi.checkNetworkConnect()
    }
}
