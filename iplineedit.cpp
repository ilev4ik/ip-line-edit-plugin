#include "iplineedit.h"
#include <QDebug>

const QRegExp IPLineEdit::regExp("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}$");

IPLineEdit::IPLineEdit(QWidget* parent):
    QLineEdit(parent),
    validness(false),
    m_correction(Correction::ZeroFilled) // Correction::NoCorrection
{
    setValidator(new QRegExpValidator(regExp, this));

    // эмуляция программных запросов (что вернётся, если
    // вызвать методы любой момент состояния строки
    QObject::connect(this, SIGNAL(textChanged(QString)),
                     this, SLOT(addressNative()));
    QObject::connect(this, SIGNAL(textChanged(QString)),
                     this, SLOT(addressBinary()));
}

IPLineEdit::~IPLineEdit() {

}

void IPLineEdit::setCorrection(Correction correction) {
    if (m_correction != correction) {
        m_correction = correction;
        emit correctionChanged(correction);
    }
}

IPLineEdit::Correction IPLineEdit::correction() const {
    return m_correction;
}

bool IPLineEdit::isValid() {
    validness = false;
    int start = 0;
    ip.native = text();

    // чтобы определить валидность в состоянии Intermediate, вручную validate()
    State curState = validator()->validate(ip.native, start);

    switch (curState) {
    case State::Acceptable:
        ip.binary.fill(0, octet_length*octet_num);
        validness = true;
        break;
    case State::Intermediate:
    {
        int current_dot_count = ip.native.count('.');
        if (m_correction == Correction::ZeroFilled) {
            fillWithZeroes(ip.native, normal_dot_count - current_dot_count);
            ip.binary.fill(0, octet_num*octet_length);
            validness = true;
        } else if (m_correction == Correction::NoCorrection) {
            bool chunk = 0;
            if (ip.native[ip.native.length()-1] != '.' &&
                    ip.native.length() > 0) {
                chunk = 1;
            }

            ip.binary.fill(0, octet_length*(current_dot_count+chunk));
        }
        break;
    }
    default:
        ip.binary.clear();
    }

    return validness;
}

void IPLineEdit::fillWithZeroes(QString& data, int rest) {
    // корректно вставляем нули при ZeroFilled
    if (data.count() > 1 && data[data.count()-1] == '.') {
        data.chop(1);
        rest++;
    } else if (data.count() == 0) {
        data.append('0');
    }

    for (int i = 0; i < rest; ++i) {
        data.append('.').append('0');
    }
}

QString IPLineEdit::addressNative() {
    isValid();

    qDebug() << ip.native << validness;
    return ip.native;
}

QBitArray IPLineEdit::addressBinary() {
    isValid();

    int lastId = text().size()-1;
    if (text()[lastId] == '.')
        text().remove(lastId, 1);

    setBinaryForm();

    qDebug() << ip.binary;
    return ip.binary;
}

void IPLineEdit::setBinaryForm() {
    QStringList octetList = ip.native.split('.');

    for (int i = 0; i < octetList.size(); ++i) {
        processOctet(QString::number(octetList[i].toInt(), 2), i);
    }
}

void IPLineEdit::processOctet(QString octet, int offset) {
    int length = octet.size();
    for (int i = 0; i < length; ++i) {
        ip.binary[octet_length*(offset+1)-length+i] = octet[i] == '1';
    }
}




