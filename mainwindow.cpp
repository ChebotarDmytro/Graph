#include <QToolBar>
#include <QAction>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <qwt_plot_renderer.h>
#include "mainwindow.h"
#include "graf.h"
#include "panel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{

    Settings settings;
    settings.s_plot.Xfrom = 0;
    settings.s_plot.Xto = 500;
    settings.s_plot.Yfrom = 0;
    settings.s_plot.Yto = 500;
    settings.s_plot.x_name = "X";
    settings.s_plot.y_name = "Y";


    d_panel = new Panel();
    d_panel->setSettings(settings);

    QWidget *w = new QWidget( this );

    graf = new Graf();

    QHBoxLayout *hLayout = new QHBoxLayout( w );
    hLayout->addWidget( d_panel );
    hLayout->addWidget( graf, 10 );

    setCentralWidget( w );

    updatePlot();

    connect( d_panel, SIGNAL( edited() ), SLOT( updatePlot() ) );

    createAction();
    createToolBar();

}

MainWindow::~MainWindow()
{
   delete graf;
}



void MainWindow::createToolBar()
{
    fileToolBar = addToolBar( tr( " &File" ) ) ;
    fileToolBar->addAction(exportAction) ;
    fileToolBar->addAction(openFile);
}

void MainWindow::createAction()
{
    exportAction = new QAction( "&Export", this );
    exportAction->setIcon(QIcon(":/images/pdf.png"));
    connect(exportAction, SIGNAL(triggered(bool) ), this, SLOT(exportPlot() ) );

    openFile = new QAction("&Open File", this );
    openFile->setIcon(QIcon(":/images/file2.png"));
    connect(openFile, SIGNAL(triggered() ), this, SLOT(open()) );
}

void MainWindow::updatePlot()
{
    graf->applySettings( d_panel->settings() );
}

void MainWindow::exportPlot()
{
    QwtPlotRenderer renderer;
    renderer.exportTo(graf, "Graph.pdf");
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                       tr("Open Graph"));
    if (!fileName.isEmpty())
                loadFile(fileName);


}

bool MainWindow::loadFile(const QString &fileName){
    if (!graf->setGrafData(fileName)) {
         QMessageBox::warning(this, tr("Graph"),
                                tr("Loading canceled"),
                                QMessageBox::Ok);
         return false;
       }

       return true;

}
