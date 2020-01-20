import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.folderlistmodel 2.1
//import QtLocation 5.11

Item {
    id: fileSelectPopup
    signal chooseFile(string filePath,string fileName)
    signal cancleChoose()

    anchors.fill: parent

    property string currentPath
    property string currentName
    property string currentBedId
    property alias usbNotRecognizedText: usbNotRecognizedText

    FolderListModel {
        id: folderModel
        showDirs: true
        showDirsFirst: true
        sortReversed: true
        nameFilters: ["info.json"]
    }
    Popup {
        id: popup
        width: 700
        height: 400
        anchors.centerIn: Overlay.overlay

        background: Rectangle{
            id: backgroundPopUp
            anchors.fill: parent
            color: "#404040"
        }
        modal: true
        focus: true
        Overlay.modal: Rectangle {
            color: "#c4000000"
        }
        //closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        Rectangle{
            id: popupRectangle

            width: parent.width
            height: parent.height
            color: "#00000000"
            Text {
                id: titleText

                text: qsTr("Select File")
                color: "#ffffff"
                font.bold: true
                font.pixelSize: 36
                anchors.left: popupRectangle.left
                anchors.top: popupRectangle.top
                anchors.topMargin: 10
                anchors.leftMargin: 20
            }
            Rectangle{
                id: xButton
                width: xIcon.width
                height: xIcon.height

                anchors.right: popupRectangle.right
                //anchors.rightMargin: 10
                anchors.top: popupRectangle.top
                //anchors.topMargin: 10

                color: "#00000000"

                Text {
                    id: xIcon
                    text: "x"
                    font.pixelSize: 50
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        cancleChoose()
                        popup.close()
                    }
                }
            }
            Rectangle{
                id: fileSelectWindow

                width: parent.width - x
                height: parent.height - y
                anchors.left: parent.left
                anchors.top: titleText.bottom
                color: "#00000000"

                Rectangle{
                    id: listViewBackground
                    width: parent.width
                    height: parent.height
                    color: "#777777"

                    ListView{
                        id: fileSelectList
                        width: parent.width - 20
                        height: parent.height - 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        z: 0
                        spacing: 2
                        focus: true
                        clip: true

                        highlightFollowsCurrentItem: true
                        highlightMoveDuration: 0

                        highlight: Rectangle { color: "#DE7317"; height: 44;}

                        model: folderModel
                        delegate: FileListDelegate{
                            onDirClicked: {
                                changeFolderPath(path)
                                currentName = name
                                currentPath = path
                                fileSelectList.currentIndex=-1
                                fileSelectList.update()
                            }
                            onFileClicked: {
//                                currentPath = path
//                                currentName = name
                                fileSelectList.currentIndex = index
                                fileSelectList.update()
                            }
//                            onFileDoubleClicked: {
//                                fileSelectList.currentIndex = index
//                                informationText.text = currentName
//                                fileSelectPopup.state = "information"
//                            }
                        }
                    }
                }
                Rectangle{
                    id: chooseFileButton
                    width: 200
                    height: 64
                    radius: 32
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.bottomMargin: 10
                    clip: false


                    gradient: Gradient{
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#E05E1B" }
                        GradientStop { position: 1.0; color: "#FF821B" }
                    }
                    Text {
                        text: "Choose File"
                        color: "white"
                        font.pixelSize: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(fileSelectList.currentIndex !== -1){
                                informationText.text = currentName
                                fileSelectPopup.state = "information"
                            }
                        }
                    }
                }
                Rectangle{
                    id: previousButton
                    width: 200
                    height: 64
                    radius: 32

                    anchors.right: chooseFileButton.left
                    anchors.rightMargin: 20
                    anchors.bottom: chooseFileButton.bottom
                    gradient: Gradient{
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#777777" }
                        GradientStop { position: 1.0; color: "#909090" }
                    }

                    property variant stringList

                    Text {
                        text: "previous"
                        color: "white"
                        font.pixelSize: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(folderModel.folder.toString() !== "file:///media"){
                                folderModel.folder=folderModel.parentFolder
                                fileSelectList.currentIndex=-1
                                fileSelectList.update()
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: fileInformationWindow

                width: parent.width - x
                height: parent.height - y

                anchors.left: parent.left
                anchors.top: titleText.bottom
                visible: false

                color: "#00000000"
                Text {
                    id: informationText
                    text: "information text"
                    font.pixelSize: 20
                    color: "white"
                }
                Rectangle{
                    id: startButton
                    width: 200
                    height: 64
                    radius: 32

                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10

                    gradient: Gradient{
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#E05E1B" }
                        GradientStop { position: 1.0; color: "#FF821B" }
                    }
                    Text {
                        text: "Start Printing"
                        color: "white"
                        font.pixelSize: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            chooseFile(currentPath,currentName)
                            popup.close()
                        }
                    }
                }
                Rectangle{
                    id: cancleButton
                    width: 200
                    height: 64
                    radius: 32

                    anchors.right: startButton.left
                    anchors.rightMargin: 20
                    anchors.bottom: startButton.bottom
                    gradient: Gradient{
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#777777" }
                        GradientStop { position: 1.0; color: "#909090" }
                    }
                    Text {
                        text: "Cancle"
                        color: "white"
                        font.pixelSize: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            fileSelectPopup.state = "select"
                        }
                    }
                }
            }
            Rectangle{
                id: usbNotRecognized

                width: parent.width - x
                height: parent.height - y
                anchors.left: parent.left
                anchors.top: titleText.bottom

                color: "#00000000"

                Rectangle{
                    id: usbNotRecognizedText

                    width: text_makeSureDeviceConnected.width
                    height: text_usbNotRecognized.height + text_makeSureDeviceConnected.height

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#00000000"

                    gradient: Gradient{
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#E05E1B" }
                        GradientStop { position: 1.0; color: "#FF821B" }
                    }
                    Text {
                        id: text_usbNotRecognized
                        text: "USB device not recognized"
                        color: "white"
                        font.pixelSize: 36
                        font.bold: true
                    }

                    Text{
                        id: text_makeSureDeviceConnected
                        text: "Please make sure that the device is connected."
                        font.pixelSize: 24
                        color: "white"

                        anchors.top: text_usbNotRecognized.bottom
                        anchors.verticalCenter: text_usbNotRecognized.verticalCenter
                    }
                }
            }
        }
        onOpened: {
            resetPath()
            resetCurrentIndex()
            console.debug(folderModel.status)
            if(folderModel.status === FolderListModel.Null){
                fileSelectPopup.state = "usbNot"
            }else{
                fileSelectPopup.state = "select"
            }
        }
        onClosed: {
        }
    }
    states: [
        State {
            name: "select"
            PropertyChanges { target: fileSelectWindow; visible: true }
            PropertyChanges { target: fileInformationWindow; visible: false }
            PropertyChanges { target: usbNotRecognized; visible: false }
        },
        State {
            name: "information"
            PropertyChanges { target: fileSelectWindow; visible: false }
            PropertyChanges { target: fileInformationWindow; visible: true }
            PropertyChanges { target: usbNotRecognized; visible: false }
        },
        State {
            name: "usbNot"
            PropertyChanges { target: fileSelectWindow; visible: false }
            PropertyChanges { target: fileInformationWindow; visible: false }
            PropertyChanges { target: usbNotRecognized; visible: true }
        }
    ]
    function openPopUp(){
        popup.open()
    }
    function resetPath(){
        folderModel.folder = "file:///media"
        fileSelectList.update()
        console.debug(folderModel.folder)
    }
    function resetCurrentIndex(){
        fileSelectList.currentIndex = -1
    }
    function changeFolderPath(path){
        folderModel.folder = "file://" + path
        console.debug("folderChange")
    }
}

