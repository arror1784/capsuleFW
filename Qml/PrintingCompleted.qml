import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultFinishMenu{
    id: printingCompleted

    title: qsTr("Printing Completed!")

    imgSource: "qrc:/image/check.png"
    imgScale: 0.6

    BackBTN{
        id: printAgainButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        text: qsTr("Print again")

        onClicked: {
            var arg = []
            connection.receiveFromQmlUnlock();
            connection.receiveFromQmlPrintStart(arg)
        }
    }
    AcceptBTN{
        id: closeButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        text: qsTr("close")

        onClicked: {
            connection.receiveFromQmlUnlock();
            stackView.pop(mainMenu,StackView.Immediate)
        }
    }
    Component.onCompleted: {
        var it = stackView.find(function(item,index){return item.isPrinMenu})

        target = it.printName

        var T = new Date(it.time)
        timesec = T.getSeconds()
        timemin = T.getMinutes()

    }
}
