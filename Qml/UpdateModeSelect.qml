import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property string updateMode
    property bool isUpdateModeSelect: true

    MenuBTN{
        id: network

        text: qsTr("Network")

        imgSource: "qrc:/image/network.png"
        imgWidth: 67
        imgHeight: 67
        imgScale: 0.57

        selectedPosition: MenuBTN.BTNPosition.TopLeft

        onClicked: {
            updateMode = "network"
            var it = stackView.find(function(item,index){return item.isUpdateMenu})

            if(it !== null){
                if(it.updateTarget === "resin"){
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
                }else{
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdate.qml"),StackView.Immediate)
                }
            }
        }
    }
    MenuBTN{
        id: usb

        text: qsTr("USB")

        imgSource: "qrc:/image/USB.png"
        imgWidth: 67
        imgHeight: 67
        imgScale: 0.85

        selectedPosition: MenuBTN.BTNPosition.TopRight

        onClicked: {
            updateMode = "usb"

            var it = stackView.find(function(item,index){return item.isUpdateMenu})

            if(it !== null){
                if(it.updateTarget === "resin"){
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdateSelectFile.qml"),StackView.Immediate)
                }else{
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdateSelectFile.qml"),StackView.Immediate)
                }
            }
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
}
