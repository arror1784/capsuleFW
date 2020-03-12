import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property int time: 1

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }
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
                width: 200
                text: stackView.get(1).currentParentName
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"
                elide: Text.ElideRight
            }
            Text {
                text: Math.ceil((time + 1) / 60) - 1 + "min " + time % 60 + "sec"
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"
            }
        }
    }
    Rectangle{
        id: printAgainButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Print again")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.get(3).clear()
                scheduler.receiveFromQmlBedPrint('A',stackView.get(1).currentPath,stackView.get(2).materialName)
                console.debug(stackView.get(1).currentPath)
                console.debug(stackView.get(2).materialName)
                stackView.pop(StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: closeButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("close")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.pop(mainMenu,StackView.Immediate)
            }
        }
    }
    Component.onCompleted: {
        time = stackView.get(3).time
    }
}
