import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import QtQuick.Particles 2.15
import "."  // Import current directory explicitly
import ".."
import "../WeatherConditionsQML"
import "../UI_Components"


import com.weather 1.0
Rectangle {
    Connections {
        target: qmlobj
        function onResultsReady(formatted) {
            city_textField.text = formatted
        }
    }
    // ------------------------------------------------------------
    width: 200
    height: 200
    layer.enabled: true
    layer.smooth: true

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 2
        height: parent.height * 2
        rotation: 67

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#593391" }
            GradientStop { position: 0.5; color: "#3B2E52" }
            GradientStop { position: 1.0; color: "#211C1C" }
        }
    }

    Rectangle {
        width: 300
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
            Keys.onReturnPressed: {
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

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("clicked")
        }

        Image {
            source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/svg/menu.svg"
            anchors.topMargin: 5
            height: 3
            width: 35
        }
    }

    Rectangle {
        color: "transparent"
        height: parent.height / 2
        width: parent.width / 2
        anchors.centerIn: parent

        Text {
            font.family: "Maple Mono"
            color: "white"
            font.pixelSize: 82
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: weatherScreen.temperature + "°F"
            anchors.verticalCenterOffset: -150
        }
    }
    Rectangle {
        property string weatherCondition: "cloudy" // your state variable

        color: "transparent"
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -45

        Image {
            anchors.centerIn: parent
            height: 100
            width: 100
            source: {
                if (qmlobj.weatherCondition === WeatherCondition.CLOUDY)
                    return "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/conditionIcons/cloud.png"
                else if (qmlobj.weatherCondition === WeatherCondition.RAINY)
                    return "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/conditionIcons/rainy-day.png"
                else if (qmlobj.weatherCondition === WeatherCondition.STORMY)
                    return "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/conditionIcons/storm.png"
                else
                    return "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/conditionIcons/sun.png"
            }
        }
    }

    Row {
        id: pageSwitcher
        spacing: 15
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        z: 10

        Button {
            text: "Hourly"
            onClicked: weatherStack.replace(
                "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/UI_Components/HourlyView.qml",
                { weatherObj: qmlobj }  // ✅ Second parameter, same line
            )
        }
        Button {
            text: "Weekly"
            onClicked: weatherStack.replace(
                "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/UI_Components/WeeklyView.qml",
                { weatherObj: qmlobj }  // ✅ Second parameter, same line
            )
        }
    }

    StackView {
        id: weatherStack
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: pageSwitcher.top
        height: 250

        initialItem: Qt.createComponent("/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/UI_Components/HourlyView.qml")
            .createObject(weatherStack, { weatherObj: qmlobj })


    }

    Image {
        anchors.fill: parent
        source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/svg/dither.png"
        fillMode: Image.Tile
        opacity: 0.03
        smooth: true
    }
    Stormy {
        visible: qmlobj.weatherCondition === WeatherCondition.STORMY
    }
    Rainy{
        visible: qmlobj.weatherCondition === WeatherCondition.RAINY
    }
    Cloudy{
        visible: qmlobj.weatherCondition === WeatherCondition.CLOUDY
    }
}
