#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QFont defaultFont = QApplication::font();
    defaultFont.setPointSize(12);
    qApp->setFont(defaultFont);
    MainWindow window;

    window.setWindowTitle("Countries and their operators");
    window.setStyleSheet("background-color: grey;");
    window.showMaximized();
    return app.exec();
}

