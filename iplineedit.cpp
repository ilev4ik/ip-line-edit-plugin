#include "iplineedit.h"
#include <QRegExp>
#include <QDebug>

IPLineEdit::IPLineEdit(QWidget* parent):
    QLineEdit(parent)
{
    QRegExp regExp("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}");
    this->setValidator(new QRegExpValidator(regExp, this));
    QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(processIP()));
}

IPLineEdit::~IPLineEdit() {

}

void IPLineEdit::processIP() {
    ipBinary.fill(0, 4*8);
    ipNative = text();


    int lastId = ipNative.size()-1;

    if (ipNative[lastId] == '.')
        ipNative.remove(lastId, 1);


    QStringList octetList = ipNative.split('.');

    qDebug() << ipNative;

    for (int i = 0; i < octetList.size(); ++i) {
        processOctet(QString::number(octetList[i].toInt(), 2), i);
    }

    qDebug() << ipBinary;
}

void IPLineEdit::processOctet(QString octet, int offset) {
    int length = octet.size();
    for (int i = 0; i < length; ++i) {
        ipBinary[8*(offset+1)-length+i] = octet[i] == '1';
    }
}
