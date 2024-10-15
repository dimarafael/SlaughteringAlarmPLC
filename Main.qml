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
                    right: lineVerticalMachine1.left
                    margins: window.defMargin
                }
                fillMode: Image.PreserveAspectFit

                source: "img/logo.png"
            }

            Text{
                id: textTitle
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: logo.right
                anchors.right: parent.right
                font.pixelSize: height / 2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                text: "Vágóhíd hibák"
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
                        font.pixelSize: window.height / 30
                        color: delegate.alarmTypeError? "darkred" : "darkblue"
                        text: delegate.alarmMessageHU + " | " + delegate.alarmMessageDE
                    }
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
                        font.pixelSize: window.height / 40
                        color: delegate2.alarmTypeError? "darkred" : "darkblue"
                        text: delegate2.alarmTimestamp.toLocaleString(Qt.locale("hu_HU"), Locale.ShortFormat) + " | " + delegate2.alarmMessageHU + " | " + delegate2.alarmMessageDE
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
