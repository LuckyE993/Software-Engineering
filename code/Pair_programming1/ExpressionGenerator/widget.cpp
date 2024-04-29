#include "widget.h"
#include "ui_widget.h"
#include <QPrintDialog>
#include <QPrinter>
#include <QIcon>
int operatorPriority[128];
int randomNumCount = 0; // 0 or 1. If 0, random number from 2 to numMaxCount. If 1, use numMaxCount.
int numMaxCount = 3;    // Range: 2 to 300000000, maximum number of digits generated.
int numMaxLength = 2;   // Range: 1 to 9, maximum length of an integer part of a number.
int numDecimalPlaces = 2; // Number of decimal places in each number.
int numExpressions = 5;   // Number of expressions to generate.
bool useParentheses = true; // Whether to use parentheses in expressions.

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("结对作业——四则运算表达式生成器");
    QIcon WindowIcon ("D:\\Document\\QT\\ExpressionGenerator\\icon.jpg");
    this->setWindowIcon(WindowIcon);
    connect(ui->PluscheckBox, &QCheckBox::stateChanged, this, &Widget::on_PluscheckBox_stateChanged);
    connect(ui->DecreasecheckBox, &QCheckBox::clicked, this, &Widget::on_DecreasecheckBox_clicked);
    connect(ui->MulcheckBox, &QCheckBox::clicked, this, &Widget::on_MulcheckBox_clicked);
    connect(ui->DivcheckBox, &QCheckBox::clicked, this, &Widget::on_DivcheckBox_clicked);

    ui->ExpressionCountlineEdit->setPlaceholderText("生成表达式的数量");
    ui->numMaxCountlineEdit->setPlaceholderText("表达式有几项");
    ui->numMaxLengthlineEdit->setPlaceholderText("项的范围 10^n");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::initialize() {
    // 初始化所有运算符优先级为-1
    for (int i = 0; i < 128; ++i) {
        operatorPriority[i] = -1;
    }
    // 默认启用所有运算符
    operatorPriority['+'] = 1;
    operatorPriority['-'] = 1;
    operatorPriority['*'] = 2;
    operatorPriority['/'] = 2;
    useParentheses = ui->ParenthesecheckBox->isChecked();  // 是否使用括号
    numExpressions = ui->ExpressionCountlineEdit->text().toInt();  // 表达式数量
}
void Widget::on_ExpressionCountlineEdit_editingFinished()
{
    // 将输入转换为整数，并更新表达式数量
    numExpressions = ui->ExpressionCountlineEdit->text().toInt();
}


void Widget::on_numMaxCountlineEdit_editingFinished()
{
    // 将输入转换为整数，并更新最大数字数量
    numMaxCount = ui->numMaxCountlineEdit->text().toInt();
}

void Widget::on_numMaxLengthlineEdit_editingFinished()
{
    // 将输入转换为整数，并更新最大数字范围
    numMaxLength = ui->numMaxLengthlineEdit->text().toInt();
}


void Widget::on_PluscheckBox_stateChanged(bool checked)
{
    // 根据复选框状态设置加法运算符的优先级
    operatorPriority['+'] = checked ? 1 : -1;
}


void Widget::on_DecreasecheckBox_clicked(bool checked)
{
    // 根据复选框状态设置加法运算符的优先级
    operatorPriority['-'] = checked ? 1 : -1;
}


void Widget::on_MulcheckBox_clicked(bool checked)
{
    // 根据复选框状态设置加法运算符的优先级
    operatorPriority['*'] = checked ? 1 : -1;
}


void Widget::on_DivcheckBox_clicked(bool checked)
{
    // 根据复选框状态设置加法运算符的优先级
    operatorPriority['/'] = checked ? 1 : -1;
}


void Widget::on_ParenthesecheckBox_clicked(bool checked)
{
    // 更新是否使用括号的设置
    useParentheses = checked;
}


void Widget::on_DecimalcheckBox_clicked(bool checked)
{
    // 更新是否生成小数的设置
    numDecimalPlaces = checked ? 2 : 0;  // 这里假设启用小数时使用2位小数
}


