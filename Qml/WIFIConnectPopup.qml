import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    signal connectButtonClicked(string ssid,string bssid,string pwd,int id)
    signal connectButtonClickedWithoutPSWD(string ssid,string bssid,int id)
    signal connectButtonClickedWithID(int id)

    property int networkID: -1
    property bool wpaEnable: false
    property bool saved: false
    property bool passwdEnable: false
    property string ssid: ""
    property string bssid: ""

    body: Rectangle{
        width: popup.bodyWidth
        height: popup.bodyHeight
        Pane{
            anchors.fill: parent
            focusPolicy: Qt.ClickFocus
        }
        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
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
                    visible: passwdEnable
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
                    visible: passwdEnable
                    onFocusChanged: {
                        if(!focus){
                            passwordField.activeFocusOnPress = true
                            keyboardWidget.closeKeyboard()
                        }
                    }
                    onPressed: {
                        keyboardWidget.showKeyboard(passwordField)
                    }
                }
            }
        }
        Switch{
            id: visible
//            anchors.left: passwordField.right
            text: qsTr("passwd visible")
            visible: passwdEnable
            onCheckedChanged: {
                if(checked){
                    passwordField.echoMode = TextInput.Normal
                }else{
                    passwordField.echoMode = TextInput.Password
                }
            }
        }
    }
    BackBTN{
        id: cancleButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5

        text: qsTr("Cancel")

        onClicked: {
            popup.close()
        }
    }
    AcceptBTN{
        id: connectButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        text: qsTr("connect")

        onClicked: {

            if(saved){
                connectButtonClickedWithID(networkID)
            }else if(wpaEnable){
                if(passwordField.text.length === 0){
                    return;
                }
                connectButtonClicked(ssid,bssid,passwordField.text,networkID)
            }else{
                connectButtonClickedWithoutPSWD(ssid,bssid,networkID)
            }

            popup.close()
        }
    }
    Connections{
        id:kWidgetConntion
        target: keyboardWidget
    }
    function openPopup(ssid,bssid,id,wpa,svd){
        setSSID(ssid)
        setBSSID(bssid)
        networkID = id
        passwordField.text = ""
        visible.checked = false
        saved = svd
        wpaEnable = wpa
        if(!saved && wpa){
            passwdEnable = true
        }else{
            passwdEnable = false
        }

        popup.open()
    }
    function setSSID(text){
        ssid = text
    }
    function setBSSID(text){
        bssid = text
    }
}
