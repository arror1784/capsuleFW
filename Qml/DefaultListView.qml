import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {

    width: 480
    height: 320

    property alias title: titleText.text
    property alias model: selectList.model
    property alias delegate: selectList.delegate
    property alias selectList: selectList
    property alias listAreaWidth: selectListArea.width
    property alias listAreaHeight: selectListArea.height
    property alias extraBoard: extraBoardItem.children

    Text {
        id: titleText

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Item{
        id: extraBoardItem

        width: childrenRect.width
        height: childrenRect.height

        anchors.horizontalCenter: titleText.horizontalCenter
        anchors.top: titleText.bottom
        anchors.topMargin: height === 0 ? 0 : 5
    }
    Rectangle{
        id: selectListArea
        width: 450
        height: 218 - extraBoardItem.height - (extraBoardItem.height === 0 ? 0 : 5)

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: extraBoardItem.bottom
        anchors.topMargin: 5

        radius: 8
        color: "#ffffff"

        ListView{
            id: selectList
            width: selectListArea.width - 75
            height: selectListArea.height - 20
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            spacing: 2
            focus: true
            clip: true

            highlightFollowsCurrentItem: true
            highlightMoveDuration: 0
            highlight: Rectangle { color: "#B6CDDC"; height: 22; radius: 5;}
        }
        Rectangle{
            id: up

            width: 50
            height: 70

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8

            Image {
                id: upImage
                anchors.centerIn: parent

                scale: 0.7
                source: "qrc:/image/arrow-up.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    selectList.flick(0,500)
                }
            }
        }
        Rectangle{
            id: down

            width: 50
            height: 70

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8
            Image {
                id: downImage

                scale: 0.7
                anchors.centerIn: parent
                source: "qrc:/image/arrow-down.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    selectList.flick(0,-500)
                }
            }
        }
    }
}
