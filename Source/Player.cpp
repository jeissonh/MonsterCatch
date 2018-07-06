#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSoundEffect>
#include <QtMath>

#include "Player.h"

const int monsterDelay = 150; // milliseconds

Player::Player()
{
	// Set graphic image
	setElementId( QString("monster%1").arg( qrand() % 3 ) );
//	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);

	// Pre-load the collision sound
	collisionSound = new QSoundEffect(qApp);
	collisionSound->setSource(QUrl("qrc:/Stop.wav"));
	collisionSound->setVolume(0.98f);

	// Randomly move this item periodically
	connect(timer, &QTimer::timeout, this, &Player::move);
	//timer->setInterval(1000);
	timer->setSingleShot(true);
	timer->start(750);

	// Continuously check for collisions
	QTimer* collisionTimer = new QTimer(this);
	connect(collisionTimer, &QTimer::timeout, this, &Player::detectCollisions);
	collisionTimer->setInterval(25);
	collisionTimer->start();
}

Player::~Player()
{
}

void Player::setInitialPos()
{
	// Place the player in the middle bottom of the scene
	qreal x = (scene()->width() - boundingRect().width()) * 0.5;
	qreal y = (scene()->height() - boundingRect().height()) * 0.5;
	setPos(x, y);
}

void Player::keyPressEvent(QKeyEvent* event)
{
	static_cast<void>(event);
/*	// Move this object if arrow keys are pressed
	if ( event->key() == Qt::Key_Left && x() )
		moveLeft();
	else if ( event->key() == Qt::Key_Right )
		moveRight();
	else if ( event->key() == Qt::Key_Up )
		setPos( x(), y() - 10.0 );
	else if ( event->key() == Qt::Key_Down )
		setPos( x(), y() + 10.0 );
	// Do something if the spacebar is pressed
	else if ( event->key() == Qt::Key_Space )
		doSomething();
*/
}

#include <iostream>
void Player::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	std::cerr << "player(" << event->pos().x() << ", " << event->pos().y() << ")\n";
}

void Player::move()
{
//	setPos( pos().x() + qrand() % 10 - 5, pos().y() + qrand() % 10 - 5 );
//	detectCollisions();

	// Start a move animation from current starting point
	this->moveAnimation = new QPropertyAnimation(this, "pos");
	this->moveAnimation->setStartValue(QPointF(pos().x(), pos().y()));

	// To a random point within the scene/screen
	float targetX = qrand() % int(scene()->width() - this->boundingRect().width());
	float targetY = qrand() % int(scene()->height() - this->boundingRect().height());
	QPointF endPos(targetX, targetY);
	this->moveAnimation->setEndValue(endPos);

	// The duration is proportional to the max distance possible
	double distance = std::hypot(targetX - pos().x(), targetY - pos().y());
	double screenDiagonal = std::hypot(scene()->width(), scene()->height());
	int duration = distance / screenDiagonal * 1500.0;
	this->moveAnimation->setDuration(duration);

	// Start the animation
	this->moveAnimation->start();

	// Schedule the next movement
	this->timer->start(duration + monsterDelay);
}

#include "Obstacle.h"
void Player::detectCollisions()
{
	// Traverse all graphic items that are colliding with this
	const QList<QGraphicsItem*>& items = collidingItems();
	for ( QGraphicsItem* item : items )
	{
		// If a graphic item is an obstacle remove it from scene
		if ( /*Obstacle* obstacle =*/ dynamic_cast<Obstacle*>(item) )
		{
			// Play the collision sound
			this->collisionSound->play();

			// Stop current move animation and move in another direction
			this->moveAnimation->stop();
			this->move();
		}
	}
}
