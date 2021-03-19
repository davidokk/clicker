import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

import PassiveBoostersModel 1.0

Page {
    id: shopPage
    visible: false
    background: Rectangle {
        color: "lightgreen"
    }

    header: Rectangle {
        height: shopPage.height / 15
        Text {
            anchors.centerIn: parent
            text: "Balance: " + player.balance
            font.pixelSize: parent.height / 2
            font.bold: true
        }
    }

    GridView {
        id: gridView

        anchors.fill: parent
        cellWidth: parent.width
        cellHeight: 100

        model: PassiveBoostersModel {
            id: passiveBoostersModel
        }

        delegate: Button {
            text: model.display
            width: gridView.cellWidth
            height: gridView.cellHeight

            onClicked: {
                player.buy(passiveBoostersModel.buy(index, player.long_balance));
            }
        }
    }

    Button {
        id: backToGame

        width: parent.width / 4
        height: parent.height / 15
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20

        text: "Back"
        font {
            bold: true
            pixelSize: Math.min(width, height) / 2
        }

        onClicked: {
            pageStack.pop();
        }
    }
}
