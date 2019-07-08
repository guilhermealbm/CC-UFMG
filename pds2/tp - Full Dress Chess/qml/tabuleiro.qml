import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2


Rectangle {
    id: tabuleiro

    width: 200
    height: 200

    Grid {
        id: divisoesTabuleiro
        rows: 8
        columns: 8
        spacing: 0

        anchors.fill: parent

        Repeater{
            id: geradorCores
            model: 8*8

            Rectangle {
                height: divisoesTabuleiro.height / 8
                width: height

                color: {
                    var linha = Math.floor(index/8);
                    var coluna = index % 8
                    if((linha + coluna) % 2 == 1)
                        "#8B4513";
                    else
                        "#FFE4B5";
                }
            }
        }
    }
}
