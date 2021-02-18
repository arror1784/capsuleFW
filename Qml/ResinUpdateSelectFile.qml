import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1
import QtQuick.Controls 2.5
import App 1.0

Item {
   width: 480
   height: 320

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
   Text {
       id: selectText
       text: qsTr("Select a file (*.updateFile)")

       font.pixelSize: 23
       font.family: openSansSemibold.name
       font.bold: true
       font.letterSpacing: 2

       anchors.top: parent.top
       anchors.topMargin: 10
       anchors.horizontalCenter: parent.horizontalCenter
   }

   Rectangle{
       id: parentDir

       width: 450
       height: 40

       anchors.horizontalCenter: parent.horizontalCenter
       anchors.top: selectText.bottom
       anchors.topMargin: 5

       radius: 8
       color: "#ffffff"

       Rectangle{
           id: parentDirButton

           width: 38
           height: 34

           anchors.verticalCenter: parent.verticalCenter
           anchors.left: parent.left
           anchors.leftMargin: 4

           radius: 4
           color: "#B6CDDC"
           Image {
               id: parentDirButtonImage

               anchors.centerIn: parent

               source: "qrc:/image/arrow-dir.png"
               scale: 0.6
           }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   if(folderModel.folder.toString() !== mediaURL){
//                        selectedFileName = ""
                       folderModel.folder=folderModel.parentFolder
                       fileSelectList.currentIndex=-1
//                        fileSelectList.update()
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
   Rectangle{
       id: fileList

       anchors.top: parentDir.bottom
       anchors.topMargin: 5
       anchors.left: parent.left
       anchors.leftMargin: 15

       width: 450
       height: 173

       radius: 8
       color: "#ffffff"

       ListView{
           id: fileSelectList
           width: 375
           height: 153
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

           model: folderModel

           delegate: FileListDelegate{
               property var dirText: parentDirText
               property var selectList: fileSelectList
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
                   fileSelectList.currentIndex = index
                   selectedFileName = name
                   selectedFilePath = path
                   fileSelectList.update()
               }
           }
       }
       Rectangle{
           id: up

           width: 50
           height: 70

           anchors.top: parent.top
           anchors.topMargin: 10
           anchors.right: parent.right
           anchors.rightMargin: 10

           color: "#B6CDDC"

           radius: 8

           Image {
               id: upImage
               anchors.centerIn: parent

               scale: 0.7
               source: "qrc:/image/arrow-up.png"
           }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   fileSelectList.flick(0,500)
               }
           }
       }
       Rectangle{
           id: down

           width: 50
           height: 70

           anchors.bottom: parent.bottom
           anchors.bottomMargin: 10
           anchors.right: parent.right
           anchors.rightMargin: 10

           color: "#B6CDDC"

           radius: 8
           Image {
               id: downImage

               scale: 0.7
               anchors.centerIn: parent
               source: "qrc:/image/arrow-down.png"
           }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   fileSelectList.flick(0,-500)
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
               if(fileSelectList.currentIndex !== -1){
                   stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
               }
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
       fileSelectList.update()
   }
   function resetPath(){
       folderModel.folder = mediaURL
       parentDirText.text = ""
       fileSelectList.update()
   }
   function resetCurrentIndex(){
       fileSelectList.currentIndex = -1
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
