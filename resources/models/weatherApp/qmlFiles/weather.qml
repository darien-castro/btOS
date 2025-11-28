import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

Rectangle {
    width: 200
    height: 200
    color: "#636363"
    Rectangle {
        width: 180
        height: 75
        anchors.left: parent.left
        anchors.margins: 25
        anchors.top: parent.top
        color: "transparent"
        TextField {
            id: city_textField
            anchors.fill: parent
            anchors.margins: 5
            placeholderText: "City"
            color: "white"
            font.pointSize: 24
            font.bold: true
            background: Rectangle {
                color: "transparent"
            }
            Keys.onReturnPressed :{
                qmlobj.store_city(city_textField.text)
            }
        }
    }
    Rectangle {
        width: 75
        height: 35
        anchors.right: parent.right
        anchors.margins: 45
        anchors.top: parent.top
        color: "transparent"
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("clicked")
            }
        }
        Image{
            source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/menu.png"
            anchors.fill: parent
        }
    }
}