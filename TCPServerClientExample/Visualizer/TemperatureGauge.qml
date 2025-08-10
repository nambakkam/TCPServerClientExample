import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    width: 250
    height: 70
    radius: 8
    color: "#1a1f2b"
    border.color: "#2a2f3b"
    border.width: 1

    property real tempValue: 37.5
    property real tempMin: 30
    property real tempMax: 45

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 6

        Label {
            text: "Temperature"
            color: "#aaaaaa"
            font.pixelSize: 12
        }

        RowLayout {
            spacing: 6
            Label {
                text: "TEMP"
                color: "#cccccc"
                font.pixelSize: 12
                Layout.preferredWidth: 45
            }
            HorizontalGauge {
                Layout.fillWidth: true
                minValue: tempMin
                maxValue: tempMax
                value: tempValue
                fillColor: "#3498db"
            }
            Label {
                text: Number(tempValue).toFixed(1) +  " °C"
                color: "#ffffff"
                font.pixelSize: 12
            }
        }
    }
}
