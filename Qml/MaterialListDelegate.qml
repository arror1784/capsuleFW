import QtQuick 2.0

Rectangle{
    id: materialDelegate

    width: parent.width
    height: fileNameText.height

    color: "#00000000"

    signal materialClicked(int index)

    property string metarialname: ""

    Text {
        id: fileNameText
        text: name
        color: "#474747"
        font.pixelSize: 20
        font.family: openSansRegular.name
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            materialClicked(index)
            metarialname = name
        }
    }
}
