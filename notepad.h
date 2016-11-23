#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextstream>
#include <QMessageBox>
#include <QDebug>
#include <QIODevice>
#include <QCloseEvent>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QUrl>
#include <QDesktopServices>
#include <QSplashScreen>
#include <QPixmap>

#include "about.h"

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    void setOkSaveState();
    ~Notepad();

private slots:
    void newFile();
    void saveAsFile();
    void openFile();
    void saveFile();
    void setNoSaveState();

    void addDateTime();

    void setFont();
    void setColor();

    void openMyWeb();
    void openAboutNotepad();

private:
    bool saveState = true;
    QString saveName;
    Ui::Notepad *ui;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // NOTEPAD_H
