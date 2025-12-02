import QtQuick 2.15
import QtQuick.Controls 2.15
import "."

Item {
    anchors.fill: parent
    property var weatherObj: null
    Connections{
        target: weatherObj
        function onweatherConditionChanged(){

        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        orientation: ListView.Horizontal
        spacing: 10
        model: 7

        delegate: ForecastInfoCard {
            label: weatherObj.weatherCondition, weatherObj.getTimeAtIndex(index)
            temperature: weatherObj.weatherCondition, weatherObj.getTempAtIndex(index) + "°F"
        }

        ScrollBar.horizontal: ScrollBar { }
    }
}
