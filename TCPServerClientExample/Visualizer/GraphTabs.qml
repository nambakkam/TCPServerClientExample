import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    anchors.fill: parent

    property alias currentIndex: tabBar.currentIndex

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton { text: "Graphs" }
            TabButton { text: "Dials" }
            TabButton { text: "Gauge Data" }

            onCurrentIndexChanged: stackLayout.currentIndex = currentIndex
        }

        StackLayout {
            id: stackLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            // Tab 1 - Graphs
            Rectangle {
                color: "#f0f0f0"
                anchors.fill: parent
                Text {
                    text: "Graph area here"
                    anchors.centerIn: parent
                    font.pixelSize: 20
                }
            }

            // Tab 2 - Dials
            Rectangle {
                color: "#e0f7fa"
                anchors.fill: parent
                Text {
                    text: "Dial controls here"
                    anchors.centerIn: parent
                    font.pixelSize: 20
                }
            }

            // Tab 3 - Gauge Data
            Rectangle {
                color: "#fce4ec"
                anchors.fill: parent
                Text {
                    text: "Gauge data display here"
                    anchors.centerIn: parent
                    font.pixelSize: 20
                }
            }
        }
    }
}
