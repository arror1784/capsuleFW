import QtQuick 2.0

Item{
    id: root

    property var animateEnable: false
    property var text
    property var color
    property Font font

    Text{
        id:movingText

        x:0

        text: parent.text
        color: parent.color
        font: parent.font

        NumberAnimation on x{
            from: root.width
            to: -1*movingText.width
            loops: Animation.Infinite
            duration: 10000
            running: animateEnable
        }
    }
    Component.onCompleted: {
        console.log(movingText.width,root.width)
        if(movingText.width > root.width){
            animateEnable = true
        }else{
            animateEnable = false
        }
    }
}
