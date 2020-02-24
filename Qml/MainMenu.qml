import QtQuick 2.0

Item {
    id: mainMenu

    width: 480
    height: 320
//    property alias rectangleWidth: rectangle.width

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }

    Rectangle{
        id: selectFile
        radius: 10
        color: "#00C6EA"
        width: 255
        height: 255

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25

        Rectangle{
            id: rectangle
            width: selectFileText.width
            height: selectFileImage.height + selectFileText.height
            anchors.centerIn: parent
            color: "#00000000"

            Image {
                id: selectFileImage

                anchors.horizontalCenter: selectFileText.horizontalCenter
                scale: 0.7
                source: "qrc:/image/file.png"
            }
            Text {
                id: selectFileText

                anchors.top: selectFileImage.bottom

                text: qsTr("Select File")
                color: "#ffffff"
                font.family: openSansSemibold.name
                font.weight: Font.Bold
                font.letterSpacing: 2
                font.pixelSize: 32
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.debug("selectfile clicked")
                console.debug(selectFileText.font.family)
            }
        }
    }
    Rectangle{
        id: calibration
        radius: 5
        color: "#DCEAF3"

        width: 155
        height: 120

        anchors.top: selectFile.top
        anchors.right: parent.right
        anchors.rightMargin: 25

        Rectangle{
            width: calibrationText.width
            height: calibrationImage.height + calibrationText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: calibrationImage
                source: "qrc:/image/calibration.png"

                scale: 0.7
                anchors.horizontalCenter: calibrationText.horizontalCenter
            }

            Text {
                id: calibrationText
                text: qsTr("Calibration")
                color: "#666666"

                anchors.top: calibrationImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
               console.debug("calibration clicked")
            }
        }
    }
    Rectangle{
        id: update
        radius: 5
        color: "#DCEAF3"

        width: 155
        height: 120

        anchors.right: parent.right
        anchors.rightMargin: 25

        anchors.bottom: selectFile.bottom
        Rectangle{
            width: updateText.width
            height: updateImage.height + updateText.height
            anchors.centerIn: parent

            color: "#00000000"
            Image {
                id: updateImage
                source: "qrc:/image/update.png"

                scale: 0.6
                anchors.horizontalCenter: updateText.horizontalCenter
            }
            Text {
                id: updateText
                text: qsTr("update")
                color: "#666666"
                anchors.top: updateImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.debug("update clicked")
            }
        }
    }
}
