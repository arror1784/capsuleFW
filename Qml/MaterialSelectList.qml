import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0


DefaultListView{
    id: materialSelectList

    property string materialName

    ListModel{
        id: materialModel
    }

    title: qsTr("Select a printing material")
    model: materialModel
    delegate: MaterialListDelegate{
        onMaterialClicked: {
            materialSelectList.selectList.currentIndex = index
            materialSelectList.selectList.update()
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
            if(materialSelectList.selectList.currentIndex !== -1){
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
            arg.push(materialSelectList.selectList.currentItem.metarialname)
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

            materialName = materialSelectList.selectList.currentItem.metarialname

            printingPopup.setText(stackView.get(1).selectedFileName,
                                  materialName,
                                  JsonObject.layer_height)
        }
    }
    Component.onCompleted: {
        materialSelectList.selectList.currentIndex = -1

        if(zipControl.hasFile(stackView.get(1).selectedFilePath,"resin.json")){
            inserMaterialList("Custom")
        }

        connection.receiveFromQmlGetMaterialList()
    }
    function inserMaterialList(name){
        materialModel.append({"name":name})
    }
}
