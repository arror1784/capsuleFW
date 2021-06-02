import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0
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
                connection.receiveFromQmlAutoReboot()
                updater.receiveFromQmlSWUpdate()
                swUpdatePopup.open()
            }else{
                connection.receiveFromQmlAutoReboot()
                updater.receiveFromQmlSWUpdateUSB(usbUpdatePath)
                swUpdatePopup.open()
            }
        }
    }
    SWUpdatePopup{
        id: swUpdatePopup
    }
    Connections{
        target: connection
        onSendToQmlAutoReboot:{
            swUpdatePopup.autoReboot()
        }
    }
    Connections{
        id: swUpdaterConnection
        target: updater

        onSendToQmlSWUpdateNotice:{
            if(mode === "network"){
                if(state === "error"){
                    updateText = qsTr("Network not connected")
                    swUpdatePopup.close()
                }else if(state === "finish"){
                    updater.receiveFromQmlSWGetVersion()
                    updateText = qsTr("Update finished")
                }else if(state === "available"){
                    updateEnable = true
                    updateText = qsTr("Update available")
                }else if(state === "notAvailable"){
                    updateEnable = false
                    updateText = qsTr("Current version is the latest")
                }
            }else{
                if(state === "error"){
                    updateInfoText.text = qsTr("Wrong file")
                    swUpdatePopup.close()
                }else if(state === "finish"){
                    updater.receiveFromQmlSWGetVersion()
                    updateText = qsTr("Update finished")
                }else if(state === "available"){
                    updateEnable = true
                    updateText = qsTr("Update available")
                }else if(state === "notAvailable"){
                    updateEnable = false
                    updateText = qsTr("Current version is the latest")
                }
            }
        }
        onSendToQmlSWSendVersion:{
            currentVersion = version
        }
        onSendToQmlSWSendLastestVersion:{
            latestVersion = version
        }
    }
    Component.onCompleted: {
        var it = stackView.find(function(item,index){return item.isUpdateModeSelect})

        if(it !== null){
            updateMode = it.updateMode

            if(updateMode === "network"){
                title = qsTr("Software update - Network")

                updater.receiveFromQmlSWGetVersion()
                updater.receiveFromQmlSWCheckUpdate()

            }else{
                title = qsTr("Software update - USB")

                updater.receiveFromQmlSWGetVersion()

                var selectFile = stackView.find(function(item,index){return item.isSWUpdateSelectFile})
                if(selectFile !== null){
                    usbUpdatePath = selectFile.selectedFilePath
                    updater.receiveFromQmlSWCheckUpdateUSB(usbUpdatePath)
                }else{
                    // ! error
                }
            }
        }
    }
}
