import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.1

Rectangle {
    id: mainView
    color: "white"
    clip: false
    width: 500; height: 100

    signal settingsButtonClicked()
    signal stopButtonClicked()

    Button {
        text: "settings"
        id: settingsButton
        transformOrigin: Item.Center
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 3
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        onClicked: mainView.settingsButtonClicked()
    }

    Button {
        text: "stop notifier"
        id: stopButton
        anchors.left: settingsButton.right
        anchors.leftMargin: 6
        anchors.rightMargin: 6
        anchors.top: settingsButton.top
        anchors.bottom: settingsButton.bottom
        anchors.right: parent.right
        onClicked: mainView.stopButtonClicked()
    }
}
