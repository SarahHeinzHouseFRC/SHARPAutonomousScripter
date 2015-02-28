#ifndef BUILDSCENE_H
#define BUILDSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
class BuildScene : public QGraphicsScene
{
public:
    BuildScene(QObject * parent);
    int clickX;
    int clickY;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif // BUILDSCENE_H
