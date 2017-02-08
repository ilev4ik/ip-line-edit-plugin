#include "iplineedit.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    IPLineEdit lineEdit;
    lineEdit.show();

    return app.exec();
}
