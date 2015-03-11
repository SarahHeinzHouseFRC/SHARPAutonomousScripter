#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H

#include <QListWidgetItem>

class SettingsOption : public QListWidgetItem
{
    Q_OBJECT
public:
    explicit SettingsOption(QObject *parent = 0, QString name = "Default");

signals:

public slots:

};

#endif // SETTINGSOPTION_H
