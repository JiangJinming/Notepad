#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("About"));

/*
QLabel label;
QMovie *movie = new QMovie("animations/fire.gif");

label.setMovie(movie);
movie->start();
*/

    QMovie *movie = new QMovie("C:/Users/jiang_000.JIANG_PC/Documents/Qt/mynotepad/face.gif");
    ui->movieLabel->setMovie(movie);
    movie->start();
}

About::~About()
{
    delete ui;
}
