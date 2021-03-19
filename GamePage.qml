import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

Page {
    property alias balance: balance.text
    property alias per_click: per_click.text
    property alias per_second: per_second.text
    property alias tap_factor: tap_factor.text
    id: gamePage
    background: Rectangle {
        color: "pink"
    }

    Text {
        id: balance
        height: parent.height / 20
        text: "Balance: " + player.balance
        font {
            bold: true
            pixelSize: Math.min(width, height) / 2
        }
        anchors.bottom: clickButton.top
        anchors.horizontalCenter: clickButton.horizontalCenter
        //anchors.margins: 10
    }

    Rectangle {
        id: clickButton
        width: parent.width / 1.5
        height: width
        radius: width / 2
        anchors.centerIn: parent
        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "cookie.png"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                player.click();
            }
        }

    }

    Button {
        id: toShopPageButton

        width: parent.width / 4
        height: parent.height / 15
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20

        text: "Shop"
        font {
            bold: true
            pixelSize: Math.min(width, height) / 2
        }

        onClicked: {
            pageStack.push(shopPage);
        }
    }

    Text {
        id: per_click
        height: parent.height / 20
        text: "Per click: " + player.per_click
        font {
            bold: true
            pixelSize: Math.min(width, height) / 2
        }
        anchors.top: clickButton.bottom
        anchors.horizontalCenter: clickButton.horizontalCenter
        anchors.topMargin: 10
        //anchors.margins: 10
    }


    Text {
        id: per_second
        height: parent.height / 20
        text: "Per second: " + player.per_second
        font {
            bold: true
            pixelSize: Math.min(width, height) / 2
        }
        anchors.top: per_click.top
        anchors.horizontalCenter: per_click.horizontalCenter
        anchors.margins: 20
    }

    Text {
        id: tap_factor
        height: parent.height / 20
        text: "Tap factor: x" + player.tap_factor
        font {
            italic: true
            pixelSize: Math.min(width, height) / 2
        }
        anchors.top: per_second.top
        anchors.horizontalCenter: per_second.horizontalCenter
        anchors.margins: 20
    }
}
