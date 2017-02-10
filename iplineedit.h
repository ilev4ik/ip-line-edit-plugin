#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include <QtDesigner/QtDesigner>
#include <QWidget>
#include <QBitArray>
#include <QRegExp>

#include "ipaddress.h"

class QDESIGNER_WIDGET_EXPORT IPLineEdit : public QLineEdit {
    Q_OBJECT
    Q_PROPERTY(Correction correction
               READ correction
               WRITE setCorrection
               NOTIFY correctionChanged
               DESIGNABLE true
               USER true)

    using State = QValidator::State;
public:
    explicit IPLineEdit(QWidget* parent = nullptr);
    ~IPLineEdit() override;

    enum class Correction {
        NoCorrection,   // нет автодополнения
        ZeroFilled      // автозаполнение нулями
    };
    Q_ENUM(Correction)

    void setCorrection(Correction);
    Correction correction() const;

    bool isValid();
signals:
    void correctionChanged(Correction);
private slots:
    // для дебага слоты, при конвертации в .so/.dll определить как public
    QBitArray addressBinary();
    QString addressNative();
private:
    static const QRegExp regExp;
    IPAddress ip;

    bool validness;
    Correction m_correction;

    State state {State::Invalid};

    void fillWithZeroes(QString&, int);
    void setBinaryForm();
    void processOctet(QString octet, int offset);

    const int octet_length = 8;
    const int octet_num = 4;
    const int normal_dot_count = 3;
};


#endif // IPLINEEDIT_H
