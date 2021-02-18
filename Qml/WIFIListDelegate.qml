import QtQuick 2.0

Rectangle{
    id: wifiDelegate

    width: parent.width
    height: wifiNameText.height

    color: "#00000000"

    signal wifiClicked(int index)

//    property string ssid: ""
//    property string bssid: ""
//    property string flags: ""

    //name, current, saved, networkID

    Text {
        id: wifiNameText
        text: current ?  "Current: " + ssid : ssid
        color: "#474747"
        font.pixelSize: 20
        font.family: openSansRegular.name
        font.bold: current
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            wifiClicked(index,ssid)
        }
    }
}
