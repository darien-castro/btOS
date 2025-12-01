import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import QtQuick.Particles 2.15
import "."  // Import current directory explicitly

Rectangle {
    Component.onCompleted: {
        console.log("THIS weather.qml instance:", this, "qmlobj is:", typeof qmlobj)
    }

    // ----------- SIGNAL CONNECTION (CORRECTLY ADDED) -----------
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
            height: 35
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

    Row {
        id: pageSwitcher
        spacing: 15
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        z: 10

        Button {
            text: "Hourly"
            onClicked: weatherStack.replace("/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/HourlyView.qml")
        }
        Button {
            text: "Weekly"
            onClicked: weatherStack.replace("/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/WeeklyView.qml")
        }
    }

    StackView {
        id: weatherStack
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: pageSwitcher.top
        height: 250

        initialItem: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/HourlyView.qml"
    }

    Image {
        anchors.fill: parent
        source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/svg/dither.png"
        fillMode: Image.Tile
        opacity: 0.03
        smooth: true
    }

    ParticleSystem {
        anchors.fill: parent

        Emitter {
            anchors.fill: parent
            anchors.top: parent.top
            emitRate: 100
            lifeSpan: 1000

            velocity: AngleDirection {
                angle: 90
                magnitude: 760
            }

            size: 4
            sizeVariation: 1
        }

        ImageParticle {
            source: "qrc:///particleresources/glowdot.png"
            color: "#cee0e0"
            colorVariation: 0.3
        }
    }

    Rectangle {
        id: lightningFlash
        anchors.fill: parent
        color: "white"
        opacity: 0
        z: 100

        Timer {
            interval: 6000 + Math.random() * 4000
            running: true
            repeat: true
            onTriggered: lightningAnimation.start()
        }

        SequentialAnimation {
            id: lightningAnimation

            NumberAnimation { target: lightningFlash; property: "opacity"; to: 0.4; duration: 40 }
            NumberAnimation { target: lightningFlash; property: "opacity"; to: 0; duration: 60 }

            PauseAnimation { duration: 80 }

            NumberAnimation { target: lightningFlash; property: "opacity"; to: 0.6; duration: 30 }
            NumberAnimation { target: lightningFlash; property: "opacity"; to: 0; duration: 150 }
        }
    }
}
