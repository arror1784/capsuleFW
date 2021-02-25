import QtQuick 2.0
import QtQuick.Controls 2.5

Button{
    id: calibrationBTN

    property alias imgSource: img.source
    property alias imgScale: img.scale
    property alias imgRotation: img.rotation
    property alias imgWidth: img.width
    property alias imgHeight: img.height
    property alias imgSourceWidth: img.sourceSize.width
    property alias imgSourceHeight: img.sourceSize.height

    width: 45
    height: 45

    state: "up"

    background: Rectangle{
        anchors.fill: parent

        color: "#C9DBE6"
        radius: 8
    }

    Image {
        id: img

        anchors.centerIn: parent
        source: "qrc:/image/arrow-up.png"

        scale: 0.5
    }
}
