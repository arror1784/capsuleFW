import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1
import QtQuick.Controls 2.5
import App 1.0

DefaultListView{
    id: fileSelectList

    property string selectedFileName : ""
    property string selectedFilePath : ""
    property string mediaURL: ""

    property bool fileSearch: false
    property bool fileCheckDisconnected: false

    property bool isFileSelectList: true

    HixFilesystemModel {
        id: folderModel
        showDirs: true
        showDirsFirst: true
        sortReversed: true
        nameFilters: [".zip"]
    }

    title: qsTr("Select a file to print (*.zip)")

    extraBoard: Rectangle{
        id: parentDir

        width: 450
        height: 40

        radius: 8
        color: "#ffffff"

        Rectangle{
            id: parentDirButton

            width: 38
            height: 34

            anchors.verticalCenter: parentDir.verticalCenter
            anchors.left: parentDir.left
            anchors.leftMargin: 4

            radius: 4
            color: "#B6CDDC"
            Image {
                id: parentDirButtonImage

                anchors.centerIn: parentDirButton

                source: "qrc:/image/arrow-dir.png"
                scale: 0.6
            }
            MouseArea{
                anchors.fill: parentDirButton
                onClicked: {
                    if(folderModel.folder.toString() !== mediaURL){
//                        selectedFileName = ""
                        folderModel.folder=folderModel.parentFolder
                        fileSelectList.selectList.currentIndex=-1
//                        fileSelectList.selectList.update()
                        if(folderModel.folder.toString() === mediaURL){
                            parentDirText.text = ""
                        }else{
                            parentDirText.text = basename(folderModel.folder.toString())
                        }
                    }
                }
            }
        }
        Text {
            id: parentDirText
            width: 396
            height: 23

            anchors.left: parentDirButton.right
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter

            elide: Text.ElideLeft

            color: "#474747"

            font.pixelSize: 22
            font.family: openSansRegular.name
        }
    }
    model: folderModel
    delegate: FileListDelegate{
        property var dirText: parentDirText
        property var selectList: fileSelectList.selectList
        onDirClicked: {
            if(!folderModel.fileExists(path))
            {
                stackView.pop(StackView.Immediate)
                return
            }
            folderModel.folder = path
//                    selectedFileName = ""
            dirText.text = name
            fileSelectList.selectList.currentIndex=-1
            fileSelectList.selectList.update()

        }
        onFileClicked: {
            if(!folderModel.fileExists(path))
            {
                stackView.pop(StackView.Immediate)
                return
            }
            fileSelectList.selectList.currentIndex = index
            selectedFileName = name
            selectedFilePath = path
            fileSelectList.selectList.update()
        }
    }
    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    AcceptBTN{
        id: selectButton

        text: qsTr("Select")

        onAcceptClicked: {
//              if(selectedFileName === "info.json"){
            if(fileSelectList.selectList.currentIndex !== -1){
//                  fileCheckDisconnected = false
                stackView.push(Qt.resolvedUrl("qrc:/Qml/MaterialSelectList.qml"),StackView.Immediate)
            }
        }
    }
    USBStorgeDisConnectedPopup{
        id: usbStrogeDisConnectedPopup
        onBack: {
            stackView.pop(mainMenu,StackView.Immediate)
        }
    }

    Timer{
        id: timer
        interval: 250
        running: fileSearch
        repeat: true
        onTriggered: {
            var path = folderModel.getUSB()
            if(path !== ""){
                fileSearch = false
                fileCheckDisconnected = true
                mediaURL = path
                setPath(path)
            }
        }
    }
    Timer{
        id: chekcTimer
        interval: 250
        running: fileCheckDisconnected
        repeat: true
        onTriggered: {
            if(!folderModel.fileExists(mediaURL)){
                fileCheckDisconnected = false
                usbStrogeDisConnectedPopup.open()
            }
        }
    }
    function setPath(path){
        folderModel.folder = path
        parentDirText.text = ""
        fileSelectList.selectList.update()
    }

    function resetPath(){
        folderModel.folder = mediaURL
        parentDirText.text = ""
        fileSelectList.selectList.update()
    }
    function resetCurrentIndex(){
        fileSelectList.selectList.currentIndex = -1
    }
    function changeFolderPath(path){
        // folderModel.folder = "file://" + path
        folderModel.folder = path

    }
    function basename(str)
    {
        return (str.slice(str.lastIndexOf("/")+1))
    }
    function reset(){
        if(folderModel.fileExists(mediaURL)){
            fileSearch = false
            fileCheckDisconnected = true
        }else{
            fileSearch = true
            fileCheckDisconnected = false
            resetCurrentIndex()
            resetPath()
        }
    }

    Component.onCompleted: {
//        resetPath()
        reset()
        usbStrogeDisConnectedPopup.close()
        resetCurrentIndex()
    }
}
