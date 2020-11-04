import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal connectButtonClicked(string ssid,string bssid,string pwd,int id)
    signal connectButtonClickedWithoutPSWD(string ssid,string bssid,int id)

    property int networkID: -1
    property bool wpaEnable: false
    property string ssid: ""
    property string bssid: ""


    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }

    Popup{
        id: popup
        width: parent.width - 60
        height: parent.height - 60
        anchors.centerIn: Overlay.overlay

        background: Rectangle{
            id: backgroundPopUp
            anchors.fill: parent
            color: "#FAFDFF"
            radius: 8
        }
        modal: false
        focus: true

        closePolicy: Popup.NoAutoClose

        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -22
            Column{
                id: optionText
                Text {
                    text: qsTr("WIFI ssid")
                    font.family: openSansSemibold.name
                    font.pixelSize: 23
                    color: "#474747"
                }
                Text {
                    id: wifiPasswordText
                    text: qsTr("WIFI password")
                    font.family: openSansSemibold.name
                    font.pixelSize: 23
                    color: "#474747"
                    visible: wpaEnable
                }
            }
            Column{
                id: valueText
                anchors.left: optionText.right
                anchors.leftMargin: 15
                Text {
                    id: ssidText
                    font.family: openSansSemibold.name
                    font.pixelSize: 23
                    font.bold: true
                    color: "#474747"
                    text: ssid
                    width: 200
                    elide: Text.ElideRight
                }
                TextField {
                    id: passwordField
                    width: parent.width
                    echoMode: TextInput.Password
                    placeholderText: "Password"
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                    visible: wpaEnable
                }
            }
        }
        Switch{
            id: visible
//            anchors.left: passwordField.right
            text: qsTr("passwd visible")
            visible: wpaEnable
            onCheckedChanged: {
                if(checked){
                    passwordField.echoMode = TextInput.Normal
                }else{
                    passwordField.echoMode = TextInput.Password
                }
            }
        }

        Rectangle{
            id: cancleButton
            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "#DCEAF3"

            radius: 8

            Text {
                text: qsTr("Cancel")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    popup.close()
                }
            }
        }
        Rectangle{
            id: connectButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8

            Text {
                text: qsTr("connect")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(wpaEnable){
                        connectButtonClicked(ssid,bssid,passwordField.text,networkID)
                    }else{
                        connectButtonClickedWithoutPSWD(ssid,bssid,networkID)
                    }

                    popup.close()
                }
            }
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }

    function open(ssid,bssid,id,wpa){
        setSSID(ssid)
        setBSSID(bssid)
        networkID = id
        passwordField.text = ""
        visible.checked = false

        wpaEnable = wpa

        popup.open()
    }
    function setSSID(text){
        ssid = text
    }
    function setBSSID(text){
        bssid = text
    }
}
