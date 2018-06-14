#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QDebug>



button::button(QString name, QGraphicsItem *parent)
{
    setRect(0,0,250,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    //draw the text
    text = new QGraphicsTextItem(name,this); // button is the parent of this text
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    setAcceptHoverEvents(true);
    qDebug() << "fuck y";
}

void button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "fuck press";
    emit clicked();

}

void button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "fuck hover1";
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
    qDebug() << "fuck hover2";
}

void button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "fuck leave1";
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
    qDebug() << "fuck leave2";
}


