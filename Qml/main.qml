import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
    visibility: Window.FullScreen
    width: 480
    height: 320
    title: qsTr("Hello World")
    color: "#EEF5F9"
    screen: Qt.application.screens[1]

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: /*PrintMenu{
            id:printMenu
        }*/
            MainMenu{
            id: mainMenu
        }
    }
    ErrorPopup{
        id: errorPopup
        onBack: {
            stackView.pop(mainMenu,StackView.Immediate)
        }
    }

    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlPrintError :{
            errorPopup.open()
        }
    }
}