void Widget::on_GeneratePushButton_clicked()
{
    QString finalExpression;
    for (int i = 0; i < numExpressions; ++i) {
        queue<QString> rpnQueue = generateRPN();
        QString expression = evaluateRPN(rpnQueue);
        finalExpression += expression + " =\n";
    }
    ui->OutputlineEdit->setText(finalExpression.trimmed());
}


void Widget::on_SaveaspushButton_clicked()
{
    // 弹出对话框让用户选择输出方式
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择输出方式");
    msgBox.setText("请选择输出方式：");
    QAbstractButton* pButtonSaveToFile = msgBox.addButton("保存到文件", QMessageBox::YesRole);
    QAbstractButton* pButtonPrint = msgBox.addButton("打印内容", QMessageBox::NoRole);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == pButtonSaveToFile) {
        // 用户选择了保存到文件
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存表达式"), "", tr("Text Files (*.txt);;All Files (*)"));
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << ui->OutputlineEdit->toPlainText();
                file.close();
            } else {
                QMessageBox::warning(this, "错误", "无法打开文件进行写入。");
            }
        }
    } else if (msgBox.clickedButton() == pButtonPrint) {
        // 用户选择了打印内容
        QPrinter printer;
        QPrintDialog printDialog(&printer, this);
        if (printDialog.exec() == QDialog::Accepted) {
            QTextDocument doc;
            doc.setPlainText(ui->OutputlineEdit->toPlainText());
            doc.print(&printer);
        }
    }
}

queue<QString> Widget::generateRPN() {
    queue<QString> outputQueue;
    int numOperators = 0, numElements = ui->numMaxCountlineEdit->text().toInt();

    for (int i = 0; i < numElements; ++i) {
        QString number;
        for (int digit = 0; digit < numMaxLength; ++digit) {
            int num = QRandomGenerator::global()->bounded(1, 10);
            number += QString::number(num);
        }

        // 添加小数部分
        if (ui->DecimalcheckBox->isChecked()) {
            number += '.';
            for (int j = 0; j < numDecimalPlaces; ++j) {
                int num = QRandomGenerator::global()->bounded(0, 10);
                number += QString::number(num);
            }
        }

        outputQueue.push(number);

        if (numOperators < (2 * i / 3) && QRandomGenerator::global()->bounded(0, 3) == 0) {
            QString operators = "+-*/";
            char op = operators.at(QRandomGenerator::global()->bounded(0, operators.size())).toLatin1();
            if (operatorPriority[op] != -1) {
                outputQueue.push(QString(op));
                numOperators++;
            }
        }
    }

    while (numOperators < numElements - 1) {
        QString operators = "+-*/";
        char op = operators.at(QRandomGenerator::global()->bounded(0, operators.size())).toLatin1();
        if (operatorPriority[op] != -1) {
            outputQueue.push(QString(op));
            numOperators++;
        }
    }

    return outputQueue;
}

QString Widget::evaluateRPN(queue<QString>& rpnQueue) {
    stack<pair<QString, int>> evalStack;

    while (!rpnQueue.empty()) {
        QString token = rpnQueue.front();
        rpnQueue.pop();

        if (token[0].isDigit() || token[0] == '.') {
            evalStack.push({token, INT_MAX});
        } else if (operatorPriority[token[0].toLatin1()] != -1) {
            int priority = operatorPriority[token[0].toLatin1()];
            auto right = evalStack.top(); evalStack.pop();
            auto left = evalStack.top(); evalStack.pop();

            QString expr;
            if (useParentheses && left.second < priority) {
                expr += "(" + left.first + ")";
            } else {
                expr += left.first;
            }
            expr += token;
            if (useParentheses && (right.second < priority || (token == "/" && right.second <= priority) || (token == "-" && right.second <= priority))) {
                expr += "(" + right.first + ")";
            } else {
                expr += right.first;
            }
            evalStack.push({expr, priority});
        }
    }

    return evalStack.empty() ? "" : evalStack.top().first;
}


