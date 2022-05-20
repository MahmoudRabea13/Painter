#include "mainwindow.h"

MainWindow::MainWindow()
{
    scene = new Scene(this);
    scene->setSceneRect(0,0,200,200);
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
    setCentralWidget(view);
    createActions();
    createConnections();
    createToolBar();
    createToolBar2();
    Time->setInterval(500);
    Time->start();

}

void MainWindow::createActions(){
    sortButton = new QPushButton("sort",this);
    searchButton = new QPushButton("search",this);
    searchButton->setShortcut(Qt::Key_Enter);

    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setIcon(QIcon(":/icons/icons/line.png"));
    lineAction->setShortcut(Qt::Key_L);
    lineAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setIcon(QIcon(":/icons/icons/Arrow.png"));
    selectAction->setCheckable(true);
    selectAction->setShortcut(Qt::Key_V);

    rectAction = new QAction("Draw Rectangle", this);
    rectAction->setData(int(Scene::DrawRect));
    rectAction->setIcon(QIcon(":/icons/icons/Rectangle.png"));
    rectAction->setShortcut(Qt::Key_R);
    rectAction->setCheckable(true);


     cirAction = new QAction("Draw Circle", this);
     cirAction->setData(int(Scene::DrawCir));
     cirAction->setIcon(QIcon(":/icons/icons/ellipse.png"));
     cirAction->setShortcut(Qt::Key_C);
     cirAction->setCheckable(true);

    spinBorder = new QSpinBox(this);
    searchTitle = new QLineEdit(this);
    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(selectAction);
    actionGroup->addAction(rectAction);
    actionGroup->addAction(cirAction);
    colorPanal = new QColorDialog(this);\

    RadioButton = new QRadioButton(this);
    RadioButton2 = new QRadioButton(this);
    Time = new QTimer(this);
}

void MainWindow::createConnections(){
    connect(actionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionGroupClicked(QAction*)));
connect(sortButton,SIGNAL(clicked()),this,SLOT(sortbuttonClicked()));
connect(searchButton,SIGNAL(clicked()),this,SLOT(searchbuttonClicked()));
connect(spinBorder,SIGNAL(editingFinished()),this,SLOT(borderEdit()));
connect(Time,SIGNAL(timeout()),this,SLOT(fillstroke()));
}

void MainWindow::sortbuttonClicked(){
   scene->setMode(Scene::SortShapes);
}
void MainWindow::searchbuttonClicked(){
    scene->Title = searchTitle->text().toStdString();
    scene->setMode(Scene::SearchShapes);
}
void MainWindow::actionGroupClicked(QAction *action){
    scene->x = spinBorder->value()-1;
    scene->setMode(Scene::Mode(action->data().toInt()));

    if (RadioButton2->isChecked()){
        scene->strokeColor = colorPanal->currentColor();

        }
    if (RadioButton->isChecked()){
        scene->fillColor = colorPanal->currentColor();

        }
}
void MainWindow::createToolBar(){
    drawingToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, drawingToolBar);
    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);
    drawingToolBar->addAction(rectAction);
    drawingToolBar->addAction(cirAction);
    drawingToolBar->addWidget(spinBorder);
    drawingToolBar->addWidget(sortButton);
    drawingToolBar->addWidget(searchTitle);
    drawingToolBar->addWidget(searchButton);
}

void MainWindow::createToolBar2(){
    drawingToolBar2 = new QToolBar;
    addToolBar(Qt::RightToolBarArea, drawingToolBar2);
    drawingToolBar2->addWidget(RadioButton);

    RadioButton->setText("Fill Color");
    RadioButton->setShortcut(Qt::Key_F);

    drawingToolBar2->addWidget(RadioButton2);
    RadioButton2->setText("Stroke Color");
    RadioButton2->setShortcut(Qt::Key_S);

    drawingToolBar2->addAction( QString("Color"));
    drawingToolBar2->addWidget(colorPanal);

    colorPanal->setOption(QColorDialog::NoButtons);



}
void MainWindow::borderEdit(){
    scene->x = spinBorder->value()-1;
}
void MainWindow::fillstroke(){
    if (RadioButton2->isChecked()){
        scene->strokeColor = colorPanal->currentColor();

        }
    if (RadioButton->isChecked()){
        scene->fillColor = colorPanal->currentColor();

        }

}
