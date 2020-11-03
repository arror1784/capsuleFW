import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {

    width: 480
    height: 320

    property var updateEnable: false

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    Text {
        id: selectText
        text: qsTr("Resin update")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        id: updateInfoText
        text: qsTr("Update check")

        color: "#474747"

        anchors.left: versionInfo.left
        anchors.leftMargin: 15
        anchors.bottom: versionInfo.top
        anchors.bottomMargin: 13

        font.pointSize: 17
        font.family: openSansRegular.name
    }
    Rectangle{
        id: versionInfo
        width: 450
        height: 115

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectText.bottom
        anchors.topMargin: 78

        radius: 8
        color: "#ffffff"

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 13
            text: qsTr("Current version")

            font.family: openSansRegular.name
            font.pixelSize: 23
            color: "#474747"
        }
        Text {
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 13

            text: qsTr("Latest version")
            font.family: openSansRegular.name
            font.pixelSize: 23
            color: "#474747"
        }
        Text {
            id: currentVersionText
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 15

            font.family: openSansSemibold.name
            font.pixelSize: 25
            font.bold: true
            color: "#474747"

            width: 250
            elide: Text.ElideRight
        }
        Text {
            id: latestVersionText
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15

            font.family: openSansSemibold.name
            font.pixelSize: 25
            font.bold: true
            color: "#474747"

            width: 250
            elide: Text.ElideRight
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
            anchors.fill: parent
            onClicked: {
                stackView.pop(StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: updateButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        opacity: updateEnable ? 1 : 0.7

        Text {
            text: qsTr("Update")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            enabled: updateEnable
            onClicked: {
                updater.receiveFromQmlResinUpdate()
                resinUpdatePopup.open()
            }
        }
    }
    ResinUpdatePopup{
        id:resinUpdatePopup
    }
    ResinUpdateNotice{
        id:resinUpdateNotice
    }

    Connections{
        id: resinUpdaterConnection
        target: updater

        onSendToQmlResinUpdateNotice:{
            console.log("update resin check",state)
            if(state === "error"){
                updateInfoText.text = "Network not connected"
            }else if(state === "finish"){
                updater.receiveFromQmlResinGetVersion()
                resinUpdateNotice.open()
                updateInfoText.text = "Update finished"
                updateEnable = false
                resinUpdatePopup.close()
            }else if(state === "available"){
                updateEnable = true
                updateInfoText.text = "Update available"
            }else if(state === "notAvailable"){
                updateEnable = false
                updateInfoText.text = "Current version is the latest"
            }
        }
        onSendToQmlResinSendVersion:{
            console.log("get resin currentVersion",version)
            currentVersionText.text = version
        }
        onSendToQmlResinSendLastestVersion:{
            console.log("get resin latestVersion",version)
            latestVersionText.text = version
        }
    }

    Component.onCompleted: {
        updater.receiveFromQmlResinCheckUpdate()

        updater.receiveFromQmlResinGetVersion()
        updater.receiveFromQmlResinGetLastestVersion()
        updater.receiveFromQmlResinCheckUpdate()
    }
}
