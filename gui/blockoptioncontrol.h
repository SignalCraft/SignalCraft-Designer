#ifndef BLOCKOPTIONCONTROL_H
#define BLOCKOPTIONCONTROL_H

#include <QGroupBox>
#include <QString>
#include <QWidget>

class BlockOptionControl : public QGroupBox {
    Q_OBJECT
public:
    explicit BlockOptionControl(const QString & title, QWidget *parent = 0);
    virtual void setCurrentValue(QString value);
    virtual QString textValue() const;
};

#endif // BLOCKOPTIONCONTROL_H
