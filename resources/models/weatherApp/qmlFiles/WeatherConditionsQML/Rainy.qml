
import QtQuick 2.15
import QtQuick.Particles 2.15

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
