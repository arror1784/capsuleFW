import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property int timesec: 0
    property int timemin: 0

    Item {
        id: rec
        width: checkImage.width + printingCompleted.contentWidth
        height: checkImage.height

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40


        Image {
            id: checkImage
            source: "qrc:/image/check.png"

            scale: 0.6
        }
        Text {
            id: printingCompleted
            text: qsTr("Printing Completed!")
            anchors.leftMargin: -2
            anchors.left: checkImage.right
            anchors.verticalCenter: checkImage.verticalCenter
            font.pixelSize: 27
            font.bold: true
            font.family: openSansSemibold.name
        }
    }
    Item{
        width: optionText.width + valueText.width + 15
        height: optionText.height

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        Column{
            id: optionText
            Text {
                text: qsTr("File name")
                font.family: openSansRegular.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("Time spent")
                font.family: openSansRegular.name
                font.pixelSize: 23
                color: "#474747"
            }
        }
        Column{
            id: valueText
            anchors.left: optionText.right
            anchors.leftMargin: 20
            Text {
                id: fileName
                width: 200
                text: ""
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"
                elide: Text.ElideRight
            }
            Text {
                text: timemin + "min " + timesec + "sec"
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"
            }
        }
    }
    BackBTN{
        id: printAgainButton

        text: qsTr("Print again")

        onBackClicked: {
            var arg = []
            connection.receiveFromQmlUnlock();
            connection.receiveFromQmlPrintStart(arg)
        }
    }
    AcceptBTN{
        id: closeButton

        text: qsTr("close")

        onAcceptClicked: {
            connection.receiveFromQmlUnlock();
            stackView.pop(mainMenu,StackView.Immediate)
        }
    }
    Component.onCompleted: {
        var it = stackView.find(function(item,index){return item.isPrinMenu})

        fileName.text = it.printName

        var T = new Date(it.time)
        timesec = T.getSeconds()
        timemin = T.getMinutes()

    }
}
