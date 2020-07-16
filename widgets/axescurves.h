#ifndef AXESCURVES_H
#define AXESCURVES_H

#include <QWidget>
#include "global.h"
#include "deviceconfig.h"

namespace Ui {
class AxesCurves;
}

class AxesCurves : public QWidget
{
    Q_OBJECT

public:
    explicit AxesCurves(int axes_number, QWidget *parent = nullptr);
    ~AxesCurves();

    void ReadFromConfig();
    void WriteToConfig();

    void RetranslateUi();

private slots:
    void on_pushButton_Linear_clicked();

    void on_pushButton_LinearInvert_clicked();

    void on_pushButton_Exponent_clicked();

    void on_pushButton_ExponentInvert_clicked();

    void on_pushButton_Shape_clicked();

private:
    Ui::AxesCurves *ui;
    int axes_number_;

    std::vector <deviceEnum_guiName_t> axes_list_ =     // дублируется в axestobuttons.h , axes.h
    {{
        {0,      tr("X")},
        {1,      tr("Y")},
        {2,      tr("Z")},
        {3,      tr("Rx")},
        {4,      tr("Ry")},
        {5,      tr("Rz")},
        {6,      tr("Slider 1")},
        {7,      tr("Slider 2")},
    }};

};

#endif // AXESCURVES_H
