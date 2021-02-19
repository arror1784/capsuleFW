import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()
    signal sendToShutdown()

    hasBTN: true

    body: Text {
        text: qsTr("Are you sure you want to exit?")
        font.family: openSansRegular.name
        font.pixelSize: 20
        color: "#474747"
    }
    BackBTN{
        id: backButton

        isPopup: true

        onBackClicked: {
            back()
            close()
        }
    }
    AcceptBTN{
        id: exitButton

        isPopup: true

        text: qsTr("exit")

        onAcceptClicked: {
            sendToShutdown()
        }
    }
}
