import QtQuick 2.0

Rectangle{
    id: parentDir

    signal clicked()

    property alias text: parentDirText.text

    width: 450
    height: 40

    radius: 8
    color: "#ffffff"

    Rectangle{
        id: parentDirButton

        width: 38
        height: 34

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 4

        radius: 4
        color: "#B6CDDC"
        ImageBTN{
            id: parentDirButtonImage

            anchors.centerIn: parentDirButton

            imgSource: "qrc:/image/arrow-dir.png"
            imgScale: 0.6
        }
        MouseArea{
            anchors.fill: parentDirButton
            onClicked: {
                btnClicked()
            }
        }
    }
    Text {
        id: parentDirText
        width: 396
        height: 23

        anchors.left: parentDirButton.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter

        elide: Text.ElideLeft

        color: "#474747"

        font.pixelSize: 22
        font.family: openSansRegular.name
    }
    function btnClicked(){
        clicked()
    }
}
