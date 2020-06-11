import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
//    visibility: Window.FullScreen
    width: 480
    height: 320
    title: qsTr("Hello World")
    color: "#EEF5F9"
    screen: Qt.application.screens[1]

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MainMenu{
            id: mainMenu
        }
    }
    ErrorPopup{
        id: errorPopup
        onBack: {
            scheduler.receiveFromQmlBusySet(false)
            stackView.pop(mainMenu,StackView.Immediate)
        }
    }
    BusyErrorPopup{
        id: busyErrorPopup
    }
    ShutdownPopup{
        id: shutDownPopup
    }

    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlPrintError :{
            errorPopup.open()
        }
        onSendToQmlExitError :{
            busyErrorPopup.open()
        }
        onSendToQmlExit:{
            shutDownPopup.open()
        }
    }
}
