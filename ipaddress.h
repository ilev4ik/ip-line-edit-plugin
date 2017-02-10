#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>
#include <QBitArray>

struct IPAddress {
    QString native;
    QBitArray binary;
};

#endif // IPADDRESS_H
