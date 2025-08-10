import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

Rectangle {
    id: root
    width: 280
    height: 140
    radius: 10
    color: "#1e2533"
    border.color: "#3c4454"
    border.width: 1

    property string ipAddress: "127.0.0.1"
    property int portNumber: 12345
    property bool isConnected: false

    signal connectClicked(string ip, int port)
    signal disconnectClicked()

    // Drop shadow effect for floating look
    layer.enabled: true
    layer.effect: DropShadow {
        anchors.fill: root
        horizontalOffset: 2
        verticalOffset: 2
        radius: 8
        samples: 16
        color: "#66000000"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        // Title
        Label {
            text: "TCP Connection"
            font.bold: true
            font.pixelSize: 14
            color: "#ffffff"
            Layout.alignment: Qt.AlignHCenter
        }

        // IP Row
        RowLayout {
            spacing: 6
            Label {
                text: "IP:"
                color: "#aaaaaa"
                font.pixelSize: 12
                Layout.preferredWidth: 30
            }
            TextField {
                Layout.fillWidth: true
                text: root.ipAddress
                color: "#ffffff"
                placeholderText: "Enter IP"
                background: Rectangle {
                    radius: 6
                    color: "#2c3444"
                }
            }
        }

        // Port Row
        RowLayout {
            spacing: 6
            Label {
                text: "Port:"
                color: "#aaaaaa"
                font.pixelSize: 12
                Layout.preferredWidth: 30
            }
            TextField {
                Layout.fillWidth: true
                text: root.portNumber.toString()
                inputMethodHints: Qt.ImhDigitsOnly
                color: "#ffffff"
                placeholderText: "Enter Port"
                background: Rectangle {
                    radius: 6
                    color: "#2c3444"
                }
            }
        }

        // Buttons Row
        RowLayout {
            spacing: 8

            Button {
                text: "Connect"
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 6
                    color: root.isConnected ? "#27ae60" : "#2ecc71"
                }
                onClicked: {
                    root.isConnected = true
                    root.connectClicked(root.ipAddress, root.portNumber)
                }
            }

            Button {
                text: "Disconnect"
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 6
                    color: "#e74c3c"
                }
                onClicked: {
                    root.isConnected = false
                    root.disconnectClicked()
                }
            }
        }
    }
}
