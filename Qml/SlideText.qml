import QtQuick 2.0

Item{
    id: root

//    width: movingText.width
    height: movingText.paintedHeight

    property alias text: movingText.text
    property alias color: movingText.color
    property alias font: movingText.font

    property var animateEnable: false

    clip: true

    Text{
        id:movingText

        x:0

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
