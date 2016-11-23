#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    //File menu
    QObject::connect(ui->newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    QObject::connect(ui->saveAction, SIGNAL(triggered()) ,this, SLOT(saveFile()));
    QObject::connect(ui->saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));
    QObject::connect(ui->openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(ui->closeAction, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(setNoSaveState()));

    //Edit menu
    QObject::connect(ui->dateTimeAction, SIGNAL(triggered()), this, SLOT(addDateTime()));

    //Style menu
    QObject::connect(ui->fontAction, SIGNAL(triggered()), this, SLOT(setFont()));
    QObject::connect(ui->colorAction, SIGNAL(triggered()), this, SLOT(setColor()));

    //Help menu
    QObject::connect(ui->aboutNotepadAction, SIGNAL(triggered()), this, SLOT(openAboutNotepad()));
    QObject::connect(ui->aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(ui->myWebAction, SIGNAL(triggered()), this, SLOT(openMyWeb()));
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::newFile()
{
    if (!saveState) {

/*
QMessageBox msgBox;
msgBox.setText("The document has been modified.");
msgBox.setInformativeText("Do you want to save your changes?");
msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
msgBox.setDefaultButton(QMessageBox::Save);
int ret = msgBox.exec();
*/
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Do you Save it ?"));
        msgBox.setText(tr("Save File"));
        msgBox.setInformativeText(tr("Do you want to save ?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

/*
switch (ret) {
  case QMessageBox::Save:
      // Save was clicked
      break;
  case QMessageBox::Discard:
      // Don't Save was clicked
      break;
  case QMessageBox::Cancel:
      // Cancel was clicked
      break;
  default:
      // should never be reached
      break;
}
*/
    switch (ret) {
    case QMessageBox::Save:
        saveAsFile();
        ui->textEdit->clear();
        break;
    case QMessageBox::Discard:
        ui->textEdit->clear();
        break;
    case QMessageBox::Cancel:
        msgBox.close();
        break;
    }

    }
    else {
        ui->textEdit->clear();
    }
}

void Notepad::saveAsFile()
{
/*
qDebug() << "Date:" << QDate::currentDate();

fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

    QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        process_line(line);
    }
*/
    qDebug() << "save as file";
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Text"), "/", tr("Text File(*.txt)"));
    saveName = filename;
    QFile *file = new QFile(filename);
    if (file->open(QIODevice::WriteOnly)) {
        QTextStream fileStream(file);
        fileStream << ui->textEdit->toPlainText();

        file->close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(tr("Error"));
        msgBox.setInformativeText(tr("Fail to save file !"));
        return ;
    }
    setOkSaveState();
}

void Notepad::saveFile()
{
    if (saveName.isEmpty()) {
        this->saveAsFile();
    }
    else {
        QFile *file = new QFile(saveName);
        if (file->open(QIODevice::WriteOnly)) {
            QTextStream fileStream(file);
            fileStream << ui->textEdit->toPlainText();
            setOkSaveState();

            file->close();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Error"));
            msgBox.setInformativeText(tr("Fail to save file !"));
            return ;
        }
    }
}

void Notepad::openFile()
{
    newFile();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Text"), "/", tr("*.txt"));
    QFile *file = new QFile(filename);
    if (file->open(QIODevice::ReadOnly)) {
        QTextStream fileStream(file);
        ui->textEdit->setText(fileStream.readAll());

        file->close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(tr("Error"));
        msgBox.setInformativeText(tr("Fail to open file !"));
        return ;
    }
}

void Notepad::setNoSaveState()
{
    qDebug() << "no save";
    this->setWindowTitle(tr("Notepad*"));
    saveState = false;
}

void Notepad::setOkSaveState()
{
    qDebug() << "saved";
    this->setWindowTitle(tr("Notepad"));
    saveState = true;
}

void Notepad::closeEvent(QCloseEvent *event)
{
    if (!saveState) {
            bool exit = QMessageBox::question(this, tr("Quit"),
                                              tr("Are you sure to quit without save ?"),
                                              QMessageBox::Yes | QMessageBox::No,
                                              QMessageBox::No) == QMessageBox::Yes;
            if (exit) {
                event->accept();
            }
            else {
                event->ignore();
            }
        }
    else {
            event->accept();
    }
}

void Notepad::setFont()
{
/*bool ok;
QFont font = QFontDialog::getFont(
                &ok, QFont("Helvetica [Cronyx]", 10), this);
if (ok) {
    // the user clicked OK and font is set to the font the user selected
} else {
    // the user canceled the dialog; font is set to the initial
    // value, in this case Helvetica [Cronyx], 10
}
*/
    bool ok;
    QFont fontname = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 16), this, 0);
    if (ok) {
        ui->textEdit->setFont(fontname);
    }

/*
int ret = QMessageBox::warning(this, tr("My Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel,
                               QMessageBox::Save);
*/
    else {
        QMessageBox::warning(this, tr("Error"), tr("No font is set"), QMessageBox::Ok);
    }
}

void Notepad::setColor()
{
/*
QColor QColorDialog::​getColor(const QColor & initial = Qt::white, QWidget * parent = 0, const QString & title = QString(), ColorDialogOptions options = 0)
*/

    QColor colorname = QColorDialog::getColor(Qt::black, this, tr("Color box"), 0);
    ui->textEdit->setTextColor(colorname);
}

void Notepad::addDateTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString addData = time.toString("ddd MMMM d yy h:m");

    ui->textEdit->append(addData);
}

void Notepad::openMyWeb()
{
/*
QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));
*/
    QUrl myweb("http://weibo.com/u/3568293300/home?wvr=5&tongji=baiduxinshouye");
    QDesktopServices::openUrl(myweb);
}

void Notepad::openAboutNotepad()
{
    About *dialog = new About;
    dialog->show();
}
