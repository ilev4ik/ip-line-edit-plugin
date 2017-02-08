#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include <QtDesigner/QtDesigner>
#include <QWidget>
#include <memory>

class QDESIGNER_WIDGET_EXPORT IPLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit IPLineEdit(QWidget* parent = nullptr);
    ~IPLineEdit();
private:
    QBitArray ipBinary;
    QString ipNative;

    void processOctet(QString octet, int offset);
private slots:
    void processIP();

};

#endif // IPLINEEDIT_H
