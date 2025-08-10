import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CustomControls 1.0
Item {
    width: 640
    height: 300
    RowLayout {
        id: dialRow
        anchors.fill: parent
        spacing: 5

        Repeater {
            model: parameterModel
            delegate: DialIndicator {
                width: parent.width * 0.25
                height: parent.height * 0.75
                parmName: model.name
                units: model.units
                minValue: model.minValue
                maxValue: model.maxValue
                value: model.value
                backgroundColor: "#0f2430"
                dialBgColor: "#2f3a44"
                progressColor: model.progressColor
                needleColor: model.needleColor
                textColor: "#ffffff"
                thickness: 12
                cornerRadius: 6
            }
        }
    }
}
