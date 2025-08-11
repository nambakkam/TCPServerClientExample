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
    property string label : "EtCO₂"
    property real etco2Value: 32.4
    property real etco2Min: 0
    property real etco2Max: 50
    property string units: "mmHg"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 6

        Label {
            text: label
            color: "#aaaaaa"
            font.pixelSize: 12
        }

        RowLayout {
            spacing: 6
            HorizontalGauge {
                Layout.fillWidth: true
                minValue: etco2Min
                maxValue: etco2Max
                value: etco2Value
                fillColor: "#e67e22"
            }
            Label {
                text: Number(etco2Value).toFixed(1) +" "+ units
                color: "#ffffff"
                font.pixelSize: 12
            }
        }
    }
}
