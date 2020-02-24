import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1

Item {

    width: 480
    height: 320

    property string currentPath
    property string currentName

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FolderListModel {
        id: folderModel
        showDirs: true
        showDirsFirst: true
        sortReversed: true
//        nameFilters: ["info.json"]
    }
    Text {
        id: selectText
        text: qsTr("Select a file to print")

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
                    if(folderModel.folder.toString() !== "file:///media"){
                        folderModel.folder=folderModel.parentFolder
                        fileSelectList.currentIndex=-1
                        fileSelectList.update()
                        parentDirText.text = folderModel.folder
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
            font.family: openSansSemibold.name
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
                onDirClicked: {
                    changeFolderPath(path)
                    currentName = name
                    currentPath = path
                    fileSelectList.currentIndex=-1
                    fileSelectList.update()
                    parentDirText.text = folderModel.folder
                }
                onFileClicked: {
                    fileSelectList.currentIndex = index
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
    }
    function resetPath(){
        folderModel.folder = "file:///media"
        parentDirText.text = ""
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
    Component.onCompleted: {
        resetPath()
        resetCurrentIndex()
        console.debug(folderModel.status)
    }
}
