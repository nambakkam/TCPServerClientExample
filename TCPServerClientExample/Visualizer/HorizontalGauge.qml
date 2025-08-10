import QtQuick 2.15

Item {
    id: gauge
    property real minValue: 0
    property real maxValue: 100
    property real value: 50
    property color fillColor: "#2ecc71"
    property color backgroundColor: "#3a3f4b"
    property int radius: 5

    implicitHeight: 12
    implicitWidth: 150

    Rectangle {
        anchors.fill: parent
        radius: gauge.radius
        color: backgroundColor
    }

    Rectangle {
        width: Math.max(0, (value - minValue) / (maxValue - minValue) * gauge.width)
        height: parent.height
        radius: gauge.radius
        color: fillColor
        Behavior on width {
            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
        }
    }
}
