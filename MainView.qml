import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3


ApplicationWindow {
    id: main
    title: qsTr("Serial Machine")

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    minimumWidth: 900
    minimumHeight: 540
    visible: true

    SidePannel {
        id: sidePannelForm
    }

    Label {
        id: inText
        text: qsTr("Data In")
        anchors.left: sidePannelForm.right
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Flickable {
        id: inTextFlick
        anchors {
            left: sidePannelForm.right
            right: parent.right
            top: inText.bottom
            topMargin: 5
            rightMargin: 15
        }
        height: parent.height * 0.5
        contentHeight: height
        clip: true

        TextArea.flickable: TextArea {
            id: inTextBox
            text: ""
            font.family: "Courier"
            background: Rectangle {
                border.color: "gray"
                color: "#282b2c"
                radius: 5
            }
            readOnly: true
            textMargin: 4           
        }

        Connections {
            target: MainPresenter
            onRcvDataArrived: inTextBox.append(MainPresenter.rcv_data)
        }

        ScrollBar.vertical: ScrollBar {}
    }

    Label {
        id: outText
        text: qsTr("Data Out")
        anchors.left: sidePannelForm.right
        anchors.top: inTextFlick.bottom
        anchors.topMargin: 10
    }

    TextArea {
        id: outTextBox
        placeholderText: qsTr("Enter data you want to send out.")
        anchors.left: sidePannelForm.right
        anchors.top: outText.bottom
        anchors.right: sendBtn.left
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        font.family: "Courier"
    }

    //        Button {
    //            text: "Save"
    //        }

    Button {
        id: sendBtn
        text: "Send"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 15
        anchors.bottomMargin: 10
        onClicked: MainPresenter.sendMsg(outTextBox.text)
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
