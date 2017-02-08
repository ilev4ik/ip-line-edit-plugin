#include "iplineedit.h"
#include "iplineeditplugin.h"

#include <QtPlugin>

IPLineEditPlugin::IPLineEditPlugin(QObject *parent):
    QObject(parent),
    initialized(false)
{

}

QString IPLineEditPlugin::name() const {
    return "IPLineEdit";
}

QString IPLineEditPlugin::group() const {
    return tr("CSS Custom Widgets");
}


QString IPLineEditPlugin::toolTip() const {
    return tr("An IPLineEdit");
}

QString IPLineEditPlugin::whatsThis() const {
    return tr("An IPLineEdit");
}

QString IPLineEditPlugin::includeFile() const {
    return "iplineedit.h";
}

QIcon IPLineEditPlugin::icon() const {
    return QIcon();
}

bool IPLineEditPlugin::isContainer() const {
    return false;
}

QWidget* IPLineEditPlugin::createWidget(QWidget *parent) {
    return new IPLineEdit(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(iplineedit, IPLineEdit)
#endif
