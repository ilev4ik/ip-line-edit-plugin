#ifndef IPLINEEDITPLUGIN_H
#define IPLINEEDITPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class IPLineEditPlugin : public QObject, public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    Q_PLUGIN_METADATA(IID "com.css.Qt.CustomWidgets")
#endif
public:
    IPLineEditPlugin(QObject* parent = nullptr);

    QString name() const;
    QString group() const;
    QString toolTip() const;
    QString whatsThis() const;
    QString includeFile() const;
    QIcon icon() const;

    bool isContainer() const;

    QWidget* createWidget(QWidget *parent);
private:
    bool initialized;
};

#endif // IPLINEEDITPLUGIN_H
