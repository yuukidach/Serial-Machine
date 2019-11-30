import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    width: portCombo.width + 20
    height: main.height
    anchors.left: main.left

    ComboBox {
        id: portCombo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 140
        height: 24
        model: MainPresenter.name_list
        onPressedChanged: if (pressed) model = MainPresenter.name_list
    }

    ComboBox {
        id: baudCombo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: portCombo.bottom
        anchors.topMargin: 15
        width: 140
        height: 24
        model: MainPresenter.baud_list
        currentIndex: 3
    }

    ComboBox {
        id: dataBitsCombo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: baudCombo.bottom
        anchors.topMargin: 15
        width: 140
        height: 26
        model: MainPresenter.data_bits_list
        currentIndex: 3
    }

    ComboBox {
        id: parityCombo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dataBitsCombo.bottom
        anchors.topMargin: 15
        width: 140
        height: 26
        model: MainPresenter.parity_list
    }

    ComboBox {
        id: stopBitsCombo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parityCombo.bottom
        anchors.topMargin: 15
        y: 218
        width: 140
        height: 26
        model: MainPresenter.stop_bits_list
    }

    CheckBox {
        id: timeStampCheck
        text: qsTr("Show Time Stamp")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: stopBitsCombo.bottom
        anchors.topMargin: 15
        height: 32
        onCheckedChanged: MainPresenter.setTimestampNeed(checked)
    }

    CheckBox {
        id: hexCheck
        text: qsTr("Show in Hex")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: timeStampCheck.bottom
        anchors.topMargin: 15
        width: timeStampCheck.width
        height: 32
        onCheckedChanged: MainPresenter.setHexModeNeed(checked)
    }

    Button {
        id: openBtn
        text: qsTr("Open")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: hexCheck.bottom
        anchors.topMargin: 15
        onClicked: {
            if (text == "Open") {
                text = "Close"
                MainPresenter.openPort(portCombo.currentText,
                                       baudCombo.currentText,
                                       dataBitsCombo.currentText,
                                       parityCombo.currentText,
                                       stopBitsCombo.currentText)
            } else {
                text = "Open"
                MainPresenter.closePort()
            }
        }
    }

    Button {
        id: clrInBtn
        text: qsTr("Clear Input")
        width: clrOutBtn.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: clrOutBtn.top
        anchors.bottomMargin: 10
        onClicked: inScrollText.text=""
    }

    Button {
        // TODO: fix the problem that this button does not work
        id: clrOutBtn
        text: qsTr("Clear Output")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: outTextBox.text=""
    }
}
