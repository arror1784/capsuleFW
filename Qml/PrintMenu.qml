import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: printMenu
    width: 480
    height: 320

    property int timesec: 0
    property int timemin: 0
    property double time: 0

    property double firstLayerTimeStart: 0

    property double startTime: 0
    property double pauseStartTime: 0
    property double pauseDuration: 0

    property int ct: 0
    property bool waitPopupOpened: false

    signal printStart()

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
            Text {
                id: fileNameText
                width: 200
//                text: stackView.get(1).currentParentName
                text: ""
                font.family: openSansSemibold.name
                font.pixelSize: 27
                font.bold: true

                elide: Text.ElideRight
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
                scheduler.receiveFromQmlBedPrintPause()

                quitPopup.open()
                quitPopup.setButtonEnabled(false)
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
            quitPopup.close()
            scheduler.receiveFromQmlBedPrintStart()
            var date = new Date();
            pauseDuration = (date.getTime() - pauseStartTime) + pauseDuration
//            printMenu.printStart()
        }
        onPrintStop: {
            quitPopup.close()
            scheduler.receiveFromQmlBedPrintFinish()
            waitPopup.open()
            waitPopupOpened = true
        }
    }

    Timer{
        id: timeTimer
        interval: 50; running: false; repeat: true
        onRunningChanged: {
           if(running){
               var date = new Date;
               startTime = date.getTime()
           }
        }
        onTriggered: {
            var date = new Date();
            var currentDuration = date.getTime() - startTime - pauseDuration
            var currentDate = new Date(currentDuration)
            time = currentDuration
            timesec = currentDate.getSeconds()
            timemin = currentDate.getMinutes()
        }
    }
    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlUpdateProgress : function onSendToQmlUpdateProgress(currentIndex,maxIndex){
            setProgressValue(Math.round( (currentIndex ) / maxIndex * 100))
        }
        onSendToQmlInit :{
            timeTimer.start()
        }
        onSendToQmlFinish :{
            timeTimer.stop()
            scheduler.receiveFromQmlSetPrintTime(time)
        }
        onSendToQmlPauseFinish :{
            var date = new Date();
            pauseStartTime = date.getTime()
            quitPopup.setButtonEnabled(true)
        }
        onSendToQmlPrintFinish :{
            if(waitPopupOpened === true){
                waitPopupOpened = false
                waitPopup.close()
            }
            quitPopup.close()
            stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingCompleted.qml"),StackView.Immediate)
        }
        onSendToQmlPrintWorkError:{

        }
        onSendToQmlWaitForMovement:{
            waitPopup.open();
            waitPopupOpened = true
        }
        onSendToqmlPrintWorkErrorFinish:{
            if(waitPopupOpened === true){
                waitPopupOpened = false
                waitPopup.close()
            }
//            quitPopup.close()
            stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingError.qml"),StackView.Immediate)
        }
        onSendToQmlFirstlayerStart:{
            var currentDate = new Date()
            firstLayerTimeStart = currentDate.getTime()
        }
        onSendToQmlFirstlayerFinish:{
            var total_layer = scheduler.receiveFromQmlGetPrintOption("total_layer")
//            var bed_curting_layer = scheduler.receiveFromQmlGetMaterialOption(stackView.get(2).materialName,"bed_curing_layer")
            var bed_curting_layer = scheduler.receiveFromQmlGetMaterialOption(scheduler.receiveFromQmlGetMaterialName(),"bed_curing_layer")

            var T = new Date()
            var Tduration = T.getTime() - firstLayerTimeStart
            var Tdate = new Date(Tduration)
            var firstLayerTime = Tdate.getTime()


            var currentDate = new Date(time + (firstLayerTime * ((total_layer - bed_curting_layer) - 1)))
            var sec = currentDate.getSeconds()
            var min = currentDate.getMinutes()
            console.debug("time : "+ time + " firstLayerTime : " + firstLayerTime)
            fileInfoPopup.setPrintingTime(min + "min " + sec + "sec")
        }
    }
    Component.onCompleted: {
        fileNameText.text = scheduler.receiveFromQmlGetPrintName()
        fileInfoPopup.setText(scheduler.receiveFromQmlGetPrintName(),
//        fileInfoPopup.setText(stackView.get(1).currentParentName,
                              "***min",
//                              stackView.get(2).materialName,
                              scheduler.receiveFromQmlGetMaterialName(),
                              scheduler.receiveFromQmlGetPrintOption("layer_height"))
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
        pauseStartTime = 0
        pauseDuration = 0

        ct = 0
        waitPopupOpened = false
    }
}
