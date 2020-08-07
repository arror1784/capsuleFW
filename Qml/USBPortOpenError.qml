import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: mainMenu

    width: 480
    height: 320
//    property alias rectangleWidth: rectangle.width

    property var name: "USBPortOpenError"

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }

    Text {
        id: text
        text: qsTr("USB PORT CONNECTION ERROR")

        anchors.centerIn: parent

        font.family: openSansSemibold.name
        font.weight: Font.Bold
        font.letterSpacing: 1
        font.pixelSize: 24
    }
}
