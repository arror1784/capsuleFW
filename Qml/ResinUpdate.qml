import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {

    width: 480
    height: 320

    property var updateEnable: false
    property string updateMode
    property string updateTitle

    property string usbUpdatePath

    Text {
        id: selectText
        text: updateTitle

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
    BackBTN{
        id: backButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        onBackClicked: {
            stackView.pop(StackView.Immediate)
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
                if(updateMode === "network"){
                    updater.receiveFromQmlResinUpdate()
                    resinUpdatePopup.open()
                }else{
                    updater.receiveFromQmlResinUpdateUSB(usbUpdatePath)
                    resinUpdatePopup.open()
                }
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

        onSendToQmlResinUpdateNotice:(state,mode) => {
            if(mode === "network"){
                if(state === "error"){
                    updateInfoText.text = "Network not connected"
                    resinUpdatePopup.close()
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
            }else{
                if(state === "error"){
                    updateInfoText.text = "Wrong file"
                    resinUpdatePopup.close()
                }else if(state === "finish"){
                    updater.receiveFromQmlResinGetVersion()
                    resinUpdateNotice.open()
                    updateInfoText.text = "Update finished"
                    updateEnable = false
                    resinUpdatePopup.close()
                    updater.receiveFromQmlSWGetVersion()
                }else if(state === "available"){
                    updateEnable = true
                    updateInfoText.text = "Update available"
                }else if(state === "notAvailable"){
                    updateEnable = false
                    updateInfoText.text = "Current version is the latest"
                }
            }
        }
        onSendToQmlResinSendVersion:{
            currentVersionText.text = version
        }
        onSendToQmlResinSendLastestVersion:(version) => {
            latestVersionText.text = version
        }
    }

    Component.onCompleted: {
        var it = stackView.find(function(item,index){return item.isUpdateModeSelect})

        if(it !== null){
            if(it.updateMode === "network"){
                updateTitle = "Resin update - Network"
                updateMode = "network"
                updater.receiveFromQmlResinGetVersion()
                updater.receiveFromQmlResinCheckUpdate()

            }else{
                updateTitle = "Resin update - USB"
                updateMode = "usb"

                updater.receiveFromQmlResinGetVersion()

                var selectFile = stackView.find(function(item,index){return item.isResinUpdateSelectFile})
                if(selectFile !== null){
                    usbUpdatePath = selectFile.selectedFilePath
                    updater.receiveFromQmlResinCheckUpdateUSB(usbUpdatePath)
                }else{
                    // ! error
                }
            }
        }
    }
}
