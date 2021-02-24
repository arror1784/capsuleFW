import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultFinishMenu{
    id: printingError

    title: qsTr("Printing Error!")

    imgSource: "qrc:/image/error.png"
    imgWidth: 96
    imgHeight: 96

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

        target = it.printName

        var T = new Date(it.time)
        timesec = T.getSeconds()
        timemin = T.getMinutes()

    }
}
