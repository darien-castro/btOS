
import QtQuick 2.15
import QtQuick.Particles 2.15


Rectangle{
    anchors.fill:parent;
    color: "transparent"

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
