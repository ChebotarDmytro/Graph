#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class Graf;
class Panel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void updatePlot();
    void exportPlot();
    void open();

private:

       QToolBar *fileToolBar ;
       QAction *exportAction;
       QAction *openFile;

       Graf *graf;
       Panel *d_panel;

       void createToolBar();
       void createAction();
       bool loadFile(const QString &fileName);

};

#endif // MAINWINDOW_H
