import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CustomControls 1.0
Item {
    width: 640
    height: 300

    ListModel {
        id: dialModel
        ListElement {
            parmName: "Heart Rate"
            units: "BPM"
            minValue: 40
            maxValue: 150
            value: 72
            backgroundColor: "#0f2430"
            dialBgColor: "#2f3a44"
            progressColor: "#ff6b6b"
            needleColor: "#ff2e6f"
            textColor: "#ffffff"
            thickness: 12
            cornerRadius: 6
        }
        ListElement {
            parmName: "Oxygen Level"
            units: "%"
            minValue: 70
            maxValue: 100
            value: 95
            backgroundColor: "#0f2430"
            dialBgColor: "#2f3a44"
            progressColor: "#4cd137"
            needleColor: "#44bd32"
            textColor: "#ffffff"
            thickness: 12
            cornerRadius: 6
        }
        ListElement {
            parmName: "Temperature"
            units: "°C"
            minValue: 30
            maxValue: 45
            value: 37
            backgroundColor: "#0f2430"
            dialBgColor: "#2f3a44"
            progressColor: "#00a8ff"
            needleColor: "#0097e6"
            textColor: "#ffffff"
            thickness: 12
            cornerRadius: 6
        }
    }

    RowLayout {
        id: dialRow
        anchors.fill: parent
        spacing: 5

        Repeater {
            model: dialModel
            delegate: DialIndicator {
                width: parent.width * 0.25
                height: parent.height * 0.75

                parmName: model.parmName
                units: model.units
                minValue: model.minValue
                maxValue: model.maxValue
                value: model.value
                backgroundColor: model.backgroundColor
                dialBgColor: model.dialBgColor
                progressColor: model.progressColor
                needleColor: model.needleColor
                textColor: model.textColor
                thickness: model.thickness
                cornerRadius: model.cornerRadius
            }
        }
    }
}
