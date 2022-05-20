#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include <QSpinBox>
#include "scene.h"
#include <QActionGroup>
#include <QAction>
#include <QButtonGroup>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QColorDialog>
#include <QTimer>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
public slots:
    void actionGroupClicked(QAction*);
    void sortbuttonClicked();
    void searchbuttonClicked();
    void borderEdit();
    void fillstroke();
private:
    QGraphicsView* view;
    Scene* scene;
    void createActions();
    void createConnections();
    void createToolBar();
    void createToolBar2();
    void createSpinbox(int x);
    QAction* lineAction;
    QAction* selectAction;
    QAction* rectAction;
    QAction* cirAction;
    QWidget* spinBox;
    QActionGroup* actionGroup;
    QToolBar* drawingToolBar;
    QToolBar* drawingToolBar2;
    QColorDialog* colorPanal;
    QSpinBox* spinBorder;
    QButtonGroup* Button;
    QPushButton* sortButton;
    QPushButton* searchButton;
    QLineEdit* searchTitle;
    QRadioButton* RadioButton;
    QRadioButton* RadioButton2;
    QTimer* Time;
};

#endif // MAINWINDOW_H
