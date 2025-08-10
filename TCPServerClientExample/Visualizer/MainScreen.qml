import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CommonMessages 1.0
Rectangle {
    id: mainScreen
    width: 1024
    height: 600
    color: "#1e2939"

    // Dummy model for the dials
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

    // Container for dials - positioned top right
    Rectangle {
        id: dialContainer
        width: parent.width * 0.55
        height: parent.height * 0.4
        anchors.top: parent.top
        anchors.right: parent.right
        color: "transparent"

        DialsRow {
            id: dialRow
            anchors.fill: parent
            anchors.margins: 10
        }
    }
    NIBPDisplay{
        id:nibpDisp
        width: parent.width*0.3
        height: parent.height*0.3
        anchors.top:dialContainer.bottom
        anchors.topMargin: parent.height*0.01
        anchors.left: dialContainer.left
        anchors.leftMargin: 5
        paramName: "NIBP"
        sysValue: dataHandler.nibp.sysValue
        diaValue: dataHandler.nibp.diaValue
        sysMin: dataHandler.nibp.sysMin
        sysMax: dataHandler.nibp.sysMax
        diaMin: dataHandler.nibp.diaMin
        diaMax: dataHandler.nibp.diaMax
        units: dataHandler.nibp.units
    }
    TemperatureGauge{
        id:tempGauge
        width: parent.width*0.3
        height: parent.height*0.12
        anchors.top:nibpDisp.bottom
        anchors.topMargin: parent.height*0.01
        anchors.left: dialContainer.left
        anchors.leftMargin: 5
        label: dataHandler.temperature.paramName
        tempValue: dataHandler.temperature.value
        tempMin: dataHandler.temperature.minValue
        tempMax: dataHandler.temperature.maxValue
        units: dataHandler.temperature.units
    }
    EtCo2Display{
        id:etco2Gauge
        width: parent.width*0.3
        height: parent.height*0.12
        anchors.top:tempGauge.bottom
        anchors.topMargin: parent.height*0.01
        anchors.left: dialContainer.left
        anchors.leftMargin: 5
    }
    ConnectToServer{
        id:connectionToTCP
        width: parent.width*0.225
        height: parent.height*0.565
        anchors{
            right: parent.right
            rightMargin: width*0.05
            bottomMargin: height*0.05
            bottom: parent.bottom
        }
        onConnectClicked: {
            tcpClient.requestConnect(ip,port)
        }
        onDisconnectClicked: {
            tcpClient.requestDisconnect()
        }
    }
}
