#ifndef IOT_QT_GRAPHIC_H
#define IOT_QT_GRAPHIC_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class QT_Graphic; }
QT_END_NAMESPACE

class QT_Graphic : public QWidget {
    Q_OBJECT

public:
    explicit QT_Graphic(QWidget *parent = nullptr);

    ~QT_Graphic() override;

private:
    Ui::QT_Graphic *ui;
};


#endif //IOT_QT_GRAPHIC_H
