#include "scene.h"
#include "mainwindow.h"
#include <QPainter>
#include <vector>
#include <algorithm>
Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    itemToDraw = 0;
    RectToDraw = 0;
    CirToDraw = 0;
}

void Scene::setMode(Mode mode){
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == DrawRect){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == DrawCir){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject){
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }
    else if(mode == SortShapes){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
        sortShapes();
    }
    else if(mode == SearchShapes){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
        searchShapes(Title);
    }
    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::makeItemsControllable(bool areControllable){
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine)
        origPoint = event->scenePos();
    else if (sceneMode == DrawRect)
        rectPoint = event->scenePos();
    else if (sceneMode == DrawCir)
        cirPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine){
        if(!itemToDraw){
            itemToDraw = new QGraphicsLineItem;
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(fillColor,x+1, Qt::SolidLine));
            itemToDraw->setPos(origPoint);
        }

        itemToDraw->setLine(0,0,
                            event->scenePos().x() - origPoint.x(),
                            event->scenePos().y() - origPoint.y());
        prod = (pow(event->scenePos().x() - origPoint.x(),2)+pow(event->scenePos().y() - origPoint.y(),2));
        length = sqrt(prod);
        temp = itemToDraw;
    }
    else if(sceneMode == DrawRect){
        if(!RectToDraw){
            RectToDraw = new QGraphicsRectItem;
            this->addItem(RectToDraw);
            RectToDraw->setPos(rectPoint);
            RectToDraw->setPen(QPen(strokeColor,x, Qt::SolidLine));
            RectToDraw->setBrush(fillColor);


        }

        RectToDraw->setRect(0,0,
                            event->scenePos().x() - rectPoint.x(),
                            event->scenePos().y() - rectPoint.y());

        length = event->scenePos().x() - rectPoint.x();
        width = event->scenePos().y() - rectPoint.y();
        temp = RectToDraw;
    }
    else if(sceneMode == DrawCir){
        if(!CirToDraw){
            CirToDraw = new QGraphicsEllipseItem;
            this->addItem(CirToDraw);
            CirToDraw->setPos(cirPoint);

            CirToDraw->setPen(QPen(strokeColor,x,Qt::SolidLine));
            CirToDraw->setBrush(fillColor);

        }
        CirToDraw->setRect(0,0,
                            event->scenePos().y() - cirPoint.y(),
                            event->scenePos().y() - cirPoint.y());

        raduis = abs((event->scenePos().y() - cirPoint.y())/2);
        temp = CirToDraw;
    }


    else
        QGraphicsScene::mouseMoveEvent(event);


}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    RectToDraw = 0;
    CirToDraw = 0;
   if (sceneMode == DrawLine){
    line[lcounter].setLength(length);
    line[lcounter].setTitle("Line"+to_string(lcounter));
    sorted.push_back(&line[lcounter]);
    unsorted.push_back(&line[lcounter]);
    lcounter++;
    undo.push(temp);
   }
   else if(sceneMode == DrawRect){
    rectangle[rcounter].setLength(length);
    rectangle[rcounter].setWidth(width);
    rectangle[rcounter].setTitle("Rectangle"+to_string(rcounter));
    sorted.push_back(&rectangle[rcounter]);
    unsorted.push_back(&rectangle[rcounter]);
    rcounter++;
    undo.push(temp);
   }
   else if (sceneMode == DrawCir){
       circle[ccounter].setRadius(raduis);
       circle[ccounter].setTitle("Circle"+to_string(ccounter));
       sorted.push_back(&circle[ccounter]);
       unsorted.push_back(&circle[ccounter]);
       ccounter++;
       undo.push(temp);


          }
    QGraphicsScene::mouseReleaseEvent(event);
}
void Scene::sortShapes(){
    if (!sorted.empty()){
    for(int i=0;i<sorted.size()-1;i++)
    {
    for(int j=0;j<sorted.size()-1;j++)
    {
    if(sorted[j+1]->perimeter()<sorted[j]->perimeter()){
    spare = sorted[j+1];
    sorted[j+1]= sorted[j];
    sorted[j]=spare;
    }
    }
    }
    for(int c=0; c<sorted.size();c++){

       std::cout<<sorted[c]->title<<endl;
        }
    std::cout << "new sort"<<endl;
    }
}
void Scene::searchShapes(string title){
    for(int i=0; i<sorted.size();i++){
        if(sorted[i]->title == title){
            std::cout<<"perimeter = "<<sorted[i]->perimeter()<<endl;
            std::cout<<"area = "<<sorted[i]->area()<<endl;
        }
    }
}
void Scene::deleteitem(string title){
    for(int i=0; i<sorted.size();i++){
        if(sorted[i]->title == title){
            deleted.push(sorted[i]);
            sorted.erase(sorted.begin()+i);
            unsorted.pop_back();
        }
    }
}
void Scene::keyPressEvent(QKeyEvent *event){

     if(event->key() == Qt::Key_U){
        if(!undo.isEmpty()){
           temp = undo.top();
           undo.pop_back();
           redo.push(temp);
           lastabbreviation = unsorted.back()->title[0];
           update(0);
           deleteitem(unsorted.back()->title);
           removeItem(temp);
           }
    }
    else if(event->key() == Qt::Key_Y){
        if(!redo.isEmpty()){
            temp = redo.top();
            undo.push(temp);
            addItem(temp);
            temp->setPos(temp->pos());
            redo.pop();
            update(1);
            sorted.push_back(deleted.top());
            unsorted.push_back(deleted.top());
            deleted.pop();
        }
    }
    else
        QGraphicsScene::keyPressEvent(event);
}
void Scene::update(int method){
    if(method == 0){
        if (lastabbreviation == 'C'){
            ccounter--;
        }
        else if(lastabbreviation == 'R'){
            rcounter--;
        }
        else{
            lcounter--;
        }
    }
    else if(method == 1){
        if (lastabbreviation == 'C'){
            ccounter++;
        }
        else if(lastabbreviation == 'R'){
            rcounter++;
        }
        else{
            lcounter++;
        }
    }

}

