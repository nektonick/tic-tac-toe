#include "mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
    show();
}

void MainWindow::renderField()
{
    // stub content
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            std::string buttonText;
            if(i == j) {
                buttonText = " ";
            } else if((i + j) % 2) {
                buttonText = "X";
            } else {
                buttonText = "O";
            }
            auto button = new QPushButton(buttonText.c_str());
            connect(button, SIGNAL(released()), this, SLOT(onClicked()));
            layout->addWidget(button, i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    // 'layout' will be deleted by ui
}

void MainWindow::onClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Clicked");
    msgBox.exec();
}
