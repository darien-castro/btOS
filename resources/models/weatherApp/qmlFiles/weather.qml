import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import "."  // Import current directory explicitly

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
            font.family: "Times New Roman"
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
        anchors.topMargin: 43
        anchors.rightMargin: 15
        anchors.top: parent.top
        color: "transparent"
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("clicked")
            }
        }
        Image{
            source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/svg/menu.svg"
            anchors.topMargin: 5
            height: 35
            width: 35
        }
    }
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 50  // Add this
        height: 100          // Add this (or whatever height you want)
        color: "transparent" // Optional: to see what's happening
        anchors.bottomMargin: 100

        ForecastCard {
            anchors.fill: parent  // Make it fill the container
            Text {
                text: "hello World"
                anchors.centerIn: parent  // Better than horizontalCenter alone
                color: "black"  // Make sure text is visible on black background
            }
        }
    }
}