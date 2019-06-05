import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 600
    height: 400
    title: qsTr("World")

    Rectangle{
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            onClicked: {
                scheduler.receiveFromQmlBedPrintStart('A');
                console.debug("clicked")
            }
        }
    }

}
