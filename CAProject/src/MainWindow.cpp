#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QApplication>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),  m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_gl=new  NGLScene(this);
    // row span col span
    m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,12,1);
    // set the rotation signals

}

MainWindow::~MainWindow()
{
    delete m_ui;
}


