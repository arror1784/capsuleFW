import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    body: Rectangle{
        Pane{
            anchors.fill: parent
            focusPolicy: Qt.ClickFocus
        }
        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -32
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
            visible: wpaEnable
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

        isPopup: true

        text: qsTr("Cancel")

        onBackClicked: {
            popup.close()
        }
    }
    AcceptBTN{
        id: connectButton

        isPopup: true

        text: qsTr("connect")

        onAcceptClicked: {
            if(passwordField.text.length === 0){
                return;
            }
            if(wpaEnable){
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
    function open(ssid,bssid,id,wpa){
        setSSID(ssid)
        setBSSID(bssid)
        networkID = id
        passwordField.text = ""
        visible.checked = false

        wpaEnable = wpa

        popup.popupOpen()
    }
    function setSSID(text){
        ssid = text
    }
    function setBSSID(text){
        bssid = text
    }
}
