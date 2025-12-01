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
        model: 24  // 24 hours in a day

        delegate: ForecastInfoCard {
            label: "hourly"

        }

        ScrollBar.horizontal: ScrollBar { }
    }
}
