import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    width: 250
    height: 140
    radius: 8
    color: "#1a1f2b"
    border.color: "#2a2f3b"
    border.width: 1

    property real sysValue: 118.9
    property real diaValue: 80.8
    property real sysMin: 40
    property real sysMax: 180
    property real diaMin: 40
    property real diaMax: 120

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        Label {
            text: "NIBP"
            color: "#aaaaaa"
            font.pixelSize: 12
        }

        RowLayout {
            spacing: 6
            Label {
                text: "SYS"
                color: "#cccccc"
                font.pixelSize: 12
                Layout.preferredWidth: 35
            }
            HorizontalGauge {
                Layout.fillWidth: true
                minValue: sysMin
                maxValue: sysMax
                value: sysValue
                fillColor: "#2ecc71"
            }
            Label {
                text: Number(sysValue).toFixed(1)
                color: "#ffffff"
                font.pixelSize: 12
            }
        }

        RowLayout {
            spacing: 6
            Label {
                text: "DIA"
                color: "#cccccc"
                font.pixelSize: 12
                Layout.preferredWidth: 35
            }
            HorizontalGauge {
                Layout.fillWidth: true
                minValue: diaMin
                maxValue: diaMax
                value: diaValue
                fillColor: "#2ecc71"
            }
            Label {
                text: Number(diaValue).toFixed(1)
                color: "#ffffff"
                font.pixelSize: 12
            }
        }

        Label {
            text: Number(sysValue).toFixed(1) + "/" + Number(diaValue).toFixed(1) + " mmHg"
            color: "#ffffff"
            font.pixelSize: 14
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
