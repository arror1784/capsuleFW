import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: defaultFinishMenu
    width: 480
    height: 320

    property int timesec: 0
    property int timemin: 0

    property alias title: titleText.text
    property alias target: fileName.text
    property alias imgSource: img.source
    property alias imgScale: img.scale
    property alias imgRotation: img.rotation
    property alias imgWidth: img.width
    property alias imgHeight: img.height

    Item {
        id: rec
        width: img.width + titleText.contentWidth
        height: img.height

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40


        Image {
            id: img
        }
        Text {
            id: titleText
            anchors.leftMargin: -2
            anchors.left: img.right
            anchors.verticalCenter: img.verticalCenter
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
}
