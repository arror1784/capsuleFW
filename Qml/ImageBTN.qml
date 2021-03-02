import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle{
    id: imageBTN

    signal clicked()

    property alias imgSource: img.source
    property alias imgScale: img.scale
    property alias imgRotation: img.rotation
    property alias imgWidth: img.width
    property alias imgHeight: img.height
    property alias imgSourceWidth: img.sourceSize.width
    property alias imgSourceHeight: img.sourceSize.height

    Image {
        id: img

        anchors.centerIn: parent
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            btnClicked()
        }
    }
    function btnClicked(){
        clicked()
    }
}
