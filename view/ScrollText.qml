import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    height: parent.height * 0.55
    anchors {
        left: sidePannelForm.right
        right: parent.right
        top: inText.bottom
        topMargin: 5
        rightMargin: 15
    }

    Connections {
        target: MainPresenter
        onRcvDataArrived: inTextBox.append(MainPresenter.rcv_data)
    }

    Rectangle {
        id: inTextBackground
        border.color: "gray"
        color: "#282b2c"
        radius: 5
        anchors.fill: parent
    }

    Flickable {
        id: inTextFlick
        anchors.fill: parent
        contentHeight: inTextBox.height
        flickableDirection: Flickable.VerticalFlick

        TextArea.flickable: TextArea {
            id: inTextBox
            text: ""
            font.family: "Courier"
            background: Rectangle{
                color: "transparent"
            }
            readOnly: true
            textMargin: 4
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }
    }
}
