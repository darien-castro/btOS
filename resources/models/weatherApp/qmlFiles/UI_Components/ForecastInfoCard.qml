import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 100
    height: 150
    radius: 12
    color: "white"

    // --- properties the model will fill ---
    property string label: ""
    property string temperature: ""
    property string iconSource: ""

    Column {
        anchors.centerIn: parent
        spacing: 4

        Text {
            font.family: "Hack"
            text: label
            font.pixelSize: 14
            font.letterSpacing: 1
            color: "black"
            font.bold: true
        }

        Image {
            source: iconSource
            width: 32
            height: 32
        }

        Text {
            font.family: "BigBlueTerminal"
            text: temperature
            font.pixelSize: 22
            color: "#93B1DA"
            font.bold: true
        }
    }
}
