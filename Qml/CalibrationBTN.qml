import QtQuick 2.0
import QtQuick.Controls 2.5

Button{
    id: calibrationBTN

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
    states: [
        State {
            name: "up"
            PropertyChanges { target: img; source: "qrc:/image/arrow-up.png" }
        },
        State {
            name: "down"
            PropertyChanges { target: img; source: "qrc:/image/arrow-down.png" }
        }
    ]
}
