import QtQuick 2.9

Rectangle{
    id: fileDelegate

    width: parent.width
    height: fileNameText.height

    color: "#88888888"

    property string filename: ""
    property string parentname: ""
    property string filepath: ""

    signal dirClicked(string path, string name,int index)
    signal fileClicked(string path, string name,int index)
    signal fileDoubleClicked(string path, string name)

    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    SlideText {
        id: fileNameText
        text: fileName
        color: "#474747"
        font.pixelSize: 20
        font.family: openSansRegular.name

        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(fileIsDir === true){
                dirClicked(filePath, fileName,index)
            }else{
                fileClicked(filePath, fileName,index)
            }
        }
        onDoubleClicked: {
            if(fileIsDir === true){
                dirClicked(filePath, fileName,index)
            }else{
                fileDoubleClicked(filePath, fileName)
            }
        }
    }
}
