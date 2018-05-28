#include <QCoreApplication>
#include "GUI/mygui.h"
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("icon_kalk.ico"));
    mygui widget;
    widget.show();

    return app.exec();
}
