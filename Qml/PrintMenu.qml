import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: printMenu
    width: 480
    height: 320

    property int timesec: 0
    property int timemin: 0
    property double time: 0
    property double eltime: 0

    property double firstLayerTimeStart: 0

    property double startTime: 0
    property int ct: 0
    property bool waitPopupOpened: false

    property bool isPrinMenu: true

    signal sendToPrintPause()
    signal sendToPrintResume()
    signal sendToPrintFinish()
    signal sendToSetPrintTime(int time)
    signal sendToSetTotalPrintTime(int time)
    signal sendToGetPrintInfoToWeb()

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }
    Rectangle{

        width: fileName.width > remainingTime.width ? fileName.width : remainingTime.width
        height: fileName.height + remainingTime.height + 20
        anchors.left: parent.left
        anchors.leftMargin: 30 + 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -22

        color: "transparent"
        Column{
            id: fileName
            Text {
                text: qsTr("File name")
                font.family: openSansRegular.name
                font.pixelSize: 15
            }

            SlideText{
                id: fileNameText
                width: 200

                anchors.top: filename.bottom
                text: ""

                font.family: openSansSemibold.name
                font.pixelSize: 27
                font.bold: true
            }

        }
        Column{
            id: remainingTime
            anchors.top: fileName.bottom
            anchors.topMargin: 20
            Text {
                text: qsTr("time")
                font.family: openSansRegular.name
                font.pixelSize: 15
            }
            Text {
                id: timeText
                text: timemin + "min " + timesec + "sec"
                font.family: openSansSemibold.name
                font.pixelSize: 27
                font.bold: true
            }
        }
    }

    CircularProgressBar{
        id: progressBar

        width: 200
        height: 200

        anchors.top: parent.top
        anchors.topMargin: 35
        anchors.right: parent.right
        anchors.rightMargin: 25
    }
    Rectangle{
        id: printInfoButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Print info")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                fileInfoPopup.open()
            }
        }
    }
    Rectangle{
        id: quitButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Quit")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                sendToPrintPause()
            }
        }
    }
    FileInfoPopup{
        id: fileInfoPopup
    }
    WaitPopup{
        id: waitPopup
    }
    QuitPopup{
        id: quitPopup
        onPrintResume: {
            sendToPrintResume()
        }
        onPrintStop: {
            sendToPrintFinish()
        }
    }

    Timer{
        id: timeTimer
        interval: 50; running: false; repeat: true
        onRunningChanged: {
           if(running){
               var date = new Date()
               startTime = date.getTime()
           }else{
               eltime = time
           }
        }
        onTriggered: {
            var date = new Date();
            var currentDuration = date.getTime() - startTime + eltime
            var currentDate = new Date(currentDuration)

            time = currentDuration
            timesec = currentDate.getSeconds()
            timemin = currentDate.getMinutes()
        }
    }
    function receiveUpdateProgress(progress) {
        setProgressValue(progress)
    }
    function receiveEnableTimer(enable){
        if(enable){
            timeTimer.start()
        }else{
            timeTimer.stop()
            sendToSetPrintTime(time)
        }
    }
    function receiveChangeToPauseStart(){
        quitPopup.open()
        quitPopup.setButtonEnabled(false)
    }
    function receiveChangeToPauseFinish(){

        quitPopup.setButtonEnabled(true)
    }
    function receiveChangeToResume(){
        quitPopup.close()

    }
    function receiveChangeToQuit(){
        quitPopup.close()
        waitPopup.open()
        waitPopupOpened = true
    }
    function receiveChangeToPrintFinish(){
        if(waitPopupOpened === true){
            waitPopupOpened = false
            waitPopup.close()
        }
        quitPopup.close()
        stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingCompleted.qml"),StackView.Immediate)
    }
    function receiveChangeToPrintWorkErrorFinish(){
        if(waitPopupOpened === true){
            waitPopupOpened = false
            waitPopup.close()
        }
//            quitPopup.close()
        stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingError.qml"),StackView.Immediate)
    }
    function receiveChangeToPrintWorkError(){
        waitPopup.open()
        waitPopupOpened = true
    }
    function receivePrintInfo(){
        eltime = elapsedTime;
        startTime = new Date().getTime()
    }

    function receivePrintInfo(printerState,material, fileName, layerHeight, elapsedTime, totalTime, progress){

    }

    function receiveFirstlayerStart(){
        var currentDate = new Date()
        firstLayerTimeStart = currentDate.getTime()
    }
    function receiveFirstlayerFinish(){
        //To do Todo

//            var JsonStringPrint = scheduler.receiveFromUIGetInfoSetting(stackView.get(1).selectedFilePath);
//            var JsonObjectPrint = JSON.parse(JsonString);

//            var JsonStringPrint = scheduler.receiveFromUIGetMaterialOption(scheduler.receiveFromUIGetMaterialName())
//            var JsonObjectPrint = JSON.parse(JsonString);

//            var total_layer = JsonObjectPrint.total_layer
//            var bed_curting_layer = scheduler.receiveFromUIGetMaterialOption(scheduler.receiveFromUIGetMaterialName(),"bed_curing_layer")

        var T = new Date()
        var Tduration = T.getTime() - firstLayerTimeStart
        var Tdate = new Date(Tduration)
        var firstLayerTime = Tdate.getTime()


        var currentDate = new Date(time + (firstLayerTime * ((total_layer - bed_curting_layer) - 1)))
        var sec = currentDate.getSeconds()
        var min = currentDate.getMinutes()

        sendToSetTotalPrintTime(currentDate)
        fileInfoPopup.setPrintingTime(min + "min " + sec + "sec")
    }
    Component.onCompleted: {
        scheduler.sendToUIUpdateProgress.connect(receiveUpdateProgress)
        scheduler.sendToUIEnableTimer.connect(receiveEnableTimer)
        scheduler.sendToUIChangeToPauseStart(receiveChangeToPauseStart)
        scheduler.sendToUIChangeToPauseFinish.connect(receiveChangeToPauseFinish)
        scheduler.sendToUIChangeToResume.connect(receiveChangeToResume)
        scheduler.sendToUIChangeToQuit.connect(receiveChangeToQuit)
        scheduler.sendToUIChangeToPrintFinish.connect(eceiveChangeToPrintFinish)
        scheduler.sendToUIChangeToPrintWorkErrorFinish.connect(receiveChangeToPrintWorkErrorFinish)
        scheduler.sendToUIChangeToPrintWorkError.connect(receiveChangeToPrintWorkError)
        scheduler.sendToUIPrintInfo.connect(receivePrintInfo)
        scheduler.sendToUIFirstlayerStart.connect(receiveFirstlayerStart)
        scheduler.sendToUIFirstlayerFinish.connect(receiveFirstlayerFinish)


        sendToPrintPause.connect(scheduler.receiveFromUIPrintPause)
        sendToPrintResume.connect(scheduler.receiveFromUIPrintResume)
        sendToPrintFinish.connect(scheduler.receiveFromUIPrintFinish)
        sendToSetPrintTime.connect(scheduler.receiveFromUISetPrintTime)
        sendToSetTotalPrintTime.connect(scheduler.receiveFromUISetTotalPrintTime)
        sendToGetPrintInfoToWeb.connect(scheduler.receiveFromUISetTotalPrintTime)

        sendToGetPrintInfoToWeb();
        clear()
    }
    function setProgressValue(value){
        progressBar.setCurrentValue(value)
    }
    function clear(){
        progressBar.setCurrentValue(0)
        timesec = 0
        timemin = 0

        time = 0

        firstLayerTimeStart = 0

        startTime = 0

        ct = 0
        waitPopupOpened = false

//        fileNameText.text = scheduler.receiveFromUIGetPrintName()
//        fileInfoPopup.setText(scheduler.receiveFromUIGetPrintName(),
//                              "Calculating",
//                              scheduler.receiveFromUIGetMaterialName(),
//                              scheduler.receiveFromUIGetPrintOption("layer_height"))
        //Todo To do
    }

}
