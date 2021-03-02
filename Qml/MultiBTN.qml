import QtQuick 2.0

Rectangle{
    id: enumBTN

    signal clicked()

    property alias text: menuText.text
    property alias font: menuText.font
    property alias fontColor: menuText.color

    property alias imgSource: iconImage.source
    property alias imgScale: iconImage.scale
    property alias imgRotation: iconImage.rotation
    property alias imgWidth: iconImage.width
    property alias imgHeight: iconImage.height
    property alias imgSourceWidth: iconImage.sourceSize.width
    property alias imgSourceHeight: iconImage.sourceSize.height

    radius: 5
    color: "#DCEAF3"

    width: 215
    height: 110

    Rectangle{
        width: iconImage.width
        height: iconImage.height + menuText.height

        anchors.centerIn: parent

        color: "#00000000"
        Image {
            id: iconImage

            antialiasing: true
            smooth: true
        }
        Text {
            id: menuText
            color: "#666666"
            anchors.top: iconImage.bottom
            anchors.horizontalCenter: iconImage.horizontalCenter

            font.family: openSansSemibold.name
            font.pixelSize: 20
            font.bold: true
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            btnClicked()
        }
    }
    function btnClicked(){
        clicked()
    }
}

