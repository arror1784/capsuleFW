import QtQuick 2.0

Item {

    width: 480
    height: 320
    function inserMaterialList(name){
        materialModel.append({"name":name})
        console.debug(name)
    }
    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }

    ListModel{
        id: materialModel
    }

    Text {
        id: selectText
        text: qsTr("Select a printing material")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Rectangle{
        id: materialSelect
        width: 450
        height: 218

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectText.bottom
        anchors.topMargin: 5

        radius: 8
        color: "#ffffff"
        ListView{
            id: materialSelectList
            width: 432
            height: 200
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

            model: materialModel
            delegate: MaterialListDelegate{
                onMaterialClicked: {
                    materialSelectList.currentIndex = index
                    materialSelectList.update()
                }
            }
        }
    }
    Rectangle{
        id: backButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Back")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
    }
    Rectangle{
        id: selectButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Select")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
    }
    Component.onCompleted: {
        materialSelectList.currentIndex = -1
    }
}
