import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: main
    title: qsTr("Serial Machine")

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    minimumWidth: 1000
    minimumHeight: 600
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

    ScrollText {
        id: inScrollText
    }

    Label {
        id: outText
        text: qsTr("Data Out")
        anchors.left: sidePannelForm.right
        anchors.top: inScrollText.bottom
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

    Button {
        id: saveBtn
        text: "Save"
       anchors {
            bottom: sendBtn.top
            bottomMargin: 10
            right: sendBtn.right
        }
        onClicked: saveFileDialog.open()
    }


    Button {
        id: sendBtn
        text: "Send"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 15
        anchors.bottomMargin: 10
        onClicked: MainPresenter.sendMsg(outTextBox.text)
    }

    FileDialog {
        id: saveFileDialog
        title: qsTr("Please choose a file")
        folder: shortcuts.home
        selectExisting: false
        onAccepted: {
            MainPresenter.saveData(saveFileDialog.fileUrl, inScrollText.text)
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
