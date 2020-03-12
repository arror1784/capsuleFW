import QtQuick 2.0

// draws two arcs (portion of a circle)
// fills the circle with a lighter secondary color
// when pressed
Canvas {
    id: canvas
    width: 240
    height: 240
    antialiasing: true

    property color primaryColor: "#DCEAF3"
    property color secondaryColor: "#00C6EA"
    property color textColor: "#474747"

    property real textFontPixelsize: 40

    property real centerWidth: width / 2
    property real centerHeight: height / 2
    property real board: 10
    property real radius: Math.min(canvas.width, canvas.height) / 2 - board

    property real minimumValue: 0
    property real maximumValue: 100

    property real currentValue: 0

    property real angle: (currentValue - minimumValue) / (maximumValue - minimumValue) * 2 * Math.PI

    property real angleOffset: -Math.PI / 2

    property string text: "0%"

    signal clicked()

    onPrimaryColorChanged: requestPaint()
    onSecondaryColorChanged: requestPaint()
    onMinimumValueChanged: requestPaint()
    onMaximumValueChanged: requestPaint()
    onCurrentValueChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d");
        ctx.save();

        ctx.clearRect(0, 0, canvas.width, canvas.height);
/*        if (mouseArea.pressed) {
            ctx.beginPath();
            ctx.lineWidth = 1;
            ctx.fillStyle = Qt.lighter(canvas.secondaryColor, 1.25);
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    canvas.radius,
                    0,
                    2*Math.PI);
            ctx.fill();
        }*/
        ctx.beginPath();
        ctx.lineWidth = board;
        ctx.strokeStyle = primaryColor;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                angleOffset + canvas.angle,
                angleOffset + 2*Math.PI);
        ctx.stroke();

        ctx.beginPath();
        ctx.lineWidth = board;
        ctx.strokeStyle = canvas.secondaryColor;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                canvas.angleOffset,
                canvas.angleOffset + canvas.angle);
        ctx.stroke();

        ctx.restore();
    }

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    Column{
        anchors.centerIn: parent
        Text {
            text: qsTr("Progress")
            color: canvas.textColor
            font.pixelSize: 20
            font.family: openSansRegular.name
        }
        Text {
            text: canvas.text
            color: canvas.textColor
            font.pixelSize: textFontPixelsize
            font.family: openSansSemibold.name
            font.bold: true
            font.letterSpacing: 2
        }
    }
    function setCurrentValue(value){
        currentValue = value
        text = value + "%"
    }
}
