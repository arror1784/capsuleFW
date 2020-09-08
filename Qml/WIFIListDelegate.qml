import QtQuick 2.0

Rectangle{
    id: wifiDelegate

    width: parent.width
    height: wifiNameText.height

    color: "#00000000"

    signal wifiClicked(int index)

    property string wifiname: ""

    //name, current, saved, networkID

    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    Text {
        id: wifiNameText
        text: current ?  "* " + name : name
        color: "#474747"
        font.pixelSize: 20
        font.family: openSansRegular.name
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            wifiClicked(index,name)
            wifiname = name
        }
    }
}
