import QtQuick 2.15
import QtQuick.Particles 2.15

ParticleSystem {
    anchors.fill: parent

    Emitter {
        anchors.fill: parent
        height: parent.height / 2
        anchors.top: parent.top
        emitRate: 1
        lifeSpan: 5000

        velocity: AngleDirection {
            angle: 0
            magnitude: 20
        }

        size: 150
        sizeVariation: 40
    }

    ImageParticle {
        source: "/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/svg/clouds.png"
        color: "#FFFFFF"
        colorVariation: 0
    }
}