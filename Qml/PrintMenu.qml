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

    property int totaltime: 0
    property bool timerRunning: false

    property double startTime: 0
    property int ct: 0
    property bool waitPopupOpened: false


    property bool isPrinMenu: true

    property string printName
    property string materialName

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

//                anchors.top: fileName.bottom
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
                text: qsTr("Remaing Time")
                font.family: openSansRegular.name
                font.pixelSize: 15
            }
            Text {
                id: timeText
                text: ""
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
    BackBTN{
        id: printInfoButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        text: qsTr("Print info")

        onClicked: {
            fileInfoPopup.open()
        }
    }
    AcceptBTN{
        id: quitButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        text: qsTr("Quit")

        onClicked: {
                connection.receiveFromQmlPrintStateChange("pause")
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
            connection.receiveFromQmlPrintStateChange("resume")
        }
        onPrintStop: {
            connection.receiveFromQmlPrintStateChange("finish")
        }
    }

    Timer{
        id: timeTimer
        interval: 50; running: timerRunning; repeat: true
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
            time = currentDuration
            var diffDuration = totaltime - currentDuration
            var currentDate
            if(totaltime === 0){
                timeText.text = "Calculating"
                return
            }

            if(diffDuration < 0){
                currentDate = new Date(-diffDuration)

                timesec = currentDate.getSeconds()
                timemin = currentDate.getMinutes()
                timeText.text = -timemin + "min " + -timesec + "sec"

            }else{
                currentDate = new Date(diffDuration)

                timesec = currentDate.getSeconds()
                timemin = currentDate.getMinutes()
                timeText.text = timemin + "min " + timesec + "sec"
            }
        }
    }
    Connections{
        target: connection
        onSendToQmlUpdateProgress: {
            setProgressValue(progress)
        }
        onSendToQmlEnableTimer:{
            if(enable){
                timeTimer.start()
            }else{
                timeTimer.stop()
                connection.receiveFromQmlSetPrintTime(time)
            }
        }
        onSendToQmlChangeState:{
            if(state == "pauseStart"){
                quitPopup.open()
                quitPopup.setButtonEnabled(false)
            }else if(state === "pauseFinish"){
                quitPopup.setButtonEnabled(true)

            }else if(state === "resume"){
                quitPopup.close()
            }else if(state == "quit"){
                quitPopup.close()
                waitPopup.open()
                waitPopupOpened = true
            }else if(state === "printFinish"){
                if(waitPopupOpened === true){
                    waitPopupOpened = false
                    waitPopup.close()
                }
                quitPopup.close()
                stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingCompleted.qml"),StackView.Immediate)
            }else if(state === "printError"){
                waitPopup.open()
                waitPopupOpened = true
            }else if(state === "printErrorFinish"){
                if(waitPopupOpened === true){
                    waitPopupOpened = false
                    waitPopup.close()
                }
        //            quitPopup.close()
                stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintingError.qml"),StackView.Immediate)
            }
        }
        onSendToQmlPrintInfo:{
            progressBar.setCurrentValue(progress)

            printName = fileName
            fileNameText.text = fileName
            fileInfoPopup.setFilename(fileName)

            materialName = material
            fileInfoPopup.setMaterial(material)

            fileInfoPopup.setLayerHeight(layerHeight)

            eltime = elapsedTime;
            startTime = new Date().getTime()
        }
        onSendToQmlChangeToPrint:{
            clear()
        }
        onSendToQmlSetTotalTime:{
            totaltime = time
            var currentDate = new Date(time)
            var sec = currentDate.getSeconds()
            var min = currentDate.getMinutes()

            fileInfoPopup.setPrintingTime(min + "min " + sec + "sec")
//            timeText.text = timemin + "min " + timesec + "sec"

            timerRunning = true
        }

    }
    function clear(){
        progressBar.setCurrentValue(0)
        timesec = 0
        timemin = 0

        time = 0

        startTime = 0
        totaltime = 0

        ct = 0
        waitPopupOpened = false

        timerRunning = false
        timeText.text = "Calculating"
        fileInfoPopup.setPrintingTime("Calculating")
        //Todo To do
    }
    function setProgressValue(value){
        progressBar.setCurrentValue(value)
    }
    Component.onCompleted: {
        connection.receiveFromQmlGetPrintInfoToWeb();
        clear()
    }
}
