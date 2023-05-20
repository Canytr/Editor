#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSaveFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    activateStatusBar();
    setCurrentFile(QString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    //clear editor
    ui->plainTextEdit->clear();
    setCurrentFile(QString());
}
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        qDebug()<<"File opened";
        load(fileName);
    }
}
bool MainWindow::saveFile()
{
    return save(currentFile);
}
void MainWindow::createActions()
{
    //New File
    ui->actionNew->setStatusTip(tr("Create a new file"));
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);

    //Open File
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);

    //Save File
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);

}
void MainWindow::activateStatusBar()
{
    statusBar()->showMessage("Activated StatusBar");
}

void MainWindow::load(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    ui->plainTextEdit->setPlainText(in.readAll());
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::save(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << ui->plainTextEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    ui->plainTextEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

