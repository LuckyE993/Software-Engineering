#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <cstdlib>
#include <queue>
#include <stack>
#include <QString>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ExpressionCountlineEdit_editingFinished();

    void on_numMaxCountlineEdit_editingFinished();

    void on_PluscheckBox_stateChanged(bool checked);

    void on_DecreasecheckBox_clicked(bool checked);

    void on_MulcheckBox_clicked(bool checked);

    void on_DivcheckBox_clicked(bool checked);

    void on_ParenthesecheckBox_clicked(bool checked);

    void on_DecimalcheckBox_clicked(bool checked);

    void on_GeneratePushButton_clicked();

    void on_SaveaspushButton_clicked();

    void on_numMaxLengthlineEdit_editingFinished();

private:
    Ui::Widget *ui;
    void initialize();
    queue<QString> generateRPN();
    QString evaluateRPN(queue<QString>& rpnQueue);

};
#endif // WIDGET_H
