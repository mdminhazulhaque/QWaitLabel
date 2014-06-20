#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->textLabel->setText("Please wait");

    //ui->waitLabel->setIndicatorType(QWaitLabel::RECT);
    ui->waitLabel->setIndicatorType(QWaitLabel::CIRCLE);

    //ui->waitLabel->setSpeed(QWaitLabel::HIGH);
    ui->waitLabel->setSpeed(QWaitLabel::MID);
    //ui->waitLabel->setSpeed(QWaitLabel::LOW);

    ui->waitLabel->setFillColor(Qt::gray);
    ui->waitLabel->setOutlineColor(Qt::black);

    setWindowTitle("QWaitLabel Test");

    connect(ui->buttonBox, SIGNAL(rejected()), qApp, SLOT(quit()));

    setGeometry(QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    qApp->desktop()->availableGeometry()));
}

Window::~Window()
{
    delete ui;
}
