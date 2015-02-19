#ifndef AUTONOMOUSGUIOBJECT_H
#define AUTONOMOUSGUIOBJECT_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class AutonomousGuiObject : public QGraphicsItem
{
public:
	AutonomousGuiObject();

	~AutonomousGuiObject()
	{
	}

	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	void setXY(int x, int y);
	void setMoveable();
	bool isSelected();

	int getX();
	int getY();
	void setNotSelected();
	// QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	//QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	bool toBeDeleted();
	void setToBeDeleted();
	void setPixmap(std::string pathToPixmap);
private:


protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	int xCoord;
	int yCoord;
	QPixmap pixmap;
	int imageHeight;
	int imageWidth;
	bool selected;
	bool hovered;
	bool shouldRemove;
};

#endif // AUTONOMOUSCOMMAND_H

