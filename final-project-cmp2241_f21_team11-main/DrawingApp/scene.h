#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QStack>
#include <QUndoStack>
#include <QUndoCommand>
#include "shape.h"
#include "circle.h"
#include "line.h"
#include "rectangle.h"
class Scene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine, DrawRect,DrawCir,SortShapes,SearchShapes,Undo,Redo};
    int x;
    string Title;
    Scene(QObject* parent = 0);
    void setMode(Mode mode);
    vector<shape *> sorted;
    vector<shape *> unsorted;
    shape* spare;
    QStack <shape *> deleted;
    QStack <QGraphicsItem* > undo;
    QStack <QGraphicsItem* > redo;
    QColor fillColor;
    QColor strokeColor;
    char lastabbreviation;
    protected:
    void sortShapes();
    void update(int method);
    void searchShapes(string title);
    void deleteitem(string title);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Mode sceneMode;
    QPointF origPoint;
    QPointF rectPoint;
    QPointF cirPoint;
    QGraphicsLineItem* itemToDraw;
    QGraphicsRectItem* RectToDraw;
    QGraphicsEllipseItem* CirToDraw;
    QRectF* Circle;
    void makeItemsControllable(bool areControllable);
    line line[100];
    circle circle[100];
    rectangle rectangle[100];
    double prod;
    double length;
    double width;
    double raduis;
    int lcounter=0;
    int rcounter=0;
    int ccounter=0;
    QGraphicsItem* temp;
//    void sort();
//    void title();
};

#endif // SCENE_H
