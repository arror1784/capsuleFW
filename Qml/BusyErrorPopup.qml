import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()

    hasBTN: true

    body: Text {
        text: qsTr("you can exit on main menu")
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
}
