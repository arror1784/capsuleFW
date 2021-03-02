import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1
import QtQuick.Controls 2.5
import App 1.0


DefaultListView{
    id: resinUpdateSelectList

    // property url currentPath
    property string selectedFileName : ""
    property string selectedFilePath : ""
    property string mediaURL: ""

    property bool fileSearch: false
    property bool fileCheckDisconnected: false

    property bool isResinUpdateSelectFile: true

    HixFilesystemModel {
        id: folderModel
        showDirs: true
        showDirsFirst: true
        sortReversed: true
        nameFilters: [".updateFile"]
    }
    title: qsTr("Select a file (*.updateFile)")
    model: folderModel
    delegate: FileListDelegate{
        property var dirText: parentDir
        property var selectList: resinUpdateSelectList.selectList
        onDirClicked: {
            if(!folderModel.fileExists(path))
            {
                stackView.pop(StackView.Immediate)
                return
            }
            folderModel.folder = path
//                    selectedFileName = ""
            dirText.text = name
            selectList.currentIndex=-1
            selectList.update()

        }
        onFileClicked: {
            if(!folderModel.fileExists(path))
            {
                stackView.pop(StackView.Immediate)
                return
            }
            selectList.currentIndex = index
            selectedFileName = name
            selectedFilePath = path
            selectList.update()
        }
    }
    extraBoard: ParentDir{
        id: parentDir
        onClicked: {
            if(folderModel.folder.toString() !== mediaURL){
//                        selectedFileName = ""
                folderModel.folder=folderModel.parentFolder
                resinUpdateSelectList.selectList.currentIndex=-1
//                        resinUpdateSelectList.selectList.update()
                if(folderModel.folder.toString() === mediaURL){
                    text = ""
                }else{
                    text = basename(folderModel.folder.toString())
                }
            }
        }
    }
    BackBTN{
        id: backButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        onClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    AcceptBTN{
        id: selectButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        text: qsTr("Select")

        onClicked: {
            if(resinUpdateSelectList.selectList.currentIndex !== -1){
                stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
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
        parentDir.text = ""
        resinUpdateSelectList.selectList.update()
    }
    function resetPath(){
        folderModel.folder = mediaURL
        parentDir.text = ""
        resinUpdateSelectList.selectList.update()
    }
    function resetCurrentIndex(){
        resinUpdateSelectList.selectList.currentIndex = -1
    }
    function changeFolderPath(path){
        // folderModel.folder = "file://" + path
        folderModel.folder = path

    }
    function basename(str){
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
