import QtQuick 2.15
import QtQuick.Controls 2.15
import "."

Item {
    anchors.fill: parent

    ListView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        orientation: ListView.Horizontal
        spacing: 10
        model: 7  // 7 days

        delegate: ForecastInfoCard {
            label: "weekly"
        }

        ScrollBar.horizontal: ScrollBar { }
    }
}
