#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    bool saveFile();
   // bool saveAs();

private:
    Ui::MainWindow *ui;
    void createActions();
    void activateStatusBar();
    void load(const QString &fileName);
    bool save(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QString currentFile;
};
#endif // MAINWINDOW_H
