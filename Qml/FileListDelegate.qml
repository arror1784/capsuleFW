import QtQuick 2.9

Rectangle{
    id: fileDelegate

    width: parent.width
    height: fileNameText.height

    color: "#00000000"

    signal dirClicked(string path, string name,int index)
    signal fileClicked(string path, string name,int index)

    Text {
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
                // console.log("fileURL ", fileURL);
                dirClicked(filePath , fileName,index)
            }else{
                fileClicked(filePath , fileName,index)
            }
        }
    }
}
