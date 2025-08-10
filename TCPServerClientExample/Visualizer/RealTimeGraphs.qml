import QtQuick 2.15
import QtQuick.Layouts 1.15
import CustomGraphs 1.0  // Your WaveformGraph registration

Rectangle {
    color: "#121212"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        WaveformGraph {
            id: ecgGraph
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 3 - 15
            paramName: dataHandler.ecg.paramName
            units: dataHandler.ecg.units
//            dataFrequencyMs: dataHandler.ecg.frequency
            timeWindowSec: 10
            lineColor: "green"
        }

        WaveformGraph {
            id: ppgGraph
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 3 - 15
            paramName: dataHandler.ppg.paramName
            units: "a.u."
//            dataFrequencyMs: dataHandler.ppg.frequency
            timeWindowSec: 10
            lineColor: "red"
        }

        WaveformGraph {
            id: respGraph
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 3 - 15
            paramName: dataHandler.respWaveForm.paramName
            units: dataHandler.respWaveForm.units
//            dataFrequencyMs: dataHandler.respWaveForm.frequency
            timeWindowSec: 10
            lineColor: "blue"
        }
    }
    Connections {
        target: dataHandler.ecg
        function onValueChanged() {
            ecgGraph.appendValue(dataHandler.ecg.value)
        }
    }
    Connections {
        target: dataHandler.ppg
        function onValueChanged() {
            ppgGraph.appendValue(dataHandler.ppg.value)
        }
    }
    Connections {
        target: dataHandler.respWaveForm
        function onValueChanged() {
            respGraph.appendValue(dataHandler.respWaveForm.value)
        }
    }

}
