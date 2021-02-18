import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {

    width: 480
    height: 320

    property string materialName

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
            width: 375
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
        Rectangle{
            id: up

            width: 50
            height: 70

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8

            Image {
                id: upImage
                anchors.centerIn: parent

                scale: 0.7
                source: "qrc:/image/arrow-up.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    materialSelectList.flick(0,500)
                }
            }
        }
        Rectangle{
            id: down

            width: 50
            height: 70

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8
            Image {
                id: downImage

                scale: 0.7
                anchors.centerIn: parent
                source: "qrc:/image/arrow-down.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    materialSelectList.flick(0,-500)
                }
            }
        }
    }

    BackBTN{
        id: backButton

        onBackClicked: {
            var it = stackView.find(function(item,index){return item.isFileSelectList})
            if(it){
                it.reset()
            }
            stackView.pop(StackView.Immediate)
        }
    }
    AcceptBTN{
        id: selectButton

        text: qsTr("Select")

        onAcceptClicked: {
            if(materialSelectList.currentIndex !== -1){
                connection.receiveFromQmlGetInfoSetting(stackView.get(1).selectedFilePath)
                printingPopup.open()
                //To do Todo
            }
        }
    }
    PrintingPopup{
        id: printingPopup
        onStartPrintingButtonClicked:{
            var arg = []
            arg.push(stackView.get(1).selectedFilePath)
            arg.push(materialSelectList.currentItem.metarialname)
            console.log(arg)
            connection.receiveFromQmlPrintStart(arg)
//            stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintMenu.qml"),StackView.Immediate)
        }
    }
    ZipControl{
        id:zipControl
    }

    Connections{
        target: connection
        onSendToQmlMaterialList:function aa(name){
            for(var i = 0; i < name.length; i++){
                inserMaterialList(name[i])
            }
        }
        onSendToQmlGetInfoSetting:{
            var JsonString = option
            var JsonObject = JSON.parse(JsonString)

            materialName = materialSelectList.currentItem.metarialname

            printingPopup.setText(stackView.get(1).selectedFileName,
                                  materialName,
                                  JsonObject.layer_height)
        }
    }
    Component.onCompleted: {
        materialSelectList.currentIndex = -1

        if(zipControl.hasFile(stackView.get(1).selectedFilePath,"resin.json")){
            inserMaterialList("Custom")
        }

        connection.receiveFromQmlGetMaterialList()
    }
    function inserMaterialList(name){
        materialModel.append({"name":name})
    }
}
