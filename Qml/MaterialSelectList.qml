import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {

    width: 480
    height: 320

    property string materialName

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    ListModel{
        id: materialModel
    }

    Text {
        id: selectText
        text: qsTr("Select a printing material")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Rectangle{
        id: materialSelect
        width: 450
        height: 218

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectText.bottom
        anchors.topMargin: 5

        radius: 8
        color: "#ffffff"
        ListView{
            id: materialSelectList
            width: 432
            height: 200
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            spacing: 2
            focus: true
            clip: true

            highlightFollowsCurrentItem: true
            highlightMoveDuration: 0
            highlight: Rectangle { color: "#B6CDDC"; height: 22; radius: 5;}

            model: materialModel
            delegate: MaterialListDelegate{
                onMaterialClicked: {
                    materialSelectList.currentIndex = index
                    materialSelectList.update()
                }
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
            anchors.fill: parent
            onClicked: {
                stackView.pop(StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: selectButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Select")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(materialSelectList.currentIndex !== -1){
                    materialName = materialSelectList.currentItem.metarialname
                    printingPopup.open()
                    printingPopup.setText(stackView.get(1).currentParentName,
                                          materialName,
                                          scheduler.receiveFromQmlGetPrintOptionFromPath(stackView.get(1).currentPath,"layer_height"))
                }
            }
        }
    }
    PrintingPopup{
        id: printingPopup
        onStartPrintingButtonClicked:{
            scheduler.receiveFromQmlBedPrint(stackView.get(1).currentPath,materialSelectList.currentItem.metarialname)
            console.debug(stackView.get(1).currentPath)
//            printSettingSocket.socketClose()
            stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintMenu.qml"),StackView.Immediate)
        }
    }
    FileValidator{
        id: validator
        treatAsImage: false
    }

    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlInsertMaterialList: function onSendToQmlInsertMaterialList(name){
            inserMaterialList(name)
        }
    }
    Component.onCompleted: {
        materialSelectList.currentIndex = -1
        validator.url = "file:" + stackView.get(1).currentPath + "/resin.json"
        if(validator.fileValid){
            inserMaterialList("Custom")
        }
        scheduler.receiveFromQmlUpdateMaterial()

    }
    function inserMaterialList(name){
        materialModel.append({"name":name})
    }
}
