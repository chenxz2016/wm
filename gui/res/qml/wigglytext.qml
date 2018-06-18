import QtQuick 2.0
import QtQuick.Particles 2.0

Rectangle {
    id: container

    property string text: "Walking Message"
    property bool animated: true

    width: parent.width; height: parent.height; color: "#ad98ff"; focus: true

    function doLayout() {
        var follow = null
        for (var i = 0; i < container.text.length; ++i) {
            var newLetter = letterComponent.createObject(container)
            newLetter.text = container.text[i]
            newLetter.follow = follow
            follow = newLetter
        }
    }

    ParticleSystem {
        id: particles
        anchors.fill: parent

        ImageParticle {
            id: bubble
            anchors.fill: parent
            source: "../login/catch.png"
            opacity: 0.25
        }
        Wander {
            xVariance: 25;
            pace: 25;
        }

        Emitter {
            width: parent.width
            height: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            startTime: 15000

            emitRate: 2
            lifeSpan: 15000

            acceleration: PointDirection{ y: -6; xVariation: 2; yVariation: 2 }

            size: 24
            sizeVariation: 16
        }
    }

    Component {
        id: letterComponent
        Text {
            id: letter
            property variant follow

            x: follow ? follow.x + follow.width : container.width / 6
            y: follow ? follow.y : container.height / 2

            font.pixelSize: 40; font.bold: true
            color: "#ffffff"; styleColor: "#222222"; style: Text.Raised

            MouseArea {
                anchors.fill: parent
                drag.target: letter; drag.axis: Drag.XAndYAxis
                onPressed: letter.color = "#dddddd"
                onReleased: letter.color = "#ffffff"
            }

            Behavior on x { enabled: container.animated; SpringAnimation { spring: 3; damping: 0.3; mass: 1.0 } }
            Behavior on y { enabled: container.animated; SpringAnimation { spring: 3; damping: 0.3; mass: 1.0 } }
        }
    }

    Component.onCompleted: doLayout()
}
