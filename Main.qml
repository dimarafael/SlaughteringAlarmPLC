import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import com.kometa.AlarmListModel
import com.kometa.AlarmHistoryListModel

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Slaughtering Alarms")

    readonly property int defMargin: window.height * 0.02
    readonly property color shadowColor: "#88000000"

    LinearGradient{
        anchors.fill: parent
        start: Qt.point(0,height)
        end: Qt.point(width,0)
        gradient: Gradient{
            GradientStop{
                position: 0.0;
                color: "#416f4c"
            }
            GradientStop{
                position: 0.5;
                color: "#ffffff"
            }
            GradientStop{
                position: 1.0;
                color: "#ce253c"
            }
        }
    }


    Item{
        id: itemRootContent
        anchors.fill: parent
        anchors.margins: window.defMargin

        Item {
            id: topMenu
            clip: true
            anchors.top: itemRootContent.top
            width: itemRootContent.width
            height: itemRootContent.height / 10

            Rectangle{
                id: topMenuBckground
                anchors.top: parent.top
                width: parent.width
                height: parent.height + window.defMargin
                color: "#416f4c"
                radius: window.defMargin
            }

            Image {
                id: logo
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    margins: window.defMargin
                }
                fillMode: Image.PreserveAspectFit

                source: "img/logo.png"
            }

            Item{
                id: itemClock
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height * 2.8
                Text{
                    id: clockText
                    anchors.fill: parent
                    font.pixelSize: height * 0.8
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    color: "white"
                }

                Timer{
                    interval: 1000; running: true; repeat: true
                    onTriggered: {
                        var date = new Date();
                        clockText.text = date.toLocaleTimeString(Qt.locale("en-GB"), Locale.ShortFormat);
                    }
                }

            }

            Text{
                id: textTitle
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: logo.right
                anchors.right: itemClock.left
                font.pixelSize: height / 2
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                text: "Vágóhíd PLC hibák"
            }
        }
        DropShadow {
            anchors.fill: topMenu
            source: topMenu
            horizontalOffset: window.defMargin / 3
            verticalOffset: window.defMargin / 3
            radius: 8.0
            samples: 17
            color: window.shadowColor
        }

        Item{
            id: itemActualAlarms
            anchors{
                top: topMenu.bottom
                left: parent.left
                right: parent.right
                topMargin: window.defMargin
            }
            height: (itemRootContent.height - topMenu.height)/2 - window.defMargin

            Rectangle{
                id: rectangleActualAlarms
                anchors.fill: parent
            }

            Item{
                anchors.fill: parent
                anchors.margins: window.defMargin / 2
                clip: true
                ListView{
                    anchors.fill: parent
                    ScrollBar.vertical: ScrollBar { }
                    model: AlarmListModel
                    delegate: Text{
                        id: delegate
                        required property string alarmMessageHU;
                        required property string alarmMessageDE;
                        required property bool alarmTypeError;
                        required property date alarmTimestamp;

                        width: itemActualAlarms.width - window.defMargin
                        height: (itemActualAlarms.height - window.defMargin) / 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: height *0.8
                        color: delegate.alarmTypeError? "darkred" : "darkblue"
                        text: delegate.alarmTimestamp.toLocaleString(Qt.locale("hu_HU"), Locale.ShortFormat) + " | " + delegate.alarmMessageHU + " | " + delegate.alarmMessageDE
                    }

                    add: Transition {
                        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
                        NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
                    }

                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutQuad }
                    }

                    remove: Transition {
                        NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 400 }
                        NumberAnimation { property: "scale"; from: 1.0; to: 0; duration: 400 }
                    }
                }
            }

            Rectangle{
                id: rectangleOffline
                anchors.centerIn: parent
                height: parent.height / 2
                width: parent.width / 2
                color: "red"
                radius: window.defMargin
                visible: !AlarmListModel.plcOnline
                Text{
                    anchors.centerIn: parent
                    color: "white"
                    font.pixelSize: rectangleOffline.height / 2
                    font.bold: true
                    text: "PLC OFFLINE"
                }
            }

        }
        DropShadow {
            anchors.fill: itemActualAlarms
            source: itemActualAlarms
            horizontalOffset: window.defMargin / 3
            verticalOffset: window.defMargin / 3
            radius: 8.0
            samples: 17
            color: window.shadowColor
        }

        Item{
            id: itemHistoryAlarms
            anchors{
                top: itemActualAlarms.bottom
                left: parent.left
                right: parent.right
                topMargin: window.defMargin
            }
            height: (itemRootContent.height - topMenu.height)/2 - window.defMargin

            Rectangle{
                id: rectangleHistoryAlarms
                anchors.fill: parent
            }

            Item{
                anchors.fill: parent
                anchors.margins: window.defMargin / 2
                clip: true

                ListView{
                    anchors.fill: parent
                    ScrollBar.vertical: ScrollBar { }
                    model: AlarmHistoryListModel
                    delegate: Text{
                        id: delegate2
                        required property string alarmMessageHU;
                        required property string alarmMessageDE;
                        required property bool alarmTypeError;
                        required property date alarmTimestamp;

                        width: itemHistoryAlarms.width - window.defMargin
                        height: (itemHistoryAlarms.height - window.defMargin) / 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: height *0.8
                        color: delegate2.alarmTypeError? "darkred" : "darkblue"
                        text: delegate2.alarmTimestamp.toLocaleString(Qt.locale("hu_HU"), Locale.ShortFormat) + " | " + delegate2.alarmMessageHU + " | " + delegate2.alarmMessageDE
                    }

                    add: Transition {
                        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
                        NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
                    }

                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutQuad }
                    }
                }
            }
        }
        DropShadow {
            anchors.fill: itemHistoryAlarms
            source: itemHistoryAlarms
            horizontalOffset: window.defMargin / 3
            verticalOffset: window.defMargin / 3
            radius: 8.0
            samples: 17
            color: window.shadowColor
        }
    }
}
