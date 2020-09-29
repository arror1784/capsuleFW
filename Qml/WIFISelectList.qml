import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {
    width: 480
    height: 320

    property string ssidName
    property string currentssidName
    property var networkList

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    ListModel{
        id: wifiModel
    }

    Text {
        id: selectText
        text: qsTr("Select a WIFI ssid")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Rectangle{
        id: wifiSelect
        width: 450
        height: 218

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectText.bottom
        anchors.topMargin: 5

        radius: 8
        color: "#ffffff"
        ListView{
            id: wifiSelectList
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

            model: wifiModel
            delegate: WIFIListDelegate{
                onWifiClicked: {
                    ssidName = name
                    wifiSelectList.currentIndex = index
                    wifiSelectList.update()
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
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.pop(StackView.Immediate)
            }
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
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log(ssidName,currentssidName)
                if(wifiSelectList.currentIndex === -1){
                    return
                }
                for(var i = 0; i < networkList.length; i++){
                    if(networkList[i]){}
                }
                if(ssidName === currentssidName){
                    wifiDisconnectPopup.open(ssidName)
                }else{
                    wifiConnectPopup.open(ssidName)

                }
            }
        }
    }
    WIFIConnectPopup{
        id:wifiConnectPopup
        onConnectButtonClicked: {
            wifi.networkConnect(ssid,pwd)
//            stackView.pop(it,StackView.Immediate)
        }
    }
    WIFIDisconnectPopup{
        id: wifiDisconnectPopup
        onDisconnectButtonClicked: {
            wifi.networkDisconnect()
//            stackView.pop(it,StackView.Immediate)
        }
    }

    Connections{
        id: wifiConnection
        target: wifi
        onNetworkListUpdate:{
            updateWIFIList()
        }
        onCurrentStateChange: {
            var currentSSID = wifi.currentSSID()
            if(currentSSID === ""){
                currentssidName = ""
                for(let i = 0; i < wifiModel.count; i++){
                    wifiModel.setProperty(i,"current",false)
                }
            }else{
                currentssidName = currentSSID
                for(let i = 0; i < wifiModel.count; i++){
                    if(wifiModel.get(i).name === currentSSID){
                        wifiModel.setProperty(i,"current",true)
                        return
                    }else{
                        wifiModel.setProperty(i,"current",false)
                    }
                }
            }
        }
    }
    function updateWIFIList(){
        wifiSelectList.currentIndex = -1
        wifiModel.clear()
        var count = wifi.networkCount()

        console.log(count)

        var currentSSID = wifi.currentSSID()
        currentssidName = currentSSID
        console.log(currentssidName)

        for(var i = 0; i < count; i++){
            var data = wifi.getNetwork(i)
            console.log(data, data.getSaved())
            if(currentSSID === data.getSsid()){
                inserWIFIList(data.getSsid(),true)
            }else{
                inserWIFIList(data.getSsid(),false)
            }
        }
    }
    function inserWIFIList(name,b){
        wifiModel.append({"name":name,"current":b})
    }
    function networkScan(){
        wifi.networkScan()
    }
}
