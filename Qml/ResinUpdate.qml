import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

DefaultUpdateView{
    id: defaultUpdateView

    property var updateEnable: false
    property string updateMode
    property string usbUpdatePath

    title: ""
    updateText: qsTr("Update check")
    currentVersion: ""
    latestVersion: ""

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
        id: updateButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        opacity: updateEnable ? 1 : 0.7
        enabled: updateEnable

        text: qsTr("Update")

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
                    updateText = "Network not connected"
                    resinUpdatePopup.close()
                }else if(state === "finish"){
                    updater.receiveFromQmlResinGetVersion()
                    resinUpdateNotice.open()
                    updateText = "Update finished"
                    updateEnable = false
                    resinUpdatePopup.close()
                }else if(state === "available"){
                    updateEnable = true
                    updateText = "Update available"
                }else if(state === "notAvailable"){
                    updateEnable = false
                    updateText = "Current version is the latest"
                }
            }else{
                if(state === "error"){
                    updateText = "Wrong file"
                    resinUpdatePopup.close()
                }else if(state === "finish"){
                    updater.receiveFromQmlResinGetVersion()
                    resinUpdateNotice.open()
                    updateText = "Update finished"
                    updateEnable = false
                    resinUpdatePopup.close()
                    updater.receiveFromQmlSWGetVersion()
                }else if(state === "available"){
                    updateEnable = true
                    updateText = "Update available"
                }else if(state === "notAvailable"){
                    updateEnable = false
                    updateText = "Current version is the latest"
                }
            }
        }
        onSendToQmlResinSendVersion:{
            currentVersion = version
        }
        onSendToQmlResinSendLastestVersion:(version) => {
            latestVersion = version
        }
    }

    Component.onCompleted: {
        var it = stackView.find(function(item,index){return item.isUpdateModeSelect})

        if(it !== null){
            if(it.updateMode === "network"){
                title = "Resin update - Network"
                updateMode = "network"
                updater.receiveFromQmlResinGetVersion()
                updater.receiveFromQmlResinCheckUpdate()

            }else{
                title = "Resin update - USB"
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
